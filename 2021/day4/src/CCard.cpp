#include "CCard.h"

std::istream& operator>>( std::istream& aInput, CCard& aCard )
{
	for( auto& row : aCard.mNumbers )
		for( auto& number : row )
			aInput >> number;
	return aInput;
}

const CCard::card_numbers& CCard::GetNumbers() const
{
	return mNumbers;
}

size_t CCard::GetRowCount() const
{
	return mNumbers.size();
}

size_t CCard::GetColumnCount() const
{
	return mNumbers.front().size();
}

CCard::optional_position CCard::FindNumber( const unsigned int& aNumber ) const
{
	for( auto rowIt = mNumbers.cbegin(); rowIt != mNumbers.cend(); ++rowIt )
		for( auto colIt = ( *rowIt ).cbegin(); colIt != ( *rowIt ).cend(); ++colIt )
			if( *colIt == aNumber )
				return std::make_pair( std::distance( mNumbers.cbegin(), rowIt ), std::distance( ( *rowIt ).cbegin(), colIt ) );
	return {};
}