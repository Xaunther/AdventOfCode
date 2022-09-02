//To solve day 11 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum class TileState
{
    floor,
    empty,
    occupied
};
TileState CharToTileState( char const s )
{
    if( s == 'L' )
        return TileState::empty;
    else if( s == '.' )
        return TileState::floor;
    else
        return TileState::occupied;
}
using SeatArray = std::vector<std::vector<TileState>>;

class SeatLayout
{
private:
    SeatArray m_seats;
    unsigned int m_epochs;
    unsigned int CountAround( TileState const seattype, unsigned int const row, unsigned int const col );
    unsigned int CountAround2( TileState const seattype, unsigned int const row, unsigned int const col );

public:
    SeatLayout() : m_epochs( 0 ) {}
    SeatLayout( std::string const filename ) : m_epochs( 0 ) { Load( filename ); }
    void Load( std::string const filename );
    bool Update();
    bool Update2();
    void AdvanceUntilStable()
    {
        while( Update() )
        {
            //std::cout << m_epochs << std::endl;
        }
    }
    void AdvanceUntilStable2()
    {
        while( Update2() )
        {
            //std::cout << m_epochs << std::endl;
        }
    }
    unsigned int CountOcuppiedSeats() const;
    unsigned int GetEpochs() const { return m_epochs; }
    void Print() const;
};

void SeatLayout::Load( std::string const filename )
{
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( infile.is_open() )
    {
        while( !infile.eof() )
        {
            std::string input_line;
            std::vector<TileState> seat_line;
            std::getline( infile, input_line );
            for( unsigned int i = 0; i < input_line.size(); i++ )
            {
                seat_line.push_back( CharToTileState( input_line[ i ] ) );
            }
            m_seats.push_back( seat_line );
        }
    }
}

bool SeatLayout::Update()
{
    //Make a copy with previous state
    SeatArray new_seats = m_seats;
    bool hasChanged = false;
    for( unsigned i = 0; i < m_seats.size(); i++ )
    {
        for( unsigned j = 0; j < m_seats[ i ].size(); j++ )
        {
            switch( m_seats[ i ][ j ] )
            {
            case TileState::empty:
                if( CountAround( TileState::occupied, i, j ) == 0 )
                {
                    new_seats[ i ][ j ] = TileState::occupied;
                    hasChanged = true;
                }
                break;
            case TileState::occupied:
                if( CountAround( TileState::occupied, i, j ) >= 4 )
                {
                    new_seats[ i ][ j ] = TileState::empty;
                    hasChanged = true;
                }
                break;
            default: break;
            }
        }
    }
    //Update
    m_seats = new_seats;
    m_epochs++;
    //Print();
    return hasChanged;
}

bool SeatLayout::Update2()
{
    //Make a copy with previous state
    SeatArray new_seats = m_seats;
    bool hasChanged = false;
    for( unsigned i = 0; i < m_seats.size(); i++ )
    {
        for( unsigned j = 0; j < m_seats[ i ].size(); j++ )
        {
            switch( m_seats[ i ][ j ] )
            {
            case TileState::empty:
                if( CountAround2( TileState::occupied, i, j ) == 0 )
                {
                    new_seats[ i ][ j ] = TileState::occupied;
                    hasChanged = true;
                }
                break;
            case TileState::occupied:
                if( CountAround2( TileState::occupied, i, j ) >= 5 )
                {
                    new_seats[ i ][ j ] = TileState::empty;
                    hasChanged = true;
                }
                break;
            default: break;
            }
        }
    }
    //Update
    m_seats = new_seats;
    m_epochs++;
    //Print();
    return hasChanged;
}

unsigned int SeatLayout::CountOcuppiedSeats() const
{
    unsigned int counter = 0;
    for( auto seat_row : m_seats )
    {
        for( auto seat : seat_row )
        {
            if( seat == TileState::occupied )
                counter++;
        }
    }
    return counter;
}

unsigned int SeatLayout::CountAround( TileState const seattype, unsigned int const row, unsigned int const col )
{
    unsigned int counter = 0;
    for( int i = int( row ) - 1; i <= int( row ) + 1; i++ )
    {
        for( int j = int( col ) - 1; j <= int( col ) + 1; j++ )
        {
            if( i < 0 || j < 0 || static_cast< unsigned int >( i ) >= m_seats.size() || static_cast< unsigned int >( j ) >= m_seats[ 0 ].size() || ( i == int( row ) && j == int( col ) ) )
                continue;
            if( m_seats[ i ][ j ] == seattype )
                counter++;
        }
    }
    //std::cout << row << ", " << col << ", " << counter << std::endl;
    return counter;
}

unsigned int SeatLayout::CountAround2( TileState const seattype, unsigned int const row, unsigned int const col )
{
    unsigned int counter = 0;
    int i, j;
    //Look on eight directions. Stop when seat is found
    //Up left
    i = int( row ) - 1;
    j = int( col ) - 1;
    while( i >= 0 && j >= 0 && static_cast< unsigned int >( i ) < m_seats.size() && static_cast< unsigned int >( j ) < m_seats[ 0 ].size() )
    {
        if( m_seats[ i ][ j ] == seattype )
        {
            counter++;
            break;
        }
        else if( m_seats[ i ][ j ] != TileState::floor )
            break;
        i--;
        j--;
    }
    //Up
    i = int( row ) - 1;
    j = int( col );
    while( i >= 0 && j >= 0 && static_cast< unsigned int >( i ) < m_seats.size() && static_cast< unsigned int >( j ) < m_seats[ 0 ].size() )
    {
        if( m_seats[ i ][ j ] == seattype )
        {
            counter++;
            break;
        }
        else if( m_seats[ i ][ j ] != TileState::floor )
            break;
        i--;
    }
    //Up right
    i = int( row ) - 1;
    j = int( col ) + 1;
    while( i >= 0 && j >= 0 && static_cast< unsigned int >( i ) < m_seats.size() && static_cast< unsigned int >( j ) < m_seats[ 0 ].size() )
    {
        if( m_seats[ i ][ j ] == seattype )
        {
            counter++;
            break;
        }
        else if( m_seats[ i ][ j ] != TileState::floor )
            break;
        i--;
        j++;
    }
    //Right
    i = int( row );
    j = int( col ) + 1;
    while( i >= 0 && j >= 0 && static_cast< unsigned int >( i ) < m_seats.size() && static_cast< unsigned int >( j ) < m_seats[ 0 ].size() )
    {
        if( m_seats[ i ][ j ] == seattype )
        {
            counter++;
            break;
        }
        else if( m_seats[ i ][ j ] != TileState::floor )
            break;
        j++;
    }
    //Down right
    i = int( row ) + 1;
    j = int( col ) + 1;
    while( i >= 0 && j >= 0 && static_cast< unsigned int >( i ) < m_seats.size() && static_cast< unsigned int >( j ) < m_seats[ 0 ].size() )
    {
        if( m_seats[ i ][ j ] == seattype )
        {
            counter++;
            break;
        }
        else if( m_seats[ i ][ j ] != TileState::floor )
            break;
        i++;
        j++;
    }
    //Down
    i = int( row ) + 1;
    j = int( col );
    while( i >= 0 && j >= 0 && static_cast< unsigned int >( i ) < m_seats.size() && static_cast< unsigned int >( j ) < m_seats[ 0 ].size() )
    {
        if( m_seats[ i ][ j ] == seattype )
        {
            counter++;
            break;
        }
        else if( m_seats[ i ][ j ] != TileState::floor )
            break;
        i++;
    }
    //Down left
    i = int( row ) + 1;
    j = int( col ) - 1;
    while( i >= 0 && j >= 0 && static_cast< unsigned int >( i ) < m_seats.size() && static_cast< unsigned int >( j ) < m_seats[ 0 ].size() )
    {
        if( m_seats[ i ][ j ] == seattype )
        {
            counter++;
            break;
        }
        else if( m_seats[ i ][ j ] != TileState::floor )
            break;
        i++;
        j--;
    }
    //Left
    i = int( row );
    j = int( col ) - 1;
    while( i >= 0 && j >= 0 && static_cast< unsigned int >( i ) < m_seats.size() && static_cast< unsigned int >( j ) < m_seats[ 0 ].size() )
    {
        if( m_seats[ i ][ j ] == seattype )
        {
            counter++;
            break;
        }
        else if( m_seats[ i ][ j ] != TileState::floor )
            break;
        j--;
    }
    return counter;
}

void SeatLayout::Print() const
{
    for( auto seat_row : m_seats )
    {
        for( auto seat : seat_row )
        {
            std::cout << ( int )seat << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "====" << std::endl;
}

//Main function
int main()
{
    SeatLayout seats( "C:\\Users\\alex1\\git\\AdventOfCode\\day11\\input.txt" );
    SeatLayout seats2 = seats;
    //Advance until stable and count
    seats.AdvanceUntilStable();
    unsigned int result = seats.CountOcuppiedSeats();

    //Second part, advance and count with new rules
    seats2.AdvanceUntilStable2();
    unsigned int result2 = seats2.CountOcuppiedSeats();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}