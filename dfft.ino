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
AudioConnection          patchCord5(filter1, 0, queue1, 0);
AudioConnection          patchCord6(filter2, 0, queue2, 0);
// GUItool: end automatically generated code

const int readPinC = A2;
const int readPin1 = A3;

elapsedMicros time;

int mode = 0;

void steup() {

	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(readPinC, INPUT);
	pinMode(readPin1, INPUT);

	filter1.frequency(1000);
	filter2.frequency(1000);

	AudioMemory(60);

	Serial.begin(9600);

	uint16_t sampleC* = queue1.readBuffer();
	uint16_t sample* = queue2.readBuffer();
}

void loop() {

}

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

			memcpy(buffer, queue2.readBuffer(), 128);
			queue2.freeBuffer();

			byte sample* = buffer;

			short int i = 0;

			while(*sample) {

				if( i % 22 == 0) {

					toFFT[w] = *sample;
					w++;
				}
				i++;
				sample += sizeof(byte);
				// only need 4 more samples 
			}
		}
	}
}