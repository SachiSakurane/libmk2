//
//  indexes_tuple.hpp
//
//
//  Created by Himatya on 2017/02/02.
//  Copyright (c) 2015 Himatya. All rights reserved.
//

#pragma once

#include <type_traits>

namespace mk2{
namespace container{
    namespace detail{
        template<std::size_t... Indexes>
        struct index_tuple{};
        
        template<std::size_t Next, typename IndexTuple>
        struct index_range_next;
        template<std::size_t Next, std::size_t... Indexes>
        struct index_range_next<Next, index_tuple<Indexes...>>
        {
            typedef index_tuple<Indexes..., (Indexes + Next)...> type;
        };
        
        template<std::size_t Next, std::size_t Tail, typename IndexTuple>
        struct index_range_next2;
        template<std::size_t Next, std::size_t Tail, std::size_t... Indexes>
        struct index_range_next2<Next, Tail, index_tuple<Indexes...>>
        {
            typedef index_tuple<Indexes..., (Indexes + Next)..., Tail> type;
        };
        
        template<
            std::size_t First,
            std::size_t Step,
            std::size_t N,
            typename Enable = void
        >
        struct index_range_impl;
        
        template<std::size_t First, std::size_t Step, std::size_t N>
        struct index_range_impl<
            First,
            Step,
            N,
            typename std::enable_if<N == 0>::type
        >
        {
            typedef index_tuple<> type;
        };
        
        template<std::size_t First, std::size_t Step, std::size_t N>
        struct index_range_impl<
            First,
            Step,
            N,
            typename std::enable_if<N == 1>::type
        >
        {
            typedef index_tuple<First> type;
        };
        
        template<std::size_t First, std::size_t Step, std::size_t N>
        struct index_range_impl<
            First,
            Step,
            N,
            typename std::enable_if<(N % 2 == 0) && (N > 1)>::type
        > : public index_range_next<
        First + N / 2,
        typename index_range_impl<First, Step, N / 2>::type
        >
        {};
        
        template<std::size_t First, std::size_t Step, std::size_t N>
            struct index_range_impl<
            First,
            Step,
            N,
            typename std::enable_if<(N % 2 == 1) && (N > 1)>::type
        > : public index_range_next2<
        First + N / 2,
        First + N - 1,
        typename index_range_impl<First, Step, N / 2>::type
        >{};
    }
    
    
    template<std::size_t First, std::size_t Last, std::size_t Step = 1>
    struct index_range : public detail::index_range_impl<First, Step, Last>{};
}
}
