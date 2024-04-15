[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverNTC.svg?color=brightgreen)](https://github.com/GyverLibs/GyverNTC/releases/latest/download/GyverNTC.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverNTC.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverNTC)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverNTC?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverNTC
Библиотека для работы с NTC термисторами по закону Стейнхарта-Харта
- Установка параметров термистора
- Получение температуры
- Встроенное усреднение
- Поддержка разного разрешения АЦП

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverNTC** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverNTC/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="init"></a>
## Инициализация
![scheme](https://github.com/GyverLibs/GyverNTC/blob/main/docs/conn2.png)  
Подключение: GND -- Rt -- ADC -- R -- VCC
- Rt - термистор
- R - балластный резистор

```cpp
GyverNTC therm;     // пустой конструктор

GyverNTC therm(uint8_t pin, uint32_t R, uint16_t B, uint8_t t = 25, uint32_t Rt = 10000, uint8_t res = 10);
// pin - аналоговый пин, к которому подключен термистор
// R - сопротивление балластного резистора, Ом
// B - бета-коэффициент термистора (см. даташит) [число в районе 1000-5000]
// t - базовая температура термистора, градусов Цельсия (см. даташит) [обычно 25 градусов]
// Rt - сопротивление термистора при базовой температуре, Ом (см. даташит)
// res - разрешение АЦП, бит. По умолчанию 10
```

<a id="usage"></a>
## Использование
### Класс

```cpp
// настроить термистор: R резистора, B термистора, t термистора, R термистора
void config(uint32_t R, uint16_t B, uint8_t t = 25, uint32_t Rt = 10000);

// настроить пин и разрешение АЦП
void setPin(uint8_t pin, uint8_t res = 10);

// прочитать температуру с пина
float getTemp();

// прочитать усреднённую температуру с пина, можно указать к-во усреднений
// не рекомендуется использовать больше 20 усреднений, это бессмысленно. используйте внешний фильтр
float getTempAverage(uint8_t samples = 20);

// получить температуру из сигнала АЦП, можно указать разрешение АЦП
float computeTemp(float analog, uint8_t res = 10);
```

### Прямой расчёт

```cpp
// сигнал АЦП, (R резистора / R термистора), B термистора, t термистора, разрешение АЦП
float NTC_compute(float analog, float baseDiv, uint16_t B, uint8_t t = 25, uint8_t res = 10);

// сигнал АЦП, R резистора, B термистора, t термистора, R термистора, разрешение АЦП
float NTC_compute(float analog, uint32_t R, uint16_t B, uint8_t t = 25, uint32_t Rt = 10000, uint8_t res = 10);
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
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

### Несколько термисторов
Необязательно делать на каждый термистор свой экземпляр класса, достаточно указать пин перед измерением:

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
## Версии
- v1.0
- v1.1 - небольшая оптимизация, повышение точности
- v1.2 - оптимизация, поддержка 100к термисторов
- v1.3 - поддержка разного разрешения АЦП
- v1.4 - исправлена критическая ошибка!
- v1.5 - добавлена отдельная функция для расчёта

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
