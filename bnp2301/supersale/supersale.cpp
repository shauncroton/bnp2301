///////////////////////////////////////////////////////////////////////////////////////////////////
///

#include <common.hpp>
#include <set>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
/// SUPERSALE
/// Firstly we go though the dataset and find all the possible results that can be realized
/// and place them into a container ordered by weight.
/// Some of the possible results will never be selected as the are better results at a lower
/// weight point.   These are removed to give optimized results which can then be used to
/// look up the best result for any given weight limit.
/// We then loop though all the weight limits given looking up the optimized result for each
/// and keeping total of all the result of the weight limit set.  This gives us the end result.
/// Since product details are less likely to change than weight limits which represent families
/// coming to do shopping it is probably also more efficient to work out all the results up front
/// meaning that each time a new family comes to the sho[  all the heavy lifting is already done.
///////////////////////////////////////////////////////////////////////////////////////////////////
///

auto supersale(const std::vector<std::pair<int, int>>& products_,
        const std::vector<int>& limits_) -> int
{
    const auto& optimized_results{[&]() {
        const auto& possible_results{[&]() {

            // create a map of all possible shopping results

            constexpr auto pair_compare = [](const auto& lhs, const auto& rhs) {
                if (lhs.first==rhs.first)
                    return lhs.second<rhs.second;
                return lhs.first<rhs.first;
            };

            std::set<std::pair<int, int>, decltype(pair_compare)> sorted;

            for (const auto& detail: products_) {
                std::vector<std::pair<int, int>> additions;
                for (const auto& pair: sorted) {
                    additions.emplace_back(pair.first+detail.second, pair.second+detail.first);
                }
                sorted.emplace(detail.second, detail.first);
                sorted.insert(additions.begin(), additions.end());
            }

            return sorted;
        }()};

        // remove all shopping results for which a better choice exists

        std::vector<std::pair<int, int>> results{{0, 0}};
        int highest_value = 0;
        std::copy_if(possible_results.begin(), possible_results.end(), std::back_inserter(results),
                [&highest_value](const auto& o) {
                    if (o.second>highest_value)
                        highest_value = o.second;
                    return highest_value==o.second;
                });

        return results;
    }()};

    // for each of the people shopping lookup their best result and append to total

    int total = 0;
    for (const auto& weight_limit: limits_) {
        const auto& it = std::lower_bound(optimized_results.begin(), optimized_results.end(), weight_limit,
                [](const auto& pair, const int value) {
                    return pair.first<value;
                });
        total += (it-1)->second;
    }

    return total;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

int
main()
{
    int test_count = 0;
    if (!get_int<1, 1000>(test_count))
        return 1;

    while (test_count--) {
        std::vector<std::pair<int, int>> product_details;
        if (!get_int_pair_vec<1, 1000, 1, 100, 1, 30>(product_details))
            return 1;

        std::vector<int> weight_limits;
        if (!get_int_vec<1, 100, 1, 30>(weight_limits))
            return 1;

        std::cout << supersale(product_details, weight_limits) << std::endl;
    }

    return 0;
}
///
///////////////////////////////////////////////////////////////////////////////////////////////////
