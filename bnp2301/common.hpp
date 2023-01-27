#ifndef COMMON_HPP
#define COMMON_HPP

///////////////////////////////////////////////////////////////////////////////////////////////////
///

#include <iostream>
#include <string>
#include <regex>
#include <limits>

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

inline
auto trim(const std::string& str) -> std::string
{
    if (str.empty() || !(std::isspace(str.front()) || std::isspace(str.back())))
        return str;

    constexpr auto pred = [](int ch) {
        return !std::isspace(ch);
    };

    return {std::find_if(str.begin(), str.end(), pred),
            std::find_if(str.rbegin(), str.rend(), pred).base()};
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///

inline
auto as_int(const std::string& str) -> int
{
    if( str.empty()) {
        std::cout << "empty string given for integer conversion " << std::endl;
        exit(0);
    }
    char* end;

    const auto result = int(std::strtol(str.data(), &end, 10));

    if (*end!=0 && !trim(end).empty()) {
        std::cout << "invalid character in integer conversion: " << str << std::endl;
        exit(0);
    }

    return result;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

template<int MIN, int MAX>
auto get_int(int& result_,
        const int min_ = std::numeric_limits<int>::min(),
        const int max_ = std::numeric_limits<int>::max()
) -> bool
{
    int result;

    std::string line;
    if (!std::getline(std::cin, line))
        return false;

    result = as_int(line);

    if (result<MIN || result>MAX) {
        std::cout << "integer out of bounds: " << MIN << " <= " << result << " <= " << MAX << std::endl;
        return false;
    }

    result_ = result;
    return true;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

template<int FIRST_MIN, int FIRST_MAX,
        int SECOND_MIN = FIRST_MIN, int SECOND_MAX = FIRST_MAX>
auto get_int_pair(std::pair<int, int>& result_,
        const int min_ = std::numeric_limits<int>::min(),
        const int max_ = std::numeric_limits<int>::max()
) -> bool
{
    std::pair<int, int> result;

    std::string line;
    if (!std::getline(std::cin, line))
        return false;

    line = trim(line);

    std::regex re("\\s+");
    std::sregex_token_iterator iter(line.begin(), line.end(), re, -1);
    std::sregex_token_iterator end;

    const auto tokens_on_line = std::distance(iter, end);
    if (tokens_on_line!=2) {
        std::cout << "integer pair has too many tokens on input line: " << line << std::endl;
        return false;
    }

    result.first = as_int(*iter);
    result.second = as_int(*++iter);

    if (result.first<FIRST_MIN || result.first>FIRST_MAX) {
        std::cout << "pair first out of bounds: " << FIRST_MIN << " <= " << result.first << " <= " << FIRST_MAX << std::endl;
        return false;
    }

    if (result.second<SECOND_MIN || result.second>SECOND_MAX) {
        std::cout << "pair second out of bounds: " << SECOND_MIN << " <= " << result.second << " <= " << SECOND_MAX << std::endl;
        return false;
    }

    result_ = std::move(result);
    return true;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

template<int COUNT_MIN, int COUNT_MAX, int FIRST_MIN, int FIRST_MAX>
auto get_int_vec(std::vector<int>& result_) -> bool
{
    std::vector<int> result;

    int integer_count;
    if (!get_int<COUNT_MIN, COUNT_MAX>(integer_count))
        return false;

    result.reserve(integer_count);

    int next_integer;
    while (integer_count-- && get_int<FIRST_MIN, FIRST_MAX>(next_integer)) {
        result.emplace_back(next_integer);
    }

    if (integer_count!=-1)
        return false;

    result_ = std::move(result);
    return true;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///

template<int COUNT_MIN, int COUNT_MAX, int FIRST_MIN, int FIRST_MAX,
        int SECOND_MIN = FIRST_MIN, int SECOND_MAX = FIRST_MAX>
auto get_int_pair_vec(std::vector<std::pair<int, int>>& result_) -> bool
{
    std::vector<std::pair<int, int>> result;

    int integer_pair_count;
    if (!get_int<COUNT_MIN, COUNT_MAX>(integer_pair_count))
        return false;

    result.reserve(integer_pair_count);

    std::pair<int, int> next_integer_pair;
    while (integer_pair_count-- && get_int_pair<FIRST_MIN, FIRST_MAX, SECOND_MIN, SECOND_MAX>(next_integer_pair)) {
        result.emplace_back(next_integer_pair);
    }

    if (integer_pair_count!=-1)
        return false;

    result_ = std::move(result);
    return true;
};

///
///////////////////////////////////////////////////////////////////////////////////////////////////

#endif // COMMON_HPP
