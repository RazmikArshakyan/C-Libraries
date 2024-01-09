#include <iostream>
#include <vector>
#include <forward_list>
#include <list>

#include "iterator/input_iterator.hpp"
#include "type_traits"

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    input_iterator<int> iter(numbers.data());
    input_iterator<int> end(numbers.data() + numbers.size());

    while (iter != end) {
        std::cout << *iter << " ";
        ++iter;
    }

    return 0;
}
