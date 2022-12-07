#pragma once

#include <istream>
#include <map>
#include <set>

class CDirectoryTree
{
public:
	using files = std::map<std::string, std::size_t>;
	using file = files::value_type;
	using directories = std::map<std::string, CDirectoryTree>;

	explicit CDirectoryTree( CDirectoryTree* aAboveLevel = nullptr );

	friend std::istream& operator>>( std::istream& aInput, CDirectoryTree& aDirectoryTree );

	const files& GetFiles() const;
	const directories& GetDirectories() const;
	const CDirectoryTree* GetAboveLevel() const;

	std::size_t SumDirectorySizesAboveThreshold( std::size_t& aResult, const std::size_t& aThreshold ) const;
	std::size_t SizeOfUpperBoundDirectory( std::size_t& aResult, const std::size_t& aThreshold ) const;

private:
	files mFiles;
	directories mDirectories;
	CDirectoryTree* mAboveLevel;
};