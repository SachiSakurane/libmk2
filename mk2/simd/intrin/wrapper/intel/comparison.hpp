//
// Created by Himatya on 2018-11-04.
//

#pragma once

#include <mk2/preprocessor/template_wrapper.hpp>
#include <mk2/simd/intrin/include.hpp>
#include <mk2/simd/intrin/utility/archtecture_requirement.hpp>

namespace mk2 { namespace simd { namespace intrin { namespace wrapper { namespace intel {

    // __mm_cmp_xxがマクロであるため実態化がうまくいかない

#define MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE(base_struct, type, macro, os, oq, us, uq) \
    template <> struct base_struct<type, true, true>                                        \
    { static decltype(auto) func(type a, type b) { return macro(a, b, os); } };             \
    template <> struct base_struct<type, true, false>                                       \
    { static decltype(auto) func(type a, type b) { return macro(a, b, oq); } };             \
    template <> struct base_struct<type, false, true>                                       \
    { static decltype(auto) func(type a, type b) { return macro(a, b, us); } };             \
    template <> struct base_struct<type, false, false>                                      \
    { static decltype(auto) func(type a, type b) { return macro(a, b, uq); } };

#define MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE_FUNCS(type, macro)                                                        \
    MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE(cmp_eq_impl,  type, macro, _CMP_EQ_OS, _CMP_EQ_OQ, _CMP_EQ_US, _CMP_EQ_UQ)    \
    MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE(cmp_lt_impl,  type, macro, _CMP_LT_OS, _CMP_LT_OQ, _CMP_LT_OS, _CMP_LT_OQ)    \
    MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE(cmp_le_impl,  type, macro, _CMP_LE_OS, _CMP_LE_OQ, _CMP_LE_OS, _CMP_LE_OQ)    \
    MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE(cmp_neq_impl, type, macro, _CMP_NEQ_OS, _CMP_NEQ_OQ, _CMP_NEQ_US, _CMP_NEQ_UQ)\
    MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE(cmp_nlt_impl, type, macro, _CMP_NLT_US, _CMP_NLT_UQ, _CMP_NLT_US, _CMP_NLT_UQ)\
    MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE(cmp_nle_impl, type, macro, _CMP_NLE_US, _CMP_NLE_UQ, _CMP_NLE_US, _CMP_NLE_UQ)

    namespace detail
    {
        template<class Type, bool Ordered, bool Signaling> struct cmp_eq_impl{};
        template<class Type, bool Ordered, bool Signaling> struct cmp_lt_impl{};
        template<class Type, bool Ordered, bool Signaling> struct cmp_le_impl{};
        template<class Type, bool Ordered, bool Signaling> struct cmp_neq_impl{};
        template<class Type, bool Ordered, bool Signaling> struct cmp_nlt_impl{};
        template<class Type, bool Ordered, bool Signaling> struct cmp_nle_impl{};

        MK2_ARCHTECTURE_REQUIREMENT_AVX(MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE_FUNCS(__m128,  _mm_cmp_ps))
        MK2_ARCHTECTURE_REQUIREMENT_AVX(MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE_FUNCS(__m128d, _mm_cmp_pd))
        MK2_ARCHTECTURE_REQUIREMENT_AVX(MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE_FUNCS(__m256,  _mm256_cmp_ps))
        MK2_ARCHTECTURE_REQUIREMENT_AVX(MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE_FUNCS(__m256d, _mm256_cmp_pd))
    }

    template<class Type, bool Ordered, bool Signaling>
    inline decltype(auto) cmp_eq(Type a, Type b) { return detail::cmp_eq_impl<Type, Ordered, Signaling>::func(a, b); }
    template<class Type, bool Ordered, bool Signaling>
    inline decltype(auto) cmp_lt(Type a, Type b) { return detail::cmp_lt_impl<Type, Ordered, Signaling>::func(a, b); }
    template<class Type, bool Ordered, bool Signaling>
    inline decltype(auto) cmp_le(Type a, Type b) { return detail::cmp_le_impl<Type, Ordered, Signaling>::func(a, b); }
    template<class Type, bool Ordered, bool Signaling>
    inline decltype(auto) cmp_neq(Type a, Type b) { return detail::cmp_neq_impl<Type, Ordered, Signaling>::func(a, b); }
    template<class Type, bool Ordered, bool Signaling>
    inline decltype(auto) cmp_nlt(Type a, Type b) { return detail::cmp_nlt_impl<Type, Ordered, Signaling>::func(a, b); }
    template<class Type, bool Ordered, bool Signaling>
    inline decltype(auto) cmp_nle(Type a, Type b) { return detail::cmp_nle_impl<Type, Ordered, Signaling>::func(a, b); }

#undef MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE_FUNCS
#undef MK2_INTEL_INTRIN_COMPARISON_FUNC_TEMPLATE

}}}}}