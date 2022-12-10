#pragma once

#include <ostream>
#include <string>

class CCPU;

class CDisplay
{
public:
	explicit CDisplay( const CCPU& aCPU, const unsigned int& aWidth );

	const unsigned int& GetWidth() const;
	std::string_view GetPixels() const;

	friend std::ostream& operator<<( std::ostream& aOutput, const CDisplay& aDisplay );

private:
	unsigned int mWidth;
	std::string mPixels;
};