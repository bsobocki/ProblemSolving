#include <iostream>
#include <utils/utils.hpp>

using namespace std;

/*
    your solution function
*/

struct Test {
    // input
    // expectedResult;

    std::string getInfo() const {
        stringstream ss;
        // ss << input;
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {

    };

    runTests(tests, [](const Test& test){
        // result_type result = solution(test.input);
        // std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        // return result == test.expectedResult;
        return true;
    });
}