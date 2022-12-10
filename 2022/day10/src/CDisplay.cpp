#include "CDisplay.h"

#include "CCPU.h"

namespace
{

inline bool AreAdjacent( const int aLHS, const int aRHS );

}

CDisplay::CDisplay( const CCPU& aCPU, const unsigned int& aWidth ):
	mWidth( aWidth ),
	mPixels( aCPU.GetCycles().size() - 1, '.' )
{
	for( unsigned int i = 0; i < aCPU.GetCycles().size() - 1; ++i )
		if( AreAdjacent( aCPU.GetCycles()[ i ], static_cast< int >( i % aWidth ) ) )
			mPixels[ i ] = '#';
}

const unsigned int& CDisplay::GetWidth() const
{
	return mWidth;
}

std::string_view CDisplay::GetPixels() const
{
	return mPixels;
}

std::ostream& operator<<( std::ostream& aOutput, const CDisplay& aDisplay )
{
	auto pixels = aDisplay.GetPixels();
	aOutput << "\n";
	for( unsigned int index = 0; index < pixels.size(); index += aDisplay.GetWidth() )
		aOutput << pixels.substr( index, aDisplay.GetWidth() ) << "\n";
	return aOutput;
}

namespace
{

inline bool AreAdjacent( const int aLHS, const int aRHS )
{
	return aLHS - 1 <= aRHS && aLHS + 1 >= aRHS;
}

}