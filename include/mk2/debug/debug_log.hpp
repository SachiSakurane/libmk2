//
// Created by Himatya on 2018/02/07.
//

#ifndef LIBMK2_DEBUG_DEBUG_LOG_HPP
#define LIBMK2_DEBUG_DEBUG_LOG_HPP

#include <iostream>

#include <mk2/debug/build_type.hpp>

#ifdef MK2_DEBUG
    #define MK2_DEBUG_STDOUT(log)               (std::cout << "FILE:" << __FILE__ << " LINE:" << __LINE__ << " " << log << std::endl)
    #define MK2_DEBUG_STDERR(log)               (std::cerr << "FILE:" << __FILE__ << " LINE:" << __LINE__ << " " << log << std::endl)
    #define MK2_DEBUG_STDOUT_IF(is_out, log)    if((is_out)){MK2_DEBUG_STDOUT(log);}
    #define MK2_DEBUG_STDERR_IF(is_err, log)    if((is_err)){MK2_DEBUG_STDERR(log);}
#else
    #define MK2_DEBUG_STDOUT(x)
    #define MK2_DEBUG_STDERR(x)
    #define MK2_DEBUG_STDOUT_IF(is_out, log)
    #define MK2_DEBUG_STDERR_IF(is_err, log)
#endif

#endif /* DEBUG_LOG_HPP */
