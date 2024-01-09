#ifndef TYPE_TRAITS
#define TYPE_TRAITS

template <typename T, T value> 
struct integral_constant;

template <bool value>  
using bool_constant = integral_constant<bool, value>;

#endif