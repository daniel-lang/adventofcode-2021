#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

void countLowHigh(std::vector<std::string> const &values, int const offset, int const size, int &low, int &high)
{
    low = 0;
    high = 0;

    for (auto const &value : values)
    {
        if (value.at(offset) == '1')
            high++;
        else
            low++;
    }
}

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);

    std::string value;
    std::vector<std::string> values;

    while (input >> value)
    {
        values.emplace_back(value);
    }

    char bit;
    int high = 0;
    int low = 0;
    int size = values[0].size();
    std::vector<std::string> oxygenValues = values;
    std::vector<std::string> co2Values = values;

    for (int i = 0; i < size; ++i)
    {
        countLowHigh(oxygenValues, i, size, low, high);
        bit = (low <= high) ? '1' : '0';

        if (oxygenValues.size() > 1)
            oxygenValues.erase(
                std::remove_if(oxygenValues.begin(), oxygenValues.end(), [bit, i](std::string const &str) { return str.at(i) != bit; }),
                oxygenValues.end()
            );

        countLowHigh(co2Values, i, size, low, high);
        bit = (low <= high) ? '0' : '1';

        if (co2Values.size() > 1)
            co2Values.erase(
                std::remove_if(co2Values.begin(), co2Values.end(), [bit, i](std::string const &str) { return str.at(i) != bit; }),
                co2Values.end()
            );
    }

    int oxygen = 0;
    int co2 = 0;

    for (int i = 0; i < size; ++i)
    {
        oxygen = oxygen << 1;
        co2 = co2 << 1;

        if (oxygenValues[0].at(i) == '1')
            oxygen += 1;

        if (co2Values[0].at(i) == '1')
            co2 += 1;
    }

    std::cout << "oxygen: " << oxygen << " co2: " << co2 << " result: " << oxygen * co2 << std::endl;

    return 0;
}