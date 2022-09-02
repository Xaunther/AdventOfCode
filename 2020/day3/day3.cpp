//To solve day 2 puzzle
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//Watch-out, first term of vector is for y-axis and second is for x-axis position
class WorldMap
{
    //Members
private:
    std::vector<std::vector<bool>> m_map;
    std::pair<unsigned int, unsigned int> m_position;

public:
    //Functions
    WorldMap() : m_position{ 0, 0 }
    {
    }
    //Move character
    bool Move( std::pair<int, int> const coords )
    {
        if( m_map.size() > 0 && m_map[ 0 ].size() > 0 )
        {
            m_position.first += coords.first;
            m_position.second = ( coords.second + m_position.second ) % m_map[ 0 ].size();
        }

        //Return false if out of bounds on y-axis
        if( m_position.first >= m_map.size() )
            return false;
        else
            return true;
    }
    //Setters
    void SetMap( std::vector<std::vector<bool>> _map ) { m_map = _map; }
    void SetPos( std::pair<int, int> _pos ) { m_position = _pos; }

    //Check if it is in a tree
    bool InTree() const { return m_map[ m_position.first ][ m_position.second ]; }
};

WorldMap ReadWorldMap( std::string filename )
{
    std::vector<std::vector<bool>> readmap;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( infile.is_open() )
    {
        while( !infile.eof() )
        {
            std::string input_thing;
            std::vector<bool> mapline;
            infile >> input_thing;
            for( unsigned int i = 0; i < input_thing.size(); i++ )
            {
                if( input_thing[ i ] == '.' )
                    mapline.push_back( false );
                else
                    mapline.push_back( true );
            }

            readmap.push_back( mapline );
        }
    }

    //Return world map
    WorldMap readworldmap;
    readworldmap.SetMap( readmap );
    return readworldmap;
}

int CountTrees( WorldMap& worldmap, std::pair<int, int> const& movement )
{
    int counter = 0;
    while( worldmap.Move( movement ) )
    {
        counter += ( int )worldmap.InTree();
    }
    return counter;
}

//Product of elements in vector
template <typename T>
T VecProd( std::vector<T> const& v )
{
    T result = 1;
    for( auto element = v.begin(); element != v.end(); ++element )
    {
        result *= *element;
    }
    return result;
}

//Main function
int main()
{
    WorldMap worldmap = ReadWorldMap( "C:\\Users\\alex1\\git\\AdventOfCode\\day3\\input.txt" );
    int N_trees = CountTrees( worldmap, { 1, 3 } );
    //Do what is being requested with different patterns
    std::vector<int> N_tree_vector;
    for( int i = 1; i < 8; i = i + 2 )
    {
        worldmap.SetPos( { 0, 0 } );
        N_tree_vector.push_back( CountTrees( worldmap, { 1, i } ) );
    }
    worldmap.SetPos( { 0, 0 } );
    N_tree_vector.push_back( CountTrees( worldmap, { 2, 1 } ) );

    std::cout << "Result: " << N_trees << std::endl;
    std::cout << "Result2: " << VecProd( N_tree_vector ) << std::endl;
    return 0;
}