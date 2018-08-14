//
// Created by Himatya on 2018/08/12.
//

#pragma once

namespace mk2 { namespace simd { namespace ipp { namespace function {
    
    #define MK2_IPP_C1(a) class a
    #define MK2_IPP_C2(a, b) class a, class b
    #define MK2_IPP_C3(a, b, c) class a, class b, class c
    #define MK2_IPP_C4(a, b, c, d) class a, class b, class c, class d
    #define IPP_GET_MACRO_NAME(_1, _2, _3, _4, NAME, ...) NAME
    #define IPP_ADD_CLASS(...) IPP_GET_MACRO_NAME(__VA_ARGS__, MK2_IPP_C4, MK2_IPP_C3, MK2_IPP_C2, MK2_IPP_C1)(__VA_ARGS__)
    
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