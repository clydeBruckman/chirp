#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"
#include <algorithm>
#include <functional>
#include <memory>

int main() {

	FILE *fp;

	const std::size_t = 64;
	// etc.

	Aquila::SignalSource cmic; // control
	Aquila::SignalSource mic0, mic1, mic2, mic3;

	// GET FILE STUFF
	cmic.SignalSource(/*double vector*/, /*sample frequency rate -- check Arduino */);
			//  ^ fp needed here.
	//

	auto fft = Aquila::FftFactory::getFft(SIZE);
		// scope resolution w/ Function? ^

	int inverse(double amp) {
		return amp * -1;
	}

	Aquila::SpectrumType cspec = fft->fft(cmic.toArray());

	// TWO WAYS (PICK ONE!)

	std::for_each(cspec.begin(), cspec.end(), &inverse); // inverse noise spectrum.
	// ^ way 1: "for_each"

	for (double amp : cspec) {
		amp *= -1; } // <Michael-approved.

	// ^ way 2: range-based for loop
	// (does this work?)

	// SpectrumType is a vector of double-vectors.
	// why?
	// run example and print contents of an ex
	// frequency spectrum.
	// is *= -1 the best way to apply an operation
	// to all elements of a vector?

