#ifndef TYPE_TRAITS
#define TYPE_TRAITS

#include <cstddef>
#include <concepts>

template <typename T, T val> 
struct integral_constant;

template <bool val>  
using bool_constant = integral_constant<bool, val>;

template <class T, T val> 
struct integral_constant {
    static constexpr T value = val; 
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <typename T, typename U> 
struct is_same : false_type {};

template <typename T>  
struct is_same<T, T> : true_type {};

template <typename T, typename U> 
inline constexpr bool is_same_v = is_same<T, U>::value;

template <typename T>  
struct remove_cv;

template <typename T> 
struct remove_const;  

template <typename T>  
struct remove_volatile;

template <typename T>  
struct remove_cv {
    using type = T;
};

template <typename T> 
struct remove_cv<const T> {
    using type = T;
};

template <typename T> 
struct remove_cv<volatile T> {
    using type = T;
};

template <typename T> 
struct remove_cv<const volatile T> {
    using type = T;
};

template <typename T> 
struct remove_const {
    using type = T;
};

template <typename T> 
struct remove_const<const T> {
    using type = T;
};

template <typename T> 
struct remove_volatile {
    using type = T;
};

template <typename T> 
struct remove_volatile<volatile T> {
    using type = T;
};

template <typename T> 
using remove_cv_t = typename remove_cv<T>::type;

template <typename T> 
using remove_const_t = typename remove_const<T>::type;

template <typename T> 
using remove_volatile_t = typename remove_volatile<T>::type;

template <class T>  
struct is_void : is_same<void, typename remove_cv<T>::type> {};

template <typename T> 
inline constexpr bool is_void_v = is_void<T>::value;

template <typename T>  
struct is_null_pointer : is_same<std::nullptr_t, remove_cv_t<T>> {};

template <typename T> 
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

template <typename T>  
concept integral_requirement = requires (T type, T* pointer, void (*foo)(T)) {
    { reinterpret_cast<T>(type) }->std::same_as<T>; 
    { foo(0) }->std::same_as<void>; 
    { pointer + type }->std::same_as<T*>;
};

template <typename T> 
struct is_integral : bool_constant<integral_requirement<T>> {};

template <typename T> 
inline constexpr bool is_integral_v = is_integral<T>::value;

template <typename T> 
struct is_floating_point : integral_constant<bool, 
    is_same_v<float, remove_cv_t<T>> 
    || is_same_v<double, remove_cv_t<T>>
    || is_same_v<long double, remove_cv_t<T>>
    > {};

template< class T >
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;

template <typename T>  
struct is_array : false_type {};

template <typename T> 
struct is_array<T[]> : true_type {};

template <typename T, std::size_t N> 
struct is_array<T[N]> : true_type {};

template <typename T> 
inline constexpr bool is_array_v = is_array<T>::value;

template <typename> 
struct is_function : false_type {};

template <typename T, typename... Args>  
struct is_function<T(Args...)> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......)> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) const> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) volatile> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) const volatile> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) const> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) volatile> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) const volatile> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) &> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) const&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) volatile&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) const volatile&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) &> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) const&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) volatile&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) &&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) const&&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) volatile&&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args...) const volatile&&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) &&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) const&&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) volatile&&> : true_type {};

template <typename T, typename... Args> 
struct is_function<T(Args......) const volatile&&> : true_type {};

template <typename T> 
inline constexpr bool is_function_v = is_function<T>::value;

template <typename T>  
struct is_pointer : false_type {};

template <typename T> 
struct is_pointer<T*> : true_type {};

template <typename T> 
struct is_pointer<T* const> : true_type {};

template <typename T> 
struct is_pointer<T* volatile> : true_type {};

template <typename T> 
struct is_pointer<T* const volatile> : true_type {};

template <typename T>  
inline constexpr bool is_pointer_v = is_pointer<T>::value;

template <typename T> 
struct is_lvalue_reference : false_type {};

template <typename T> 
struct is_lvalue_reference<T&> : true_type {};

template <typename T>  
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

template <typename T> 
struct is_rvalue_reference : false_type {};

template <typename T> 
struct is_rvalue_reference<T&&> : true_type {};

template <typename T>  
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

template <typename T> 
struct is_reference : false_type {};

template <typename T> 
struct is_reference<T&> : true_type {};

template <typename T> 
struct is_reference<T&&> : true_type {};

template <typename T>  
inline constexpr bool is_reference_v = is_reference<T>::value;

template <typename T>  
struct is_enum : integral_constant<bool, 
    !is_integral_v<T> &&
    !is_array_v<T> && 
    !is_floating_point_v<T> &&
    !is_void_v<T> &&
    !is_function_v<T> &&
    !is_pointer_v<T> &&
    !is_reference_v<T>>
    {};

template <typename T>  
inline constexpr bool is_enum_v = is_enum<T>::value;

#endif
