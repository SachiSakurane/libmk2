//
// Created by Himatya on 2018-10-29.
//

#pragma once

#include <boost/preprocessor.hpp>
#include <mk2/preprocessor/unpack_tuple.hpp>

#define MK2_PP_ADD_CLASS_IMPL_FOR_PRED(r, state) BOOST_PP_LESS(BOOST_PP_TUPLE_ELEM(0, state), BOOST_PP_TUPLE_ELEM(1, state))
#define MK2_PP_ADD_CLASS_IMPL_FOR_OP(r, state) (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(0, state)), BOOST_PP_TUPLE_ELEM(1, state), BOOST_PP_TUPLE_ELEM(2, state))
#define MK2_PP_ADD_CLASS_IMPL_FOR_MACRO(r, state) BOOST_PP_COMMA_IF(BOOST_PP_TUPLE_ELEM(0, state)) class BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_ELEM(0, state), BOOST_PP_TUPLE_ELEM(2, state))

#define MK2_PP_ADD_CLASS_IMPL(first, last, ...) BOOST_PP_FOR((first, last, (__VA_ARGS__)), MK2_PP_ADD_CLASS_IMPL_FOR_PRED, MK2_PP_ADD_CLASS_IMPL_FOR_OP, MK2_PP_ADD_CLASS_IMPL_FOR_MACRO)
#define MK2_PP_ADD_CLASS(...) MK2_PP_ADD_CLASS_IMPL(0, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), __VA_ARGS__)

#define MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func, return_type, ...)   \
template<> struct base_struct<__VA_ARGS__>                                          \
{                                                                                   \
    template<class ...Args> static return_type func(Args&&... args)                 \
    { return base_func(std::forward<Args>(args)...); }                              \
};

#define MK2_PP_REPLACE_TO_TEMPLATE(func_name, base_func, return_type, signature, args, template_name)   \
namespace detail                                                                                        \
{                                                                                                       \
    template<MK2_PP_ADD_CLASS(MK2_PP_UNPACK_TUPLE(template_name))> struct func_name##_impl{};           \
    MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(func_name##_impl, base_func, return_type)                     \
}                                                                                                       \
template<MK2_PP_ADD_CLASS(MK2_PP_UNPACK_TUPLE(template_name))>                                          \
inline return_type func_name(MK2_PP_UNPACK_TUPLE(signature))                                            \
{ return detail::func_name##_impl<MK2_PP_UNPACK_TUPLE(template_name)>::func(MK2_PP_UNPACK_TUPLE(args)); }


#define MK2_PP_REPLACE_TO_TEMPLATE_ADDITIVE(func_name, base_func, return_type, signature, args, template_name)  \
namespace detail                                                                                                \
{                                                                                                               \
    MK2_PP_REPLACE_TO_TEMPLATE_ASSOCIATOR(func_name##_impl, base_func, return_type)                             \
}                                                                                                               \
template<MK2_PP_ADD_CLASS(MK2_PP_UNPACK_TUPLE(template_name))>                                                  \
inline return_type func_name(MK2_PP_UNPACK_TUPLE(signature))                                          \
{ return detail::func_name##_impl<MK2_PP_UNPACK_TUPLE(template_name)>::func(MK2_PP_UNPACK_TUPLE(args)); }
