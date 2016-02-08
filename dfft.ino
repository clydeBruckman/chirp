#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=175,142
AudioInputAnalog         adc2(A3);           //xy=197,252
AudioAnalyzePeak         peak2;          //xy=318,322
AudioAnalyzePeak         peak1;          //xy=330,78
AudioFilterStateVariable filter1;        //xy=360,141
AudioFilterStateVariable filter2;        //xy=360,253
AudioRecordQueue         queue1;         //xy=506,133
AudioRecordQueue         queue2;         //xy=526,277
AudioConnection          patchCord1(adc1, peak1);
AudioConnection          patchCord2(adc1, 0, filter1, 0);
AudioConnection          patchCord3(adc2, peak2);
AudioConnection          patchCord4(adc2, 0, filter2, 0);
AudioConnection          patchCord5(filter1, 0, queue1, 0);	// too scared of ambiguous code
AudioConnection          patchCord6(filter2, 0, queue2, 0); // to name vars how I like them
// GUItool: end automatically generated code

// "C" : "CONTROL"

const int readPinC = A2;
const int readPin1 = A3;

elapsedMicros time;

int mode = 0;

void steup() {

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(readPinC, INPUT);
	pinMode(readPin1, INPUT);

	filter1.frequency(1000);
	filter2.frequency(1000); // hopefully the Audio connections take care of this...

	AudioMemory(60); // hopefully this is enough memory

	Serial.begin(9600);

	uint16_t sampleC* = queue1.readBuffer();
	uint16_t sample* = queue2.readBuffer();
}

void loop() {

}

//set mode in these! (check Audio/examples/Recorder)

void startRecording() {
	Serial.println("Recording...");
	queue2.begin();
}

void continueRecording() {

	byte toFFT[1024];
	short int w = 0;

	while(w <= 1024) {

		if (queue2.available() >= 2) {
			byte buffer[128];

			memcpy(buffer, queue2.readBuffer(), 128); // this is how u allocate queue memory
			queue2.freeBuffer();

			byte sample* = buffer;

			short int i = 0;

			while(*sample) { // cycling w/ pointers to save space/time

				if( i % 22 == 0) {

					toFFT[w] = *sample;
					w++;
				} // PROBLEM: w will pass 2014 before all multiples of 22 in sample* buffer are allocated.
				i++;
				sample += sizeof(byte);
				// only need 4 more samples once you start on new buffer...
			}
		}
	}
}