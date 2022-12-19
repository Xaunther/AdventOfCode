#pragma once

#include <iostream>
#include <vector>

class CWinds
{
public:
	using winds = std::vector<bool>;

	friend std::istream& operator>>( std::istream& aInput, CWinds& aWinds );

	const winds& GetWinds() const;

private:
	winds mWinds;
};