#pragma once

#include <string>
#include <fstream>
#include <ranges>

/**
 * @brief Creates an object from a text file.
 * @param aFileName File name.
 * @pre The object must overload operator>>.
 *
*/
template<typename T> T CreateFromFile( const std::string& aFileName )
{
	T result;

	std::ifstream infile;
	infile.open( aFileName );
	if( infile )
		infile >> result;
	infile.close();

	return result;
}

/**
 * @brief Creates an unordered container of an object from a text file.
 * @param aFileName File name.
 * @pre The object must overload operator>>.
 * @pre The container must implement emplace_back method.
 *
*/
template<typename T> T CreateUnorderedContainerFromFile( const std::string& aFileName )
{
	T result;

	std::ifstream infile;
	infile.open( aFileName );
	if( infile )
		for( auto& object : std::ranges::istream_view<typename T::value_type>( infile ) )
			result.emplace_back( std::move( object ) );
	infile.close();

	return result;
}

/**
 * @brief Creates an ordered container of an object from a text file.
 * @param aFileName File name.
 * @pre The object must overload operator>>.
 * @pre The container must implement emplace method.
 *
*/
template<typename T> T CreateOrderedContainerFromFile( const std::string& aFileName )
{
	T result;

	std::ifstream infile;
	infile.open( aFileName );
	if( infile )
		for( auto& object : std::ranges::istream_view<typename T::value_type>( infile ) )
			result.emplace( std::move( object ) );
	infile.close();

	return result;
}