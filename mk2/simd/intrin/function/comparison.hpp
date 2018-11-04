//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <mk2/simd/intrin/type_traits/architecture.hpp>
#include <mk2/simd/intrin/wrapper/intel/comparison.hpp>

namespace mk2 { namespace simd { namespace intrin {
namespace function {

#define MK2_INTRIN_COMPARISON_TEMPLATE(op)                                                                              \
    namespace detail                                                                                                    \
    {                                                                                                                   \
        template <class Type, bool Ordered, bool Signaling>                                                             \
        struct cmp_##op##_impl                                                                                          \
        {                                                                                                               \
            static decltype(auto) func(Type a, Type b, mk2::simd::intrin::arch_avx)                                     \
            {                                                                                                           \
                return mk2::simd::intrin::wrapper::intel::cmp_##op<Type, Ordered, Signaling>(a, b);                     \
            }                                                                                                           \
        };                                                                                                              \
    }                                                                                                                   \
    template <class Type, bool Ordered = true, bool Signaling = false>                                                  \
    inline decltype(auto) cmp_##op(Type a, Type b)                                                                      \
    {                                                                                                                   \
        return detail::cmp_##op##_impl<Type, Ordered, Signaling>::func(a, b, mk2::simd::intrin::available_architecture);\
    }

    MK2_INTRIN_COMPARISON_TEMPLATE(eq)
    MK2_INTRIN_COMPARISON_TEMPLATE(lt)
    MK2_INTRIN_COMPARISON_TEMPLATE(le)
    MK2_INTRIN_COMPARISON_TEMPLATE(neq)
    MK2_INTRIN_COMPARISON_TEMPLATE(nlt)
    MK2_INTRIN_COMPARISON_TEMPLATE(nle)


#undef MK2_INTRIN_COMPARION_TEMPLETE

}
}}}