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

// ** question for PJRC
// *  question for Michael
//    question for me

double scale_factor_1;

void setup() {

	AudioMemory(12); // ** how do I choose how much audio memory?

	fft1024_1.WindowFunction(AudioWindowHanning1024); // which window?
	fft1024_2.WindowFunction(AudioWindowHanning1024); // http://electronicdesign.com/analog/choose-right-fft-window-function-when-evaluating-precision-adcs

	scale_factor_1 = 0;

	filter1.frequency(1000);
	filter2.frequency(1000);

}

void loop() {

	// FIRST: SCALE PEAKS
	if (peak1.available() && peak2.available()) {
		scale_factor_1 *= (peak1.read() / peak2.read()); // ratio?
	} // peak, or peak-to-peak? I'm thinking the second...

	if (fft1024_1.available() && fft1024_2.available()) { // if these have 500+ bins why tf does the ex code only cycle through 40???
		for(int i = 0; i <= 511; i++){
			if ( abs( fft1024_1.read(i) * scale_factor_1 + fft1024_2.read(i) ) > 0.1 ) { // replace .01 with "SIGNIFICANT" defined static var.
				// something! // here's the "GPS and coordinate system" stuff
				//https://www.pjrc.com/teensy/td_libs_TinyGPS.html
				//https://forum.pjrc.com/threads/24979-Teensy-3-1-Ultimate-GPS-code
				//should I connect Teensy to Arduino via digital ins and outs, and make Arduino handle the GPS code?
				//why not
			} //  Is it bad/incorrect to scale frequency bins in this manner?
		} 
	}

	// SCALE FFT1 TO MATCH FFT2, THEN INVERT 1 AND ADD TOGETHER. THEN ANALYZE
	// MARGIN OF ERROR .01
}