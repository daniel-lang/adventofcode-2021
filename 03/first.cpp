#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);

    std::string value;
    int bit;
    int offset = 0;
    std::vector<int> high;
    std::vector<int> low;

    while (input >> value)
    {
        offset = 0;

        for (int i = 0; i < value.size(); ++i)
        {
            if (i >= high.size()) {
                high.push_back(0);
                low.push_back(0);
            }

            if (value.at(i) == '1')
                high[offset]++;
            else
                low[offset]++;

            offset++;
        }
    }

    int gamma = 0;
    int epsilon = 0;

    for (int i = 0; i < high.size(); ++i)
    {
        epsilon = epsilon << 1;
        gamma = gamma << 1;

        if (low[i] > high[i])
            epsilon += 1;
        else
            gamma += 1;
    }

    std::cout << "epsilon: " << epsilon << " gamma: " << gamma << " result: " << gamma * epsilon << std::endl;

    return 0;
}