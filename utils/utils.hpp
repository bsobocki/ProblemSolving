#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <format>

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

enum class PrintFlag : int8_t {
    SHOW_EVERYTHING,
    SHOW_FAILS_ONLY
};

template<typename T>
requires (!std::same_as<T, bool>)
std::string getTestResultInfo(const std::string& testInfo, T result, bool passed, PrintFlag flag = PrintFlag::SHOW_EVERYTHING) {
    const bool showFailsOnly = flag == PrintFlag::SHOW_FAILS_ONLY;
    if (!showFailsOnly || (showFailsOnly && !passed) ) {
        std::stringstream ss;
        ss << "| " << testInfo << " | | " << result << " | " << getColoredResult(passed) << " |" ;
        return ss.str();
    }
    return "";
}

template<typename T>
std::string getTestResultInfo(const std::string& testInfo, T expected, T result, PrintFlag flag = PrintFlag::SHOW_EVERYTHING) {
    const bool showFailsOnly = flag == PrintFlag::SHOW_FAILS_ONLY;
    bool passed = expected == result;
    if (!showFailsOnly || (showFailsOnly && !passed) ) {
        std::stringstream ss;
        ss << "| " << testInfo << " | " << expected << " | " << result << " | " << getColoredResult(passed) << " |" ;
        return ss.str();
    }
    return "";
}

template<typename T>
std::string getTestResultInfo(const std::string& testInfo, const std::vector<T> possibleResults, T result, PrintFlag flag = PrintFlag::SHOW_EVERYTHING) {
    bool passed = false;
    for(auto res : possibleResults) {
        if (res == result)
            passed = true;
    }

    const bool showFailsOnly = flag == PrintFlag::SHOW_FAILS_ONLY;
    if (!showFailsOnly || (showFailsOnly && !passed) ) {
        std::stringstream ss;
        ss << "| " << testInfo << " | " << possibleResults << " | " << result << " | " << getColoredResult(passed) << " |" ;
        return ss.str();
    }
    return "";
}

template<typename TestType, typename TestFunc>
void runTests(const std::vector<TestType>& tests, TestFunc runTest) {
    std::cout << getResultInfoHeader() << std::endl;

    const size_t passedCount = std::count_if(tests.begin(), tests.end(), runTest);
    
    if (passedCount == tests.size())
        std::cout << std::endl << greenStr("✓ ALL TESTS PASSED!") << std::endl;
    else
        std::cout << std::endl << redStr(std::format("✗ {}/{} TESTS FAILED!", tests.size()-passedCount, tests.size())) << std::endl; 
}