#include "CDirectoryTree.h"

#include <vector>
#include <string>

namespace
{

std::vector<std::string> SplitByChar( const std::string& aWord, const char& aSplitChar );

}

std::istream& operator>>( std::istream& aInput, CDirectoryTree& aDirectoryTree )
{
	std::string inputWord;
	CDirectoryTree* currentDirectory = &aDirectoryTree;
	aInput >> inputWord;
	while( !inputWord.empty() )
	{
		aInput >> inputWord;
		if( inputWord == "cd" )
		{
			aInput >> inputWord;
			if( inputWord == "/" )
				currentDirectory = &aDirectoryTree;
			else
			{
				for( const auto& folderName : SplitByChar( inputWord, '/' ) )
				{
					if( folderName == ".." )
						currentDirectory = currentDirectory->mAboveLevel;
					else
						currentDirectory = &currentDirectory->mDirectories.at( folderName );
				}
			}
			inputWord.clear();
			aInput >> inputWord;
		}
		else
		{
			aInput >> inputWord;
			while( !inputWord.empty() && inputWord != "$" )
			{
				if( inputWord == "dir" )
				{
					aInput >> inputWord;
					currentDirectory->mDirectories.emplace( inputWord, CDirectoryTree{ currentDirectory } );
				}
				else
				{
					std::string fileName;
					aInput >> fileName;
					currentDirectory->mFiles.emplace( fileName, std::stoull( inputWord ) );
				}
				inputWord.clear();
				aInput >> inputWord;
			}
		}
	}
	return aInput;
}

CDirectoryTree::CDirectoryTree( CDirectoryTree* aAboveLevel ):
	mAboveLevel( aAboveLevel )
{
}

const CDirectoryTree::files& CDirectoryTree::GetFiles() const
{
	return mFiles;
}

const CDirectoryTree::directories& CDirectoryTree::GetDirectories() const
{
	return mDirectories;
}

const CDirectoryTree* CDirectoryTree::GetAboveLevel() const
{
	return mAboveLevel;
}

std::size_t CDirectoryTree::SumDirectorySizesAboveThreshold( std::size_t& aResult, const std::size_t& aThreshold ) const
{
	std::size_t totalSum{ 0 };

	for( const auto& file : mFiles )
		totalSum += file.second;
	for( const auto& directory : mDirectories )
		totalSum += directory.second.SumDirectorySizesAboveThreshold( aResult, aThreshold );
	if( totalSum <= aThreshold )
		aResult += totalSum;

	return totalSum;
}

std::size_t CDirectoryTree::SizeOfUpperBoundDirectory( std::size_t& aResult, const std::size_t& aThreshold ) const
{
	std::size_t totalSum{ 0 };

	for( const auto& file : mFiles )
		totalSum += file.second;
	for( const auto& directory : mDirectories )
		totalSum += directory.second.SizeOfUpperBoundDirectory( aResult, aThreshold );

	if( aResult < aThreshold || ( totalSum >= aThreshold && totalSum < aResult ) )
		aResult = totalSum;

	return totalSum;
}


namespace
{

std::vector<std::string> SplitByChar( const std::string& aWord, const char& aSplitChar )
{
	std::vector<std::string> result;

	std::size_t currentIndex = 0;
	std::size_t foundIndex;
	while( ( foundIndex = aWord.find( aSplitChar, currentIndex ) ) != std::string::npos )
	{
		result.push_back( aWord.substr( currentIndex, foundIndex - currentIndex ) );
		currentIndex = foundIndex + 1;
	}
	result.push_back( aWord.substr( currentIndex ) );

	return result;
}

}