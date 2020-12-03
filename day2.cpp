//To solve day 2 puzzle
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Password
{
    //Members
private:
    int m_min;
    int m_max;
    char m_letter;
    std::string m_pass;

    //In/out functions
public:
    void SetMin(int _min) { m_min = _min; }
    void SetMax(int _max) { m_max = _max; }
    void SetLetter(char _letter) { m_letter = _letter; }
    void SetPassword(std::string _password) { m_pass = _password; }
    bool IsValid() const
    {
        int matches = 0;
        //Loop over string
        for (int i = 0; i < m_pass.size(); i++)
        {
            if (m_pass[i] == m_letter)
                matches++;
        }
        //See if it meets the requirements
        if (matches >= m_min && matches <= m_max)
            return true;
        else
            return false;
    }
};

int CheckCorrect(std::vector<Password> const &values)
{
    int correct = 0;
    for (auto pass = values.begin(); pass != values.end(); ++pass)
    {
        correct += (int)pass->IsValid();
    }

    return correct;
}

std::vector<Password> ReadPasswords(std::string filename)
{
    std::vector<Password> readlist;
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            //3 columns to fill
            Password pass;
            std::string input_thing;
            //Min-max
            infile >> input_thing;
            pass.SetMin(stoi(input_thing.substr(0, input_thing.find('-'))));
            pass.SetMax(stoi(input_thing.substr(input_thing.find('-') + 1)));
            //Character
            infile >> input_thing;
            pass.SetLetter(input_thing[0]);
            //Password
            infile >> input_thing;
            pass.SetPassword(input_thing);

            //Append
            readlist.push_back(pass);
        }
    }
    return readlist;
}

//Main function
int main()
{
    std::vector<Password> values = ReadPasswords("C:\\Users\\alex1\\git\\AdventOfCode\\day2\\input.txt");
    int correct = CheckCorrect(values);
    std::cout << "Result: " << correct << std::endl;
    return 0;
}