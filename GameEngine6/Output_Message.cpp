#include"Output_Message.h"

#include<compare>
#include<initializer_list>
#include<iostream>

#include"Constexpr_Array.h"
#include"Function.h"
#include"Tuple.h"

constexpr std::string getLastPathComponent(std::string path) {
	std::string r;
	size_t p = 0;
	for (size_t i = path.size() - 1; i > 0; i--)
	{
		if (path[i] == '\\')
		{

			p = i;
			break;
		}
	}
	for (int i = static_cast<int>(p) + 1; i < path.size(); i++)
		r.push_back(path[i]);
	return r;
}

std::string Type_id_change_String(std::string path)
{

	size_t start_point = path.find("class N_Constexpr::String");

	if (start_point == std::string::npos)
	{
		return path;
	}


	std::string subString = path.substr(start_point);

	size_t char_start_point = subString.find("{char{") + 6;

	size_t end_point = subString.find("}}");

	std::string char_number;

	char_number += 32;
	char_number += 34;

	for (size_t i = char_start_point; i < end_point; i++)
	{
		std::string char_number_chip;

		for (i; !(',' == subString[i] || '}' == subString[i]); i++)
		{
			char_number_chip += subString[i];
		}

		char_number += static_cast<char>(std::stoi(char_number_chip));
	}
	char_number += 34;
	char_number += 32;

	path.replace(start_point, end_point + 2, char_number);

	return Type_id_change_String(path);

}

std::string Type_id_delete_head_class_struct(std::string path)
{
	size_t delete_p = path.find("class ");

	while (delete_p != std::string::npos)
	{
		path = path.erase(delete_p, 5);
		delete_p = path.find("class ");
	}

	delete_p = path.find("struct ");

	while (delete_p != std::string::npos)
	{
		path = path.erase(delete_p, 6);
		delete_p = path.find("struct ");
	}

	return path;
}

void H::Args_1(int a)
{
	C_OUT(a);
}

void H::Args_2(int a, int b)
{
	C_OUT(a);
	C_OUT(b);
}

void H::Args_3(int a, int b, int c)
{
	Args_2(a, b);
	C_OUT(c);
}

void H::Args_4(int a, int b, int* c, int& d)
{
	//Args_3(a, b, c);
	Args_2(a, b);
	C_OUT(*c);
	C_OUT(d);

}

void H::Args_5(int a, int b, int c, int d, int e)
{
	//Args_4(a, b, c, d);
	C_OUT(e);
}

void H::Args_6(int a, int b, int c, int d, int e, int f)
{
	Args_5(a, b, c, d, e);
	C_OUT(f);
}

void H::Args_7(int a, int b, int c, int d, int e, int f, int g)
{
	Args_6(a, b, c, d, e, f);
	C_OUT(g);
}

void H::Static_Args_1(int a)
{
	C_OUT(a);
	//a = 100;
}

void H::Static_Args_2(int& a, int& b)
{
	C_OUT(a);
	a = 1000;
	C_OUT(b);
}

void H::Static_Args_3(int a, int b, int c)
{
	Static_Args_2(a, b);
	C_OUT(c);
}

void H::Static_Args_4(int a, int b, int* c, int* d)
{
	Static_Args_2(a, b);
	(*c) = 10000;
	C_OUT((*c));
	C_OUT((*d));
	//C_OUT(d);

}

void H::Static_Args_5(int a, int b, int c, int d, int e)
{
	//Static_Args_4(a, b, c, d);
	C_OUT(e);
}

void H::Static_Args_6(int a, int b, int c, int d, int e, int f)
{
	Static_Args_5(a, b, c, d, e);
	C_OUT(f);
}

void H::Static_Args_7(int a, int b, int c, int d, int e, int f, int g)
{
	Static_Args_6(a, b, c, d, e, f);
	C_OUT(g);
}

void H::Static_Args_88(auto ...a)
{

}

void H::Static_Args_88(auto a, auto ...b)
{
	//TYPE_ID(decltype(a));
	//C_OUT(a);
	//Static_Args_88(b...);
}