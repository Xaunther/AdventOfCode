#include "CSignal.h"

#include <ranges>
#include <set>

namespace
{

template<typename T> bool HasUniqueElements( const T& aContainer );

}

std::istream& operator>>( std::istream& aInput, CSignal& aSignal )
{
	aSignal = CSignal{};
	for( const auto& inputChar : std::ranges::istream_view<char>( aInput ) )
		aSignal.mSignal.push_back( inputChar );
	return aInput;
}

const CSignal::signal& CSignal::GetSignal() const
{
	return mSignal;
}

unsigned int CSignal::FindStartMarker( const unsigned int aMarkerSize ) const
{
	unsigned int result = 0;

	signal sequence;
	for( const auto& signalElement : mSignal )
	{
		++result;
		sequence.push_back( signalElement );
		if( sequence.size() > aMarkerSize )
			sequence.pop_front();
		if( sequence.size() == aMarkerSize && HasUniqueElements( sequence ) )
			return result;
	}

	return result;
}

namespace
{

template<typename T> bool HasUniqueElements( const T& aContainer )
{
	std::set<typename T::value_type> containerSet;
	for( const auto& element : aContainer )
		if( !containerSet.insert( element ).second )
			return false;
	return true;
}

}