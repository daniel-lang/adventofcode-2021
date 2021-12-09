#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

struct coordinate_t
{
    int x;
    int y;
};

struct KeyHash
{
    std::size_t operator()(const coordinate_t &k) const
    {
        return std::hash<int>()(k.x) ^
               (std::hash<int>()(k.y) << 1);
    }
};

struct KeyEqual
{
    bool operator()(const coordinate_t &lhs, const coordinate_t &rhs) const
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

struct line_t
{
    coordinate_t start;
    coordinate_t end;
};

enum class line_type
{
    horizontal,
    vertical,
    diagonal
};

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);
    std::string text;
    std::vector<line_t> lines;

    while (std::getline(input, text))
    {
        line_t line;
        std::sscanf(text.c_str(), "%d,%d -> %d,%d", &(line.start.x), &(line.start.y), &(line.end.x), &(line.end.y));
        lines.push_back(line);
    }

    std::unordered_map<coordinate_t, int, KeyHash, KeyEqual> map;

    for (auto const &line : lines)
    {
        line_type type;
        coordinate_t point = line.start;
        int diffX = 0;
        int diffY = 0;

        if (line.start.x == line.end.x)
        {
            type = line_type::vertical;
            diffY = line.end.y - line.start.y;
            point.y = std::min(line.start.y, line.end.y);
        }
        else if (line.start.y == line.end.y)
        {
            type = line_type::horizontal;
            diffX = line.end.x - line.start.x;
            point.x = std::min(line.start.x, line.end.x);
        }
        else
        {
            type = line_type::diagonal;
            diffX = line.end.x - line.start.x;
            diffY = line.end.y - line.start.y;
        }

        int count = std::max(std::abs(diffX), std::abs(diffY));

        for (int i = 0; i <= count; ++i)
        {
            /* iterator is returned if element already exists */
            auto pair = map.insert(std::pair<coordinate_t, int>(point, 1));
            /* element existed -> increment */
            if (!pair.second)
                pair.first->second++;

            switch (type)
            {
            case line_type::horizontal:
                point.x++;
                break;
            
            case line_type::vertical:
                point.y++;
                break;

            case line_type::diagonal:
                diffX > 0 ? point.x++ : point.x--;
                diffY > 0 ? point.y++ : point.y--;
                break;
            }
        }
    }

    int result = std::count_if(map.cbegin(), map.cend(), [](std::pair<coordinate_t, int> point)
                               { return point.second >= 2; });

    std::cout << "Result: " << result << std::endl;

    return 0;
}