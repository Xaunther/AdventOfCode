//To solve day 24 puzzle
#include <iostream>
#include <fstream>
#include <string>

using Keys = std::pair<uint64_t, uint64_t>;

Keys ReadKeys( std::string const& filename )
{
    Keys keys;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( !infile.is_open() )
        return keys;

    // Each key into its spot
    infile >> keys.first;
    infile >> keys.second;
    infile.close();
    return keys;
}

uint64_t DoLoop( uint64_t key, uint64_t const& subject_number, uint64_t const& divider_number )
{
    key = key * subject_number;
    key = key % divider_number;
    //std::cout << key << std::endl;
    return key;
}

uint64_t GetLoopSize( uint64_t const& key, uint64_t const& subject_number, uint64_t const& divider_number )
{
    uint64_t number = 1;
    uint64_t loop_size = 0;
    while( number != key )
    {
        number = DoLoop( number, subject_number, divider_number );
        loop_size++;
    }
    return loop_size;
}

Keys GetLoopSizes( Keys const& keys, uint64_t const& subject_number, uint64_t const& divider_number )
{
    Keys loop_sizes;
    loop_sizes.first = GetLoopSize( keys.first, subject_number, divider_number );
    loop_sizes.second = GetLoopSize( keys.second, subject_number, divider_number );
    return loop_sizes;
}

uint64_t DoNLoops( uint64_t key, uint64_t const& N, uint64_t const& subject_number, uint64_t const& divider_number )
{
    for( unsigned int i = 0; i < N; i++ )
    {
        key = DoLoop( key, subject_number, divider_number );
    }
    return key;
}

int main()
{
    //Read the public keys
    auto keys = ReadKeys( "C:\\Users\\alex1\\git\\AdventOfCode\\day25\\input.txt" );
    //Get the secret loop sizes
    auto loop_sizes = GetLoopSizes( keys, 7, 20201227 );
    //Use one of the keys as subject number, use loop size of the other. Start by 1
    auto result = DoNLoops( 1, loop_sizes.second, keys.first, 20201227 );

    std::cout << "Result: " << result << std::endl;

    return 0;
}