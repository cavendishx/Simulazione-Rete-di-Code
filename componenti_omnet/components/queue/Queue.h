#ifndef __QUEUE_H_
#define __QUEUE_H_

#include <omnetpp.h>
#include "Job_m.h"
#include <list>

using namespace omnetpp;

class Queue : public cSimpleModule
{
  private:
    std::list<Job*> queueClass1;
    std::list<Job*> queueClass2;

    // Parametri service rule
    int a1, b1, a2, b2;               // service rule
    double sp1, l1, u1;               // servizio classe1
    double sp2, l2, u2;               // servizio classe2
    double sv, z, w, h;               // vacation e setup
    int N;                            // soglia classe1 per setup

    bool waitingForUsers; // indica se siamo in attesa della soglia N
    bool batchInProgress; // indica se stiamo ancora ricevendo un batch di job
    bool waitingForBatchComplete; // indica se stiamo aspettando di eseguire la richiesta del server perché siamo nel mezzo di una ricezione di un batch dalla source

    // per stimare numero utenti nel sistema per classe
    int numSystemClass1 = 0;
    int numSystemClass2 = 0;
    cOutVector vecSystemClass1;
    cOutVector vecSystemClass2;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

    void serveBatch();
    void startVacation();
    void startSetUp();
};

#endif
