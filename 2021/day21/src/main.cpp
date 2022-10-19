#include <iostream>
#include <string>

#include "year.h"
#include "day.h"

#include "CDeterministicDie.h"
#include "CDiracDie.h"
#include "CGame.h"
#include "FileUtils.h"

namespace
{

using namespace std::literals;

static const std::string INPUT_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/input.txt";
static const std::string EXAMPLE_FILE_NAME = "../../../../" + YEAR + "/" + DAY + "/example.txt";

std::size_t Part1( const std::string& aFileName );
std::size_t Part2( const std::string& aFileName );

}

int main()
{
	std::cout << "Part 1 example: " << Part1( EXAMPLE_FILE_NAME ) << std::endl;
	std::cout << "Part 1 solution: " << Part1( INPUT_FILE_NAME ) << std::endl;
	std::cout << "Part 2 example: " << Part2( EXAMPLE_FILE_NAME ) << std::endl;
	std::cout << "Part 2 solution: " << Part2( INPUT_FILE_NAME ) << std::endl;
	return 0;
}

namespace
{

std::size_t Part1( const std::string& aFileName )
{
	std::ifstream input;
	input.open( aFileName );
	std::string basura;
	CGame::CPlayerState::position p1Start;
	input >> basura >> basura >> basura >> basura >> p1Start;
	CGame::CPlayerState::position p2Start;
	input >> basura >> basura >> basura >> basura >> p2Start;
	input.close();

	CDeterministicDie die;
	CGame game{ 10, 1000, CGame::state{ { { CGame::CPlayerState{ p1Start }, CGame::CPlayerState{ p2Start } }, 1 } } };
	game.Play( die );
	return game.GetLowestScore() * die.GetRollCount();
}

std::size_t Part2( const std::string& aFileName )
{
	std::ifstream input;
	input.open( aFileName );
	std::string basura;
	CGame::CPlayerState::position p1Start;
	input >> basura >> basura >> basura >> basura >> p1Start;
	CGame::CPlayerState::position p2Start;
	input >> basura >> basura >> basura >> basura >> p2Start;
	input.close();

	CDiracDie die;
	CGame game{ 10, 21, CGame::state{ { { CGame::CPlayerState{ p1Start }, CGame::CPlayerState{ p2Start } }, 1 } } };
	game.Play( die );
	return game.GetMostWins();
}

}