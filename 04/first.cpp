#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <array>

constexpr int SIZE = 5;

struct entry_t
{
    int value;
    bool marked = false;
};

typedef std::array<std::array<entry_t, SIZE>, SIZE> board_t;

void calcResult(int const draw, board_t const &board)
{
    int sum = 0;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (!board[i][j].marked)
                sum += board[i][j].value;
        }
    }

    std::cout << "Draw: " << draw << " sum: " << sum << " result: " << draw * sum << std::endl;
}

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);

    std::string line;
    std::vector<int> draws;
    std::vector<board_t> boards;
    int index = 0;
    int row = 0;
    int column = 0;

    while (input >> line)
    {
        if (draws.size() == 0)
        {
            std::string value;
            std::istringstream stream(line);
            while (getline(stream, value, ','))
                draws.push_back(std::stoi(value));

            board_t newBoard;
            boards.push_back(newBoard);
        }
        else
        {
            if (column == 5)
            {
                column = 0;
                row++;
            }
            if (row == 5)
            {
                row = 0;
                index++;
                board_t newBoard;
                boards.push_back(newBoard);
            }

            boards[index][row][column].value = std::stoi(line);
            column++;
        }
    }

    bool won = false;

    for (auto draw : draws)
    {
        for (auto &board : boards)
        {
            /* mark draw and check if row won */
            for (int i = 0; i < SIZE; ++i)
            {
                bool rowWon = true;

                for (int j = 0; j < SIZE; ++j)
                {
                    if (board[i][j].value == draw)
                        board[i][j].marked = true;

                    if (!board[i][j].marked)
                        rowWon = false;
                }

                if (rowWon)
                {
                    calcResult(draw, board);
                    return 0;
                }
            }

            /* check if column won */
            for (int j = 0; j < SIZE; ++j)
            {
                bool columnWon = true;
                for (int i = 0; i < SIZE; ++i)
                {
                    if (!board[i][j].marked)
                        columnWon = false;
                }

                if (columnWon)
                {
                    calcResult(draw, board);
                    return 0;
                }
            }
        }
    }

    return 0;
}