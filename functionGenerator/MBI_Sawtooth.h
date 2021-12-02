#ifndef HEADER_MBI_SAWTOOTH
#define HEADER_MBI_SAWTOOTH

#include "MBI_Triangle.h"



class MBI_Sawtooth : public MBI_Triangle
{
  public:
    virtual void init(double Dt);
    virtual void setParams(double amp, double freq, double rampDur1, double rampDur2);
    virtual void getParams();
    virtual double evaluate(double t);

  private:
    double rampDur1;
    double rampDur2;

};

#endif
