//To solve day 20 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using Cups = std::pair<std::map<size_t, size_t>, size_t>;

void Print( Cups& cups, size_t N = 1 )
{
    for( size_t i = 0; i < cups.first.size(); i++ )
    {
        std::cout << cups.first[ N ];
        N = cups.first[ N ];
    }
    std::cout << std::endl;
}

Cups StringToCups( std::string const& str, size_t const size )
{
    Cups cups;
    for( size_t i = 0; i < size - 1; i++ )
    {
        if( i < str.size() - 1 )
            cups.first[ str[ i ] - 48 ] = str[ i + 1 ] - 48;
        else if( i == str.size() - 1 )
            cups.first[ str[ i ] - 48 ] = str.size() + 1;
        else
            cups.first[ i + 1 ] = i + 2;
    }
    cups.first[ size ] = str[ 0 ] - 48;
    if( cups.first.size() > size )
        cups.second = str[ str.size() - 1 ] - 48;
    else
        cups.second = size;

    return cups;
}

Cups ReadCups( std::string const& filename, size_t size = 0 )
{
    Cups cups;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( !infile.is_open() )
        return cups;

    // Just one line, transform string into digits
    std::string input_thing;
    std::getline( infile, input_thing );
    if( size == 0 )
        size = input_thing.size();
    cups = StringToCups( input_thing, size );
    infile.close();
    return cups;
}

size_t GetNBelow( size_t const& N, std::vector<size_t> const& moving_cups, size_t const& size )
{
    size_t search_index = N - 1;
    if( search_index == 0 )
        search_index = size;
    for( size_t i = 0; i < moving_cups.size(); i++ )
    {
        auto cup = std::find( moving_cups.begin(), moving_cups.end(), search_index );
        if( cup == moving_cups.end() )
            return search_index;

        search_index--;
        if( search_index == 0 )
            search_index = size;
    }
    return search_index;
}

void PlayCups( Cups& cups, uint32_t const N_cupsmoved )
{
    //So for any Number of moved cups, we must do several changes
    //The next element to be played with is N moves away, let's get it and save it for later
    size_t new_first = cups.first[ cups.second ];
    size_t new_last = new_first;
    std::vector<size_t> moving_cups;
    for( size_t i = 0; i < N_cupsmoved; i++ )
    {
        new_first = cups.first[ new_first ];
        moving_cups.push_back( new_first );
    }
    new_first = cups.first[ new_first ];
    size_t N_below = GetNBelow( new_last, moving_cups, cups.first.size() );
    //We need to change 4 numbers in the map:
    //1) The last element being moved will now point to the value our N-1 was previously pointing to
    cups.first[ *moving_cups.rbegin() ] = cups.first[ N_below ];
    //2) The N-1(or whatever) entry number will now contain the first value being moved
    cups.first[ N_below ] = moving_cups[ 0 ];
    //3) The last element will now point to the (old) first number
    //4) The (old) first element will now point to the element 4 moves away
    if( cups.second == N_below )
    {
        cups.first[ cups.second ] = *moving_cups.begin();
        cups.first[ *moving_cups.rbegin() ] = new_last;
    }
    else
    {
        cups.first[ cups.second ] = new_last;
    }
    cups.first[ new_last ] = new_first;
    cups.second = new_last;
    return;
}

void PlayCups( Cups& cups, size_t const N_rounds, uint32_t const N_cupsmoved )
{
    //Play N rounds
    for( size_t i = 0; i < N_rounds; i++ )
    {
        PlayCups( cups, N_cupsmoved );
    }
}

uint64_t GetProduct( Cups& cups, size_t const N, size_t start )
{
    uint64_t result = 1;
    for( uint64_t i = 0; i < N; i++ )
    {
        result = result * cups.first[ start ];
        start = cups.first[ start ];
    }
    return result;
}

int main()
{
    //Read the cups
    auto cups = ReadCups( "C:\\Users\\alex1\\git\\AdventOfCode\\day23\\input.txt" );
    //Play 100 rounds
    PlayCups( cups, 100, 3 );

    std::cout << "Result: ";
    Print( cups, 1 );

    //Part two, read the cups in a different manner and replay the game
    cups = ReadCups( "C:\\Users\\alex1\\git\\AdventOfCode\\day23\\input.txt", 1000000 );
    //Play 10^7 rounds
    PlayCups( cups, 10000000, 3 );

    auto result2 = GetProduct( cups, 2, 1 );
    std::cout << "Result2: " << result2 << std::endl;

    return 0;
}