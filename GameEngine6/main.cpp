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


void Expand_zip_test(int n1,int n2,int n3,int n4)
{
	H::Static_Args_88(n1, n2, n3, n4);
}




int main()
{

	int n = 3;

	int* np = &n;

	int nr = *np;


	vec4a vec4_test(vec3a(vec2a(1, 2), 3), 4);

	//N_Tuple::Apply(&Expand_zip_testa, vec4_test);
	
	//Array<int,3> ary_0(1, 3, 5);

	using ary_0t = Array<int, 3>;
	using ary_1t = Array<float, 3>;

	//Array ary_1(1.0f, 3.0f, 5.0f);

	//Array ary_2(ary_0,ary_1);
	
	

	//convertible_from_C<Array<int,3> , int>::
	//Array ary_2(ary_0,ary_1);
	


	using na = N_Tuple::N_Apply::I_Apply_Type_Chack<
		tuple_t<std::array<ary_0t, 2>
		//,std::array<ary_1t, 2>
		>,
		//N_Tuple::U_Repeat_Multiple<decltype(ary_0), 5 >,
		tuple_t<ary_0t, ary_1t
		//, ary_1t, ary_0t
		>
	>::type::conversion_expand_list;
	using nb = N_Tuple::N_Apply::I_Apply_Type_Chack<
		tuple_t<std::array<ary_0t, 2>
		//,std::array<ary_1t, 2>
		>,
		//N_Tuple::U_Repeat_Multiple<decltype(ary_0), 5 >,
		tuple_t<ary_0t, ary_1t
		//, ary_1t, ary_0t
		>
	>::type::conversion_zip_list;


	TYPE_ID(na);
	TYPE_ID(nb);
	_CrtDumpMemoryLeaks();
	return 0;
	size-(3-1)
		12345
		123 4 5

}

//tuple_t< 
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 1>,
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 2>,
//	N_Tuple::N_Apply::S_Conversion_Zip< std::array< Array<int, 3>, 2>, 1> >
//
//	tuple_t<
//	N_Tuple::N_Apply::S_Conversion_Expand<Array<int, 3>, 2>,
//	N_Tuple::N_Apply::S_Conversion_Expand<Array<float, 3>, 1>>


//tuple_t< N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Expand< Array<float, 3>, 1>,
//	N_Tuple::N_Apply::S_Conversion_Zip<Array<int, 3>, 2>, 
//	N_Tuple::N_Apply::S_Conversion_Zip<std::array< Array<int, 3>, 2>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Expand< Array<int, 3>, 1> >

//tuple_t< N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Expand< Array<float, 3>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 2>,
//	N_Tuple::N_Apply::S_Conversion_Zip< std::array< Array<int, 3>, 2>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Expand< Array<int, 3>, 2> >
//
//tuple_t< 
//	N_Tuple::N_Apply::S_Conversion_Expand< Array<int, 3>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Expand< Array<float, 3>, 2>, 
//	N_Tuple::N_Apply::S_Conversion_Expand< Array<float, 3>, 3>, 
//	N_Tuple::N_Apply::S_Conversion_Expand< Array<int, 3>, 4> >



//tuple_t< 
//			 N_Apply::S_Conversion_Zip< Array<float, 3>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<float, 3>, 2>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< std::array< Array<float, 3>, 2>, 1>,
//
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 2>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 3>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< std::array< Array<int, 3>, 2>, 2> >


//tuple_t< N_Tuple::N_Apply::S_Conversion_Zip< tuple_t<Array<float, 3>>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< tuple_t< Array<float, 3>, Array<float, 3> >, 2>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< tuple_t< std::array< Array<float, 3>, 2> >, 1>, 
//
//	N_Tuple::N_Apply::S_Conversion_Zip< tuple_t< Array<int, 3>, std::array< Array<float, 3>, 2> >, 2>,
//	N_Tuple::N_Apply::S_Conversion_Zip< tuple_t< Array<int, 3>, Array<int, 3>, std::array< Array<float, 3>, 2> >, 3>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< tuple_t< std::array< Array<int, 3>, 2>, std::array< Array<float, 3>, 2> >, 2> >