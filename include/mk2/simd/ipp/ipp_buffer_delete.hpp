//
// Created by Himatya on 2018/11/21.
//

#pragma once

#include <type_traits>

#include <ipps.h>

namespace mk2 { namespace simd { namespace ipp {

    template <class T>
    struct ipp_buffer_delete
    {
        void operator()(T* ptr) 
        {
            if (ptr)
            {
                ippsFree(ptr);
            }
        }
    };
    
}}}