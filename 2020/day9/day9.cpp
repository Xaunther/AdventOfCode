//To solve day 9 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

std::vector<unsigned long long> ReadNumbers( std::string filename )
{
    std::vector<unsigned long long> numbers;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( infile.is_open() )
    {
        while( !infile.eof() )
        {
            //Reading is quite easy
            unsigned long long input_number;
            infile >> input_number;
            numbers.push_back( input_number );
        }
    }
    return numbers;
}

std::optional<unsigned long long> GetFirstNotAddingWith( std::vector<unsigned long long> const& numbers, unsigned long long const& previous )
{
    for( size_t i = previous; i < numbers.size(); i++ )
    {
        bool found = false;
        for( size_t j = i - previous; j < i - 1; j++ )
        {
            for( size_t k = j + 1; k < i; k++ )
            {
                if( numbers[ j ] + numbers[ k ] == numbers[ i ] && numbers[ j ] != numbers[ k ] )
                {
                    found = true;
                    break;
                }
            }
            if( found )
                break;
        }
        if( !found )
            return numbers[ i ];
    }
    return {};
}

std::pair<unsigned int, unsigned int> FindContiguousSetAdding( std::vector<unsigned long long> const& numbers, unsigned long long const& result )
{
    unsigned long long sum = 0;
    //We loop over all vector numbers, start already summing two
    for( unsigned int i = 0; i < numbers.size() - 1; i++ )
    {
        sum = numbers[ i ] + numbers[ i + 1 ];
        //Now we loop over the incoming ones, until we reach the result (or pass it)
        for( unsigned int j = i + 2; j < numbers.size(); j++ )
        {
            if( sum > result ) //Start again
                break;
            if( sum == result ) //Bingo
                return { i, j - 1 };
            sum += numbers[ j ];
        }
    }
    return { 0, 0 };
}

unsigned long long FindMinInRange( std::vector<unsigned long long> const& numbers, std::pair<unsigned int, unsigned int> const& range )
{
    unsigned long long result = numbers[ range.first ];
    for( unsigned int i = range.first + 1; i <= range.second; i++ )
    {
        if( numbers[ i ] < result )
            result = numbers[ i ];
    }
    return result;
}
unsigned long long FindMaxInRange( std::vector<unsigned long long> const& numbers, std::pair<unsigned int, unsigned int> const& range )
{
    unsigned long long result = numbers[ range.first ];
    for( unsigned int i = range.first + 1; i <= range.second; i++ )
    {
        if( numbers[ i ] > result )
            result = numbers[ i ];
    }
    return result;
}

unsigned long long AddMinMaxInRange( std::vector<unsigned long long> const& numbers, std::pair<unsigned int, unsigned int> const& range )
{
    return FindMinInRange( numbers, range ) + FindMaxInRange( numbers, range );
}

//Main function
int main()
{
    std::vector<unsigned long long> numbers = ReadNumbers( "C:\\Users\\alex1\\git\\AdventOfCode\\day9\\input.txt" );
    std::optional<unsigned long long> result = GetFirstNotAddingWith( numbers, 25 );
    std::pair<unsigned int, unsigned int> result2 = FindContiguousSetAdding( numbers, result.value() );

    std::cout << "Result: " << result.value() << std::endl;
    std::cout << "Result2: " << AddMinMaxInRange( numbers, result2 ) << std::endl;
    return 0;
}