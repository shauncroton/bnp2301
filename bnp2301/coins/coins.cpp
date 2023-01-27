///////////////////////////////////////////////////////////////////////////////////////////////////
///

#include <common.hpp>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
/// COINS
/// We keep accumulating coins starting with 1 coin for 1 day then incrementing the magnitude
/// to 2 coins for 2 days, 3 or 3, etc.  We do this until be have equal to or over our target day.
/// At this point we need to adjust because we might have overpaid.  We take the hit of needing to
/// do an adjustment at the end because the alternative is to have checks inside the loop paying
/// a cost for each iteration rather than just once at the end.
///////////////////////////////////////////////////////////////////////////////////////////////////
///

auto coins(int paydays_) -> int
{
    int accumulated = 0;
    int magnitude = 0;

    while (paydays_>0) {
        ++magnitude;
        accumulated += magnitude*magnitude;
        paydays_ -= magnitude;
    }

    accumulated += magnitude*paydays_;

    return accumulated;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

int
main()
{
    int next_integer = 0;
    while (get_int<0, 10000>(next_integer)) {
        if (next_integer==0) break;
        std::cout << next_integer << " " << coins(next_integer) << std::endl;
    }

    if (next_integer!=0)
        std::cout << "list was not terminated with a zero line" << std::endl;

    return 0;
}

///
///////////////////////////////////////////////////////////////////////////////////////////////////
