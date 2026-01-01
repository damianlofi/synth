This is my attempt at a synthesizer using portaudio and raylib to learn C.

You need to install the portaudio library on your system to build and you can use the command in run.sh to build with gcc. On Debian 13:

```
sudo apt update
sudo apt install portaudio19-dev
gcc -Wall -Wextra -Werror -pedantic -o synth main.c dsp.c osc.c control.c -lportaudio -lm 
```

Currently the synthesizer consists of only just one oscillator that is turned on by default when starting the program. You can type "j", "k" or "l" (and then Enter) to change to different frequencies and "x" to leave.

---

This project is licensed under the MIT License – see the LICENSE file for details. 

See /licenses for third-party licenses.

