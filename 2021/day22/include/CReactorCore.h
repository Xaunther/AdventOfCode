#ifndef C_REACTOR_CORE_H
#define C_REACTOR_CORE_H

#include <array>
#include <list>
#include <set>

#include "CRebootStep.h"

class CReactorCore
{
public:
	using ranges = CRebootStep::ranges;
	using lit_ranges = std::set<ranges>;
	using reboot_steps = std::list<CRebootStep>;

	const lit_ranges& GetLitRanges() const;
	std::size_t CountLitCubes() const;

	void Initialize( const reboot_steps& aRebootSteps, const CRebootStep::range& aRangeX, const CRebootStep::range& aRangeY, const CRebootStep::range& aRangeZ );
	void Reboot( const reboot_steps& aRebootSteps );

private:
	lit_ranges mLitRanges;
};

#endif // C_REACTOR_CORE_H