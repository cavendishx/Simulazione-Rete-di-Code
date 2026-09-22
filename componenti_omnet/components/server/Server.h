#ifndef __SERVER_H_
#define __SERVER_H_

#include <omnetpp.h>
#include "Job_m.h"
#include <vector>

using namespace omnetpp;

class Server : public cSimpleModule
{
  private:
    cMessage *endService;           // messaggio schedulato per fine servizio
    std::vector<Job*> batchJobs;    // job accumulati per il batch corrente

    //Per stimare fattore di utilizzo
    simtime_t lastBusyStart;
    cOutVector utilizationVector;

    //Per stimare durata media delle vacation
    simtime_t vacationStart;
    cOutVector vecVacationDurations;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    void batchService();
};

#endif
