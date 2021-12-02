#ifndef HEADER_MBI_TRIANGLE
#define HEADER_MBI_TRIANGLE

#include "MBI_Waveform.h"



class MBI_Triangle : public MBI_Waveform
{
  public:
    virtual void init(double Dt);
    virtual void setParams(double amp, double freq, double phase, double dutyCycle);
    virtual double evaluate(double t);
    virtual void getParams();
    virtual void stop();

  protected:
    int count;
    int samplesPerWave;
    int pt1, pt2;
    double increment;
    double val;
};

#endif
