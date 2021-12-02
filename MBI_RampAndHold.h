#ifndef HEADER_MBI_RAMPANDHOLD
#define HEADER_MBI_RAMPANDHOLD

#include "MBI_Triangle.h"



class MBI_RampAndHold : public MBI_Triangle
{
  public:
    virtual void init(double Dt);
    virtual void setParams(double amp, double rampDur1, double holdDur, double rampDur2);
    virtual void getParams();
    virtual double evaluate(double t);

  private:
    double rampDur1;
    double holdDur;
    double rampDur2;
};

#endif
