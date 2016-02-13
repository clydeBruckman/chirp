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

void AudioAnalyzeFFT1024::update(void)
{
  audio_block_t *block;
  
  block = receiveReadOnly();
  if(!block) return;

#if defined(KINETISK)
  switch(state) {
  case 0:
    blocklist[0] = block;
    state = 1;
    break;
  case 1:
    blocklist[1] = block;
    state = 2;
    break;
  case 2:
    blocklist[2] = block;
    for(int i = 0; i < 9; i++){
      double  decimated_buffer[128];
      int counter = 0;
      int decimated_index = 0;

      while( blocklist[i]->data ) {
	audio_block_t *cycle = &blocklist[i]->data
	if( (counter % 22) = 0 ) {
	  decimated_buffer[decimated_index] = *cycle;
	  decimated_index++;
	}
	cycle += SIZEOF(audio_block_t);
	counter++;
      }
      copy_to_fft_buffer(buffer+0x000, decimated_buffer[0]);
