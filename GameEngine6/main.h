#pragma once

#include<concepts>


#define DONT_COPY(ClassName) \
ClassName(ClassName&) = delete; \
void operator=(auto) = delete; \

#define Class_Core(Name)\
using Name = Core<#Name>;\
template<> \
class Core<#Name> \

