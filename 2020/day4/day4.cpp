//To solve day 4 puzzle
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>

class Passport
{
    //Members
private:
    std::optional<std::string> m_byr;
    std::optional<std::string> m_iyr;
    std::optional<std::string> m_eyr;
    std::optional<std::string> m_hgt;
    std::optional<std::string> m_hcl;
    std::optional<std::string> m_ecl;
    std::optional<std::string> m_pid;
    std::optional<std::string> m_cid;

public:
    //Print values
    void Print() const
    {
        if( m_byr.has_value() )
            std::cout << "byr: " << m_byr.value() << std::endl;
        if( m_iyr.has_value() )
            std::cout << "iyr: " << m_iyr.value() << std::endl;
        if( m_eyr.has_value() )
            std::cout << "eyr: " << m_eyr.value() << std::endl;
        if( m_hgt.has_value() )
            std::cout << "hgt: " << m_hgt.value() << std::endl;
        if( m_hcl.has_value() )
            std::cout << "hcl: " << m_hcl.value() << std::endl;
        if( m_ecl.has_value() )
            std::cout << "ecl: " << m_ecl.value() << std::endl;
        if( m_pid.has_value() )
            std::cout << "pid: " << m_pid.value() << std::endl;
        if( m_cid.has_value() )
            std::cout << "cid: " << m_cid.value() << std::endl;
        std::cout << std::endl;
        return;
    }
    //Check if the passport has the required entries
    bool IsPresent() const
    {
        return ( m_byr.has_value() && m_iyr.has_value() && m_eyr.has_value() && m_hgt.has_value() && m_hcl.has_value() && m_ecl.has_value() && m_pid.has_value() );
    }

    //Check if the passport has valid values
    bool IsValid() const
    {
        if( !this->IsPresent() )
            return false;
        if( std::stoi( m_byr.value() ) < 1920 || std::stoi( m_byr.value() ) > 2002 )
            return false;
        if( std::stoi( m_iyr.value() ) < 2010 || std::stoi( m_iyr.value() ) > 2020 )
            return false;
        if( std::stoi( m_eyr.value() ) < 2020 || std::stoi( m_eyr.value() ) > 2030 )
            return false;
        if( m_hgt.value().find( "in" ) != std::string::npos )
        {
            if( std::stoi( m_hgt.value().substr( 0, m_hgt.value().find( "in" ) ) ) < 59 || std::stoi( m_hgt.value().substr( 0, m_hgt.value().find( "in" ) ) ) > 76 )
                return false;
        }
        else if( m_hgt.value().find( "cm" ) != std::string::npos )
        {
            if( std::stoi( m_hgt.value().substr( 0, m_hgt.value().find( "cm" ) ) ) < 150 || std::stoi( m_hgt.value().substr( 0, m_hgt.value().find( "cm" ) ) ) > 193 )
                return false;
        }
        else
            return false;
        if( m_hcl.value()[ 0 ] != '#' )
            return false;
        /*try
        {
            stoi( m_hcl.value().substr( 1 ), 0, 16 );
        }
        catch( std::exception& e )
        {
            return false;
        }*/
        if( m_ecl.value() != "amb" && m_ecl.value() != "blu" && m_ecl.value() != "brn" && m_ecl.value() != "gry" && m_ecl.value() != "grn" && m_ecl.value() != "hzl" && m_ecl.value() != "oth" )
            return false;
        if( m_pid.value().size() != 9 )
            return false;
        /*try
        {
            stoi( m_pid.value() );
        }
        catch( std::exception& e )
        {
            return false;
        }*/
        return true;
    }

    //Find using this line
    void Fill( std::string const& input )
    {
        //Check byr
        if( input.find( "byr:" ) != std::string::npos )
        {
            m_byr = input.substr( input.find( "byr:" ) + 4, input.find( " ", input.find( "byr:" ) ) - input.find( "byr:" ) - 4 );
        }
        //Check iyr
        if( input.find( "iyr:" ) != std::string::npos )
        {
            m_iyr = input.substr( input.find( "iyr:" ) + 4, input.find( " ", input.find( "iyr:" ) ) - input.find( "iyr:" ) - 4 );
        }
        //Check eyr
        if( input.find( "eyr:" ) != std::string::npos )
        {
            m_eyr = input.substr( input.find( "eyr:" ) + 4, input.find( " ", input.find( "eyr:" ) ) - input.find( "eyr:" ) - 4 );
        }
        //Check hgt
        if( input.find( "hgt:" ) != std::string::npos )
        {
            m_hgt = input.substr( input.find( "hgt:" ) + 4, input.find( " ", input.find( "hgt:" ) ) - input.find( "hgt:" ) - 4 );
        }
        //Check hcl
        if( input.find( "hcl:" ) != std::string::npos )
        {
            m_hcl = input.substr( input.find( "hcl:" ) + 4, input.find( " ", input.find( "hcl:" ) ) - input.find( "hcl:" ) - 4 );
        }
        //Check ecl
        if( input.find( "ecl:" ) != std::string::npos )
        {
            m_ecl = input.substr( input.find( "ecl:" ) + 4, input.find( " ", input.find( "ecl:" ) ) - input.find( "ecl:" ) - 4 );
        }
        //Check pid
        if( input.find( "pid:" ) != std::string::npos )
        {
            m_pid = input.substr( input.find( "pid:" ) + 4, input.find( " ", input.find( "pid:" ) ) - input.find( "pid:" ) - 4 );
        }
        //Check cid
        if( input.find( "cid:" ) != std::string::npos )
        {
            m_cid = input.substr( input.find( "cid:" ) + 4, input.find( " ", input.find( "cid:" ) ) - input.find( "cid:" ) - 4 );
        }
        return;
    }

    //Fill with a raw vector
    void Fill( std::vector<std::string> const& inputs )
    {
        //Read each input line
        for( auto input = inputs.begin(); input != inputs.end(); input++ )
        {
            this->Fill( *input );
        }
    }
};

std::vector<Passport> ReadPassports( std::string filename )
{
    std::vector<Passport> readlist;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( infile.is_open() )
    {
        while( !infile.eof() )
        {
            //Read passports
            Passport pass;
            std::string input_thing;
            std::vector<std::string> input_things;
            //Min-max
            do
            {
                input_thing = "";
                std::getline( infile, input_thing );
                if( input_thing != "" )
                    input_things.push_back( input_thing );
            } while( input_thing != "" );
            pass.Fill( input_things );
            readlist.push_back( pass );
        }
    }
    return readlist;
}

int CheckPassports( std::vector<Passport> const& passports )
{
    int result = 0;
    for( auto& passport : passports )
    {
        result += ( int )passport.IsPresent();
    }
    return result;
}
int ValidPassports( std::vector<Passport> const& passports )
{
    int result = 0;
    for( auto& passport : passports )
    {
        result += ( int )passport.IsValid();
    }
    return result;
}

//Main function
int main()
{
    std::vector<Passport> passports = ReadPassports( "C:\\Users\\alex1\\git\\AdventOfCode\\day4\\input.txt" );
    int result = CheckPassports( passports );
    int result2 = ValidPassports( passports );

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}