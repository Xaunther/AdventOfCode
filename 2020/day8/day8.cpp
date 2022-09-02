//To solve day 8 puzzle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

//3 types of instructions
enum Instruction
{
    acc,
    jmp,
    nop
};
//Instructions vector
using Instructions = std::vector<std::pair<bool, std::pair<Instruction, int>>>;

Instruction StringToInstruction( std::string_view str_instruction )
{
    if( str_instruction == "acc" )
        return acc;
    if( str_instruction == "jmp" )
        return jmp;
    if( str_instruction == "nop" )
        return nop;
    return {};
}

Instructions ReadInstructions( std::string filename )
{
    Instructions instructions;
    std::ifstream infile;
    infile.open( filename.c_str() );
    if( infile.is_open() )
    {
        while( !infile.eof() )
        {
            //Reading is quite easy, it's a pair of instruction with argument
            std::pair<std::string, std::string> input_things;
            infile >> input_things.first;
            infile >> input_things.second;
            instructions.push_back( { false, {StringToInstruction( input_things.first ), std::stoi( input_things.second )} } );
        }
    }
    return instructions;
}

//Returns true if reached end properly
std::pair<bool, int> GetAccBeforeLoopOrEnd( Instructions instructions )
{
    int accumulator = 0;
    int i = 0;
    while( !instructions[ i ].first )
    {
        int j = i;
        instructions[ i ].first = true;

        switch( instructions[ i ].second.first )
        {
        case acc:
            accumulator += instructions[ i ].second.second;
            i++;
            break;
        case jmp:
            i += instructions[ i ].second.second;
            break;
        case nop:
            i++;
            break;
        }
        //Check if we actually reached the end
        if( i == instructions.size() && i == j + 1 )
        {
            return { true, accumulator };
        }
        //Check if we are within bounds
        if( i < 0 || i >= instructions.size() )
            return { false, accumulator };
    }
    return { false, accumulator };
}

int GetAccFixed( Instructions instructions )
{
    for( unsigned int i = 0; i < instructions.size(); i++ )
    {
        std::pair<bool, int> result = { false, 0 };
        //Switcheroo
        switch( instructions[ i ].second.first )
        {
        case acc:
            break;
        case nop:
            instructions[ i ].second.first = jmp;
            result = GetAccBeforeLoopOrEnd( instructions );
            instructions[ i ].second.first = nop;
            break;
        case jmp:
            instructions[ i ].second.first = nop;
            result = GetAccBeforeLoopOrEnd( instructions );
            instructions[ i ].second.first = jmp;
            break;
        }
        if( result.first )
            return result.second;
    }
    return 0;
}

//Main function
int main()
{
    Instructions instructions = ReadInstructions( "C:\\Users\\alex1\\git\\AdventOfCode\\day8\\input.txt" );
    std::pair<bool, int> result = GetAccBeforeLoopOrEnd( instructions );
    int result2 = GetAccFixed( instructions );

    std::cout << "Result: " << result.second << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}