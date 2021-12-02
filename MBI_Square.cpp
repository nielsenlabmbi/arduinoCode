#include "MBI_Square.h"
#include "Arduino.h"



void MBI_Square::init(double dt)
{
  phase = 0;
  dutyCycle = 50;
  count = 0;
  this->dt = dt;
  pt1 = 0;
  val = 0.0;
  waveName = "Square";
}


double MBI_Square::evaluate(double t)
{
  if (count <= pt1)
  {
    val = amp;
  }
  else
  {
    val = 0;
  }

  // time to restart?
  if (count == samplesPerWave)
  {
    val = 0;
    count = -1;
  }
  ++count;

  return val;
}


void MBI_Square::stop()
{  
  count = 0;
  val = 0;

  MBI_Waveform::stop();
}


void MBI_Square::getParams()
{
  Serial.print(waveName);
  Serial.print(" : amp = ");
  Serial.print(amp, 2);
  Serial.print(", freq = ");
  Serial.print(freq, 2);
  Serial.print(", pt1 = ");
  Serial.print(pt1);
  Serial.print(", dutyCycle = ");
  Serial.println(dutyCycle);
}


void MBI_Square::setDutyCycle(double dc)
{
  this->dutyCycle = dc;
}


void MBI_Square::setFreq(double freq)
{
  this->freq = freq;
  this->samplesPerWave = (int)(freq / dt);
}


void MBI_Square::setParams(double amp, double freq, double phase, double dutyCycle)
{
  if(dutyCycle < 1)
  {
    Serial.print("\nMBI_Square::setParams() : dutyCycle < 1\n");
  }
  this->amp = amp + MBI_Waveform::amplifierOffset;
  this->freq = freq;
  this->phase = phase;
  this->dutyCycle = dutyCycle;

  this->samplesPerWave = (int)(round((1/freq) / dt));
  this->count = 0;

  pt1 = (int)(round(samplesPerWave * (this->dutyCycle / 100.0)));
}
