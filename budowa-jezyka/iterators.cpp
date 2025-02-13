#include <iostream>
#include <vector>
#include <list>
#include <map>

int main() {
    // 1. Iterators with a vector
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::cout << "Vector elements using iterator: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 2. Iterators with a list
    std::list<std::string> lst = {"apple", "banana", "cherry"};

    std::cout << "List elements using iterator: ";
    for (std::list<std::string>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 3. Iterators with a map (key-value pairs)
    std::map<int, std::string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};

    std::cout << "Map elements using iterator: ";
    for (std::map<int, std::string>::iterator it = mp.begin(); it != mp.end(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }
    std::cout << std::endl;

    // 4. Using reverse iterator with vector
    std::cout << "Vector elements in reverse order: ";
    for (std::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // 5. Using const iterator with vector (read-only access), returns a const pointer
    std::cout << "Vector elements using const iterator: ";
    for (std::vector<int>::const_iterator cit = vec.cbegin(); cit != vec.cend(); ++cit) {
        std::cout << *cit << " ";
    }
    std::cout << std::endl;

    return 0;
}
