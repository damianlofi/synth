#include <stdatomic.h>
#include "osc.h"
#include "dsp.h"
#include <stdio.h>

float osc_process(osc *o)
{
    o->phase += o->inc;
    if (o->phase >= 1.0) {
        o->phase -= 1.0;
    }

    float target = atomic_load(&o->inc_target);
    o->inc += 0.001f * (target - o->inc);

    float index = o->phase * 2048;
    int i0 = (int)(index);
    int i1 = (i0 + 1) & (2048 - 1);
    float s0 = o->wavetable[i0];
    float s1 = o->wavetable[i1];

    float frac = index - i0;
    return s0 + (s1-s0) * frac;
}

void osc_create(osc *o, float freq, float sample_rate, float *wavetable)
{
    o->phase = 0.0;
    float inc = freq / sample_rate;
    o->inc = inc;
    o->wavetable = wavetable;
    atomic_store(&o->inc_target, inc);
}
