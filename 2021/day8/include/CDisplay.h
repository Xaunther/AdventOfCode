#ifndef C_DISPLAY_H
#define C_DISPLAY_H

#include <set>
#include <array>
#include <map>
#include <istream>
#include "CDigit.h"

class CDisplay
{
public:
	using reference_digits = std::array<CDigit, 10>;
	using output_digits = std::array<CDigit, 4>;
	using solution = std::map<CDigit::digit, unsigned int>;
	using inverse_solution = std::map<unsigned int, CDigit::digit>;

	friend std::istream& operator>>( std::istream& aInput, CDisplay& aDisplay );

	const reference_digits& GetReference() const;
	const output_digits& GetOutput() const;
	const solution& GetSolution() const;

	unsigned int CountUniqueOutputs() const;

	unsigned int SolveOutput() const;

private:
	void Solve();

	reference_digits mReference;
	output_digits mOutput;
	solution mSolution;
	inverse_solution mInverseSolution;
};

#endif // C_DISPLAY_H