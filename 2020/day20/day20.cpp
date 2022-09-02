//To solve day 20 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <math.h>

enum class Rotation
{
    clockwise,
    anticlockwise
};

bool CharToBool( char const c )
{
    if( c == '#' )
        return true;
    else
        return false;
}

std::vector<bool> StringToVectorBool( std::string const& str )
{
    std::vector<bool> v;
    for( auto s : str )
        v.push_back( CharToBool( s ) );
    return v;
}

using Square = std::vector<std::vector<bool>>;

//First class, it's a square of booleans with its ID number
class Camera
{
private:
    size_t m_ID;
    Square m_square;

public:
    Camera() {}
    Camera( size_t rows, size_t cols )
    {
        m_square.resize( rows );
        for( int i = 0; i < rows; i++ )
        {
            m_square[ i ].resize( cols );
        }
    }
    void Rotate( Rotation const );
    void Flip();
    void SetID( size_t const ID ) { m_ID = ID; }
    void SetPoint( size_t const row, size_t const col, bool const val ) { m_square[ row ][ col ] = val; }
    void push_back( std::vector<bool> _line ) { m_square.push_back( _line ); }
    size_t GetID() const { return m_ID; }
    std::vector<bool> GetLine( size_t const index ) { return m_square[ index ]; }
    size_t GetSize() const { return m_square.size(); }
    bool GetValue( size_t row, size_t col ) const { return m_square[ row ][ col ]; }
    void Print();
    void Trim();
    uint64_t CountPattern();
    void CountPatternHere();
    void RemoveMonsters( std::vector<std::vector<bool>> const& pattern, size_t const row, size_t const col );
};

void Camera::RemoveMonsters( std::vector<std::vector<bool>> const& pattern, size_t const row, size_t const col )
{
    //Loop over the pattern
    for( size_t i = 0; i < pattern.size(); i++ )
    {
        for( size_t j = 0; j < pattern[ i ].size(); j++ )
        {
            if( !pattern[ i ][ j ] )
                continue;
            else if( !m_square[ row + i ][ col + j ] )
                return;
        }
    }

    //If we reached this point it means we found a monster, time to remove it from the map now
    //Loop over the pattern again
    for( size_t i = 0; i < pattern.size(); i++ )
    {
        for( size_t j = 0; j < pattern[ i ].size(); j++ )
        {
            if( pattern[ i ][ j ] )
                m_square[ row + i ][ col + j ] = false;
        }
    }
    return;
}

void Camera::CountPatternHere()
{
    //The pattern is like this
    std::vector<std::string> str_pattern;
    str_pattern.push_back( "                  # " );
    str_pattern.push_back( "#    ##    ##    ###" );
    str_pattern.push_back( " #  #  #  #  #  #   " );
    std::vector<std::vector<bool>> pattern;
    for( auto& p : str_pattern )
        pattern.push_back( StringToVectorBool( p ) );

    //Once done, we search line by line
    for( size_t i = 0; i < m_square.size() - pattern.size() + 1; i++ )
    {
        //We search from the beginning
        for( size_t j = 0; j < m_square[ i ].size() - pattern[ 0 ].size() + 1; j++ )
        {
            //In each search, we loop and try to see if this pattern matches
            RemoveMonsters( pattern, i, j );
        }
    }
}

uint64_t Camera::CountPattern()
{
    //Try all orientations
    for( int i = 0; i < 2; i++ )
    {
        for( int j = 0; j < 4; j++ )
        {
            CountPatternHere();
            Rotate( Rotation::clockwise );
        }
        Flip();
    }
    //Sum all remaining trues
    uint64_t result = 0;
    for( auto row : m_square )
    {
        for( auto b : row )
            result += b;
    }
    return result;
}

void Camera::Trim()
{
    Square new_square;
    new_square.resize( m_square.size() - 2 );
    for( size_t i = 0; i < new_square.size(); i++ )
    {
        new_square[ i ].resize( m_square[ i ].size() - 2 );
    }
    for( size_t i = 1; i < m_square.size() - 1; i++ )
    {
        for( size_t j = 1; j < m_square[ i ].size() - 1; j++ )
        {
            new_square[ i - 1 ][ j - 1 ] = m_square[ i ][ j ];
        }
    }
    //Update
    m_square = new_square;
    return;
}

void Camera::Print()
{
    for( auto a : m_square )
    {
        for( auto b : a )
        {
            if( b )
                std::cout << "#";
            else
                std::cout << ".";
        }
        std::cout << std::endl;
    }
}

void Camera::Rotate( Rotation const orientation )
{
    Square new_square = m_square;
    if( orientation == Rotation::clockwise )
    {
        for( auto i = 0; i < m_square.size(); i++ )
        {
            for( auto j = 0; j < m_square[ i ].size(); j++ )
            {
                new_square[ j ][ m_square.size() - 1 - i ] = m_square[ i ][ j ];
            }
        }
    }
    else
    {
        for( auto i = 0; i < m_square.size(); i++ )
        {
            for( auto j = 0; j < m_square[ i ].size(); j++ )
            {
                new_square[ m_square.size() - 1 - j ][ i ] = m_square[ i ][ j ];
            }
        }
    }
    m_square = new_square;
}

void Camera::Flip()
{
    Square new_square = m_square;
    for( auto i = 0; i < m_square.size(); i++ )
    {
        for( auto j = 0; j < m_square[ i ].size(); j++ )
        {
            new_square[ i ][ m_square.size() - 1 - j ] = m_square[ i ][ j ];
        }
    }
    m_square = new_square;
}

//Collection of cameras
class BigCamera
{
public:
    std::vector<std::vector<Camera>> m_cameras;

    BigCamera() {}
    void Rotate( Rotation const );
    void Flip();
    Camera MergeCameras();
};

Camera BigCamera::MergeCameras()
{
    uint64_t len = m_cameras.size() * ( m_cameras[ 0 ][ 0 ].GetSize() - 2 );
    Camera camera( len, len );
    std::vector<bool> line;
    int x_sq = 0;
    int y_sq = 0;
    for( auto v_cam = m_cameras.begin(); v_cam != m_cameras.end(); ++v_cam )
    {
        for( auto cam = v_cam->begin(); cam != v_cam->end(); ++cam )
        {
            cam->Trim();
            //cam->Print();
            for( size_t i = 0; i < cam->GetSize(); i++ )
            {
                for( size_t j = 0; j < cam->GetSize(); j++ )
                {
                    camera.SetPoint( x_sq * cam->GetSize() + i, y_sq * cam->GetSize() + j, cam->GetValue( i, j ) );
                }
            }
            y_sq++;
        }
        x_sq++;
    }
    return camera;
}

void BigCamera::Rotate( Rotation const direction )
{
    for( auto& v_cam : m_cameras )
    {
        for( auto& cam : v_cam )
        {
            cam.Rotate( direction );
        }
    }
}
void BigCamera::Flip()
{
    for( auto& v_cam : m_cameras )
    {
        for( auto& cam : v_cam )
        {
            cam.Flip();
        }
    }
}

std::vector<Camera> ReadCameras( std::string const& filename )
{
    std::vector<Camera> cameras;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( !infile.is_open() )
        return cameras;

    std::string input_thing;
    std::getline( infile, input_thing );
    while( input_thing != "" )
    {
        Camera camera;
        //First the tile
        camera.SetID( std::stoi( input_thing.substr( 5, input_thing.size() - 6 ) ) );
        //Read each line
        std::getline( infile, input_thing );
        while( input_thing != "" )
        {
            camera.push_back( StringToVectorBool( input_thing ) );
            input_thing = "";
            std::getline( infile, input_thing );
        }
        input_thing = "";
        std::getline( infile, input_thing );
        cameras.push_back( camera );
    }
    infile.close();
    return cameras;
}

bool CanConnect( std::vector<bool> const& side, Camera& camera )
{
    //We have 8 comparisons to do, always with the row on top on camera (4 rotations + 4 flipped rotations)
    for( int i = 0; i < 2; i++ )
    {
        for( int j = 0; j < 4; j++ )
        {
            if( side == camera.GetLine( 0 ) )
                return true;
            camera.Rotate( Rotation::clockwise );
        }
        camera.Flip();
    }
    return false;
}

uint64_t ConnectingSides( std::vector<Camera>& cameras, size_t const index )
{
    Camera this_camera = cameras[ index ];
    std::vector<std::vector<bool>> sides;
    uint64_t result = 0;
    //Go side per side and add
    for( int i = 0; i < 4; i++ )
    {
        sides.push_back( this_camera.GetLine( 0 ) );
        this_camera.Rotate( Rotation::clockwise );
    }
    for( auto side : sides )
    {
        for( size_t i = 0; i < cameras.size(); i++ )
        {
            if( i == index ) //Do not compare with itself
                continue;
            if( CanConnect( side, cameras[ i ] ) )
            {
                result++;
                break;
            }
        }
    }
    //std::cout << "Connecting sides " << result << std::endl;
    return result;
}

uint64_t GetProductOfCorners( std::vector<Camera>& cameras )
{
    uint64_t result = 1;
    //Corners only have 2 sides which can connect to others
    for( size_t i = 0; i < cameras.size(); i++ )
    {
        if( ConnectingSides( cameras, i ) == 2 )
        {
            result = result * cameras[ i ].GetID();
        }
    }
    return result;
}

Camera GetFirstCorner( std::vector<Camera>& cameras )
{
    int i = 0;
    Camera res;
    for( auto camera = cameras.begin(); camera != cameras.end(); ++camera )
    {
        if( ConnectingSides( cameras, i ) == 2 )
        {
            res = *camera;
            cameras.erase( camera );
            break;
        }
        i++;
    }
    //Rotate appropiately
    //Rotate until failure
    bool top_connects;
    do
    {
        res.Rotate( Rotation::clockwise );
        top_connects = false;
        for( auto camera : cameras )
        {
            if( CanConnect( res.GetLine( 0 ), camera ) )
            {
                top_connects = true;
                break;
            }
        }
    } while( top_connects );
    //Rotate again and check
    res.Rotate( Rotation::clockwise );
    top_connects = false;
    for( auto camera : cameras )
    {
        if( CanConnect( res.GetLine( 0 ), camera ) )
        {
            top_connects = true;
            break;
        }
    }
    if( top_connects ) //Rotate twice to compensate
    {
        res.Rotate( Rotation::clockwise );
        res.Rotate( Rotation::clockwise );
    }
    else //Rotate back
        res.Rotate( Rotation::anticlockwise );
    return res;
}

Camera GetMatching( std::vector<bool> const pattern, std::vector<Camera>& cameras, bool look_top )
{
    Camera res;
    for( auto camera = cameras.begin(); camera != cameras.end(); ++camera )
    {
        //4 rotations, 2 orientations
        for( int i = 0; i < 2; i++ )
        {
            for( int j = 0; j < 4; j++ )
            {
                if( pattern == camera->GetLine( 0 ) ) //Found it!
                {
                    if( look_top ) //It is already matching properly
                    {
                        res = *camera;
                        cameras.erase( camera );
                        return res;
                    }
                    else //We have to flip and rotate anticlockwise
                    {
                        res = *camera;
                        cameras.erase( camera );
                        res.Flip();
                        res.Rotate( Rotation::anticlockwise );
                        return res;
                    }
                }
                camera->Rotate( Rotation::clockwise );
            }
            camera->Flip();
        }
    }
    std::cout << "Mierda" << std::endl;
    return res;
}

BigCamera MergeCameras( std::vector<Camera> cameras )
{
    BigCamera bigcamera;
    //Get side length of the square and resize camera square
    uint64_t length = uint64_t( sqrt( cameras.size() ) );
    bigcamera.m_cameras.resize( length );
    for( int i = 0; i < length; i++ )
        bigcamera.m_cameras[ i ].resize( length );

    //Fill the big square
    for( int i = 0; i < length; i++ )
    {
        for( int j = 0; j < length; j++ )
        {
            //std::cout << length << i << j << std::endl;
            //First corner. Just get a corner
            if( i == 0 && j == 0 )
            {
                bigcamera.m_cameras[ i ][ j ] = GetFirstCorner( cameras );
            }
            else if( i == 0 ) //During first row we must compare with those at the left
            {
                bigcamera.m_cameras[ i ][ j - 1 ].Rotate( Rotation::anticlockwise );
                bigcamera.m_cameras[ i ][ j ] = GetMatching( bigcamera.m_cameras[ i ][ j - 1 ].GetLine( 0 ), cameras, false );
                bigcamera.m_cameras[ i ][ j - 1 ].Rotate( Rotation::clockwise );
            }
            else //Compare with the one above
            {
                bigcamera.m_cameras[ i ][ j ] = GetMatching( bigcamera.m_cameras[ i - 1 ][ j ].GetLine( bigcamera.m_cameras[ i - 1 ][ j ].GetSize() - 1 ), cameras, true );
            }
        }
    }
    return bigcamera;
}

int main()
{
    auto cameras = ReadCameras( "C:\\Users\\alex1\\git\\AdventOfCode\\day20\\input.txt" );
    auto result = GetProductOfCorners( cameras );

    auto bigcamera = MergeCameras( cameras ).MergeCameras();
    auto result2 = bigcamera.CountPattern();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}
