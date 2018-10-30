//
// Created by Himatya on 2018-10-30.
//

#pragma once

#include <boost/preprocessor.hpp>

#define MK2_PP_IMPL_FOR_PRED(r, state)  BOOST_PP_LESS(BOOST_PP_TUPLE_ELEM(0, state), BOOST_PP_TUPLE_ELEM(1, state))
#define MK2_PP_IMPL_FOR_OP(r, state)    (BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(0, state)), BOOST_PP_TUPLE_ELEM(1, state), BOOST_PP_TUPLE_ELEM(2, state))
#define MK2_PP_IMPL_FOR_MACRO(r, state) BOOST_PP_COMMA_IF(BOOST_PP_TUPLE_ELEM(0, state)) BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_ELEM(0, state), BOOST_PP_TUPLE_ELEM(2, state))

#define MK2_PP_UNPACK_TUPLE_IMPL(first, last, x) BOOST_PP_FOR((first, last, x), MK2_PP_IMPL_FOR_PRED, MK2_PP_IMPL_FOR_OP, MK2_PP_IMPL_FOR_MACRO)
#define MK2_PP_UNPACK_TUPLE(x) MK2_PP_UNPACK_TUPLE_IMPL(0, BOOST_PP_TUPLE_SIZE(x), x)
