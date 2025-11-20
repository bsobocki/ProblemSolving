# C++ Custom Testing Utilities (`utils.hpp`)

This header file provides a lightweight, header-only testing framework designed to run unit tests in the console with formatted output, color coding, and generic container support. It leverages modern C++ features to keep the main solution files clean and focused on algorithms.

## Key Features

*   **Generic Test Runner:** A template-based engine (`runTests`) that accepts any struct-based test cases and lambda validators.
*   **SFINAE Container Printing:** Automatically detects iterable containers (vectors, lists, etc.) and prints them nicely (e.g., `{a, b, c}`), while correctly excluding `std::string` to print them normally.
*   **C++20 Concepts:** Uses `requires` clauses to constrain template types.
*   **Visual Feedback:** ANSI color codes for ✅ Passed (Green) and ❌ Failed (Red) results.
*   **Table Formatting:** Outputs results in a clean, aligned pipe-table format.

## Implementation Details

### 1. SFINAE Container Detection
To allow `std::cout << vector` to work without breaking `std::cout << string`, the code uses **Substitution Failure Is Not An Error (SFINAE)**.

The struct `is_container` checks if a type has `begin()` and `end()` iterators but explicitly returns `false` for `std::string` types. This ensures we don't format strings as `{c, h, a, r}`.

```cpp
// SFINAE Trait
template<typename T>
struct is_container<T, std::void_t<...>> : std::bool_constant<
    !std::is_same_v<T, std::string> && ... 
> {};
```

### 2. C++20 Concepts & Formatting
The code utilizes C++20 features for type safety and string formatting:
*   **`std::format`:** Used for constructing summary messages.
*   **`requires` clauses:** Ensures type constraints on template functions.

```cpp
template<typename T>
requires (!std::same_as<T, bool>)
std::string getTestResultInfo(...)
```

### 3. Flexible Test Runner
The `runTests` function takes a vector of test objects and a lambda. This allows the testing logic to be decoupled from the data.

```cpp
template<typename TestType, typename TestFunc>
void runTests(const std::vector<TestType>& tests, TestFunc runTest) {
    // Iterates tests, tracks pass/fail count, and prints summary
}
```

## Usage Example

```cpp
#include "utils/utils.hpp"

struct TestCase {
    int input;
    int expected;
};

void testSquare() {
    std::vector<TestCase> tests = { {2, 4}, {3, 9}, {4, 16} };

    runTests(tests, [](const TestCase& t) {
        int result = t.input * t.input;
        // Helper formats the output row
        std::cout << getTestResultInfo("Square Test", t.expected, result) << std::endl;
        return result == t.expected;
    });
}
```

## Requirements
*   **C++ Standard:** C++20 or later (due to `<format>` and `requires`).
*   **OS:** Any (ANSI colors require a terminal that supports them, such as Linux bash, macOS zsh, or Windows Terminal).