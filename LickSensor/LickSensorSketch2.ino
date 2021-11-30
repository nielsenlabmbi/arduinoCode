
#include <CapacitiveSensor.h>

/*
   CapitiveSense Library Demo Sketch
   Paul Badger 2008
   Uses a high value resistor e.g. 10M between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
*/


CapacitiveSensor   cs_6_9 = CapacitiveSensor(6, 9);       // 10M resistor between pins 5 & 6, pin 6 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_5_10 = CapacitiveSensor(5,10);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_3_11 = CapacitiveSensor(3,11);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

int calibrateTimer = 0;

int threshold[3] {450, 450, 450}; 



void setup()
{
  //cs_3_11.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  
}

void loop()
{

  int val1 = (1 - digitalRead(2)) * 300; //threshold[1];
int val2 = (1 - digitalRead(4)) * 300; //threshold[2];
int val3 = (1 - digitalRead(7)) * 300; //threshold[3];

  unsigned long start = millis();
  long total1 =  cs_6_9.capacitiveSensor(30);
  long total2 =  cs_5_10.capacitiveSensor(30);
  long total3 =  cs_3_11.capacitiveSensor(30);

digitalWrite(2,HIGH);
digitalWrite(4,HIGH);
digitalWrite(7,HIGH);


//check for threshold-crossing
if (total1 > threshold[0] || total2 > threshold[1] || total3 > threshold[2]) {
    delayMicroseconds(20000);
    if (total1 > threshold[0]){ //&& (total1 > total3)){
    digitalWrite(2, LOW);
  }

  if (total2 > threshold[1]){ //&& (total2 > total1) && (total2 > total3)){
    digitalWrite(4, LOW);
  }

  if (total3 > threshold[2]){ //&& (total3 > total1)){
    digitalWrite(7, LOW);
  }
}



  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");
  Serial.print(threshold[0]);
    Serial.print("\t");
  Serial.print(threshold[1]);
    Serial.print("\t");
  Serial.print(threshold[2]);
  Serial.print("\t");                    // tab character for debug windown spacing
  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total2);                  // print sensor output 2
  Serial.print("\t");
  Serial.print(total3);                // print sensor output 3
  Serial.print("\t");
  Serial.print(val1);
Serial.print("\t");
Serial.print(val2);
Serial.print("\t");
Serial.println(val3);


    
  delay(1);                             // arbitrary delay to limit data to serial port

  calibrateTimer = calibrateTimer + 1;
  if (calibrateTimer > 20)
  {
    cs_6_9.reset_CS_AutoCal();
    cs_5_10.reset_CS_AutoCal();
    cs_3_11.reset_CS_AutoCal();
    calibrateTimer = 0;
  }
    
}
