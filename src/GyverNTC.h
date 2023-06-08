/*
    Библиотека для работы с NTC термисторами по закону Стейнхарта-Харта
    Документация: 
    GitHub: https://github.com/GyverLibs/GyverNTC
    Возможности:
    - Установка параметров термистора
    - Получение температуры
    - Встроенное усреднение
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License

    Версии:
    v1.0 - релиз
    v1.1 - небольшая оптимизация, повышение точности
    v1.2 - оптимизация, поддержка 100к термисторов
    v1.3 - поддержка АЦП с разной битностью
*/

#ifndef _GyverNTC_h
#define _GyverNTC_h
#include <Arduino.h>

class GyverNTC {
public:
    // подключение: GND --- Rt --- ADC --- R --- VCC
    
    GyverNTC() {}
    
    // пин, R резистора, B термистора, t термистора, R термистора, разрешение АЦП
    GyverNTC(uint8_t pin, uint32_t R, uint16_t B, uint8_t t = 25, uint32_t Rt = 10000, uint8_t res = 10) {
        config(R, B, t, Rt);
        setPin(pin, res);
    }
    
    // настроить термистор: R резистора, B термистора, t термистора, R термистора
    void config(uint32_t R, uint16_t B, uint8_t t = 25, uint32_t Rt = 10000) {
        _beta = B;
        _tempBase = t;
        _baseDivRes = (float)Rt / R;
    }
    
    // настроить пин и разрешение АЦП
    void setPin(uint8_t pin, uint8_t res = 10) {
        _pin = pin;
        _res = res;
    }
    
    // прочитать температуру с пина
    float getTemp() {
        return computeTemp(analogRead(_pin), _res);
    }
    
    // прочитать усреднённую температуру с пина, можно указать к-во усреднений
    float getTempAverage(uint8_t samples = 20) {
        uint16_t aver = 0;
        for (uint8_t i = 0; i < samples; i++) aver += analogRead(_pin);
        return computeTemp((float)aver / samples, _res);
    }
    
    // получить температуру из сигнала АЦП, можно указать разрешение АЦП
    float computeTemp(float analog, uint8_t res = 10) {
        analog = _baseDivRes / ((float)((1 << res) - 1) / analog - 1.0f);
        analog = (log(analog) / _beta) + 1.0f / (_tempBase + 273.15f);
        return (1.0f / analog - 273.15f);
    }
    
private:
    uint8_t _res = 10;
    uint8_t _pin = 0;
    uint16_t _beta = 3435;
    uint8_t _tempBase = 25;
    float _baseDivRes = 1.0;
};
#endif