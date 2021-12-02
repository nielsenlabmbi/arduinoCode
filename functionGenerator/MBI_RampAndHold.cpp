#include "MBI_RampAndHold.h"



void MBI_RampAndHold:: init(double dt) 
{
  phase = 0;
  dutyCycle = 100;
  count = 0;
  this->dt = dt;
  increment = 0;
  pt1 = 0;
  pt2 = 0;
  val = 0.0;
  rampDur1 = .9;
  holdDur = .4;
  rampDur2 = .9;
  waveName = "RampAndHold";
}


void MBI_RampAndHold::setParams(double amp, double rampDur1, double holdDur, double rampDur2)
{
  this->amp = amp + MBI_Waveform::amplifierOffset;
  this->rampDur1 = rampDur1;
  this->holdDur = holdDur;
  this->rampDur2 = rampDur2;
  
  this->samplesPerWave = (int)(round(  (this->rampDur1 + this->holdDur + this->rampDur2) / dt));
  this->count = 0;

  pt1 = (int)(round(this->rampDur1 / dt));
  pt2 = (int)(round(this->holdDur / dt));
  increment = amp / (double)pt1;
  pt2 += pt1;
  
  val = 0.0;
}


void MBI_RampAndHold::getParams()
{
  Serial.print(waveName);
  Serial.print(" : amp = ");
  Serial.print(amp, 2);
  Serial.print(", rampDur1 = ");
  Serial.print(rampDur1, 2);
  Serial.print(", holdDur = ");
  Serial.print(holdDur, 2);
  Serial.print(", rampDur2 = ");
  Serial.println(rampDur2, 2);
}


double MBI_RampAndHold::evaluate(double t)
{
  if (count == pt1)
  {
    val = amp;
    increment = 0;
  }
  else if (count == pt2)
  {
    increment = amp / round(this->rampDur2 / dt);
    increment = -1.0 * increment;
  }
  else if(count == samplesPerWave)
  {
    increment = amp / (double)pt1;
    val = -increment;
    count = -1;
  }
  
  val = val + increment;
  ++count;

  return val;
}
