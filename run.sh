#!/bin/sh

clear
gcc -Wall -Wextra -Werror -pedantic -o synth main.c dsp.c osc.c control.c -lm -lportaudio
./synth
