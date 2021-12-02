#include "MBI_Sawtooth.h"



void MBI_Sawtooth:: init(double dt)
{
  this->dt = dt;
  waveName = "Sawtooth";
}


void MBI_Sawtooth::setParams(double amp, double freq, double rampDur1, double rampDur2)
{
  this->amp = amp + MBI_Waveform::amplifierOffset;
  this->freq = freq;
  this->rampDur1 = rampDur1;
  this->rampDur2 = rampDur2;
  this->phase = 0;
  this->dutyCycle = 0;
  this->count = 0;
  
  samplesPerWave = (int)(round((1/freq) / dt));
  pt1 = (int)(round(rampDur1 / dt));
  pt2 = pt1 + (int)(round(rampDur2 / dt));
  increment = this->amp / ((double)pt1);
  val = 0.0;
}


void MBI_Sawtooth::getParams()
{
  Serial.print(waveName);
  Serial.print(" : amp = ");
  Serial.print(amp, 2);
  Serial.print(", freq = ");
  Serial.print(freq, 2);
  Serial.print(", samplesPerWave = ");
  Serial.print(samplesPerWave);
  Serial.print(", pt1 = ");
  Serial.print(pt1);
  Serial.print(", rampDur1 = ");
  Serial.print(rampDur1, 2);
  Serial.print(", rampDur2 = ");
  Serial.println(rampDur2, 2);
}


double MBI_Sawtooth::evaluate(double t)
{
  if (count == pt1)
  {
    increment = -1.0 * (this->amp / (rampDur2 / dt));
  }
  else if (count == pt2)
  {
    val = 0;
    increment = 0;
  }
  
  if (count == samplesPerWave)
  {
    val = 0;
    increment = this->amp / ((double)pt1);
    count = -1;
  }

  val = val + increment;
  ++count;

  return val;
}
