#ifndef C_REBOOT_STEP_H
#define C_REBOOT_STEP_H

#include <array>
#include <istream>
#include <utility>

class CRebootStep
{
public:
	using range = std::pair<long, long>;
	using ranges = std::array<range, 3>;

	friend std::istream& operator>>( std::istream& aInput, CRebootStep& aRebootStep );

	const bool GetSwitch() const;
	const ranges& GetRanges() const;

private:
	bool mSwitch;
	ranges mRanges;
};

#endif // C_REBOOT_STEP_H