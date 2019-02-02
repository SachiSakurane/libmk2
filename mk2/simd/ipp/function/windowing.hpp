//
// Created by Himatya on 2018/08/13.
//

#pragma once

#include <ipps.h>

#include <mk2/simd/ipp/function/macro.hpp>

namespace mk2 { namespace simd { namespace ipp {
namespace function {

#define MK2_IPP_WINDOWING_ASSOCIATOR(base_struct, base_func, name, desc)                    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s,  name, desc), (Ipp16s))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f,  name, desc), (Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f,  name, desc), (Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc))

// common
#define MK2_IPP_WINDOWING_SIGNATURE (const Type* psrc, Type* pdst, int len)
#define MK2_IPP_WINDOWING_ARGS (psrc, pdst, len)

    MK2_IPP_REPLACE_TEMPLATE(win_bartlett,     ippsWinBartlett,    , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_blackman_std, ippsWinBlackmanStd, , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_blackman_opt, ippsWinBlackmanOpt, , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_hamming,      ippsWinHamming,     , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_hann,         ippsWinHann,        , MK2_IPP_WINDOWING_SIGNATURE, MK2_IPP_WINDOWING_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)

#undef MK2_IPP_WINDOWING_SIGNATURE
#undef MK2_IPP_WINDOWING_ARGS

// inplace
#define MK2_IPP_WINDOWING_I_SIGNATURE (Type* psec_dst, int len)
#define MK2_IPP_WINDOWING_I_ARGS (psec_dst, len)

    MK2_IPP_REPLACE_TEMPLATE(win_bartlett_inplace,     ippsWinBartlett,    _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_blackman_std_inplace, ippsWinBlackmanStd, _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_blackman_opt_inplace, ippsWinBlackmanOpt, _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_hamming_inplace,      ippsWinHamming,     _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_hann_inplace,         ippsWinHann,        _I, MK2_IPP_WINDOWING_I_SIGNATURE, MK2_IPP_WINDOWING_I_ARGS, (Type), MK2_IPP_WINDOWING_ASSOCIATOR)

#undef MK2_IPP_WINDOWING_I_SIGNATURE
#undef MK2_IPP_WINDOWING_I_ARGS

// kaiser
#define MK2_IPP_WINDOWING_WITH_ALPHA_ASSOCIATOR(base_struct, base_func, name, desc)                 \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16s, name, desc),  (Ipp16s, Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32f, name, desc),  (Ipp32f, Ipp32f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64f, name, desc),  (Ipp64f, Ipp64f))    \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_16sc, name, desc), (Ipp16sc, Ipp32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_32fc, name, desc), (Ipp32fc, Ipp32f))   \
    MK2_PP_REPLACE_TO_TEMPLATE_FUNC(base_struct, base_func(_64fc, name, desc), (Ipp64fc, Ipp64f))

    MK2_IPP_REPLACE_TEMPLATE(win_kaiser, ippsWinKaiser, , (const Type* psrc, Type* pdst, int len, AlphaType alpha), (psrc, pdst, len, alpha), (Type, AlphaType), MK2_IPP_WINDOWING_WITH_ALPHA_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_kaiser_inplace, ippsWinKaiser, _I, (Type* psec_dst, int len, AlphaType alpha), (psec_dst, len, alpha), (Type, AlphaType), MK2_IPP_WINDOWING_WITH_ALPHA_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_blackman, ippsWinBlackman, , (const Type* psrc, Type* pdst, int len, AlphaType alpha), (psrc, pdst, len, alpha), (Type, AlphaType), MK2_IPP_WINDOWING_WITH_ALPHA_ASSOCIATOR)
    MK2_IPP_REPLACE_TEMPLATE(win_blackman_inplace, ippsWinBlackman, _I, (Type* psec_dst, int len, AlphaType alpha), (psec_dst, len, alpha), (Type, AlphaType), MK2_IPP_WINDOWING_WITH_ALPHA_ASSOCIATOR)

#undef MK2_IPP_WINDOWING_ASSOCIATOR
#undef MK2_IPP_WINDOWING_WITH_ALPHA_ASSOCIATOR

    enum class window_type
    {
        kBartlett,
        kBlackmanStd,
        kBlackmanOpt,
        kHamming,
        kHann,
        kKaiser,
        kBlackman,
    };

    template<class Type>
    void windowing(window_type type, const Type* src, Type* dst, int len, Type alpha)
    {
        switch(type)
        {
            case window_type::kBartlett:    mk2::simd::ipp::function::win_bartlett(src, dst, len);        break;
            case window_type::kBlackman:    mk2::simd::ipp::function::win_blackman(src, dst, len, alpha); break;
            case window_type::kBlackmanOpt: mk2::simd::ipp::function::win_blackman_opt(src, dst, len);    break;
            case window_type::kBlackmanStd: mk2::simd::ipp::function::win_blackman_std(src, dst, len);    break;
            case window_type::kHamming:     mk2::simd::ipp::function::win_hamming(src, dst, len);         break;
            case window_type::kHann:        mk2::simd::ipp::function::win_hann(src, dst, len);            break;
            case window_type::kKaiser:      mk2::simd::ipp::function::win_kaiser(src, dst, len, alpha);   break;
        }
    }

    template<class Type>
    void windowing_inplace(window_type type, Type* src_dst, int len, Type alpha)
    {
        switch(type)
        {
            case window_type::kBartlett:    mk2::simd::ipp::function::win_bartlett_inplace(src_dst, len);        break;
            case window_type::kBlackman:    mk2::simd::ipp::function::win_blackman_inplace(src_dst, len, alpha); break;
            case window_type::kBlackmanOpt: mk2::simd::ipp::function::win_blackman_opt_inplace(src_dst, len);    break;
            case window_type::kBlackmanStd: mk2::simd::ipp::function::win_blackman_std_inplace(src_dst, len);    break;
            case window_type::kHamming:     mk2::simd::ipp::function::win_hamming_inplace(src_dst, len);         break;
            case window_type::kHann:        mk2::simd::ipp::function::win_hann_inplace(src_dst, len);            break;
            case window_type::kKaiser:      mk2::simd::ipp::function::win_kaiser_inplace(src_dst, len, alpha);   break;
        }
    }

}}}}