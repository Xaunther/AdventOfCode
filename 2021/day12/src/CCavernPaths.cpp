#include "CCavernPaths.h"

namespace
{

bool IsSmallCavern( const CCaverns::cavern& aCavern );
CCavernPaths::paths FindAllPaths( const CCavernPaths::path& aPath, const CCaverns::cavern_map& aCavernMap );
CCavernPaths::paths FindAllPaths( const CCavernPaths::path& aPath, const CCaverns::cavern_map& aCavernMap, const bool aHasVisitedSmallCaveTwice );

}

CCavernPaths::CCavernPaths( const CCaverns::cavern_map& aCavernMap, bool aVisitSmallCavesOnce ):
	mPaths( aVisitSmallCavesOnce ? FindAllPaths( { "start" }, aCavernMap ) : FindAllPaths( { "start" }, aCavernMap, false ) )
{
}

const CCavernPaths::paths& CCavernPaths::GetPaths() const
{
	return mPaths;
}

namespace
{

bool IsSmallCavern( const CCaverns::cavern& aCavern )
{
	for( const auto& letter : aCavern )
		if( letter != std::tolower( letter ) )
			return false;
	return true;
}

CCavernPaths::paths FindAllPaths( const CCavernPaths::path& aPath, const CCaverns::cavern_map& aCavernMap )
{
	CCavernPaths::paths result;

	if( aPath.back() == "end" )
		result.emplace_back( aPath );
	else
	{
		for( const auto& destination : aCavernMap.at( aPath.back() ) )
		{
			if( !IsSmallCavern( destination ) || std::find( aPath.cbegin(), aPath.cend(), destination ) == aPath.cend() )
			{
				auto nextPath = aPath;
				nextPath.emplace_back( destination );
				for( auto& foundPath : FindAllPaths( nextPath, aCavernMap ) )
					result.emplace_back( std::move( foundPath ) );
			}
		}
	}

	return result;
}

CCavernPaths::paths FindAllPaths( const CCavernPaths::path& aPath, const CCaverns::cavern_map& aCavernMap, const bool aHasVisitedSmallCaveTwice )
{
	CCavernPaths::paths result;

	if( aPath.back() == "end" )
		result.emplace_back( aPath );
	else
	{
		for( const auto& destination : aCavernMap.at( aPath.back() ) )
		{
			auto found = aPath.cend();
			const auto& isSmallCavern = IsSmallCavern( destination );
			if( !isSmallCavern || ( found = std::find( aPath.cbegin(), aPath.cend(), destination ) ) == aPath.cend() || !aHasVisitedSmallCaveTwice )
			{
				const auto& isSecondVisit = found != aPath.cend() || aHasVisitedSmallCaveTwice;
				auto nextPath = aPath;
				nextPath.emplace_back( destination );
				for( auto& foundPath : FindAllPaths( nextPath, aCavernMap, isSecondVisit ) )
					result.emplace_back( std::move( foundPath ) );
			}
		}
	}

	return result;
}

}