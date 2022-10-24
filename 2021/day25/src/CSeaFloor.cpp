#include "CSeaFloor.h"

#include <ranges>

std::istream& operator>>( std::istream& aInput, CSeaFloor& aSeaFloor )
{
	CSeaFloor::sea_cucumber::first_type rowIndex{ 0 };
	CSeaFloor::sea_cucumber::second_type colIndex{ 0 };
	for( const auto& line : std::ranges::istream_view<std::string>( aInput ) )
	{
		for( const auto& element : line )
		{
			switch( element )
			{
			case 'v':
				aSeaFloor.mSouthSeaCucumbers.emplace( rowIndex, colIndex );
				break;
			case '>':
				aSeaFloor.mEastSeaCucumbers.emplace( rowIndex, colIndex );
			}
			++colIndex;
		}
		aSeaFloor.mSize.second = colIndex;
		colIndex = 0;
		++rowIndex;
	}
	aSeaFloor.mSize.first = rowIndex;

	return aInput;
}

const CSeaFloor::sea_cucumbers& CSeaFloor::GetEastSeaCucumbers() const
{
	return mEastSeaCucumbers;
}

const CSeaFloor::sea_cucumbers& CSeaFloor::GetSouthSeaCucumbers() const
{
	return mSouthSeaCucumbers;
}

const CSeaFloor::size& CSeaFloor::GetSize() const
{
	return mSize;
}

const std::size_t& CSeaFloor::GetSteps() const
{
	return mSteps;
}

const std::size_t& CSeaFloor::MoveUntilStalled()
{
	bool changes;
	do
	{
		++mSteps;
		changes = false;

		//First move east
		{
			auto newEastSeaCucumbers = MoveEast();
			changes |= ( mEastSeaCucumbers != newEastSeaCucumbers );
			mEastSeaCucumbers = std::move( newEastSeaCucumbers );
		}

		//Then south
		{
			auto newSouthSeaCucumbers = MoveSouth();
			changes |= ( mSouthSeaCucumbers != newSouthSeaCucumbers );
			mSouthSeaCucumbers = std::move( newSouthSeaCucumbers );
		}

	} while( changes );

	return GetSteps();
}

CSeaFloor::sea_cucumbers CSeaFloor::MoveEast() const
{
	sea_cucumbers result;

	for( const auto& eastSeaCucumber : mEastSeaCucumbers )
	{
		sea_cucumber movedSeaCucumber{ eastSeaCucumber.first, static_cast< sea_cucumber::second_type >( ( eastSeaCucumber.second + sea_cucumber::second_type{ 1 } ) % mSize.second ) };
		if( !mEastSeaCucumbers.contains( movedSeaCucumber ) && !mSouthSeaCucumbers.contains( movedSeaCucumber ) )
			result.insert( std::move( movedSeaCucumber ) );
		else
			result.insert( eastSeaCucumber );
	}

	return result;
}

CSeaFloor::sea_cucumbers CSeaFloor::MoveSouth() const
{
	sea_cucumbers result;

	for( const auto& southSeaCucumber : mSouthSeaCucumbers )
	{
		sea_cucumber movedSeaCucumber{ static_cast< sea_cucumber::first_type >( ( southSeaCucumber.first + 1 ) % mSize.first ), southSeaCucumber.second };
		if( !mEastSeaCucumbers.contains( movedSeaCucumber ) && !mSouthSeaCucumbers.contains( movedSeaCucumber ) )
			result.insert( std::move( movedSeaCucumber ) );
		else
			result.insert( southSeaCucumber );
	}

	return result;
}
