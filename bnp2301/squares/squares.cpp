///////////////////////////////////////////////////////////////////////////////////////////////////
///

#include <common.hpp>
#include <unordered_set>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
/// SQUARES
/// use the new point to check if any square can be found using all the existing known points.
/// We do this by making a diagonal with all the other known points, then working out the other
/// diagonal that the square would need.  Then we check if that other diagonal exists.  If so we
/// have a square, otherwise we remember the original diagonal as it might end up being the other
/// at some later POINT in time (pun intended)
///////////////////////////////////////////////////////////////////////////////////////////////////
///

using point_t = std::pair<double, double>;

using line_t = std::pair<point_t, point_t>;

auto squares(const std::vector<std::pair<int, int>>& points_) -> int
{
    constexpr auto line_hash = [](const line_t& l) {
        constexpr std::hash<float> hash_float;
        return hash_float(l.first.first) ^ hash_float(l.first.second)
                ^ hash_float(l.second.first) ^ hash_float(l.second.second);
    };

    std::unordered_set<line_t, decltype(line_hash)> diagonals;

    int matches = 0;

    for (const auto& point_one: points_) {
        for (const auto& point_two: points_) {
            if (point_one==point_two)
                break;

            const point_t mid_point{
                    float(point_one.first+point_two.first)/2,
                    float(point_one.second+point_two.second)/2
            };

            const line_t possible_other_line{ //
                    {mid_point.first-(point_one.second-mid_point.second),
                            mid_point.second+(point_one.first-mid_point.first)},
                    {mid_point.first-(point_two.second-mid_point.second),
                            mid_point.second+(point_two.first-mid_point.first)}
            };

            matches += (diagonals.find(possible_other_line)!=std::end(diagonals));

            diagonals.emplace(point_one, point_two);
            diagonals.emplace(point_two, point_one);
        }
    }

    return matches;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

int
main()
{
    std::vector<std::pair<int, int>> next_integer_vector;
    while (get_int_pair_vec<0, 1000, -20000, 20000>(next_integer_vector)) {
        if (next_integer_vector.empty())
            break;

        std::cout << squares(next_integer_vector) << std::endl;
    }

    return 0;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
