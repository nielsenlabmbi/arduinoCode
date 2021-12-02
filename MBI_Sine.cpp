#include "MBI_Sine.h"
#include "Arduino.h"



void  MBI_Sine::init(double dt)
{
  this->dt = dt;
  waveName = "Sine";
}


void MBI_Sine::setParams(double ampInVolts, double freq, double phase, double dutyCycle)
{
  this->freq = freq;
  this->phase = phase;
  this->dutyCycle = dutyCycle;
  setAmp(ampInVolts);
}


void MBI_Sine::setAmp(double amp)
{
  this->amp = amp;
  this->offset = amp / 1.0 + MBI_Waveform::amplifierOffset;
}



double MBI_Sine::evaluate(double t)
{
  return (amp * sin(TWO_PI * freq * t + phase)) + offset;
}
