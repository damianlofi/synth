#include "dsp.h"
#include "osc.h"
#include <stdlib.h>
#include <math.h>

#ifndef TAU
#define TAU (6.283185307179586)
#endif

float next_sample(synthesizer *synth)
{
    osc *vco1 = &synth->vco1;

    float s = 0;

    // float freq = 220 + 30 * osc_process(lfo2, SAMPLE_RATE);
    // atomic_store(&data->vco1.freq_target, freq);

    s += osc_process(vco1);

    s *= 0.4;

    return s;
}

synthesizer *synth_create(float sample_rate)
{
    synthesizer *synth = malloc(sizeof *synth);
    if (!synth)
        return NULL;

    synth->sr = sample_rate;

    for (int i = 0; i < 2048; i++) {
        synth->wavetable[i] = sin((float)i * TAU/2048);
    }

    float base = 220;
    osc_create(&synth->vco1, base, sample_rate, synth->wavetable);
    osc_create(&synth->vco2, base * 5.0/4.0 * 1.003, sample_rate, synth->wavetable);
    osc_create(&synth->vco3, base * 3.0/2.0 * 0.998, sample_rate, synth->wavetable);
    osc_create(&synth->lfo1, 440, sample_rate, synth->wavetable);
    osc_create(&synth->lfo2, 880, sample_rate, synth->wavetable);

    return synth;
}

void synth_destroy(synthesizer *s) {
    free(s);
} 
