#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>
#include<string>
//#define Debug 1;

constexpr std::string getLastPathComponent(std::string path);

std::string Type_id_change_String(std::string path);

std::string Type_id_delete_head_class_struct(std::string path);

#define Constant static constexpr auto \

#define C_OUT(message) \
std::cout<<getLastPathComponent(__FILE__)<<" : "<<__LINE__<< " << " <<message<<std::endl; \

#define HOGE(Name)\
void Hoge() \
{ \
C_OUT(Name) \
} \

#define SIZE_OF(className) \
C_OUT(sizeof(className));\

#define TYPE_ID(className) \
C_OUT(Type_id_delete_head_class_struct(Type_id_change_String(typeid(className).name()))); \

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

	static void Static_Args_1(int a);
	static void Static_Args_2(int a, int b);
	static void Static_Args_3(int a, int b, int c);
	static void Static_Args_4(int a, int b, int c, int d);
	static void Static_Args_5(int a, int b, int c, int d, int e);
	static void Static_Args_6(int a, int b, int c, int d, int e, int f);
	static void Static_Args_7(int a, int b, int c, int d, int e, int f, int g);

	static void Static_Args_88(auto ...a);
	static void Static_Args_88(auto a,auto ...b);
};

static H* h= new H();

struct MyStruct
{

private:

	void Hoge(){}

public:

	int a = 1;

};


template<class t>
class TEST
{
public:
	using type = t;

};