#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <fstream>
#include <vector>

template<typename T> typename std::vector<T> CreateVectorFromFile( const std::string& aFileName );

template<typename T> typename std::vector<T> CreateVectorFromFile( const std::string& aFileName )
{
	std::vector<T> result;

	std::ifstream infile;
	infile.open( aFileName );
	if( infile )
	{
		T input;
		while( infile >> input )
			result.emplace_back( std::move( input ) );
	}
	infile.close();

	return result;
}

#endif // FILE_UTILS_H