#include "CPolymer.h"
#include "CInsertionRules.h"

#include <algorithm>
namespace
{

CPolymer::polymer CountPairs( const std::string& aPolymer );
CPolymer::element_count CountElements( const std::string& aPolymer );

}

std::istream& operator>>( std::istream& aInput, CPolymer& aPolymer )
{
	std::string rawPolymer;
	aInput >> rawPolymer;
	aPolymer.mPolymer = CountPairs( rawPolymer );
	aPolymer.mElementCount = CountElements( rawPolymer );
	return aInput;
}

const CPolymer::polymer& CPolymer::GetPolymer() const
{
	return mPolymer;
}

const std::size_t& CPolymer::GetMostCommonElementCount() const
{
	return ( *std::max_element( mElementCount.cbegin(), mElementCount.cend(),
		[]( const auto& aLeft, const auto& aRight ) { return aLeft.second < aRight.second; } ) ).second;
}

const std::size_t& CPolymer::GetLeastCommonElementCount() const
{
	return ( *std::min_element( mElementCount.cbegin(), mElementCount.cend(),
		[]( const auto& aLeft, const auto& aRight ) { return aLeft.second < aRight.second; } ) ).second;
}

void CPolymer::Polymerize( const CInsertionRules& aInsertionRules )
{
	auto newPolymer = mPolymer;
	for( const auto& sequence : mPolymer )
	{
		const auto& found = aInsertionRules.GetInsertionRules().find( sequence.first );
		if( found != aInsertionRules.GetInsertionRules().cend() )
		{
			newPolymer[ ( *found ).second.first ] += sequence.second;
			newPolymer[ ( *found ).second.second ] += sequence.second;
			newPolymer[ sequence.first ] -= sequence.second;
			mElementCount[ ( *found ).second.first.back() ] += sequence.second;
		}
	}
	mPolymer = newPolymer;
}

namespace
{

CPolymer::polymer CountPairs( const std::string& aPolymer )
{
	CPolymer::polymer result;
	for( std::size_t index = 1; index < aPolymer.size(); ++index )
		++result[ aPolymer.substr( index - 1, 2 ) ];
	return result;
}

CPolymer::element_count CountElements( const std::string& aPolymer )
{
	CPolymer::element_count result;
	for( const auto& element : aPolymer )
		++result[ element ];
	return result;
}

}