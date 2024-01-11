#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <cstdint>
#include <array>
#include <type_traits>

#include "iterator/input_iterator.hpp"
#include "type_traits/type_traits.hpp"

void foo() {}

static_assert
(
    is_void_v<void> == true and
    is_void_v<const void> == true and
    is_void_v<volatile void> == true and
    is_void_v<void*> == false and
    is_void_v<int> == false and
    is_void_v<decltype(foo)> == false and
    is_void_v<is_void<void>> == false
);

static_assert(is_null_pointer_v<decltype(nullptr)>);
static_assert(!is_null_pointer_v<int*>);
//static_assert(!is_pointer_v<decltype(nullptr)>);
//static_assert(is_pointer_v<int*>);

class A {};

enum class Ec : int {};
static_assert(std::is_enum_v<Ec> == true);
 
static_assert(std::is_enum_v<int> == false);

template<typename>
struct PM_traits {};
 
template<class T, class U>
struct PM_traits<U T::*> { using member_type = U; };

int f() { return 1; }

static_assert(
           ! is_pointer<A>::value
        && ! is_pointer_v<A>    
        && ! is_pointer<A>()    
        && ! is_pointer<A>{}    
        && ! is_pointer<A>()()  
        && ! is_pointer<A>{}()  
        &&   is_pointer_v<A*>
        &&   is_pointer_v<A const* volatile>
        && ! is_pointer_v<A&>
        &&   is_pointer_v<void*>
        && ! is_pointer_v<int>
        &&   is_pointer_v<int*>
        &&   is_pointer_v<int**>
        && ! is_pointer_v<int[10]>
        && ! is_pointer_v<std::nullptr_t>
        &&   is_pointer_v<void (*)()>
    );

enum class E {};
 
union U { class UC {}; };

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    input_iterator<int> iter(numbers.data());
    input_iterator<int> end(numbers.data() + numbers.size());

    while (iter != end) {
        std::cout << *iter << " ";
        ++iter;
    }
    std::cout << std::endl;
    
    std::cout << is_same<int, std::int32_t>::value << ' '; 
    std::cout << is_same<int, std::int64_t>::value << ' '; 
    std::cout << is_same<int, short>::value << ' '; 
    std::cout << is_same<char, bool>::value << ' '; 
    std::cout << is_same<long long, std::int64_t>::value << ' '; 
    std::cout << is_same_v<int, std::int32_t> << ' ';  
    std::cout << is_same_v<int, std::int64_t> << '\n';

    std::cout << is_integral<int>::value << " ";
    std::cout << is_integral<double>::value << " ";
    std::cout << is_integral<char>::value << " ";
    std::cout << is_integral<float>::value << std::endl;

    std::cout << std::boolalpha;
    std::cout << "A: " << is_floating_point<A>::value << '\n';
    std::cout << "float: " << is_floating_point<float>::value << '\n';
    std::cout << "float&: " << is_floating_point<float&>::value << '\n';
    std::cout << "double: " << is_floating_point<double>::value << '\n';
    std::cout << "double&: " << is_floating_point<double&>::value << '\n';
    std::cout << "int: " << is_floating_point<int>::value << '\n';

    std::cout << std::boolalpha;
    std::cout << is_array<A>::value << '\n';
    std::cout << is_array<A[]>::value << '\n';
    std::cout << is_array<A[3]>::value << '\n';
    std::cout << is_array<float>::value << '\n';
    std::cout << is_array<int>::value << '\n';
    std::cout << is_array<int[]>::value << '\n';
    std::cout << is_array<int[3]>::value << '\n';
    std::cout << is_array<std::array<int, 3>>::value << '\n';

    std::cout << std::boolalpha;
    std::cout << "#1 " << is_function_v<A> << '\n';
    std::cout << "#2 " << is_function_v<int(int)> << '\n';
    std::cout << "#3 " << is_function_v<decltype(f)> << '\n';
    std::cout << "#4 " << is_function_v<int> << '\n';
 
    class C {};
    std::cout << "Is member object pointer?\n" << std::boolalpha
              << is_member_object_pointer_v<int(C::*)>
              << ": int(C::*)\n"
              << is_member_object_pointer_v<int(C::*)()>
              << ": int(C::*)()\n";

    return 0;
}
