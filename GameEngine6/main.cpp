#include"main.h"
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


	int n1;
	int n;

	template<int N>
	constexpr int& get()
	{
		return n1;
	}

	template<>
	constexpr int& get<1>()
	{
		return n;
	}

	constexpr vec2(int set_n1, int set_n2) :
		n1(set_n1), n(set_n2) {}
};

struct vec3
{
	using tuple = tuple_t<vec2, int>;

	vec2 vec3v;
	int n;

	template<int n>
	constexpr vec2& get()
	{
		return vec3v;
	}

	template<int N>
		requires(N != 0)
	constexpr int& get()
	{
		return n;
	}

	constexpr vec3(vec2 set_vec3v, int set_n) :
		vec3v(set_vec3v), n(set_n) {}

};

struct vec4
{
	using tuple = tuple_t<vec3,int>;

	vec3 vec3v;
	int n;


	template<int n>
	constexpr vec3& get()
	{
		return vec3v;
	}

	template<int N>
		requires(N != 0)
	constexpr int& get()
	{
		return n;
	}


	constexpr vec4(vec3 set_vec3v, int set_n) :
		vec3v(set_vec3v), n(set_n) {}
	

};

struct vec7
{
	using tuple = tuple_t<vec2, int, int, int, int, int>;
};

struct vec2a
{
	using tuple = tuple_t<int, int>;

	int n1;
	int n;

	template<int N>
	constexpr int& get()
	{
		return n1;
	}

	template<>
	constexpr int& get<1>()
	{
		return n;
	}


	constexpr vec2a(int set_n1, int set_n2) :
		n1(set_n1), n(set_n2) {}
};

struct vec3a
{
	using tuple = tuple_t<vec2a, int>;


	vec2a vec3v;
	int n;

	template<int n>
	constexpr vec2a& get()
	{
		return vec3v;
	}

	template<int N>
		requires(N != 0)
	constexpr int& get()
	{
		return n;
	}

	constexpr vec3a(vec2a set_vec3v, int set_n) :
		vec3v(set_vec3v), n(set_n) {}
};

struct vec4a
{
	using tuple = tuple_t<vec3a, int>;


	vec3a vec3v;
	int n;

	template<int n>
	constexpr vec3a& get()
	{
		return vec3v;
	}

	template<int N>
		requires(N != 0)
	constexpr int& get()
	{
		return n;
	}

	constexpr vec4a(vec3a set_vec3v, int set_n) :
		vec3v(set_vec3v), n(set_n) {}
};

void Expand_zip_testa(vec4 vec)
{
	H::Static_Args_88(
		vec.vec3v.vec3v.n1,
		vec.vec3v.vec3v.n,
		vec.vec3v.n,
		vec.n);
}


void Expand_zip_test(int&& n1,auto&& n2,int n3,int n4)
{
	H::Static_Args_88(n1, n2, n3, n4);
}




int main()
{
	float f = 2.0f;
	


	int n = 3;

	Expand_zip_test(f, n, 5.0f, 6.0f);


	int* np = &n;

	int nr = *np;


	vec4a vec4_test(vec3a(vec2a(1, 2), 3), 4);

	//N_Tuple::Apply(&Expand_zip_testa, vec4_test);
	
	Array<int,3> ary_0(1, 3, 5);


	Array<float,3> ary_1(1.0f, 3.0f, 5.0f);

	
	//Array ary_2(ary_0, ary_1);
	
	

//using na = N_Tuple::N_Apply::I_Apply_Type_Chack<N_Tuple::U_Repeat_Multiple<decltype(ary_0), 10>, tuple_t<decltype(ary_0), decltype(ary_1)>>::type::request;

		//N_Array::args_chack<decltype(ary_0), decltype(ary_0), decltype(ary_1), decltype(ary_0)>;

	//TYPE_ID(na);
	//std::array<int, 3> ary_t = { 2, 4, 6 };
	//H::Static_Args_88(std::get<0>(ary_t), std::get<1>(ary_t), std::get<2>(ary_t));

	//using t=std::bool_constant<convertible_to<float&,int&>>::


	//auto ary= N_Tuple::Apply<std::array<std::array<int, 3>,2>>(ary_0, ary_1);

	//H::Static_Args_88(ary[0][0],ary[0][1],ary[0][2]);
	//H::Static_Args_88(ary[1][0],ary[1][1],ary[1][2]);

	//Array ary_2(ary_0, 1,2,3);


	//using u = N_Tuple::N_Apply::I_Apply_Type_Chack<tuple_t<std::array<std::array<int, 3>, 2>>, tuple_t<decltype(ary_0), int, int, int>>;
	//TYPE_ID(u::type::request);
	//TYPE_ID(u::type::conversion_expand_list);
	//TYPE_ID(u::type::conversion_zip_list);
	//type_id(ary_2);
	//Array ary_2(ary_0,ary_1);


	//using t=std::bool_constant<convertible_to<decltype(ary_0), decltype(ary_1)>>::

	//Array ary_1(1, 3, 5);




	//N_Tuple::Apply(&Expand_zip_testa, 1,2,3,4);

	//using req = N_Tuple::N_Apply::I_Apply_Type_Chack <tuple_t<vec4>, 
		//tuple_t<int,int,int,int>>::conversion::conversion_zip_list;

	//TYPE_ID(req::type);
	//TYPE_ID(req::next::type);
	//Hogegege(&np);
	//return 0;
	//C_OUT(nn[0]);
	//C_OUT(nn[1]);
	//C_OUT(nn[2]);

	//N_Tuple::Apply<std::array<int, 3>>

	//Array ary(3, 4, 4, 9, 20);



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
