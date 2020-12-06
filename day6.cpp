//To solve day 6 puzzle
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <optional>

class Custom
{
private:
    std::vector<bool> m_answers;
    std::vector<std::vector<bool>> m_raw_answers;

public:
    Custom() : m_answers(26, false) {}
    void Fill(std::string_view input)
    {
        for (int i = 0; i < input.size(); i++)
        {
            m_answers[(int)input[i] - 97] = true;
            m_raw_answers[m_raw_answers.size() - 1][(int)input[i] - 97] = true;
        }
    }
    void Fill(std::vector<std::string> const &inputs)
    {
        for (auto input : inputs)
        {
            m_raw_answers.push_back(std::vector<bool>(26, false));
            Fill(input);
        }
        return;
    }
    unsigned int GetSum() const
    {
        unsigned int result = 0;
        for (auto answer : m_answers)
        {
            result += (int)answer;
        }
        return result;
    }
    unsigned int GetCommonSum() const
    {
        std::vector<bool> vec_result(26, true);
        for (auto raw_answer : m_raw_answers)
        {
            for (int i = 0; i < raw_answer.size(); i++)
            {
                vec_result[i] = vec_result[i] * raw_answer[i];
            }
        }
        unsigned int result = 0;
        for (auto vec_res : vec_result)
        {
            result += (int)vec_res;
        }
        return result;
    }
};

std::vector<Custom> ReadCustoms(std::string filename)
{
    std::vector<Custom> readlist;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            //Read passports
            Custom custom;
            std::string input_thing;
            std::vector<std::string> input_things;
            //Min-max
            do
            {
                input_thing = "";
                std::getline(infile, input_thing);
                if (input_thing != "")
                    input_things.push_back(input_thing);
            } while (input_thing != "");
            custom.Fill(input_things);
            readlist.push_back(custom);
        }
    }
    return readlist;
}

unsigned int GetSum(std::vector<Custom> const &customs)
{
    unsigned int result = 0;
    for (auto custom : customs)
    {
        result += custom.GetSum();
    }
    return result;
}
unsigned int GetCommonSum(std::vector<Custom> const &customs)
{
    unsigned int result = 0;
    for (auto custom : customs)
    {
        result += custom.GetCommonSum();
    }
    return result;
}

//Main function
int main()
{
    std::vector<Custom> customs = ReadCustoms("C:\\Users\\alex1\\git\\AdventOfCode\\day6\\input.txt");
    unsigned int result = GetSum(customs);
    unsigned int result2 = GetCommonSum(customs);

    std::cout << "Result: " << result << std::endl;
    std::cout << "Result2: " << result2 << std::endl;
    return 0;
}