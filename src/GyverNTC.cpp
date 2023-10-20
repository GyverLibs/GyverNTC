#include "GyverNTC.h"

// сигнал АЦП, (R резистора / R термистора), B термистора, t термистора, разрешение АЦП
float NTC_compute(float analog, float baseDiv, uint16_t B, uint8_t t, uint8_t res) {
    analog = baseDiv / ((float)((1 << res) - 1) / analog - 1.0f);
    analog = (log(analog) / B) + 1.0f / (t + 273.15f);
    return (1.0f / analog - 273.15f);
}

// сигнал АЦП, R резистора, B термистора, t термистора, R термистора, разрешение АЦП
float NTC_compute(float analog, uint32_t R, uint16_t B, uint8_t t, uint32_t Rt, uint8_t res) {
    return NTC_compute(analog, (float)R / Rt, B, t, res);
}