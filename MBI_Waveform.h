#ifndef HEADER_MBI_WAVEFORM
#define HEADER_MBI_WAVEFORM
#include <Arduino.h>

class MBI_Waveform
{
  public:
    virtual void init(double dt);    
    virtual void setParams(double amp, double freq, double phase, double dutyCycle = 0);
    virtual void getParams();
    virtual void setDutyCycle(double dc);
    virtual void setAmp(double amp);
    virtual void setFreq(double freq);
    virtual void stop();
    virtual double evaluate(double t) = 0;

  public:
    
  protected:
    char* waveName;
    double amp;
    double freq;
    double phase;
    double dutyCycle;
    double dt;

    const static unsigned int amplifierOffset = 8;

};

#endif
