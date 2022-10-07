#include "CPaper.h"

#include <string>

namespace
{

void FoldLeft( CPaper::dots& aDots, const size_t& aX );
void FoldUp( CPaper::dots& aDots, const size_t& aY );

}

std::istream& operator>>( std::istream& aInput, CPaper& aPaper )
{
	std::string rawLine;
	while( true )
	{
		aInput >> rawLine;
		if( rawLine.find( "fold" ) != std::string::npos )
			break;
		size_t xCoordinate = std::stoi( rawLine.substr( 0, rawLine.find( "," ) ) );
		size_t yCoordinate = std::stoi( rawLine.substr( rawLine.find( "," ) + 1 ) );
		aPaper.mDots.emplace( xCoordinate, yCoordinate );
	}

	while( aInput )
	{
		aInput >> rawLine;
		aInput >> rawLine;
		if( rawLine.empty() )
			break;
		if( rawLine.substr( 0, rawLine.find( "=" ) ) == "x" )
			aPaper.mFolds.emplace_back( CPaper::E_FOLD_TYPE::X, std::stoi( rawLine.substr( rawLine.find( "=" ) + 1 ) ) );
		else
			aPaper.mFolds.emplace_back( CPaper::E_FOLD_TYPE::Y, std::stoi( rawLine.substr( rawLine.find( "=" ) + 1 ) ) );
		aInput >> rawLine;
		rawLine.clear();
	}

	return aInput;
}

std::ostream& operator<<( std::ostream& aOutput, const CPaper& aPaper )
{
	aOutput << std::endl;
	const auto& paperSize = aPaper.CalculateSize();
	for( size_t y = 0; y < paperSize.second; ++y )
	{
		for( size_t x = 0; x < paperSize.first; ++x )
		{
			if( aPaper.GetDots().contains( { x, y } ) )
				aOutput << "#";
			else
				aOutput << ".";
		}
		aOutput << std::endl;
	}
	return aOutput;
}

const CPaper::dots& CPaper::GetDots() const
{
	return mDots;
}

const CPaper::folds& CPaper::GetFolds() const
{
	return mFolds;
}

void CPaper::Fold()
{
	switch( mFolds.front().first )
	{
	case E_FOLD_TYPE::X:
		FoldLeft( mDots, mFolds.front().second );
		break;
	case E_FOLD_TYPE::Y:
		FoldUp( mDots, mFolds.front().second );
		break;
	}

	mFolds.pop_front();
}

void CPaper::FoldAll()
{
	for( ; mFolds.size() > 0; )
		Fold();
}

CPaper::coordinates CPaper::CalculateSize() const
{
	coordinates result{ 0, 0 };

	for( const auto& dot : mDots )
	{
		if( dot.first + 1 > result.first )
			result.first = dot.first + 1;
		if( dot.second + 1 > result.second )
			result.second = dot.second + 1;
	}

	return result;
}

namespace
{

void FoldLeft( CPaper::dots& aDots, const size_t& aX )
{
	for( auto dotIt = aDots.begin(); dotIt != aDots.end(); )
	{
		if( ( *dotIt ).first > aX )
		{
			aDots.emplace( 2 * aX - ( *dotIt ).first, ( *dotIt ).second );
			dotIt = aDots.erase( dotIt );
		}
		else
			++dotIt;
	}
}

void FoldUp( CPaper::dots& aDots, const size_t& aY )
{
	for( auto dotIt = aDots.begin(); dotIt != aDots.end(); )
	{
		if( ( *dotIt ).second > aY )
		{
			aDots.emplace( ( *dotIt ).first, 2 * aY - ( *dotIt ).second );
			dotIt = aDots.erase( dotIt );
		}
		else
			++dotIt;
	}
}

}