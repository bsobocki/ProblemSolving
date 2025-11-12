#pragma once

#include <string>
#include <sstream>
#include <vector>

template<typename Container>
std::string to_string(const Container& cont) {
    if (cont.empty()) return "{}";

    std::stringstream  res;
    auto it = cont.begin();

    res << "{" << *it++;
    while (it != cont.end()) res << ", " << *it++;
    res << "}";

    return res.str();
}

// SFINAE (Substitution Failure Is Not An Error) for overloading operator<< only for containers

template<typename T, typename = void>
struct is_container : std::false_type {};

template<typename T>
struct is_container<T, std::void_t<
    typename T::value_type,
    typename T::iterator,
    decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end())
>> : std::bool_constant<
    !std::is_same_v<T, std::string> &&           // Exclude std::string
    !std::is_same_v<T, std::wstring> &&          // Exclude std::wstring
    !std::is_same_v<T, std::u16string> &&        // Exclude std::u16string
    !std::is_same_v<T, std::u32string>           // Exclude std::u32string
> {};

// Overload operator<< only for containers
template<typename Container>
std::enable_if_t<is_container<Container>::value, std::ostream&>
operator<<(std::ostream& os, const Container& cont) {
    return os << to_string(cont);
}


// ------------ Get Formatted Test Results ----------------

const std::string setGreen = "\033[32m";
const std::string setRed = "\033[31m";
const std::string endColor = "\033[m";

std::string getColoredResult(bool isPassed) {
    return (isPassed ? setGreen + "Passed" : setRed + "Failed") + endColor;
}

std::string greenStr(const std::string& str) {
    return setGreen + str + endColor;
}

std::string redStr(const std::string& str) {
    return setRed + str + endColor;
}

std::string getResultInfoHeader() {
    return "| TEST | EXPECTED | OUTPUT | RESULT |\n|-----------------------------------|";
}

template<typename T>
std::string getTestResultInfo(const std::string& testInfo, T expected, T result) {
    std::stringstream ss;
    ss << "| " << testInfo << " | " << expected << " | " << result << " | " << getColoredResult(expected == result) << " |" ;
    return ss.str();
}

template<typename T>
std::string getTestResultInfo(const std::string& testInfo, const std::vector<T> expected, T result) {
    bool passed = false;
    for(auto res : expected) {
        if (res == result)
            passed = true;
    }
    std::stringstream ss;
    ss << "| " << testInfo << " | " << expected << " | " << result << " | " << getColoredResult(passed) << " |" ;
    return ss.str();
}