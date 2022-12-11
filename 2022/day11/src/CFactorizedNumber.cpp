#include "CFactorizedNumber.h"

#include <numeric>

CFactorizedNumber::CFactorizedNumber( unsigned int aNumber )
{
	do
	{
		mComponents.push_front( aNumber % 10 );
		aNumber /= 10;
	} while( aNumber > 0 );

}

CFactorizedNumber::CFactorizedNumber( const components& aComponents ):
	mComponents( aComponents )
{
	while( mComponents.size() > 1 && mComponents.front() == 0 )
		mComponents.pop_front();
}

std::istream& operator>>( std::istream& aInput, CFactorizedNumber& aFactorizedNumber )
{
	unsigned int number;
	aInput >> number;
	aFactorizedNumber = CFactorizedNumber{ number };
	return aInput;
}
std::ostream& operator<<( std::ostream& aOutput, const CFactorizedNumber& aFactorizedNumber )
{
	for( const auto& component : aFactorizedNumber.mComponents )
		aOutput << component;
	return aOutput;
}

CFactorizedNumber operator+( const CFactorizedNumber& aLHS, const CFactorizedNumber& aRHS )
{
	CFactorizedNumber::components result;
	auto lhsIt = aLHS.mComponents.crbegin();
	auto rhsIt = aRHS.mComponents.crbegin();
	unsigned int carry{ 0 };
	for( ; lhsIt != aLHS.mComponents.crend() && rhsIt != aRHS.mComponents.crend(); ++lhsIt, ++rhsIt )
	{
		auto sum = ( *lhsIt ) + ( *rhsIt ) + carry;
		carry = sum / 10;
		result.push_front( sum % 10 );
	}
	while( lhsIt != aLHS.mComponents.crend() )
	{
		auto sum = ( *lhsIt ) + carry;
		carry = sum / 10;
		result.push_front( sum % 10 );
		++lhsIt;
	}
	while( rhsIt != aRHS.mComponents.crend() )
	{
		auto sum = ( *rhsIt ) + carry;
		carry = sum / 10;
		result.push_front( sum % 10 );
		++rhsIt;
	}
	if( carry > 0 )
		result.push_front( carry );
	return CFactorizedNumber{ result };
}

CFactorizedNumber operator*( const CFactorizedNumber& aLHS, const CFactorizedNumber& aRHS )
{
	std::list<CFactorizedNumber::components> result;
	for( auto lhsIt = aLHS.mComponents.crbegin(); lhsIt != aLHS.mComponents.crend(); ++lhsIt )
	{
		CFactorizedNumber::components partialResult( result.size(), 0 );
		unsigned int carry{ 0 };
		for( auto rhsIt = aRHS.mComponents.crbegin(); rhsIt != aRHS.mComponents.crend(); ++rhsIt )
		{
			auto product = ( *lhsIt ) * ( *rhsIt ) + carry;
			carry = product / 10;
			partialResult.push_front( product % 10 );
		}
		partialResult.push_front( carry );
		result.push_front( std::move( partialResult ) );
	}
	return std::accumulate( result.cbegin(), result.cend(), CFactorizedNumber{ 0 },
		[]( const CFactorizedNumber& aResult, const CFactorizedNumber::components& aComponent )
		{ return aResult + CFactorizedNumber{ aComponent }; } );
}

CFactorizedNumber operator/( const CFactorizedNumber& aLHS, const unsigned int& aRHS )
{
	CFactorizedNumber::components result;
	std::size_t remainder = 0;
	for( const auto& component : aLHS.mComponents )
	{
		auto lhs = remainder * 10 + component;
		result.push_back( static_cast< unsigned int >( lhs / aRHS ) );
		remainder = lhs % aRHS;
	}
	return CFactorizedNumber{ result };
}

unsigned int operator%( const CFactorizedNumber& aLHS, const unsigned int& aRHS )
{
	unsigned int remainder = 0;

	for( const auto& component : aLHS.mComponents )
	{
		auto lhs = remainder * 10 + component;
		remainder = lhs % aRHS;
	}

	return remainder;
}

std::size_t CFactorizedNumber::GetSize() const
{
	return mComponents.size();
}