#include "CChecker.h"

namespace
{

CChecker::alus CalculatePossibleAlus( const CChecker::alus& aAlus, const CInstruction& aInstruction, const bool aKeepMax );
CChecker::alus CalculatePossibleAlus( const CChecker::alus::value_type& aAluModelNumber, const CInstruction& aInstruction );

CChecker::alus Inp( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA );
CChecker::alus Add( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB );
CChecker::alus Mul( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB );
CChecker::alus Div( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB );
CChecker::alus Mod( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB );
CChecker::alus Eql( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB );

}

CChecker::CChecker():
	mAlus( { { CAlu{}, CModelNumber{} } } )
{
}

void CChecker::Check( const instructions& aInstructions, const bool aKeepMax )
{
	std::size_t index = 0;
	for( const auto& instruction : aInstructions )
		mAlus = CalculatePossibleAlus( mAlus, instruction, aKeepMax );
}

CModelNumber CChecker::GetMaximumValidNumber() const
{
	CModelNumber result;
	for( const auto& alu : mAlus )
		if( alu.first.GetNumber( CAlu::NUMBER::Z ) == 0 )
			result = std::max( alu.second, result );
	return result;
}

CModelNumber CChecker::GetMinimumValidNumber() const
{
	CModelNumber result{ 9,9,9,9,9,9,9,9,9,9,9,9,9,9 };
	for( const auto& alu : mAlus )
		if( alu.first.GetNumber( CAlu::NUMBER::Z ) == 0 )
			result = std::min( alu.second, result );
	return result;
}

namespace
{

CChecker::alus CalculatePossibleAlus( const CChecker::alus& aAlus, const CInstruction& aInstruction, const bool aKeepMax )
{
	CChecker::alus result;

	for( const auto& aluModelNumber : aAlus )
	{
		auto resultAlus = CalculatePossibleAlus( aluModelNumber, aInstruction );
		//Combine and keep highest or lowest model number
		for( auto& resultAlu : resultAlus )
		{
			const auto& found = result.find( resultAlu.first );
			if( found == result.end() )
				result.emplace( std::move( resultAlu ) );
			else
			{
				if( aKeepMax )
					( *found ).second = std::max( ( *found ).second, resultAlu.second );
				else
					( *found ).second = std::min( ( *found ).second, resultAlu.second );
			}
		}
	}

	return result;
}

CChecker::alus CalculatePossibleAlus( const CChecker::alus::value_type& aAluModelNumber, const CInstruction& aInstruction )
{
	switch( aInstruction.GetType() )
	{
	case CInstruction::TYPE::INP:
		return Inp( aAluModelNumber, aInstruction.GetArguments().first );
	case CInstruction::TYPE::ADD:
		if( ( *aInstruction.GetArguments().second ).index() == 0 )
			return Add( aAluModelNumber, aInstruction.GetArguments().first, aAluModelNumber.first.GetNumber( std::get<CAlu::NUMBER>( *aInstruction.GetArguments().second ) ) );
		else
			return Add( aAluModelNumber, aInstruction.GetArguments().first, std::get<int>( *aInstruction.GetArguments().second ) );
	case CInstruction::TYPE::MUL:
		if( ( *aInstruction.GetArguments().second ).index() == 0 )
			return Mul( aAluModelNumber, aInstruction.GetArguments().first, aAluModelNumber.first.GetNumber( std::get<CAlu::NUMBER>( *aInstruction.GetArguments().second ) ) );
		else
			return Mul( aAluModelNumber, aInstruction.GetArguments().first, std::get<int>( *aInstruction.GetArguments().second ) );
	case CInstruction::TYPE::DIV:
		if( ( *aInstruction.GetArguments().second ).index() == 0 )
			return Div( aAluModelNumber, aInstruction.GetArguments().first, aAluModelNumber.first.GetNumber( std::get<CAlu::NUMBER>( *aInstruction.GetArguments().second ) ) );
		else
			return Div( aAluModelNumber, aInstruction.GetArguments().first, std::get<int>( *aInstruction.GetArguments().second ) );
	case CInstruction::TYPE::MOD:
		if( ( *aInstruction.GetArguments().second ).index() == 0 )
			return Mod( aAluModelNumber, aInstruction.GetArguments().first, aAluModelNumber.first.GetNumber( std::get<CAlu::NUMBER>( *aInstruction.GetArguments().second ) ) );
		else
			return Mod( aAluModelNumber, aInstruction.GetArguments().first, std::get<int>( *aInstruction.GetArguments().second ) );
	case CInstruction::TYPE::EQL:
		if( ( *aInstruction.GetArguments().second ).index() == 0 )
			return Eql( aAluModelNumber, aInstruction.GetArguments().first, aAluModelNumber.first.GetNumber( std::get<CAlu::NUMBER>( *aInstruction.GetArguments().second ) ) );
		else
			return Eql( aAluModelNumber, aInstruction.GetArguments().first, std::get<int>( *aInstruction.GetArguments().second ) );
	default:
		return {};
	}
}

CChecker::alus Inp( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA )
{
	CChecker::alus result;

	for( CModelNumber::value_type digit = 1; digit < 10; ++digit )
	{
		CAlu alu = aAluModelNumber.first;
		alu[ aA ] = digit;
		CModelNumber modelNumber = aAluModelNumber.second;
		modelNumber.push_back( digit );
		result.emplace( std::move( alu ), std::move( modelNumber ) );
	}

	return result;
}

CChecker::alus Add( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB )
{
	CAlu alu = aAluModelNumber.first;
	alu[ aA ] = alu[ aA ] + aB;
	return { { std::move( alu ), aAluModelNumber.second } };
}

CChecker::alus Mul( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB )
{
	CAlu alu = aAluModelNumber.first;
	alu[ aA ] = alu[ aA ] * aB;
	return { { std::move( alu ), aAluModelNumber.second } };
}

CChecker::alus Div( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB )
{
	CAlu alu = aAluModelNumber.first;
	alu[ aA ] = alu[ aA ] / aB;
	return { { std::move( alu ), aAluModelNumber.second } };
}

CChecker::alus Mod( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB )
{
	CAlu alu = aAluModelNumber.first;
	alu[ aA ] = alu[ aA ] % aB;
	return { { std::move( alu ), aAluModelNumber.second } };
}

CChecker::alus Eql( const CChecker::alus::value_type& aAluModelNumber, const CAlu::NUMBER& aA, const int& aB )
{
	CAlu alu = aAluModelNumber.first;
	alu[ aA ] = alu[ aA ] == aB;
	return { { std::move( alu ), aAluModelNumber.second } };
}


}