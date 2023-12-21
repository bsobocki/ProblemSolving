#include <string>
#include <sstream>

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