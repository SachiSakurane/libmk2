//
// Created by Himatya on 2018/02/07.
//

#ifndef LIBMK2_DEBUG_BUILD_TYPE_HPP
#define LIBMK2_DEBUG_BUILD_TYPE_HPP

#ifdef DEBUG
    #define MK2_DEBUG
#endif

#ifndef DEBUG
    #define MK2_RELEASE
#endif

#endif /* BUILD_TYPE_HPP */
