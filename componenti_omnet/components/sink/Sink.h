#ifndef __SINK_H_
#define __SINK_H_

#include <omnetpp.h>
#include "Job_m.h"

using namespace omnetpp;

class Sink : public cSimpleModule
{
  private:
    //Per stimare tempo di permanenza degli utenti nel sistema
    cOutVector vecTimeClass1;
    cOutVector vecTimeClass2;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    //virtual void finish() override;
};

#endif
