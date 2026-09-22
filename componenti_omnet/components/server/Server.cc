#include "Server.h"

Define_Module(Server);

void Server::initialize()
{
    endService = new cMessage("endService");
    batchJobs.clear();

    utilizationVector.setName("utilization");
    vecVacationDurations.setName("VacationDurations");

    // all'avvio chiede un batch alla coda
    EV << "Richiesta batch\n";
    send(new cMessage("ServerRequestBatch"), "outQueue");
}

void Server::handleMessage(cMessage *msg)
{
    if (msg == endService) {

        //Per stima fattore di utilizzo
        simtime_t busyDuration = simTime() - lastBusyStart;
        utilizationVector.record(busyDuration); // busy intervals per calcolare il fattore di utilizzo

        //Notifica alla coda che un job sta uscendo dal sistema (per statistiche)
        int batchSize = batchJobs.size();
        int uClass = batchJobs.front()->getUserClass(); // tutti stessa classe
        cMessage *batchDeparture = new cMessage("JobDeparture");
        batchDeparture->addPar("batchSize") = batchSize;
        batchDeparture->addPar("userClass") = uClass;
        send(batchDeparture, "outQueue");

        // Invia tutti i job del batch al sink (avranno tutti lo stesso "tempo di fine servizio").
        for (auto job : batchJobs) {
            send(job, "outSink");
        }
        batchJobs.clear();

        // Chiedi un nuovo batch alla coda
        EV << "Richiesta batch\n";
        send(new cMessage("ServerRequestBatch"), "outQueue");
    }
    else if (strcmp(msg->getName(), "StartVacation") == 0){
        EV << "Inizio vacation\n";
        vacationStart = simTime();
        simtime_t vacationTime = msg->par("vacationTime").doubleValue();
        delete msg;
        cMessage *vacationEnd = new cMessage("VacationEnd");
        scheduleAt(simTime() + vacationTime, vacationEnd);
    }
    else if (strcmp(msg->getName(), "VacationEnd") == 0) {
        //Calcolo durata vacation
        simtime_t vacationDuration = simTime() - vacationStart;
        vecVacationDurations.record(vacationDuration);

        //Notifica alla coda che la vacation e' terminata
        send(new cMessage("ServerVacationEnded"), "outQueue");
        delete msg;
    }
    else if (strcmp(msg->getName(), "StartSetup") == 0) {
       EV << "Inizio setup\n";
       simtime_t setupTime = msg->par("setupTime").doubleValue();
       delete msg;
       cMessage *setupEnd = new cMessage("SetupEnd");
       scheduleAt(simTime() + setupTime, setupEnd);
    }
    else if (strcmp(msg->getName(), "SetupEnd") == 0) {
       // Chiede un nuovo batch alla coda dopo il setUp
       EV << "Richiesta batch\n";
       send(new cMessage("ServerRequestBatch"), "outQueue");
       delete msg;
    }
    else if (strcmp(msg->getName(), "BatchComplete") == 0) {
        // Tutti i job del batch sono arrivati
        delete msg;

        EV << "Inizio servizio batch\n";
        batchService();
    }
    else{
        Job *job = check_and_cast<Job*>(msg);
        batchJobs.push_back(job);
    }
}

void Server::batchService()
{
    lastBusyStart = simTime();

    // Recupero il serviceTime da uno dei job
    simtime_t serviceTime = batchJobs.front()->par("serviceTime").doubleValue();

    // Schedula fine servizio per tutto il batch
    scheduleAt(simTime() + serviceTime, endService);
}

void Server::finish()
{
    cancelAndDelete(endService);

    // De-alloca i job rimasti nel server alla fine della simulazione
    for (auto job : batchJobs)
        delete job;
    batchJobs.clear();
}

