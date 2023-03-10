#ifndef MEDIAN_HPP
#define MEDIAN_HPP

///////////////////////////////////////////////////////////////////////////////////////////////////
///

#include <limits>
#include <set>
#include <cstdint>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

class median {
protected: ////////////////////////////////////////////////////////////////////////////// names

public: ///////////////////////////////////////////////////////////////////////////// interface

    auto update(int data_) -> int;

protected: ///////////////////////////////////////////////////////////////////// implementation

private: ////////////////////////////////////////////////////////////////////////////// helpers

public: ////////////////////////////////////////////////////////////////////////////// lifetime

    median(const median&) = default;

    auto operator=(median&) -> median& = default;

    median(median&&) = default;

    auto operator=(median&&) -> median& = default;

    ~median() = default;

    median() = default;

private: //////////////////////////////////////////////////////////////////////////////// state

    std::multiset<int32_t> dataset{0, std::numeric_limits<int32_t>::max()};

    std::multiset<int32_t>::iterator tracker{dataset.begin()};
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // MEDIAN_HPP