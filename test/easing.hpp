//
// Created by Himatya on 2019-03-31.
//

#pragma once

#include <iostream>
#include <random>

#include <mk2/easing.hpp>

inline void easing_test()
{
    std::cout << "easing test" << std::endl;

    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());

    std::uniform_real_distribution<float> float_dist(0.f, 1.f);
    std::uniform_real_distribution<double> double_dist(0.0, 1.0);

    const float float_value = float_dist(engine);
    const double double_value = double_dist(engine);

    // type test
    assert(mk2::easing::ease_in<mk2::easing::linear>(float_value) == float_value);
    assert(mk2::easing::ease_in<mk2::easing::linear>(double_value) == double_value);

    // ease test
    std::cout << "value: " << float_value << std::endl;
    std::cout << "easein(linear) -> " << mk2::easing::ease_in<mk2::easing::linear>(float_value) << std::endl;
    std::cout << "easeout(linear) -> " << mk2::easing::ease_out<mk2::easing::linear>(float_value) << std::endl;
    std::cout << "easeinout(linear) -> " << mk2::easing::ease_in_out<mk2::easing::linear>(float_value) << std::endl;
    std::cout << std::endl;

    // ease type test
    std::cout << "value: " << float_value << std::endl;
    std::cout << "easein(back) -> " << mk2::easing::ease_in<mk2::easing::back>(float_value) << std::endl;
    std::cout << "easein(bounce) -> " << mk2::easing::ease_in<mk2::easing::bounce>(float_value) << std::endl;
    std::cout << "easein(circular) -> " << mk2::easing::ease_in<mk2::easing::circular>(float_value) << std::endl;
    std::cout << "easein(cubic) -> " << mk2::easing::ease_in<mk2::easing::cubic>(float_value) << std::endl;
    std::cout << "easein(elastic) -> " << mk2::easing::ease_in<mk2::easing::elastic>(float_value) << std::endl;
    std::cout << "easein(exponential) -> " << mk2::easing::ease_in<mk2::easing::exponential>(float_value) << std::endl;
    std::cout << "easein(quadratic) -> " << mk2::easing::ease_in<mk2::easing::quadratic>(float_value) << std::endl;
    std::cout << "easein(quart) -> " << mk2::easing::ease_in<mk2::easing::quart>(float_value) << std::endl;
    std::cout << "easein(quint) -> " << mk2::easing::ease_in<mk2::easing::quint>(float_value) << std::endl;
    std::cout << "easein(sine) -> " << mk2::easing::ease_in<mk2::easing::sine>(float_value) << std::endl;
    std::cout << std::endl;

    std::cout << "finish easing test" << std::endl;
}