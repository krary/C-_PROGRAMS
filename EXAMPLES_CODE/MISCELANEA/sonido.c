#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <alsa/asoundlib.h>

#define SAMPLE_RATE 44100
#define DURATION_SEC 1
#define FREQUENCY 440.0 // Nota La (440 Hz)

int main(void) {
    snd_pcm_t *pcm_handle;
    snd_pcm_hw_params_t *params;
    int err;

    // 1. Abrir el dispositivo de audio predeterminado en modo REPRODUCCIÓN (PLAYBACK)
    err = snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        fprintf(stderr, "Error al abrir el dispositivo de audio: %s\n", snd_strerror(err));
        return 1;
    }

    // 2. Asignar e inicializar la estructura de parámetros de hardware
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_handle, params);

    // Configurar acceso intercalado (interleaved), formato PCM 16-bit Signed Little-Endian y 1 Canal (Mono)
    snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_channels(pcm_handle, params, 1);

    // Configurar la frecuencia de muestreo a 44100 Hz
    unsigned int sample_rate = SAMPLE_RATE;
    snd_pcm_hw_params_set_rate_near(pcm_handle, params, &sample_rate, 0);

    // Aplicar los parámetros al hardware
    err = snd_pcm_hw_params(pcm_handle, params);
    if (err < 0) {
        fprintf(stderr, "Error al configurar los parámetros: %s\n", snd_strerror(err));
        snd_pcm_close(pcm_handle);
        return 1;
    }

    // 3. Generar el búfer con la onda cuadrada en memoria
    int total_samples = SAMPLE_RATE * DURATION_SEC;
    int16_t *buffer = malloc(total_samples * sizeof(int16_t));

    double period_samples = (double)SAMPLE_RATE / FREQUENCY;

    for (int i = 0; i < total_samples; i++) {
        // Generamos la onda cuadrada alternando amplitud
        if (fmod(i, period_samples) < (period_samples / 2.0)) {
            buffer[i] = 3000;  // Amplitud positiva (volumen moderado)
        } else {
            buffer[i] = -3000; // Amplitud negativa
        }
    }

    // 4. Enviar los datos del búfer a la tarjeta de sonido
    snd_pcm_sframes_t frames_written = snd_pcm_writei(pcm_handle, buffer, total_samples);
    
    // Manejo de underflow (si el búfer de la tarjeta se queda vacío)
    if (frames_written < 0) {
        frames_written = snd_pcm_recover(pcm_handle, frames_written, 0);
    }

    if (frames_written < 0) {
        fprintf(stderr, "Error al escribir audio: %s\n", snd_strerror(frames_written));
    }

    // 5. Esperar a que finalice la reproducción y limpiar recursos
    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);
    free(buffer);

    return 0;
}
