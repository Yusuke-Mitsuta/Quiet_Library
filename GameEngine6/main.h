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





static int static_n=0;

template<class ...T_Types>
struct tuple_t;

struct MyStruct
{

private:

	void Hoge(){}

public:

	int a[2];
	
	using tuple = tuple_t<int, int>;

	MyStruct(int aa, int bb) :
		a{ aa , bb } {}

	//MyStruct(int aa) :	a{ aa , 5 } {}

	template<size_t I>
	int& get()
	{
		return a[I];
	};
										


};






class TEST
{
public:
	TEST(int a,int& b,int* c) {}

};

template<class T_base,class ...T_Args>
concept base_Ar = requires(T_base, T_Args... args)
{
	T_base(args...);
};