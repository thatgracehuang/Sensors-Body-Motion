

#include <Wire.h>
#include "MAX30105.h"
#include <Servo.h>
#include "heartRate.h"
MAX30105 particleSensor;

int pos = 90;
Servo myservo;
int sample; 
float inittemp = 26;
void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  //Attach Servo
    myservo.attach(9);

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

   particleSensor.setup(0);
  // inittemp = particleSensor.readTemperature();
   //Serial.print(inittemp);

}


void loop()
{
    float temperature = particleSensor.readTemperature();
    Serial.print("temperatureC=");
  Serial.print(temperature, 4);
  float  tempdiff = temperature-inittemp;
   Serial.print("tempdiff=");
  Serial.print(tempdiff, 4);
  Serial.println(" ");
  sample = particleSensor.readTemperature();

  
  if (tempdiff<1){
    for (pos = random(173, 179); pos<=180; pos+=1){
    myservo.write(pos);
    delay(15);
    }
    for (pos = 180; pos>=170; pos-=1){
    myservo.write(pos);
    delay(15);
    }
    }

     else if (tempdiff >= 1){
    for (pos = 174-(tempdiff*tempdiff); pos<=180; pos+=1){
    myservo.write(pos);
    delay(15);
    }
    for (pos = 180; pos>=174-(tempdiff*tempdiff); pos-=1){
    myservo.write(pos);
    delay(15);
    }
    }
    
}


