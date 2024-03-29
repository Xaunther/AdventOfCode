#pragma once

#include <istream>
#include <list>
#include <map>
#include <set>

class CMap
{
public:
	using coordinates = std::pair<int, int>;
	using beacons = std::set<coordinates>;
	using sensor = std::pair<coordinates, coordinates>;
	using sensors = std::map<coordinates, coordinates>;

	friend std::istream& operator>>( std::istream& aInput, CMap& aMap );

	const beacons& GetBeacons() const;
	const sensors& GetSensors() const;

	unsigned int CountForbiddenPositions( const int& aRow ) const;
	std::size_t TuningFrequency( const int& aMaxCoordinate ) const;

private:
	std::list<coordinates> FindReachedSegments( const int& aRow ) const;

private:
	beacons mBeacons;
	sensors mSensors;
};