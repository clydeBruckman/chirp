#ifndef analyze_dfft1024_h_
#define analyze_dfft2014_h_

#include "AudioStream.h"
#include "arm_math.h"

extern "C" {
	extern const int16_t AudioWindowHanning1024[];
	extern const int16_t AudioWindowBartlett1024[];
	extern const int16_t AudioWindowBlackman1024[];
	extern const int16_t AudioWindowFlattop1024[];
	extern const int16_t AudioWindowBlackmanHarris1024[];
	extern const int16_t AudioWindowNuttall1024[];
	extern const int16_t AudioWindowWelch1024[];
	extern const int16_t AudioWindowHamming1024[];
	extern const int16_t AudioWindowCosine1024[];
	extern const int16_t AudioWindowTukey1024[];
}

class AudioAnalyzeDFFT1024 : public AudioStream
{
public:
	AudioAnalyzeDFFT1024() : AudioStream(1, inputQueueArray), // < how u stream audio from queue object?
	window(AudioWindowHanning1024), state(0), outputflag(false) {
		arm_cfft_radix4_init_q15(&fft_inst, 1024, 0, 1);
	}
	bool available() {
		if (outputflag == true) {
			outputflag = false;
			return true;
		}
		return false;
	}
	float read(unsigned int binNumber) {
		if (binNumber > 511) return 0.0;
		return (float)(output[binNumber]) * (1.0 / 16384.0);
	}
	float read(unsigned int binFirst, unsigned int binLast) {
		if (binFirst > binLast) {
			unsigned int tmp = binLast;
			binLast = binFirst;
			binFirst = tmp;
		}
		if (binFirst > 511) return 0.0;
		if (binLast > 511) binLast = 511;
		uint32_t sum = 0;
		do {
			sum += output[binFirst++];
		} while (binFirst <= binLast);
		return (float)sum * (1.0 / 16384.0);
	}
	void averageTogether(uint8_t n) {
		// not yet implemented
	}
	void windowFunction(const int16_t *w) {
		window = w;
	}
	virtual void update(void);
	uint16_t output[512] __attribute__ ((aligned (4)));
private:
	void init(void);
	const int16_t *window;
	audio_block_t *blocklist[8];
	int16_t buffer[2048] __attribute__ ((aligned (4)));
	//uint32_t sum[512];
	//uint8_t count;
	uint8_t state;
	//uint8_t naverage;
	volatile bool outputflag;
	audio_block_t *inputQueueArray[1];
	arm_cfft_radix4_instance_q15 fft_inst;
};

#endif