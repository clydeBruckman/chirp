#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h" // probably not for the Whole thing.
#include <algorithm>
#include <functional>
#include <memory>

int main() {

	FILE *fp;

	const std::size_t = 64;
	// etc.

	Aquila::SignalSource cmic; // control
	Aquila::SignalSource mic0, mic1, mic2, mic3;

	// ASSIGN ALL READINGS TO VARS
	//this will require a review of file-io C++

	cmic.SignalSource(/*double vector*/, /*sample frequency rate -- check Arduino */);
			//  ^ fp needed here.

	auto fft = Aquila::FftFactory::getFft(SIZE);

	Aquila::SpectrumType cspec = fft->fft(cmic.toArray());

	for (/*ComplexType syntax*/ amp : cspec) {
		amp *= -1; } // except it ain't double, it's ComplexType.


	// SpectrumType is a vector of double-vectors.
	// why?
	// run example and print contents of an ex
	// frequency spectrum.
	// is *= -1 the best way to apply an operation
	// to all elements of a vector?

