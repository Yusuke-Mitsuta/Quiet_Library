#pragma once


#include"Constexpr_Array.h"
#include"Constexpr_String.h"

#define CLASS(className,bassClassName) \
template<> \
class Core<className> : \
public Core<bassClassName> \
{ \
public: \
 \
template<N_Constexpr::String t_Str> \
void Hoge(){} \

#define DONT_COPY(ClassName) \
ClassName(ClassName&) = delete; \
void operator=(auto) = delete; \

