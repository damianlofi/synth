#include "control.h"
#include <stdio.h>
#include <stdatomic.h>

int control_run(synthesizer *synth)
{
    while (1) {
        int c = getchar();

        (void) synth;

        float base = 200.0;

        if (c == 'j') {
            float inc = base / synth->sr;
            atomic_store(&synth->vco1.inc_target, inc);
        }
        if (c == 'k') {
            float inc = base *2 / synth->sr;
            atomic_store(&synth->vco1.inc_target, inc);
        }
        if (c == 'l') {
            float inc = base * 4/ synth->sr;
            atomic_store(&synth->vco1.inc_target, inc);
        }
        if (c == 'x') {
            return 0;
        }
    }
}
