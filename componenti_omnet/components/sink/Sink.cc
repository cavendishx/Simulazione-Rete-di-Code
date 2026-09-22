#include "Sink.h"

Define_Module(Sink);

void Sink::initialize(){
    vecTimeClass1.setName("TimeInSystemClass1");
    vecTimeClass2.setName("TimeInSystemClass2");
}

void Sink::handleMessage(cMessage *msg)
{
    Job *job = check_and_cast<Job*>(msg);

    // Calcola tempo di permanenza nel sistema
    simtime_t timeInSystem = simTime() - job->getArrivalTime();
    if (job->getUserClass() == 1)
        vecTimeClass1.record(timeInSystem);
    else
        vecTimeClass2.record(timeInSystem);

    // Job ricevuto, lo cancella (simula la fine del servizio)
    delete job;
}


