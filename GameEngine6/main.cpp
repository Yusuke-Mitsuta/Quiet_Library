#include"main.h"
#include<compare>
#include<initializer_list>
#include<iostream>

#include"Constexpr_Array.h"
#include"Function.h"
#include"Tuple.h"

#include "Output_Message.h"



constexpr int a = '"';



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
	//C_OUT(vec.n);
	
	C_OUT(
		vec.vec3v.vec3v.n1);
	C_OUT(

		vec.vec3v.vec3v.n);
	C_OUT(
		vec.vec3v.n);
	C_OUT(
		vec.n);
	
}


void Expand_zip_test(int n1,int n2,int n3,int n4)
{
	//H::Static_Args_88(n1, n2, n3, n4);
}

int main()
{

	int n = 3;

	int* np = &n;

	int nr = *np;
	//static int n = __LINE__;

	//vec4a vec4_test(vec3a(vec2a(1, 2), 3), 4);

	//C_OUT("a");

	//TYPE_ID();


	//N_Tuple::Apply(&Expand_zip_testa, vec4_test);
	
	Array<int,3> ary_0(1, 3, 5);

	using ary_0t = Array<int, 3>;
	using ary_1t = Array<float, 3>;


	Array<float, 3> ary_1(1.0f, 3.0f, 5.0f);

	//N_Tuple::Apply<std::array<Array<int, 3>, 2>>(ary_0, ary_1);

	

	Array ary_2(3,3,ary_0,ary_1);

	
	//TYPE_ID(

	//using tu= N_Tuple::N_Apply::S_Infinite_Args<int>;

	//TYPE_ID(tu);

	//using t_test = N_Tuple::N_Apply::I_Apply_Type_Chack<tuple_t<N_Tuple::N_Apply::S_Infinite_Args<int>>, tuple_t<ary_0t,ary_1t>>::type::request::

	//TYPE_ID(t_test);
	//std::cout<< typeid(t_test).name();

	//convertible_from_C<Array<int,3> , int>::
	//Array ary_2(ary_0,ary_1);
	
	

	//N_Tuple::Apply(&Expand_zip_testa, vec4_test);
	//using n_ = N_Tuple::N_Apply::I_Apply_Type_Chack<tuple_t<std::array<ary_0t, 2>, std::array<ary_1t, 2>>, tuple_t<ary_0t, ary_1t,ary_1t, ary_0t>>::type;
	//using na = n_::conversion_expand_list;TYPE_ID(na);
	//using nb = n_::conversion_zip_list;TYPE_ID(nb);
	_CrtDumpMemoryLeaks();
	return 0;


}
//
//tuple_t< N_Tuple::N_Apply::S_Conversion_Zip< Array<float, 3>, 1>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<float, 3>, 2>, 
//	N_Tuple::N_Apply::S_Conversion_Zip< std::array< Array<float, 3>, 2>, 1>, 
//
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 2>,
//	N_Tuple::N_Apply::S_Conversion_Zip< Array<int, 3>, 3>,
//	N_Tuple::N_Apply::S_Conversion_Zip< std::array< Array<int, 3>, 2>, 2> >

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