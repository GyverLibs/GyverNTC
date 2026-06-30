This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverNTC.svg?color=brightgreen)](https://github.com/GyverLibs/GyverNTC/releases/latest/download/GyverNTC.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverNTC.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverNTC)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverNTC?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverNTC
Library for working with NTC thermistors under the Steinhart-Hart Act
- Set thermistor parameters
- Obtaining temperature
- Built-in average
- Support for different ADC permissions

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Initialization](#init)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="init"></a>
## Initialization
![scheme](https://github.com/GyverLibs/GyverNTC/blob/main/docs/conn2.png)  
Connection: GND -- Rt -- ADC -- R -- VCC
- Rt - Thermistor
- R - ballast resistor

```cpp
GyverNTC therm;     // builder

GyverNTC therm(uint8_t pin, uint32_t R, uint16_t B, uint8_t t = 25, uint32_t Rt = 10000, uint8_t res = 10);
// pin - analog pin to which the thermistor is connected
// R = ballast resistor resistance, Om
// B is the thermistor beta coefficient (see datashite) [number in the region of 1000-5000] ]
// t is the base temperature of the thermistor, degrees Celsius (see datashite) [usually 25 degrees]
// Rt = resistance of the thermistor at base temperature, Om (see datashite)
// res is the ADC resolution, bit. Default 10.
```

<a id="usage"></a>
## Use of use
### Class class

```cpp
// adjust the thermistor: R resistor, B thermistor, t thermistor, R thermistor
void config(uint32_t R, uint16_t B, uint8_t t = 25, uint32_t Rt = 10000);

// set up pin and ADC resolution
void setPin(uint8_t pin, uint8_t res = 10);

// pinpoint
float getTemp();

// read the average temperature from the pin, you can specify the averaging
// It is not recommended to use more than 20 averaging, it is pointless. Use an external filter
float getTempAverage(uint8_t samples = 20);

// get the temperature from the ADC signal, you can specify the ADC resolution
float computeTemp(float analog, uint8_t res = 10);
```

### Direct calculation.

```cpp
// ADC signal, (R resistor/R thermistor), B thermistor, t thermistor, ADC resolution
float NTC_computeRR(float analog, float baseDiv, uint16_t B, uint8_t t = 25, uint8_t res = 10);

// ADC signal, R resistor, B thermistor, t thermistor, R thermistor, ADC resolution
float NTC_compute(float analog, uint32_t R, uint16_t B, uint8_t t = 25, uint32_t Rt = 10000, uint8_t res = 10);
```

<a id="example"></a>
## Example
For more examples see **examples**!
```cpp
#include <GyverNTC.h>
GyverNTC therm(0, 10000, 3435);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Temperature ");
  Serial.print(therm.getTempAverage());
  Serial.println(" *C");
  delay(500);
}
```

### Several thermistors
It is not necessary to make a copy of the class on each thermistor, it is enough to specify the pin before measuring:

```cpp
#include <GyverNTC.h>
GyverNTC therm;

void setup() {
  Serial.begin(9600);
  therm.config(10000, 3435);
}

void loop() {
  therm.setPin(0);
  Serial.print("Temp (pin 0): ");
  Serial.print(therm.getTempAverage());
  Serial.println(" *C");
  delay(500);
  
  therm.setPin(2);
  Serial.print("Temp (pin 2): ");
  Serial.print(therm.getTempAverage());
  Serial.println(" *C");
  delay(500);
}
```

<a id="versions"></a>
## Versions
- v1.0
- V1.1 - small optimization, increased accuracy
- v1.2 - Optimization, support for 100k thermistors
- v1.3 - Support for different ADC resolution
- v1.4 - Critical error corrected!
- v1.5 - a separate function is added to calculate
- v1.5.4 - normal operation during overheating (zero ADC signal) - function returns float inf

<a id="install"></a>
## Installation
- The library can be found under the name **GyverNTC** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverNTC/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
