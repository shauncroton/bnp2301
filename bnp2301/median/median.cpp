///////////////////////////////////////////////////////////////////////////////////////////////////
///

#include "median.hpp"
#include <common.hpp>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
/// MEDIAN
/// My approach here is to place the data into a set moving a tracking iterator to the left or
/// right depending on which side the new data was inserted and if there is currently an odd
/// or even number of data points in the data set
///////////////////////////////////////////////////////////////////////////////////////////////////
///

auto median::update(const int data_) -> int
{
    dataset.emplace(data_);

    const bool is_odd_dataset_size = (dataset.size() & 1);

    if (*tracker<=data_ && is_odd_dataset_size) {
        tracker++;
    }

    else if (*tracker>data_ && !is_odd_dataset_size) {
        tracker--;
    }

    return is_odd_dataset_size
           ? *tracker
           : (*tracker++ +*tracker--)/2;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

int
main()
{
    median calculator;

    int integer_count = 10000;
    int next_integer = 0;
    while (get_int<0, std::numeric_limits<int32_t>::max()>(next_integer)) {
        if (integer_count--==0) {
            std::cout << "exceeded maximum integer count" << std::endl;
            break;
        }
        std::cout << calculator.update(next_integer) << std::endl;
    }

    return 0;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
