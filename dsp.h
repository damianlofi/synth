#ifndef DSP_H
#define DSP_H

#include "osc.h"

typedef struct synthesizer {
    float sr;
    float wavetable[2048];
    osc vco1, vco2, vco3;
    osc lfo1, lfo2;
} synthesizer;

synthesizer *synth_create(float sample_rate);

void synth_destroy(synthesizer *s);

float next_sample(synthesizer *synth);

#endif
