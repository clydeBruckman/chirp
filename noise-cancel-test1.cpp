
// take a signal, fft it, and inverse everything.

#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"
#include <algorithm>
#include <functional>
#include <memory>

int main()
{

	const std::size_t SIZE = 64;
	const Aquila::FrequencyType f_lp = 500;
	const Aquila::FrequencyType sampleFreq = 2000;
	const Aquila::FrequencyType f1 = 56, f2 = 30, f3 = 75, f4 = 900;

	Aquila::SineGenerator sineGenerator1(sampleFreq);
	sineGenerator1.setAmplitude(32).setFrequency(f1).generate(SIZE);
	Aquila::SineGenerator sineGenerator2(sampleFreq);
	sineGenerator2.setAmplitude(8).setFrequency(f4).setPhase(0.75).generate(SIZE);
	Aquila::SineGenerator sineGenerator3(sampleFreq);
	sineGenerator3.setAmplitude)(20).setFrequency(f3).setPhase(2.1).generate(SIZE);
	Aquila::SineGenerator sineGenerator4(sampleFreq);
	sineGenerator4.setAmplitude(60).setFrequency(f2).setPhase(0.4).generate(SIZE);

	auto sum = sineGenerator4 + sineGenerator3 + sineGenerator2 + sineGenerator1;

	Aquila::TextPlot plt("Signal waveform before filtration");
	plt.plot(sum);

	// just get this much working.

}