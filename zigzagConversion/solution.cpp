#include <iostream>
#include <vector>

using namespace std;

std::string setGreen = "\033[32m";
std::string setRed = "\033[31m";
std::string endColor = "\033[m";

std::string getColoredResult(bool isPassed) {
    return isPassed ? setGreen + "Passed" + endColor : setRed + "Failed" + endColor;
}

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1 || s.length() == 0 || numRows >= s.length()) return s;

        string result;

        // we are going through all rows by taking numRows-1 steps twice (up and down) 
        int initStep = (numRows - 1) * 2;

        // for the first [0] row
        for (int i = 0; i < s.length(); i += initStep)
            result += s[i];
 
        // even steps are different than odd steps (expect the middle row when numRows is odd)
        int evenStep = 2; // for second row we make 2 steps to the next letter
        int oddStep = initStep-2; // for second row we will make less steps by 2 than initStep number

        // for steps inside
        for (int currRowNum = 1; currRowNum < numRows-1; currRowNum++) {
            bool isOddStep = true;
            int i = currRowNum;
            while (i < s.length()) {
                result += s[i];

                if (isOddStep) i += oddStep;
                else i += evenStep;
                isOddStep = !isOddStep;
            }
            // with each row we are lower, so odd steps will be shorter by 2 and even steps will be longer by 2
            oddStep -= 2;
            evenStep += 2;
        }

        // for the last [numRows-1] row
        for (int i = numRows-1; i < s.length(); i += initStep)
            result += s[i];

        return result;
    }
};

struct Test {
    string s;
    int numRows;
    string result;
};

void runSolution() {
    std::vector<Test> tests = {
        {"PAYPALISHIRING", 1, "PAYPALISHIRING"},
        {"PAYPALISHIRING", 2, "PYAIHRNAPLSIIG"},
        {"PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"},
        {"PAYPALISHIRING", 4, "PINALSIGYAHRPI"},
        {"PAYPALISHIRING", 5, "PHASIYIRPLIGAN"},
        {"PAYPALISHIRING", 6, "PRAIIYHNPSGAIL"},
        {"PAYPALISHIRING", 7, "PNAIGYRPIAHLSI"},
        {"PAYPALISHIRING", 8, "PAGYNPIARLIIHS"},
        {"PAYPALISHIRING", 9, "PAYPGANLIIRSIH"},
        {"PAYPALISHIRING", 10, "PAYPALGINSIHRI"},
        {"AB", 1, "AB"},
    };
    Solution sol;
    std::cout << "Input | Expected | Output | Result" << endl;
    for (auto& test : tests) {
        string result = sol.convert(test.s, test.numRows);
        cout << test.s << " | " << test.numRows << " | " << test.result << " | " << result << " | " << getColoredResult(result == test.result) << endl;
    }
}