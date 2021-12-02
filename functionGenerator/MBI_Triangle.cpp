#include "MBI_Triangle.h"
#include "Arduino.h"



void MBI_Triangle:: init(double dt) 
{
  phase = 0;
  dutyCycle = 100;
  count = 0;
  this->dt = dt;
  increment = 0;
  pt1 = 0;
  val = 0.0;
  waveName = "Triangle";
}


void MBI_Triangle::stop()
{  
  count = 0;
  val = 0;
  increment = amp / (double)pt1;

  MBI_Waveform::stop();
}


void MBI_Triangle::getParams()
{
  Serial.print(waveName);
  Serial.print(" : amp = ");
  Serial.print(amp, 2);
  Serial.print(", freq = ");
  Serial.print(freq, 2);
  Serial.print(", dt = ");
  Serial.print(dt, 6);
  Serial.print(", pt1 = ");
  Serial.println(pt1);
}


void MBI_Triangle::setParams(double amp, double freq, double phase, double dutyCycle)
{
  this->amp = amp + MBI_Waveform::amplifierOffset;
  this->freq = freq;
  this->phase = phase;
  this->dutyCycle = dutyCycle;
  
  this->samplesPerWave = (int)(round((1/freq) / dt));
  this->count = 0;
  pt1 = (int)(round((double)samplesPerWave / 2.0));
  increment = amp / (double)pt1;
  val = 0.0;
}


double MBI_Triangle::evaluate(double t)
{
  if (count == pt1)
  {
    val = amp;
    increment = -1.0 * increment;
  }
  else if (count == samplesPerWave)
  {
    val = 0;
    increment = -1.0 * increment;
    count = 0;
  }

  val = val + increment;
  ++count;

  return val;
}
