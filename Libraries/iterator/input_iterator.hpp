#ifndef INPUT_ITERATOR
#define INPUT_ITERATOR

#include <cstddef>
#include <iterator>

template <typename T> 
class input_iterator {
public: 
    using value_type = T;
    using reference = T const&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    constexpr input_iterator() noexcept 
        : input_iter{} {}

    constexpr input_iterator(pointer input_iter) noexcept
        : input_iter(input_iter) {}

    constexpr input_iterator(const input_iterator& other) noexcept
        : input_iter(other.input_iter) {}
    
    constexpr input_iterator& operator=(const input_iterator& other) {
        input_iter = other.input_iter;
        return *this;
    }

    constexpr input_iterator& operator++() {
        input_iter++;
        return *this;
    }

    constexpr reference operator*() const {
        return *input_iter;
    }

    constexpr pointer operator->() const {
        return input_iter;
    }

    constexpr input_iterator operator++(int) {
        return input_iterator(input_iter++);
    }

    constexpr bool operator==(const input_iterator& other) const noexcept {
        return (input_iter == other.input_iter);
    }

    constexpr bool operator!=(const input_iterator& other) const noexcept {
        return (input_iter != other.input_iter);
    }
 
private:  
    T* input_iter;
};

#endif