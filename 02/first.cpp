#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    int depth = 0;
    int horizontal = 0;

    std::fstream input(argv[1]);

    std::string command;
    int count;
    while (input >> command >> count)
    {
        if (command == "forward")
            horizontal += count;
        else if (command == "up")
            depth -= count;
        else if (command == "down")
            depth += count;
    }

    std::cout << "Depth: " << depth << ", horizontal position: " << horizontal << " result: " << depth * horizontal << std::endl;

    return 0;
}