#include "CDisplay.h"

#include <algorithm>
#include <iterator>
#include <functional>

#include <iostream>
namespace
{

const CDigit::digit& GetDigitWithSize( const CDisplay::reference_digits& aDigits, const unsigned int& aSize );

}


std::istream& operator>>( std::istream& aInput, CDisplay& aDisplay )
{
	for( auto& referenceDigit : aDisplay.mReference )
	{
		CDigit digit;
		aInput >> digit;
		referenceDigit = std::move( digit );
	}

	aInput.ignore( 3 );

	for( auto& outputDigit : aDisplay.mOutput )
	{
		CDigit digit;
		aInput >> digit;
		outputDigit = std::move( digit );
	}

	aDisplay.Solve();
	return aInput;
}

const CDisplay::reference_digits& CDisplay::GetReference() const
{
	return mReference;
}

const CDisplay::output_digits& CDisplay::GetOutput() const
{
	return mOutput;
}

const CDisplay::solution& CDisplay::GetSolution() const
{
	return mSolution;
}

unsigned int CDisplay::CountUniqueOutputs() const
{
	return static_cast< unsigned int >( std::count_if( mOutput.cbegin(), mOutput.cend(), std::mem_fn( &CDigit::IsUnique ) ) );
}

unsigned int CDisplay::SolveOutput() const
{
	return 1000 * mSolution.at( mOutput[ 0 ].GetDigit() ) + 100 * mSolution.at( mOutput[ 1 ].GetDigit() ) + 10 * mSolution.at( mOutput[ 2 ].GetDigit() ) + mSolution.at( mOutput[ 3 ].GetDigit() );
}

void CDisplay::Solve()
{
	// Unique numbers
	mInverseSolution[ 1 ] = mSolution.emplace( GetDigitWithSize( mReference, 2 ), 1 ).first->first;
	mInverseSolution[ 4 ] = mSolution.emplace( GetDigitWithSize( mReference, 4 ), 4 ).first->first;
	mInverseSolution[ 7 ] = mSolution.emplace( GetDigitWithSize( mReference, 3 ), 7 ).first->first;
	mInverseSolution[ 8 ] = mSolution.emplace( GetDigitWithSize( mReference, 7 ), 8 ).first->first;
	// Solvable with unique
	for( const auto& digit : mReference )
	{
		if( digit.GetDigit().size() == 6 && std::includes( digit.GetDigit().cbegin(), digit.GetDigit().cend(), mInverseSolution[ 1 ].cbegin(), mInverseSolution[ 1 ].cend() ) )
		{
			if( std::includes( digit.GetDigit().cbegin(), digit.GetDigit().cend(), mInverseSolution[ 4 ].cbegin(), mInverseSolution[ 4 ].cend() ) )
				mInverseSolution[ 9 ] = mSolution.emplace( digit.GetDigit(), 9 ).first->first;
			else
				mInverseSolution[ 0 ] = mSolution.emplace( digit.GetDigit(), 0 ).first->first;
		}
		else if( digit.GetDigit().size() == 5 && std::includes( digit.GetDigit().cbegin(), digit.GetDigit().cend(), mInverseSolution[ 1 ].cbegin(), mInverseSolution[ 1 ].cend() ) )
			mInverseSolution[ 3 ] = mSolution.emplace( digit.GetDigit(), 3 ).first->first;
	}
	// Solvable second step
	for( const auto& digit : mReference )
		if( !mSolution.contains( digit.GetDigit() ) && digit.GetDigit().size() == 6 )
			mInverseSolution[ 6 ] = mSolution.emplace( digit.GetDigit(), 6 ).first->first;
	CDigit::digit oneAndSix;
	std::set_intersection( mInverseSolution[ 1 ].cbegin(), mInverseSolution[ 1 ].cend(), mInverseSolution[ 6 ].cbegin(), mInverseSolution[ 6 ].cend(), std::inserter( oneAndSix, oneAndSix.cbegin() ) );
	// Solvable third step
	for( const auto& digit : mReference )
	{
		if( !mSolution.contains( digit.GetDigit() ) )
		{
			if( std::includes( digit.GetDigit().cbegin(), digit.GetDigit().cend(), oneAndSix.cbegin(), oneAndSix.cend() ) )
				mInverseSolution[ 5 ] = mSolution.emplace( digit.GetDigit(), 5 ).first->first;
			else
				mInverseSolution[ 2 ] = mSolution.emplace( digit.GetDigit(), 2 ).first->first;
		}
	}

}

namespace
{

const CDigit::digit& GetDigitWithSize( const CDisplay::reference_digits& aDigits, const unsigned int& aSize )
{
	for( const auto& digit : aDigits )
		if( digit.GetDigit().size() == aSize )
			return digit.GetDigit();

	static CDigit::digit EMPTY;
	return EMPTY;
}

}