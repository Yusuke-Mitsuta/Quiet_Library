#pragma once

#include"Array.h"

#include<iostream>

#define FG 1

#if FG

struct Float3
{
    //このクラスがコンストラクタで受け取る型、及び、
    //　構造化束縛された際に返す型を[tuple]で宣言する。
    using tuple = quiet::Array<float,3>;

    tuple data;

    //[tuple]で宣言した型を受け取るコンストラクタ
    template<class ...T>
        requires requires(T ...t)
    {
        tuple{ t... };
    }
    Float3(T... t) :
        data(t...)
    {}


};

#endif // FG


#if (FG==0)

struct Float3
{

    std::array<float,3> data;


    //コピーコンストラクタ
    Float3(std::array<float,3> set_data) :
        data(set_data)
    {}

    //[ float + float + float ]で受け取るコンストラクタ
    Float3(float set_0,float set_1,float set_2) :
        data({set_0,set_1,set_2})
    {}

    //[ std::array<float,2> + float ]で受け取るコンストラクタ
    Float3(std::array<float,2> set_01, float set_2) :
        data({ set_01[0], set_01[1],set_2})
    {}

    //[float + std::array<float,2>]で受け取るコンストラクタ
    Float3(float set_0, std::array<float, 2> set_12) :
        data({ set_0, set_12[0],set_12[1] })
    {}

};
#endif // FG

static void Output(auto data)
{
    std::cout << typeid(data).name()<<std::endl;

    std::cout << "[0] :"<<data[0] << std::endl;
    std::cout << "[1] :"<<data[1] << std::endl;
    std::cout << "[2] :"<<data[2] << std::endl;

}
