#pragma once

#include <istream>
#include <list>
#include <map>
#include <set>
#include <vector>

class CBoardMap
{
public:
	enum class EDirection
	{
		RIGHT,
		DOWN,
		LEFT,
		UP
	};

	using position = unsigned short;
	using walls = std::vector<bool>;
	using range = std::pair<position, position>;
	using row = std::pair<range, walls>;
	using board_map = std::vector<row>;

	using instruction = std::pair<position, EDirection>;
	using instructions = std::list<instruction>;

	using cube_map = std::map<std::pair<range, EDirection>, std::pair<range, EDirection>>;

	friend std::istream& operator>>( std::istream& aInput, CBoardMap& aBoardMap );

	const board_map& GetBoardMap() const;
	const instructions& GetInstructions() const;
	const cube_map& GetCubeMap() const;

	std::size_t FinalPassword() const;
	std::size_t FinalPassword2() const;

private:
	board_map mBoardMap;
	instructions mInstructions;
	cube_map mCubeMap;
};