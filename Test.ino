#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const int myInput = AUDIO_INPUT_LINEIN;
const int myInput = AUDIO_INPUT_MIC_1;


// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=174,211
AudioInputAnalog         adc2;           //xy=176,263
AudioAnalyzeFFT1024      fft1024_1;      //xy=371,211
AudioAnalyzeFFT1024      fft1024_2;      //xy=373,264
AudioAnalyzeFFT1024	 new_fft;	 //xy=no idea
AudioAnalyzeFFT1024	 fft_sum;	 // ditto
AudioConnection          patchCord1(adc1, fft1024_1);
AudioConnection          patchCord2(adc2, fft1024_2);
// GUItool: end automatically generated code
AudioOutputI2S		 audioOutput;

void setup() {

	AudioMemory(12); // check this out later.

	
	// messy band-pass... Most likely this is all wrong.
	for( int i = 0; i < 511; i++ ) {
		double freq = fft_sum.read(i);
		if( freq > 200 && freq < 520 ) {
			new_fft.output[i] = freq; } else {
			new_fft.output[i] = 0;
		}
 
