#include "Source.h"

Define_Module(Source);

//Inizializza i parametri
void Source::initialize()
{
    userClass = par("userClass");
    meanInterArrival = par("meanInterArrival");
    batchMin = par("batchMin");
    batchMax = par("batchMax");

    generateEvent = new cMessage("generateBatch");

    scheduleAt(simTime(), generateEvent); //Avvia subito la creazione dei batch
}

//Riceve messaggi da se' stessa
void Source::handleMessage(cMessage *msg)
{
    if (msg == generateEvent)
    {
        // Estraggo dimensione batch (distribuzione uniforme discreta)
        int batchSize = intuniform(batchMin, batchMax);

        //  Creo tutti i job del batch
        EV << "Source batch: "<< batchSize << "\n";
        for (int i = 0; i < batchSize; i++)
        {
            Job *job = new Job("job");

            // Salvo la classe utente (uguale per tutti i job del batch)
            job->setUserClass(userClass);

            // Salvo timestamp di arrivo (uguale per tutti i job del batch)
            job->setArrivalTime(simTime());

            send(job, "out");
        }

        //Notifica alla queue che il batch è completo
        cMessage *batchDone = new cMessage("SourceBatchComplete");
        send(batchDone, "out");

        // Pianifica prossimo batch
        simtime_t nextArrival = exponential(meanInterArrival);
        scheduleAt(simTime() + nextArrival, generateEvent);
    }
}

// Viene chiamata quando simTime raggiunge il tempo di fine simulazione
void Source::finish()
{
    cancelAndDelete(generateEvent); //De-alloca i messaggi dalla memoria
}
