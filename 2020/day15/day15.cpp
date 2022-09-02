//To solve day 15 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

using Game = std::pair<std::pair<uint32_t, uint64_t>, std::map<uint32_t, uint64_t>>;

std::list<std::string> SplitString( std::string const s, std::string const pattern )
{
    if( s.find( pattern ) == std::string::npos )
        return { s };

    std::list<std::string> s_list;
    size_t i = 0;
    while( s.find( pattern, i ) != std::string::npos )
    {
        s_list.push_back( s.substr( i, s.find( pattern, i ) - i ) );
        i = s.find( pattern, i ) + 1;
    }
    //Add last
    s_list.push_back( s.substr( i ) );
    return s_list;
}

Game ListStringToGame( std::list<std::string> const& str_v )
{
    Game game;
    uint32_t i = 0;
    for( auto str_el = str_v.begin(), j = --str_v.end(); str_el != j; ++str_el )
    {
        i++;
        game.second[ uint32_t( std::stoi( *str_el ) ) ] = i;
        game.first = { uint32_t( std::stoi( *str_el ) ), i };
    }
    game.first = { uint32_t( std::stoi( *--str_v.end() ) ), i + 1 };
    return game;
}
Game ReadGame( std::string const& filename )
{
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( infile.is_open() )
    {
        std::string input_thing;
        std::getline( infile, input_thing );
        auto str_numbers = SplitString( input_thing, "," );
        infile.close();
        return ListStringToGame( str_numbers );
    }

    return {};
}

uint32_t FindSameAsLastNumber( std::list<uint32_t> const& numbers )
{
    size_t _size = numbers.size();
    size_t i = _size;
    uint32_t _last = 0;

    for( auto number = numbers.rbegin(); number != numbers.rend(); ++number )
    {
        if( number == numbers.rbegin() )
        {
            _last = *number;
            continue;
        }
        i--;
        if( *number == _last )
        {
            return int( _size - i );
        }
    }
    return 0;
}

void PlayGame( Game& game, uint64_t const steps )
{
    for( uint64_t i = 0; game.first.second < steps; i++ )
    {
        if( game.second.find( game.first.first ) != game.second.end() ) //This number was there before
        {
            uint32_t thisN = game.first.first;
            game.first = { uint32_t( game.first.second - game.second[ game.first.first ] ), game.first.second + 1 };
            game.second[ thisN ] = game.first.second - 1;
            //std::cout << "O: " << game.first.first << ", " << game.first.second << std::endl;
        }
        else //New number
        {
            game.second[ game.first.first ] = game.first.second;
            game.first = { 0, game.first.second + 1 };
            //std::cout << "N: " << game.first.first << ", " << game.first.second << std::endl;
        }
    }
}

//Main function
int main()
{

    auto game = ReadGame( "C:\\Users\\alex1\\git\\AdventOfCode\\day15\\input.txt" );
    PlayGame( game, 2020 );
    std::cout << "Result: " << game.first.first << std::endl;
    PlayGame( game, 30000000 );
    std::cout << "Result2: " << game.first.first << std::endl;
    return 0;
}