
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
	auto other_sum = sineGenerator4 + sineGenerator3 + sineGenerator2 + sineGenerator1;

	Aquila::TextPlot plt("Signal waveform before filtration");
	plt.plot(sum);

	// just get this much working.

	// where does fft Get its freq values from???

	auto fft = Aquila::FftFactory::getFft(SIZE);
	Aquila::SpectrumType spectrum = fft->fft(sum.toArray());
	plt.setTitle("Signal spectrum before filtration");
	plt.splotSpectrum(spectrum);

	Aquila::SpectrumType inverse(SIZE);
	for (std::size_t i = 0; i < SIZE; ++i) {
		inverse[i] = -1;
	}

	plt.setTitle("inverse Spectrum");
	plt.plotSpectrum(inverse);

	std::transform(
		std::begin(spectrum),
		std::end(spectrum),
		std::begin(inverse),
		std::begin(spectrum),
		[] (Aquila::ComplexType x, Aquila::ComplexType y) {return x * y}
	);
	plt.setTitle("Flipped Signal");
	plt.plotSpectrum(spectrum);

	// back to time-domain
	double flip_sig[SIZE];
	fft->ifft(spectrum, flip_sig);
	plt.setTitle("Signal after flipping");
	plt.plot(flip_sig, SIZE);

	// sum norm and flipped versions; 0? Does it add frequency spectra?
	auto final = flip_sig + other_sum;
	plt.setTitle("Cancelled noise?");
	plt.plot(final);

}