#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>
#include<string>
#define Debug 1;

std::string getLastPathComponent(std::string path);

#define C_OUT(message) \
std::cout<<getLastPathComponent(__FILE__)<<" : "<<__LINE__<< " << " <<message<<std::endl; \

#define HOGE(Name)\
void Hoge() \
{ \
C_OUT(Name) \
} \

#define TYPE_ID(className) \
C_OUT(typeid(className).name()) \

#define type_id(className) \
TYPE_ID(decltype(className))\

#define DONT_COPY(ClassName) \
ClassName(ClassName&) = delete; \
void operator=(auto) = delete; \

#define Class_Core(Name)\
using Name = Core<#Name>;\
template<> \
class Core<#Name> \

