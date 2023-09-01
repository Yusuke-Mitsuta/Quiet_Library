#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>
#include<string>
//#define Debug 1;

constexpr std::string getLastPathComponent(std::string path);

#define Constant static constexpr auto \

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

struct H
{
	void Args_1(int a);

	void Args_2(int a, int b);

	void Args_3(int a, int b, int c);

	void Args_4(int a, int b, int c, int d);

	void Args_5(int a, int b, int c, int d, int e);

	void Args_6(int a, int b, int c, int d, int e, int f);

	void Args_7(int a, int b, int c, int d, int e, int f, int g);


};

static H* h= new H();

struct MyStruct
{

private:

	void Hoge(){}

public:

	int a = 1;

};

