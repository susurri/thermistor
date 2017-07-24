#define THERMISTOR_IN 14 //A0
#define DEBUG 1

#include <Thermistor.h>

// 61.9Kohm serial linearization resistor 
Thermistor thermistor = Thermistor_NXFT15WF104FA2B(61.9, THERMISTOR_IN);

void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(1000);
  double temperature;
  temperature = thermistor.readTempC();
  Serial.print(temperature);
  Serial.println("*C");
}
