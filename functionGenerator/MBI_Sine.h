#ifndef HEADER_MBI_SINE
#define HEADER_MBI_SINE

#include "MBI_Waveform.h"



class MBI_Sine : public MBI_Waveform
{
  public:
    virtual void init(double dt);
    virtual void setParams(double amp, double freq, double phase, double dutyCycle);
    virtual void setAmp(double amp);
    virtual double evaluate(double t);

  private:
    double offset;  // prevent negative values since they're not recognized by D to A
};

#endif
