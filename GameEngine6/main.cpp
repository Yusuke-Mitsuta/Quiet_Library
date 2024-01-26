#include"main.h"
#include<iostream>
#include<initializer_list>
#include<compare>

#include"Tuple.h"
#include"Function.h"
#include"Constexpr_Array.h"


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

	path.replace(start_point, end_point+2, char_number);

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
		path= path.erase(delete_p, 6);
		delete_p = path.find("struct ");
	}
	
	return path;
}

constexpr int a = '"';

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

void H::Static_Args_88(auto a,auto ...b)
{
	//TYPE_ID(decltype(a));
	C_OUT(a);
	Static_Args_88(b...);
}



void Hogege(int* t) 
{
	C_OUT("ポインタ-");
	//(t.*h)(10, 30);
}

void Hogege(int*& t)
{
	C_OUT("ポインター参照");
	//(t.*h)(10, 30);
}

template<class T>
void Hogegege1(T&& t)

{
	type_id(t);
	Hogege(std::forward<T>(t));
	//H::Static_Args_88(t.a[0], t.a[1]);
}

template<class T>
void Hogegege(T&& t)

{
	type_id(t);
	Hogegege1(std::forward<T>(t));
	//H::Static_Args_88(t.a[0], t.a[1]);
}
#include"Tuple_Apply_Type_Chack.h"



struct vec2
{
	using tuple = tuple_t<int, int>;
};

struct vec3
{
	using tuple = tuple_t<vec2, int>;
};

struct vec4
{
	using tuple = tuple_t<vec3,int>;
};

struct vec2a
{
	using tuple = tuple_t<int, int>;
};

struct vec3a
{
	using tuple = tuple_t<vec2a, int>;
};

struct vec4a
{
	using tuple = tuple_t<vec3a, int>;
};

int main()
{

	int n = 3;

	int* np = &n;

	int nr = *np;

	using req = N_Tuple::N_Apply::I_Apply_Type_Chack <tuple_t<vec4>, tuple_t<vec3a,int>>::type::conversion;
	TYPE_ID(req);
	nr = 5;

	C_OUT(n);
	//Hogegege(&np);
	//return 0;
	//C_OUT(nn[0]);
	//C_OUT(nn[1]);
	//C_OUT(nn[2]);

	//N_Tuple::Apply<std::array<int, 3>>

	//Array ary(3, 4, 4, 9, 20);


	 bool b = std::convertible_to<int&, int>;
	 bool c = 1;// std::convertible_to<int&, int*>;
	 bool d = std::convertible_to<int&, int&>;

	H::Static_Args_88(b, c,d);
	b = 1;//std::convertible_to<int*, int>;
	c = std::convertible_to<int*, int*>;
	d = 1;//std::convertible_to<int*, int&>;
	C_OUT("");
	H::Static_Args_88(b, c,d);

	b = std::convertible_to<int, int>;
	c = std::convertible_to<int, int*>;
	d = std::convertible_to<int, int&>;
	C_OUT("");
	H::Static_Args_88(b, c,d);

	//using 
	
	//r = N_Function::I_Function_Args_Chack<N_Tuple::U_Repeat_Multiple<Array<int, 2>, 5>,

		//tuple_t< Array<int, 2>, Array<int, 2>>>;

//	TYPE_ID(r);

	//fn(h, 4, 5);
	//using t = N_Tuple::U_Repeat_Multiple<Array<int, 3>, 10>;
	//TYPE_ID(t);


	//Array ary0(3, 5,  9);

	//Array ary1(0.3f, 4,3);
	

	//Array ary2(ary0, ary1,ary0);

	////std::array<Array<int, 3>, 3> aaa;
//
	//H::Static_Args_88(
	//	ary2[0][0],
	//	ary2[0][1],
	//	ary2[0][2],
	//	ary2[1][0],
	//	ary2[1][1],
	//	ary2[1][2],
	//	ary2[2][0],
	//	ary2[2][1],
	//	ary2[2][2]);

//	N_Tuple::N_Apply::S_Select_Type<decltype(&H::Args_2)>::

	_CrtDumpMemoryLeaks();
	return 0;

}
