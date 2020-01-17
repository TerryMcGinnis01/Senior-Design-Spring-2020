
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
    Serial.print("co2(ppm):");
    Serial.println(airSensor.getCO2());
    

    Serial.print(" temp(C):");
    Serial.println(airSensor.getTemperature(), 1);


   Serial.print(" humidity(%):");
   Serial.println(airSensor.getHumidity(), 1);
   
   
  
  }
  else
    Serial.println("No data");

  delay(1000);
}
