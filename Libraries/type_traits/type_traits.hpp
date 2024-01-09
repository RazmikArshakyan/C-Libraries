#ifndef TYPE_TRAITS
#define TYPE_TRAITS

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
struct is_same : false_type 
{
};

template <typename T>  
struct is_same<T, T> : true_type
{
};

template <typename T, typename U> 
inline constexpr bool is_same_v = is_same<T, U>::value;

#endif
