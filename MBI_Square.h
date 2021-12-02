#ifndef HEADER_MBI_SQUARE
#define HEADER_MBI_SQUARE

#include "MBI_Waveform.h"



class MBI_Square : public MBI_Waveform
{
  public:
    virtual void init(double dt);
    virtual void getParams();
    virtual void setParams(double amp, double freq, double phase, double dutyCycle);
    virtual double evaluate(double t);
    virtual void setDutyCycle(double dc);  // i.e.  50% ->  50
    virtual void setFreq(double freq);
    virtual void stop();

  private:
    int count;
    int samplesPerWave;
    int pt1;
    double val;
};

#endif
