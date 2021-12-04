#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>

constexpr bool second = true;

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);
    std::vector<int> measurements;
    int measurement;

    while (input >> measurement)
        measurements.emplace_back(measurement);

    int count = 0;
    int last = 0;
    bool first = true;

    for (int i = 0; i < measurements.size() - 2; ++i)
    {
        int sum = std::accumulate(measurements.cbegin() + i, measurements.cbegin() + i + 3, 0);
        if (!first && sum > last)
            count++;

        first = false;
        last = sum;
    }

    std::cout << "Count: " << count << std::endl;

    return 1;
}