//
// Created by Himatya on 2018/08/12.
//

#pragma once

#include <boost/preprocessor.hpp>

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
	#define IPP_ADD_CLASS_IMPL_FOR_PRED(r, state) BOOST_PP_LESS(BOOST_PP_TUPLE_ELEM(0, state), BOOST_PP_TUPLE_ELEM(1, state))
	#define IPP_ADD_CLASS_IMPL_FOR_OP(r, state) (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(0, state)), BOOST_PP_TUPLE_ELEM(1, state), BOOST_PP_TUPLE_ELEM(2, state))
	#define IPP_ADD_CLASS_IMPL_FOR_MACRO(r, state) BOOST_PP_COMMA_IF(BOOST_PP_TUPLE_ELEM(0, state)) class BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_ELEM(0, state), BOOST_PP_TUPLE_ELEM(2, state))

	#define IPP_ADD_CLASS_IMPL(first, last, ...) BOOST_PP_FOR((first, last, (__VA_ARGS__)), IPP_ADD_CLASS_IMPL_FOR_PRED, IPP_ADD_CLASS_IMPL_FOR_OP, IPP_ADD_CLASS_IMPL_FOR_MACRO)
	#define IPP_ADD_CLASS(...) IPP_ADD_CLASS_IMPL(0, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), __VA_ARGS__)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func, ...)                                         \
    template<> struct base_struct<__VA_ARGS__>                                                                          \
    { template<class ...Args> static IppStatus func(Args&&... args) { return base_func(std::forward<Args>(args)...); }};
    
    //#define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(base_struct, base_func, descriptor, ...)   \
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32f##descriptor, __VA_ARGS__)   \
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64f##descriptor, __VA_ARGS__)   \
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_32fc##descriptor, __VA_ARGS__) \
    //IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func##_64fc##descriptor, __VA_ARGS__)
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE(func_name, base_func, descriptor, ...)                                \
    namespace detail                                                                                                \
    {                                                                                                               \
        template<IPP_ADD_CLASS(__VA_ARGS__)> struct func_name##_impl{};                                             \
        IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(func_name##_impl, base_func, descriptor)                       \
    }                                                                                                               \
    template<IPP_ADD_CLASS(__VA_ARGS__)> inline IppStatus func_name(IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE)    \
    { return detail::func_name##_impl<__VA_ARGS__>::func(IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS); }
    
    #define IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ADDITIVE(func_name, base_func, descriptor, ...)                       \
    namespace detail                                                                                                \
    {                                                                                                               \
        IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ASSOCIATOR(func_name##_impl, base_func, descriptor)                       \
    }                                                                                                               \
    template<IPP_ADD_CLASS(__VA_ARGS__)> inline IppStatus func_name(IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_SIGNATURE)    \
    { return detail::func_name##_impl<__VA_ARGS__>::func(IPP_FUNCTIONS_REPLACE_TO_TEMPLATE_ARGS); }
}
}
}
}