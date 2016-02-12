#include "analyze_dfft_1024.h"
#include "sqrt_integer.h"
#include "utility/dspinst.h"

static void copy_to_fft_buffer(void *destination, const void *source)
{
	const uint16_t *src = (const uint16_t *)source;
	uint32_t *dst = (uint32_t *)destination;

	for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
		*dst++ = *src++; // real sample plus a zero for imaginary
	}
}

static void apply_window_to_fft_buffer(void *buffer, const void *window)
{
	int16_t *buf = (int16_t *)buffer;
	const int16_t *win = (int16_t *)window;

	for (int i = 0; i < 1024; i++) {
		int32_t val = *buf * *win++;
		*buf = val >> 15;
		buf += 2;
	}
}