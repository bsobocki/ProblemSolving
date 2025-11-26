#include <iostream>
#include <utils/utils.hpp>

using namespace std;
using grid_t = vector<vector<int>>;
using memo_t = vector<vector<vector<int>>>;

constexpr int modulo = 1000000007;

int paths(int i, int j, int reminder, grid_t& grid, int k) {
    const int rows = grid.size();
    // from constraints we know that grid is not empty
    const int columns = grid[0].size();

    // there is no path that goes outside matrix
    if (i >= rows || j >= columns) return 0;

    int currReminder = (reminder + grid[i][j]) % k;

    // we reached the end, so there is only one possible path from end to end
    // it depends of current remainder (if it is 0 then we know that sum is divisible by k)
    if (i == rows-1 && j == columns-1) return currReminder == 0;

    // otherwise we are somewhere in the middle
    // we need to check paths when we move right and when we moved down passing curent reminder
    // NOTE: those numbers can be too big for integer, so we need to do modulo on each of them and the sum
    return (
            paths(i + 1, j, currReminder, grid, k) % modulo +
            paths(i, j + 1, currReminder, grid, k) % modulo
        ) % modulo;
}

// as a first attempt do a recursion
// Time Complexity: O(2^(nm))
// Space Complexity: O(n)
// (constant additional memory for one function call allocated O(n) times on the stack at once)
int numberOfPathsRecursion(vector<vector<int>>& grid, int k) {
    const int rows = grid.size();
    // from constraints we know that grid is not empty
    const int columns = grid[0].size();
    
    // begin on state: start [0,0] with no reminder (0)
    return paths(0, 0, 0, grid, k);
}

// the next step to make it better (because time complexity O(2^(nm)) is way too big)
// is to save the result for each state we are currently in
int paths(int i, int j, int reminder, memo_t& mem, const grid_t& grid, int k) {
    const int rows = grid.size();
    // from constraints we know that grid is not empty
    const int columns = grid[0].size();

    if (i >= rows || j >= columns) return 0;

    if (mem[i][j][reminder] != -1) return mem[i][j][reminder];

    int currReminder = (reminder + grid[i][j]) % k;

    // if we are at the last element then we can have max 1 path from it to the end
    // but only if reminder added to current value is divisible by k (we reached a sum divisible by k)
    if (i == rows-1 && j == columns-1) {
        // if we get into current i,j with this reminder for the first time
        // then we just save this state into our memory
        mem[i][j][reminder] = currReminder == 0; // at the end of the matrix we can only have 1 or 0 for each state
    }
    else {
        int res = (
                paths(i + 1, j, currReminder, mem, grid, k) % modulo + 
                paths(i, j + 1, currReminder, mem, grid, k) % modulo
            ) % modulo;

        mem[i][j][reminder] = res;
    }

    return mem[i][j][reminder];
}

// Time Complexity: O(nmk) because we are going through the whole table 'mem'
// Space Complexity: O(nmk) - mem
int numberOfPathsMemorized(const vector<vector<int>>& grid, int k) {
    const int rows = grid.size();
    // from constraints we know that grid is not empty
    const int columns = grid[0].size();

    // initialize our memory - we will go through each path checking only reminders from partial sums
    // that is why 3th demention vector is only size k (1 - 50) because there is only k reminders of modulo k operation
    // if we get into position [i,j] with current reminder then we check if we had this state already
    // if yes, then we just returns it, because we can't have different result then previously calculated for that state
    vector<vector<vector<int>>> mem(rows, vector<vector<int>>(columns, vector<int>(k, -1)));

    return paths(0, 0, 0, mem, grid, k);
}

struct Test {
    vector<vector<int>> grid;
    int k;
    int expectedResult;

    std::string getInfo() const {
        stringstream ss;
        ss << " k: " << k << "grid: { ";
        for (auto row : grid) {
            ss << row << " | ";
        }
        ss << " }";
        return ss.str();
    }
};

void runSolution() {
    const std::vector<Test> tests = {
        // some basic tests

         // Example 1
        { 
            { {5,2,4}, {3,0,5}, {0,7,2} }, // grid
            3,                             // k
            2                              // expectedResult
        },
        // Example 2
        { 
            { {0,0} }, 
            5, 
            1 
        },
        // Example 3
        { 
            { {7,3,4,9}, {2,3,6,2}, {2,3,7,0} }, 
            1, 
            10 
        },
        // Additional Test: 1x1 grid, divisible
        { 
            { {5} }, 
            5, 
            1 
        },
        // Additional Test: 1x1 grid, not divisible
        { 
            { {5} }, 
            3, 
            0 
        }
    };

    runTests(tests, [](const Test& test){
        int result = numberOfPathsMemorized(test.grid, test.k);
        std::cout << getTestResultInfo(test.getInfo(), test.expectedResult, result) << std::endl;
        return result == test.expectedResult;
    });
}