#include "Queue.h"
Define_Module(Queue);

void Queue::initialize()
{
    a1 = par("a1");
    b1 = par("b1");
    a2 = par("a2");
    b2 = par("b2");

    sp1 = par("sp1");
    l1 = par("l1");
    u1 = par("u1");
    sp2 = par("sp2");
    l2 = par("l2");
    u2 = par("u2");

    sv = par("sv");
    z = par("z");
    w = par("w");
    h = par("h");
    N = par("N");

    waitingForUsers = false;
    batchInProgress = false;
    waitingForBatchComplete = false;

    vecSystemClass1.setName("NumUsersSystemClass1");
    vecSystemClass2.setName("NumUsersSystemClass2");
    vecSystemClass1.record(0);
    vecSystemClass2.record(0);
}

void Queue::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "ServerRequestBatch") == 0) {
        delete msg;
        if(!batchInProgress)
            serveBatch();
        else
            waitingForBatchComplete = true;
    }
    else if (strcmp(msg->getName(), "JobDeparture") == 0) {
        // questo ramo serve solo per stimare il numero di utenti nel sistema
        int batchSize = msg->par("batchSize");
        int userClass = msg->par("userClass");
        if (userClass == 1)
            numSystemClass1 -= batchSize;
        else
            numSystemClass2 -= batchSize;
        vecSystemClass1.record(numSystemClass1);
        vecSystemClass2.record(numSystemClass2);
        delete msg;
    }
    else if (strcmp(msg->getName(), "ServerVacationEnded") == 0) {
        delete msg;
        // controlla se soglia N raggiunta
        if ((int)queueClass1.size() >= N) {
            startSetUp();
        }
        else{
            EV << "Attesa raggiungimento soglia N: " << (int)queueClass1.size() << "\n";
            waitingForUsers = true; //altrimenti attende nuovi utenti
        }
    }
    else if(strcmp(msg->getName(), "SourceBatchComplete")==0){
        delete msg;
        batchInProgress = false;
        vecSystemClass1.record(numSystemClass1);
        vecSystemClass2.record(numSystemClass2);
        // se stiamo aspettando nuovi utenti, controlla soglia N
        if (waitingForUsers && (int)queueClass1.size() >= N) {
           waitingForUsers = false;
           startSetUp();
        }
        else if(waitingForBatchComplete){
            waitingForBatchComplete = false;
            serveBatch();
        }
    }
    else {
        // messaggio dalla Source
        Job *job = check_and_cast<Job*>(msg);
        batchInProgress = true;

        if (job->getUserClass() == 1){
            queueClass1.push_back(job);
            numSystemClass1++;
        }
        else{
            queueClass2.push_back(job);
            numSystemClass2++;
        }
    }
}

void Queue::serveBatch()
{
    int n1 = queueClass1.size();
    int n2 = queueClass2.size();
    std::vector<Job*> batch;
    int r = 0;
    double serviceTime = 0;

    if (n1 >= a1) {
        r = std::min(n1, b1);
        EV << "Batch da servire classe 1 " << r << "\n";
        for (int i = 0; i < r; ++i) {
            batch.push_back(queueClass1.front());
            queueClass1.pop_front();
        }

        // serviceTime classe 1
        double s = (r / double(b1)) * sp1;
        double q = uniform(l1, u1);
        serviceTime = s + q;
    }
    else if (n2 >= a2) {
        r = std::min(n2, b2);
        EV << "Batch da servire classe 2 " << r << "\n";
        for (int i = 0; i < r; ++i) {
            batch.push_back(queueClass2.front());
            queueClass2.pop_front();
        }

        // serviceTime classe 2
        double s = (r / double(b2)) * sp2;
        double q = uniform(l2, u2);
        serviceTime = s + q;
    }
    else {
        startVacation();
        return;
    }

    // Invio del batch al server
    for (auto job : batch) {
        job->addPar("serviceTime") = serviceTime; // tutti i job del batch usano lo stesso serviceTime
        send(job, "out");
    }
    cMessage *batchDone = new cMessage("BatchComplete");
    send(batchDone, "out");
}

void Queue::startVacation()
{
    int k_class1 = queueClass1.size();
    double t1 = ((k_class1 + 1) / double(b1)) * sv;
    double t2 = uniform(z, w);
    double vacationTime = t1 + t2;
    cMessage *vacationMsg = new cMessage("StartVacation");
    vacationMsg->addPar("vacationTime") = vacationTime;
    send(vacationMsg, "out");
}

void Queue::startSetUp()
{
    double setupTime = exponential(h);
    cMessage *setupMsg = new cMessage("StartSetup");
    setupMsg->addPar("setupTime") = setupTime; // tempo che il server deve rispettare
    send(setupMsg, "out");
}

void Queue::finish()
{
    // De-alloca i job rimasti in coda alla fine della simulazione
    for (auto job : queueClass1)
        delete job;
    queueClass1.clear();

    for (auto job : queueClass2)
        delete job;
    queueClass2.clear();

}
