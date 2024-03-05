/*!
 * main.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>
#include<string>
//#define Debug 1;


#include"Array.h"

#include"Tuple.h"

#include"Function.h"


struct Vector2a
{

    using tuple = quiet::Tuple<float, float>;

    tuple vec2;


    template<class T_Tuple = tuple, class ...T>
        requires requires
    {
        requires quiet::N_Tuple::N_Apply::Chack<T_Tuple, T...>();
    }
    constexpr Vector2a(T... t) :
        vec2({ quiet::Tuple(t...) })
    {}

    template<size_t I>
    quiet::N_Tuple::U_Element_t<I, tuple>& get()
    {
        return std::get<I>(vec2);
    }
};

struct Vector3a
{
    

    using tuple = quiet::Tuple<float, float, float>;

    tuple vec3;

    template<class T_Tuple = tuple, class ...T>
        requires requires
    {
        requires quiet::N_Tuple::N_Apply::Chack<T_Tuple, T...>();
    }
    Vector3a(T... t) :
        vec3(quiet::Tuple(t...))
    {}

    template<size_t I>
    quiet::N_Tuple::U_Element_t<I, tuple>& get()
    {
        return std::get<I>(vec3);
    }
};