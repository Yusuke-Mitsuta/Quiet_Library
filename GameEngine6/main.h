#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>

#define Debug 1;

#define TYPE_ID(className) \
std::cout<<typeid(className).name()<<std::endl; \


#define DONT_COPY(ClassName) \
ClassName(ClassName&) = delete; \
void operator=(auto) = delete; \

#define Class_Core(Name)\
using Name = Core<#Name>;\
template<> \
class Core<#Name> \


