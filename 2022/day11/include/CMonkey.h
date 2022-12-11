#pragma once

#include "COperation.h"

#include <list>
#include <vector>

class CMonkey
{
public:
	using items = std::list<std::size_t>;
	using test_outcomes = std::pair<unsigned int, unsigned int>;
	using throws = std::vector<std::pair<items::value_type, test_outcomes::first_type>>;

	friend std::istream& operator>>( std::istream& aInput, CMonkey& aMonkey );

	const unsigned int& GetDivisorTest() const;
	const unsigned int& GetInspectedItemsCount() const;

	throws PlayTurn( const unsigned int& aRelieveFactor, const unsigned int& aMonkeyProduct );
	void AddItem( const std::size_t& aItem );

private:
	items mItems;
	COperation mOperation;
	unsigned int mDivisorTest;
	test_outcomes mTestOutcomes;
	unsigned int mInspectedItemsCount = 0;
};