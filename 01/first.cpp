#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);
    int measurement;

    int last = 0;
    bool first = true;
    int count = 0;

    while (input >> measurement)
    {
        if (!first && measurement > last)
                count++;

        first = false;
        last = measurement;
    }

    std::cout << "Count: " << count << std::endl;

    return 1;
}