#pragma once

#include<concepts>
#include<typeinfo>
#include<iostream>
#include<string>

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

#define TYPE_ID(...) \
C_OUT(Type_id_delete_head_class_struct(Type_id_change_String(typeid(__VA_ARGS__).name()))); \

#define type_id(className) \
TYPE_ID(decltype(className))\

#define name_change(name) #name\

#define CONCEPT (type1,type2)\
std::cout<<getLastPathComponent(__FILE__)<<" : "<<__LINE__<< " << " <<"same_as < "<<\
 Type_id_delete_head_class_struct(Type_id_change_String(typeid(type1).name()))\
<<" , "<< \
Type_id_delete_head_class_struct(Type_id_change_String(typeid(type2).name())) \
<<" > = "<<same_as<type1,type2>; \


struct H
{
	void Args_1(int a);
	void Args_2(int a, int b);
	void Args_3(int a, int b, int c);
	void Args_4(int a, int b, int* c, int& d);
	void Args_5(int a, int b, int c, int d, int e);
	void Args_6(int a, int b, int c, int d, int e, int f);
	void Args_7(int a, int b, int c, int d, int e, int f, int g);

	static void Static_Args_1(int a);
	static void Static_Args_2(int& a, int& b);
	static void Static_Args_3(int a, int b, int c);
	static void Static_Args_4(int a, int b, int* c, int* d);
	static void Static_Args_5(int a, int b, int c, int d, int e);
	static void Static_Args_6(int a, int b, int c, int d, int e, int f);
	static void Static_Args_7(int a, int b, int c, int d, int e, int f, int g);

	static void Static_Args_88() {}
	static void Static_Args_88(auto a, auto ...b)
	{
		TYPE_ID(decltype(a));
		C_OUT(a);
		Static_Args_88(b...);
		
	}

};