#ifndef OSC_H
#define OSC_H

#include <stdatomic.h>

typedef struct osc {
    const float *wavetable;
    float phase; // in [0.0, 1.0)
    float inc;
    _Atomic float inc_target;
} osc;

float osc_process(osc *o);

void osc_create(osc *o, float freq, float sample_rate, float *wavetable);

#endif
