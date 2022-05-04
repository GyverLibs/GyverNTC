# GyverNTC
Library for working with NTC thermistors according to the Steinhart-Hart law
- Setting the parameters of the thermistor
- Get temperature
- Built-in averaging

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverNTC** and installed via the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/GyverNTC/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
![scheme](https://github.com/GyverLibs/GyverNTC/blob/main/docs/conn2.png)
```cpp
// connection: GND --- thermistor --- A0 --- 10k --- 5V
GyverNTC therm(0, 10000, 3435); // pin, R thermistor at 25 degrees, B thermistor. (R default resistor 10000)
GyverNTC therm(0, 10000, 3435, 25, 10000); // pin, R thermistor, B thermistor, base temperature, R resistor
```

<a id="usage"></a>
## Usage
```cpp
float getTemp(); // read temperature from pin
float getTempAverage(); // read the average temperature from the pin
float computeTemp(float analog); // get the temperature from 10 bits of the ADC signal (can be averaged)
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
#include <GyverNTC.h>
GyverNTC therm(0, 10000, 3435);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Temperature");
  Serial.print(therm.getTempAverage());
  Serial.println("*C");
  delay(500);
}
```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - small optimization, accuracy improvement
- v1.2 - optimization, support for 100k thermistors

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!