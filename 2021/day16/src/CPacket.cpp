#include "CPacket.h"

#include <bitset>
#include <charconv>
#include <iostream>
#include <numeric>

using binary_sequence = CPacket::binary_sequence;

namespace
{

binary_sequence ToBinarySequence( unsigned short aNumber, std::optional<unsigned short> aDigits );
CPacket::literal_value::value_type ToValue( const binary_sequence& aBinaryDeque );
CPacket::version ExtractVersion( binary_sequence& aBinaryPacket );
CPacket::type_id ExtractTypeID( binary_sequence& aBinaryPacket );
CPacket::literal_value ExtractLiteral( binary_sequence& aBinaryPacket );
std::size_t ExtractSubPacketsNumber( binary_sequence& aBinaryPacket );
std::size_t ExtractSubPacketsLength( binary_sequence& aBinaryPacket );
CPacket::COperator::length_type_id ExtractLengthTypeID( binary_sequence& aBinaryPacket );

template <bool>CPacket::COperator::packets ExtractPackets( binary_sequence& aBinaryPacket );
template <>CPacket::COperator::packets ExtractPackets<true>( binary_sequence& aBinaryPacket )
{
	CPacket::COperator::packets result;

	const auto& subPacketsNumber = ExtractSubPacketsNumber( aBinaryPacket );
	result.reserve( subPacketsNumber );
	for( std::size_t index = 0; index < subPacketsNumber; ++index )
		result.emplace_back( aBinaryPacket );

	return result;
}

template <>CPacket::COperator::packets ExtractPackets<false>( binary_sequence& aBinaryPacket )
{
	CPacket::COperator::packets result;

	const auto& subPacketsLength = ExtractSubPacketsLength( aBinaryPacket );

	const auto& sizeAfterExtraction = aBinaryPacket.size() - subPacketsLength;
	while( aBinaryPacket.size() > sizeAfterExtraction )
		result.emplace_back( aBinaryPacket );

	return result;
}

}

CPacket::COperator::COperator( binary_sequence& aBinarySequence ):
	mLengthTypeID( ExtractLengthTypeID( aBinarySequence ) ),
	mPackets( mLengthTypeID ? ExtractPackets<true>( aBinarySequence ) : ExtractPackets<false>( aBinarySequence ) )
{

}

CPacket::CPacket( binary_sequence& aBinarySequence ):
	mVersion( ExtractVersion( aBinarySequence ) ),
	mTypeID( ExtractTypeID( aBinarySequence ) ),
	mLiteralValue( mTypeID == 4 ? ExtractLiteral( aBinarySequence ) : literal_value{} ),
	mOperator( mLiteralValue ? optional_operator{} : COperator{ aBinarySequence } )
{
}

std::istream& operator>>( std::istream& aInput, CPacket& aPacket )
{
	std::string rawStringPacket;
	binary_sequence rawBinaryPacket;
	aInput >> rawStringPacket;
	for( std::size_t index = 0; index < rawStringPacket.size(); ++index )
	{
		unsigned short rawHexNumber;
		std::from_chars( rawStringPacket.data() + index, rawStringPacket.data() + index + 1, rawHexNumber, 16 );
		for( const auto& bit : ToBinarySequence( rawHexNumber, std::make_optional( static_cast< unsigned short >( 4 ) ) ) )
			rawBinaryPacket.push_back( std::move( bit ) );
	}

	CPacket packet{ rawBinaryPacket };
	std::swap( packet, aPacket );

	return aInput;
}

std::size_t CPacket::COperator::SumVersions() const
{
	std::size_t result{ 0 };
	for( const auto& packet : mPackets )
		result += packet.SumVersions();

	return result;
}

const CPacket::COperator::packets& CPacket::COperator::GetPackets() const
{
	return mPackets;
}

std::size_t CPacket::SumVersions() const
{
	std::size_t result{ mVersion };

	if( mOperator )
		result += ( *mOperator ).SumVersions();

	return result;
}

std::size_t CPacket::Operate() const
{
	std::size_t result;

	switch( mTypeID )
	{
	case 0:
	{
		result = 0;
		for( const auto& packet : ( *mOperator ).GetPackets() )
			result += packet.Operate();
		break;
	}
	case 1:
	{
		result = 1;
		for( const auto& packet : ( *mOperator ).GetPackets() )
			result *= packet.Operate();
		break;
	}
	case 2:
	{
		result = ( *mOperator ).GetPackets().front().Operate();
		for( const auto& packet : ( *mOperator ).GetPackets() )
			result = std::min( result, packet.Operate() );
		break;
	}
	case 3:
	{
		result = ( *mOperator ).GetPackets().front().Operate();
		for( const auto& packet : ( *mOperator ).GetPackets() )
			result = std::max( result, packet.Operate() );
		break;
	}
	case 5:
	{
		result = ( *mOperator ).GetPackets().front().Operate() > ( *mOperator ).GetPackets().back().Operate();
		break;
	}
	case 6:
	{
		result = ( *mOperator ).GetPackets().front().Operate() < ( *mOperator ).GetPackets().back().Operate();
		break;
	}
	case 7:
	{
		result = ( *mOperator ).GetPackets().front().Operate() == ( *mOperator ).GetPackets().back().Operate();
		break;
	}
	default:
	{
		result = static_cast< std::size_t >( *mLiteralValue );
		break;
	}
	}

	return result;
}

namespace
{

binary_sequence ToBinarySequence( unsigned short aNumber, std::optional<unsigned short> aDigits )
{
	binary_sequence result;

	while( ( aDigits && result.size() < aDigits ) || aNumber > 0 )
	{
		result.push_front( aNumber % 2 );
		aNumber /= 2;
	}

	return result;
}

CPacket::literal_value::value_type ToValue( const binary_sequence& aBinaryDeque )
{
	CPacket::literal_value::value_type result{ 0 };

	for( auto binIt = aBinaryDeque.crbegin(); binIt != aBinaryDeque.crend(); ++binIt )
		if( *binIt )
			result += static_cast< CPacket::literal_value::value_type >( std::pow( 2, std::distance( aBinaryDeque.crbegin(), binIt ) ) );
	return result;
}

CPacket::version ExtractVersion( binary_sequence& aBinaryPacket )
{
	CPacket::version result{ 0 };

	for( short power = 2; power >= 0; --power )
	{
		if( aBinaryPacket.front() )
			result += static_cast< CPacket::version >( std::pow( 2, power ) );
		aBinaryPacket.pop_front();
	}

	return result;
}

CPacket::type_id ExtractTypeID( binary_sequence& aBinaryPacket )
{
	return ExtractVersion( aBinaryPacket );
}

CPacket::literal_value ExtractLiteral( binary_sequence& aBinaryPacket )
{
	bool isLastGroup;
	binary_sequence totalGroup;
	do
	{
		isLastGroup = !aBinaryPacket.front();
		aBinaryPacket.pop_front();

		for( auto index = 0; index < 4; ++index )
		{
			totalGroup.push_back( aBinaryPacket.front() );
			aBinaryPacket.pop_front();
		}

	} while( !isLastGroup );

	return ToValue( totalGroup );
}

std::size_t ExtractSubPacketsNumber( binary_sequence& aBinaryPacket )
{
	std::size_t result{ 0 };

	for( auto power = 10; power >= 0; --power )
	{
		if( aBinaryPacket.front() )
			result += static_cast< std::size_t >( std::pow( 2, power ) );
		aBinaryPacket.pop_front();
	}

	return result;
}

std::size_t ExtractSubPacketsLength( binary_sequence& aBinaryPacket )
{
	std::size_t result{ 0 };

	for( auto power = 14; power >= 0; --power )
	{
		if( aBinaryPacket.front() )
			result += static_cast< std::size_t >( std::pow( 2, power ) );
		aBinaryPacket.pop_front();
	}

	return result;
}

CPacket::COperator::length_type_id ExtractLengthTypeID( binary_sequence& aBinaryPacket )
{
	CPacket::COperator::length_type_id result{ aBinaryPacket.front() };
	aBinaryPacket.pop_front();
	return result;
}

}