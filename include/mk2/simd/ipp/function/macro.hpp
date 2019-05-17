//
// Created by Himatya on 2018/08/12.
//

#pragma once

#include <boost/preprocessor.hpp>
#include <mk2/preprocessor/template_wrapper.hpp>

#define MK2_IPP_NAME_FUNC(dif, base, descriptor) BOOST_PP_CAT(base, BOOST_PP_CAT(dif, descriptor))

#define MK2_IPP_REPLACE_TEMPLATE(name, base_name, descriptor, signature, args, template_name, associator)   \
MK2_IPP_REPLACE_TEMPLATE_REDUNDANCY(name, base_name, descriptor, signature, args, template_name, template_name, associator)

#define MK2_IPP_REPLACE_TEMPLATE_REDUNDANCY(name, base_name, descriptor, signature, args, template_name, template_init, associator)    \
MK2_PP_REPLACE_TO_TEMPLATE_REDUNDANCY(name, MK2_IPP_NAME_FUNC, signature, args, template_name, template_init, associator, base_name, descriptor)


#define MK2_IPP_REPLACE_TEMPLATE_ADDITIVE(name, base_name, descriptor, signature, args, template_name, associator)   \
MK2_IPP_REPLACE_TEMPLATE_ADDITIVE_REDUNDANCY(name, base_name, descriptor, signature, args, template_name, template_name, associator)

#define MK2_IPP_REPLACE_TEMPLATE_ADDITIVE_REDUNDANCY(name, base_name, descriptor, signature, args, template_name, template_init, associator)    \
MK2_PP_REPLACE_TO_TEMPLATE_ADDITIVE_REDUNDANCY(name, MK2_IPP_NAME_FUNC, signature, args, template_name, template_init, associator, base_name, descriptor)
