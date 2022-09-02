//To solve day 4 puzzle
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>
#include <cmath>

class BoardingPass
{
    unsigned int m_row;
    unsigned int m_col;

public:
    void SetRow( std::string _row )
    {
        unsigned int result = 0;
        for( unsigned int i = 0; i < _row.size(); i++ )
        {
            if( _row[ i ] == 'B' )
                result += uint32_t( std::pow( 2, 6 - i ) );
        }
        m_row = result;
        return;
    }
    void SetCol( std::string _col )
    {
        unsigned int result = 0;
        for( unsigned int i = 0; i < _col.size(); i++ )
        {
            if( _col[ i ] == 'R' )
                result += uint32_t( std::pow( 2, 2 - i ) );
        }
        m_col = result;
        return;
    }
    void SetSeat( std::string seat )
    {
        SetRow( seat.substr( 0, 7 ) );
        SetCol( seat.substr( 7, 3 ) );
        return;
    }
    unsigned int SeatID() const
    {
        return m_row * 8 + m_col;
    }
};

std::vector<BoardingPass> ReadBoardingPasses( std::string filename )
{
    std::vector<BoardingPass> readlist;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( infile.is_open() )
    {
        while( !infile.eof() )
        {
            BoardingPass input_pass;
            std::string input_string;
            infile >> input_string;
            input_pass.SetSeat( input_string );
            readlist.push_back( input_pass );
        }
    }
    return readlist;
}

unsigned int MaxBoardingPassSeatID( std::vector<BoardingPass> const& boardingpasses )
{
    unsigned int max_result = 0;
    for( auto boardingpass : boardingpasses )
    {
        unsigned int result = boardingpass.SeatID();
        if( max_result < result )
            max_result = result;
    }
    return max_result;
}

bool IsSeatTaken( std::vector<BoardingPass> const& boardingpasses, unsigned int const i )
{
    for( auto boardingpass : boardingpasses )
    {
        if( i == boardingpass.SeatID() )
            return true;
    }
    return false;
}

unsigned int FindEmptySeat( std::vector<BoardingPass> const& boardingpasses )
{
    for( unsigned int i = 8; i < 1016; i++ )
    {
        if( !IsSeatTaken( boardingpasses, i ) )
        {
            if( IsSeatTaken( boardingpasses, i - 1 ) && IsSeatTaken( boardingpasses, i + 1 ) )
                return i;
        }
    }
    return 0;
}

//Main function
int main()
{
    std::vector<BoardingPass> boardingpasses = ReadBoardingPasses( "C:\\Users\\alex1\\git\\AdventOfCode\\day5\\input.txt" );
    unsigned int result = MaxBoardingPassSeatID( boardingpasses );
    unsigned int result2 = FindEmptySeat( boardingpasses );

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}