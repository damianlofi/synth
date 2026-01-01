/* 
 * This program uses the PortAudio Portable Audio Library and contains code adapted from PortAudio examples.
 * Copyright (c) 1999–2000 Ross Bencina and Phil Burk
 * Licensed under the MIT License – see licenses/portaudio.txt
 */

#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#include "osc.h"
#include "dsp.h"
#include "control.h"

#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (128)

static int audio_callback(
    const void *inputBuffer,
    void *outputBuffer,
    unsigned long framesPerBuffer, 
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData
) {
    synthesizer *synth = (synthesizer*)userData;
    float *out = (float*)outputBuffer;
    
    // Prevent unused variable warnings
    (void) timeInfo;     (void) statusFlags;
    (void) inputBuffer;
 
    for (unsigned long i=0; i<framesPerBuffer; i++) {
        float s = next_sample(synth);

        s *= 0.2;

        if (s > 1.0) s = 1.0;
        if (s < -1.0) s = -1.0;
        *out++ = s;
        *out++ = s;
    }
 
    return paContinue;
}

static int run_app(synthesizer *synth)
{
    PaStreamParameters outputParameters;
    PaStream *stream = NULL;
    PaError paerr;

    paerr = Pa_Initialize();
    if( paerr != paNoError ) goto cleanup;

    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        paerr = paNoDevice;
        goto cleanup;
    }

    /* stereo output */
    outputParameters.channelCount = 2;       
    /* 32 bit floating point output */
    outputParameters.sampleFormat = paFloat32; 
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    paerr = Pa_OpenStream(
              &stream,
              NULL, /* no input */
              &outputParameters,
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,
              audio_callback,
              synth );
    if( paerr != paNoError ) goto cleanup;

    paerr = Pa_StartStream( stream );
    if( paerr != paNoError ) goto cleanup;

    // start the control interface and let the stream run until control_run() returns
    int control_err = 0;
    control_err = control_run(synth);

    goto cleanup;

cleanup:
    if (stream) {
        Pa_StopStream( stream );
        Pa_CloseStream( stream );
    }

    Pa_Terminate();

    if (paerr != paNoError) {
        fprintf( stderr, "An error occurred while using the portaudio stream\n" );
        fprintf( stderr, "Error number: %d\n", paerr );
        fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( paerr ) );
        return 1;
    }

    return control_err;
}

int main(void)
{
    synthesizer *synth = synth_create(SAMPLE_RATE);
    if (!synth) return 1;
    int err = run_app(synth);
    synth_destroy(synth);
    return err;
}
