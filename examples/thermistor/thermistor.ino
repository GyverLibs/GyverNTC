// подключение: GND --- термистор --- A0 --- 10к --- 5V
#include <GyverNTC.h>
GyverNTC therm(0, 10000, 3435);
// серый 4300, проводной 3950

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Temperature ");
  Serial.print(therm.getTempAverage());
  Serial.println(" *C");
  delay(500);
}
