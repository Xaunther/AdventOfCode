//To solve day 24 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <array>
#include <list>
#include <math.h>

enum class Move
{
    ne,
    e,
    se,
    sw,
    w,
    nw
};

using Direction = std::list<Move>;
using Directions = std::list<Direction>;
using Position = std::array<int, 2>;
using Tile = std::pair<Position, bool>;
using Tiles = std::map<Position, bool>;

Direction StringToDirection( std::string const& str )
{
    Direction direction;
    for( size_t i = 0; i < str.size(); i++ )
    {
        switch( str[ i ] )
        {
        case 'e':
            direction.push_back( Move::e );
            break;
        case 'w':
            direction.push_back( Move::w );
            break;
        case 'n':
            if( str[ i + 1 ] == 'e' )
                direction.push_back( Move::ne );
            else
                direction.push_back( Move::nw );
            i++;
            break;
        case 's':
            if( str[ i + 1 ] == 'e' )
                direction.push_back( Move::se );
            else
                direction.push_back( Move::sw );
            i++;
            break;
        }
    }
    return direction;
}

Directions ReadDirections( std::string const& filename )
{
    Directions directions;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( !infile.is_open() )
        return directions;

    // Just one line, transform string into digits
    std::string input_thing;
    std::getline( infile, input_thing );
    while( input_thing != "" )
    {
        //Split ingredients and allergens
        directions.push_back( StringToDirection( input_thing ) );
        input_thing = "";
        std::getline( infile, input_thing );
    }
    infile.close();
    return directions;
}

Position MoveToVec( Move const& move )
{
    switch( move )
    {
    case Move::ne:
        return { 1, 1 };
    case Move::e:
        return { 2, 0 };
    case Move::se:
        return { 1, -1 };
    case Move::sw:
        return { -1, -1 };
    case Move::w:
        return { -2, 0 };
    case Move::nw:
        return { -1, 1 };
    default:
        return { 0, 0 };
    }
}

Position VecSum( Position const& v1, Position const& v2 )
{
    Position result = { 0, 0 };
    for( unsigned int i = 0; i < v1.size(); i++ )
        result[ i ] = v1[ i ] + v2[ i ];
    return result;
}

void AddTile( Tiles& tiles, Direction const& direction )
{
    //Initialize position
    Position position = { 0, 0 };
    for( auto& move : direction )
        position = VecSum( position, MoveToVec( move ) );
    //Change tile status
    if( tiles.find( position ) != tiles.end() )
        tiles[ position ] = !tiles[ position ]; //Flip
    else
        tiles[ position ] = true;
}

uint32_t CountTiles( Tiles const& tiles )
{
    uint32_t result = 0;
    for( auto tile : tiles )
        result += ( int )tile.second;
    return result;
}

Tiles MakeTiles( Directions const& directions )
{
    Tiles tiles;
    for( auto direction : directions )
    {
        AddTile( tiles, direction );
    }
    return tiles;
}

void Expand( Tiles& tiles, Tile const& tile )
{
    Position pos;
    pos = VecSum( tile.first, MoveToVec( Move::ne ) );
    if( tiles.find( pos ) == tiles.end() ) //If new, add with false
        tiles[ pos ] = false;
    pos = VecSum( tile.first, MoveToVec( Move::e ) );
    if( tiles.find( pos ) == tiles.end() ) //If new, add with false
        tiles[ pos ] = false;
    pos = VecSum( tile.first, MoveToVec( Move::se ) );
    if( tiles.find( pos ) == tiles.end() ) //If new, add with false
        tiles[ pos ] = false;
    pos = VecSum( tile.first, MoveToVec( Move::sw ) );
    if( tiles.find( pos ) == tiles.end() ) //If new, add with false
        tiles[ pos ] = false;
    pos = VecSum( tile.first, MoveToVec( Move::w ) );
    if( tiles.find( pos ) == tiles.end() ) //If new, add with false
        tiles[ pos ] = false;
    pos = VecSum( tile.first, MoveToVec( Move::nw ) );
    if( tiles.find( pos ) == tiles.end() ) //If new, add with false
        tiles[ pos ] = false;
}

void Expand( Tiles& tiles )
{
    Tiles old_tiles = tiles;
    for( auto& tile : old_tiles )
    {
        Expand( tiles, tile );
    }
}

uint32_t CountAround( Tiles& tiles, Position const& pos )
{
    uint32_t result = 0;
    Position p;
    p = VecSum( pos, MoveToVec( Move::ne ) );
    result += ( int )tiles[ p ];
    p = VecSum( pos, MoveToVec( Move::e ) );
    result += ( int )tiles[ p ];
    p = VecSum( pos, MoveToVec( Move::se ) );
    result += ( int )tiles[ p ];
    p = VecSum( pos, MoveToVec( Move::sw ) );
    result += ( int )tiles[ p ];
    p = VecSum( pos, MoveToVec( Move::w ) );
    result += ( int )tiles[ p ];
    p = VecSum( pos, MoveToVec( Move::nw ) );
    result += ( int )tiles[ p ];
    return result;
}

void Update( Tiles& tiles, Position const& pos, Tiles& old_tiles )
{
    //Count how many black tiles around
    uint32_t blacks = CountAround( old_tiles, pos );

    //If black
    if( old_tiles[ pos ] )
    {
        if( blacks == 0 || blacks > 2 )
            tiles[ pos ] = !tiles[ pos ]; //Flip
    }
    else
    {
        if( blacks == 2 )
            tiles[ pos ] = !tiles[ pos ]; //Flip
    }
}

void Update( Tiles& tiles )
{
    //For each entry in the dictionary, check what's around and update
    //This will automatically create new entries around existing tiles :)
    //We also need to copy the original map
    Tiles old_tiles = tiles;
    for( auto& tile : tiles )
        Update( tiles, tile.first, old_tiles );
}

void Update( Tiles& tiles, uint32_t const N )
{
    for( uint32_t i = 0; i < N; i++ )
    {
        Expand( tiles ); //Add adjacent tiles to map (they may be flipped too)
        Update( tiles ); //Update acoording to rules
    }
}

int main()
{
    //Read the directions
    auto directions = ReadDirections( "C:\\Users\\alex1\\git\\AdventOfCode\\day24\\input.txt" );
    //Get the positions mentioned by the map, with their status
    auto tiles = MakeTiles( directions );

    //Count true tiles
    auto result = CountTiles( tiles );
    std::cout << "Result: " << result << std::endl;

    //Now we update the tiles 100 times (days)
    Update( tiles, 100 );

    auto result2 = CountTiles( tiles );
    std::cout << "Result2: " << result2 << std::endl;

    return 0;
}