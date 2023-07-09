#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>

#define Debug 1;

#define TYPE_ID(className) \
std::cout<<typeid(className).name()<<std::endl; \


#define C_OUT(message) \
std::cout<<message<<std::endl; \

#define HOGE(Name)\
void Hoge() \
{ \
C_OUT(Name) \
} \

#define DONT_COPY(ClassName) \
ClassName(ClassName&) = delete; \
void operator=(auto) = delete; \

#define Class_Core(Name)\
using Name = Core<#Name>;\
template<> \
class Core<#Name> \


