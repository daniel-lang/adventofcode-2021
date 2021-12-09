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

struct board_t
{
    bool won = false;
    std::array<std::array<entry_t, SIZE>, SIZE> field;
};

void calcResult(int const draw, board_t const &board)
{
    int sum = 0;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (!board.field[i][j].marked)
                sum += board.field[i][j].value;
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

            boards[index].field[row][column].value = std::stoi(line);
            column++;
        }
    }

    bool won = false;
    int boardCount = boards.size();

    for (auto draw : draws)
    {
        for (auto &board : boards)
        {
            if (board.won)
                continue;

            /* mark draw and check if row won */
            for (int i = 0; i < SIZE; ++i)
            {
                bool rowWon = true;

                for (int j = 0; j < SIZE; ++j)
                {
                    if (board.field[i][j].value == draw)
                        board.field[i][j].marked = true;

                    if (!board.field[i][j].marked)
                        rowWon = false;
                }

                if (rowWon && !board.won)
                {
                    board.won = true;
                    boardCount--;
                    if (boardCount == 0)
                    {
                        calcResult(draw, board);
                        return 0;
                    }
                }
            }

            /* check if column won */
            for (int j = 0; j < SIZE; ++j)
            {
                bool columnWon = true;
                for (int i = 0; i < SIZE; ++i)
                {
                    if (!board.field[i][j].marked)
                        columnWon = false;
                }

                if (columnWon && !board.won)
                {
                    board.won = true;
                    boardCount--;
                    if (boardCount == 0)
                    {
                        calcResult(draw, board);
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}