#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>
#include<string>
#include"Output_Message.h"
//#define Debug 1;


#define DONT_COPY(ClassName) \
ClassName(ClassName&) = delete; \
void operator=(auto) = delete; \


#define Class_Core(Name)\
using Name = Core<#Name>;\
template<> \
class Core<#Name> \

