#include "MBI_Waveform.h"
#include "Arduino.h"


void MBI_Waveform::init(double dt)
{
  this->dt = dt;    
  waveName = "AbstractWaveform";
}


void MBI_Waveform::stop()
{  
//  Serial.println("Stop");
}


void MBI_Waveform::setParams(double amp, double freq, double phase, double dutyCycle)
{
  this->amp = amp + amplifierOffset;
  this->freq = freq;
  this->phase = phase;
  this->dutyCycle = dutyCycle;
}


void MBI_Waveform::setAmp(double amp)
{
  this->amp = amp;  
}


void MBI_Waveform::setFreq(double freq)
{
  this->freq = freq;  
}


void MBI_Waveform::setDutyCycle(double dutyCycle)
{
  this->dutyCycle = dutyCycle;
}


void MBI_Waveform::getParams()
{
  Serial.print(waveName);
  Serial.print(" : amp = ");
  Serial.print(amp, 2);
  Serial.print(", freq = ");
  Serial.print(freq, 2);
  Serial.print(", phase = ");
  Serial.print(phase, 2);
  Serial.print(", dutyCycle = ");
  Serial.println(dutyCycle, 2);
}
