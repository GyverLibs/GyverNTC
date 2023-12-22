This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyverntc
Library for working with NTC Termistors according to the law of Steinhart-Hart
- Installation of the parameters of thermistor
- Obtaining temperature
- Built -in averaging
- support for different resolutions of ADC

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** gyverntc ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyverntc/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
! [Scheme] (https://github.com/gyverlibs/gyverntc/blob/main/docs/conn2.png)
Connection: GND - RT - ADC - R - VCC
- RT - thermistor
- R - ballast resistor

`` `CPP
Gyverntc therm;// empty designer

Gyverntc therm (uint8_t pin, uint32_t r, uint16_t b, uint8_t t = 25, uint32_t rt = 10000, uint8_t res = 10);
// PIN - analog PIN to which the termistor is connected
// r - resistance of a ballast resistor, ohm
// B-beta-coefficient of thermistor (see Datashit) [number in the region of 1000-5000]
// t - the basic temperature of the termistor, Celsius degrees (see Datashit) [usually 25 degrees]
// RT - resistance of thermistor at the base temperature, ohm (see Datashit)
// res - resolution of ADC, bit.By default 10
`` `

<a id="usage"> </a>
## Usage
### Class

`` `CPP
// Configure the termistor: R resistor, b termistor, t termistor, r termistor
Void Config (Uint32_t R, Uint16_t B, Uint8_t T = 25, Uint32_T RT = 10000);

// configure PIN and resolution of ADC
VOID setpin (uint8_t pin, uint8_t res = 10);

// Read the temperature with PIN
Float gettemp ();

// Read the average temperature from the pin, you can indicate the value of
Float Gettempaverage (Uint8_t Samples = 20);

// get the temperature from the ADC signal, you can specify the resolution of the ADC
Float Computetemp (Float ANALOG, UINT8_T Res = 10);
`` `

## direct calculation

`` `CPP
// signal ACP, (R resistor / r termistoRA), b termistor, t termistor, resolution of ADC
Float ntc_compute (Float analog, Float basediv, uint16_t b, uint8_t t = 25, uint8_t res = 10);

// signal ADC, R resistor, B termistor, t thermistor, R termistor, ACP resolution
Float ntc_compute (Float analog, uint32_t r, uint16_t b, uint8_t t = 25, uint32_t RT = 10000, uint8_t res = 10);
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
#include <gyverntc.h>
Gyverntc Therm (0, 10000, 3435);

VOID setup () {
  Serial.Begin (9600);
}

VOID loop () {
  Serial.print ("Temperature");
  Serial.print
  Serial.println (" *c");
  Delay (500);
}
`` `

### several termistors
It is not necessary to make its own instance of the class for each termistor, just specify the pin before the measurement:

`` `CPP
#include <gyverntc.h>
Gyverntc therm;

VOID setup () {
  Serial.Begin (9600);
  Therm.config (1000, 3435);
}

VOID loop () {
  Therm.setpin (0);
  Serial.print ("TEMP (PIN 0):");
  Serial.print
  Serial.println (" *c");
  Delay (500);
  
  Therm.Setpin (2);
  Serial.print ("TEMP (PIN 2):");
  Serial.print
  Serial.println (" *c");
  Delay (500);
}
`` `

<a id="versions"> </a>
## versions
- V1.0
- V1.1 - slight optimization, increasing accuracy
- V1.2 - optimization, support of 100k termistors
- v1.3 - support for different resolutions of ADC
- V1.4 - A critical error is fixed!
- V1.5 - A separate function for calculation is added

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code