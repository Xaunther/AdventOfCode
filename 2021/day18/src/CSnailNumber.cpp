#include "CSnailNumber.h"

#include <algorithm>
#include <string>

namespace
{

bool CanExplode( const CSnailNumber::component& aLHS, const CSnailNumber::component& aRHS );
bool SameDepth( const CSnailNumber::component& aLHS, const CSnailNumber::component& aRHS );
bool CanSplit( const CSnailNumber::component& aComponent );
std::size_t PairMagnitude( const CSnailNumber::value& aLHS, const CSnailNumber::value& aRHS );

}

std::istream& operator>>( std::istream& aInput, CSnailNumber& aSnailNumber )
{
	std::string rawSnailNumber;
	aInput >> rawSnailNumber;

	CSnailNumber::depth depth{ 0 };
	for( const auto& character : rawSnailNumber )
	{
		if( character == '[' )
			++depth;
		else if( character == ']' )
			--depth;
		else if( character != ',' )
			aSnailNumber.mComponents.emplace_back( static_cast< CSnailNumber::value >( character - 48 ), depth );
	}

	return aInput;
}

CSnailNumber& CSnailNumber::operator+=( const CSnailNumber& aRHS )
{
	if( !mComponents.empty() && !aRHS.GetComponents().empty() )
	{
		for( auto& component : mComponents )
			++component.second;

		for( const auto& component : aRHS.GetComponents() )
			mComponents.emplace_back( component.first, static_cast< depth >( component.second + 1 ) );

		Reduce();
	}
	else
		for( const auto& component : aRHS.GetComponents() )
			mComponents.emplace_back( component );

	return *this;
}

void CSnailNumber::Reduce()
{
	bool hasChanged;
	do
	{
		hasChanged = false;
		hasChanged |= Explode();
		if( !hasChanged )
			hasChanged |= Split();
	} while( hasChanged );

}

bool CSnailNumber::Explode()
{
	const auto& found = std::adjacent_find( mComponents.begin(), mComponents.end(), CanExplode );
	if( found != mComponents.end() )
	{
		if( found != mComponents.begin() )
			( *std::prev( found ) ).first += ( *found ).first;

		const auto& adjacent = std::next( found );
		const auto& after = std::next( adjacent );
		if( after != mComponents.end() )
			( *after ).first += ( *adjacent ).first;

		( *found ).first = 0;
		--( *found ).second;
		mComponents.erase( adjacent );

		return true;
	}
	else
		return false;

}

bool CSnailNumber::Split()
{
	const auto& found = std::find_if( mComponents.begin(), mComponents.end(), CanSplit );
	if( found != mComponents.end() )
	{
		++( *found ).second;
		mComponents.insert( found, component{ static_cast< value >( ( *found ).first / 2 ), ( *found ).second } );
		( *found ).first = static_cast< value >( ( *found ).first / 2 + ( *found ).first % 2 );

		return true;
	}
	else
		return false;
}

const CSnailNumber::components& CSnailNumber::GetComponents() const
{
	return mComponents;
}

std::size_t CSnailNumber::Magnitude() const
{
	auto componentsCopy = mComponents;

	auto found = componentsCopy.begin();

	while( ( found = std::adjacent_find( componentsCopy.begin(), componentsCopy.end(), SameDepth ) ) != componentsCopy.end() )
	{
		const auto& adjacent = std::next( found );
		const auto& result = PairMagnitude( ( *found ).first, ( *adjacent ).first );
		componentsCopy.erase( adjacent );
		( *found ).first = result;
		--( *found ).second;
	}

	return componentsCopy.front().first;
}


namespace
{

bool CanExplode( const CSnailNumber::component& aLHS, const CSnailNumber::component& aRHS )
{
	return aLHS.second >= 5 && aLHS.second == aRHS.second;
}

bool SameDepth( const CSnailNumber::component& aLHS, const CSnailNumber::component& aRHS )
{
	return aLHS.second == aRHS.second;
}

bool CanSplit( const CSnailNumber::component& aComponent )
{
	return aComponent.first >= 10;
}

std::size_t PairMagnitude( const CSnailNumber::value& aLHS, const CSnailNumber::value& aRHS )
{
	return static_cast< std::size_t >( 3 * aLHS + 2 * aRHS );
}

}