#ifndef __SOURCE_H_
#define __SOURCE_H_

#include <omnetpp.h>
#include "Job_m.h"

using namespace omnetpp;

class Source : public cSimpleModule
{
  private:
    cMessage *generateEvent;

    int userClass;
    double meanInterArrival;
    int batchMin;
    int batchMax;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

#endif
