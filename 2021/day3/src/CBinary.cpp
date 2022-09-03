#include "CBinary.h"
#include <string>
#include <cmath>

namespace
{

CBinary::binary_number CreateRate( const std::vector<unsigned int>& aVectorSum, const size_t& aSumCount, const CBinary::E_RATE& aRate );

}

CBinary::CBinary()
{
}

CBinary::CBinary( const std::vector<unsigned int>& aVectorSum, const size_t& aSumCount, const E_RATE& aRate ) :
	mBinaryNumber( CreateRate( aVectorSum, aSumCount, aRate ) )
{
}

std::istream& operator>>( std::istream& aInput, CBinary& aBinary )
{
	std::string binaryString;
	aInput >> binaryString;
	aBinary.mBinaryNumber.reserve( binaryString.size() );
	for( const auto& numberChar : binaryString )
		aBinary.mBinaryNumber.push_back( numberChar != '0' );

	return aInput;
}

const CBinary::binary_number& CBinary::GetBinaryNumber() const
{
	return mBinaryNumber;
}

unsigned int CBinary::CalculateDecimalNumber() const
{
	unsigned int result = 0;

	unsigned int power = static_cast< unsigned int >( mBinaryNumber.size() ) - 1;
	for( const auto& number : mBinaryNumber )
		result += static_cast< unsigned int >( number ) * static_cast< unsigned int > ( std::pow( 2, power-- ) );

	return result;
}

namespace
{

CBinary::binary_number CreateRate( const std::vector<unsigned int>& aVectorSum, const size_t& aSumCount, const CBinary::E_RATE& aRate )
{
	CBinary::binary_number result;
	result.reserve( aVectorSum.size() );
	for( const auto& sum : aVectorSum )
		result.push_back( ( 2 * sum < aSumCount ) == static_cast< bool >( aRate ) );

	return result;
}

}