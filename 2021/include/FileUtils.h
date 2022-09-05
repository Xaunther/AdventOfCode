#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <list>

template<typename T> T CreateContainerFromFile( const std::string& aFileName );
template<typename T> T CreateFromFile( const std::string& aFileName );
template<typename T> typename std::vector<T> CreateVectorFromFile( const std::string& aFileName );
template<typename T> typename std::list<T> CreateListFromFile( const std::string& aFileName );

template<typename T> T CreateContainerFromFile( const std::string& aFileName )
{
	T result;

	std::ifstream infile;
	infile.open( aFileName );
	if( infile )
	{
		typename T::value_type input;
		while( infile >> input )
			result.emplace_back( std::move( input ) );
	}
	infile.close();

	return result;
}

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

template<typename T> typename std::vector<T> CreateVectorFromFile( const std::string& aFileName )
{
	return CreateContainerFromFile<std::vector<T>>( aFileName );
}

template<typename T> typename std::list<T> CreateListFromFile( const std::string& aFileName )
{
	return CreateContainerFromFile<std::list<T>>( aFileName );
}

#endif // FILE_UTILS_H