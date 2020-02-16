
#include <Wire.h>

#include "SparkFun_SCD30_Arduino_Library.h" 

SCD30 airSensor;

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  Serial.println("SCD30 Example");

  airSensor.begin(); //This will cause readings to occur every two seconds
}

void loop()
{
  if (airSensor.dataAvailable())
  {
    Serial.print("c");
    Serial.println(airSensor.getCO2());
    delay(100);
    Serial.print("t");
    Serial.println(airSensor.getTemperature(), 1);
    delay(100);
    Serial.print("h");
    Serial.println(airSensor.getHumidity(), 1);
    delay(100);
  }


}
