#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=82,93
AudioInputAnalog         adc2;           //xy=82,143
AudioAnalyzePeak         peak1;          //xy=243,26
AudioFilterStateVariable filter1;        //xy=249,97
AudioFilterStateVariable filter2;        //xy=250,163
AudioAnalyzePeak         peak2;          //xy=252,230
AudioAnalyzeFFT1024      fft1024_1;      //xy=433,86
AudioAnalyzeFFT1024      fft1024_2;      //xy=437,167
AudioConnection          patchCord1(adc1, peak1);
AudioConnection          patchCord2(adc1, 0, filter1, 0);
AudioConnection          patchCord3(adc2, peak2);
AudioConnection          patchCord4(adc2, 0, filter2, 0);
AudioConnection          patchCord5(filter1, 0, fft1024_1, 0);
AudioConnection          patchCord6(filter2, 0, fft1024_2, 0);
// GUItool: end automatically generated code

double peak_1_scaled;
double peak_2_scaled;

void setup() {

	AudioMemory(12); // ** how do I choose how much audio memory?

	fft1024_1.WindowFunction(AudioWindowHanning1024);
	fft1024_2.WindowFunction(AudioWindowHanning1024);

	peak_1_scaled = 0;
	peak_2_scaled = 0;

}

void loop() {

	// FIRST: SCALE PEAKS
	if (peak1.available() && peak2.available()) {
		peak_1_scaled *= (peak2.read() / peak1.read()); // ratio?
		peak_2_scaled = peak2.read();
	}

	if (fft1024_1.available()) {

	}

	// SCALE FFT1 TO MATCH FFT2, THEN INVERT 1 AND ADD TOGETHER. THEN ANALYZE
	// MARGIN OF ERROR .01
}