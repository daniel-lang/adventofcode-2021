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

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);
    std::string text;
    std::vector<line_t> lines;

    while (std::getline(input, text))
    {
        line_t line;
        std::sscanf(text.c_str(), "%d,%d -> %d,%d", &(line.start.x), &(line.start.y), &(line.end.x), &(line.end.y));

        /* only vertical or horizontal lines */
        if (line.start.x == line.end.x || line.start.y == line.end.y)
            lines.push_back(line);
    }

    std::unordered_map<coordinate_t, int, KeyHash, KeyEqual> map;

    for (auto const &line : lines)
    {
        bool horizontal;
        coordinate_t point = line.start;
        int diff;

        if (line.start.x == line.end.x)
        {
            horizontal = false;
            diff = line.end.y - line.start.y;
            point.y = std::min(line.start.y, line.end.y);
        }
        else
        {
            horizontal = true;
            diff = line.end.x - line.start.x;
            point.x = std::min(line.start.x, line.end.x);
        }

        int count = std::abs(diff);

        for (int i = 0; i <= count; ++i)
        {
            /* iterator is returned if element already exists */
            auto pair = map.insert(std::pair<coordinate_t, int>(point, 1));
            /* element existed -> increment */
            if (!pair.second)
                pair.first->second++;

            if (horizontal)
                point.x++;
            else
                point.y++;
        }
    }

    int result = std::count_if(map.cbegin(), map.cend(), [](std::pair<coordinate_t, int> point)
                               { return point.second >= 2; });

    std::cout << "Result: " << result << std::endl;

    return 0;
}