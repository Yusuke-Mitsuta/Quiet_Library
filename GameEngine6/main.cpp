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
void Expand_zip_testf(float n1, int n2, int n3, double n4)
{
	C_OUT(n1, n2, n3, n4);
	//H::Static_Args_88(n1, n2, n3, n4);
}

void Expand_zip_test(int n1,int n2,int n3,double n4)
{
	C_OUT(n1, n2, n3, n4);
	//H::Static_Args_88(n1, n2, n3, n4);
}

int main()
{
	//TYPE_ID(
		//N_Function::I_Function_Args_Chack<tuple_t<int, int, float>, tuple_t<int, float,int>>::type
	//);

	Function a(&Expand_zip_test, &Expand_zip_testa);

	TYPE_ID(
	decltype(a)::vaild::function);
		//N_Function::I_Function_Base_Data<
		//decltype(&Expand_zip_test),
		//decltype(&Expand_zip_test)>::type;

	Function fn_1(&Expand_zip_test, 1);
	Function fn_2(&Expand_zip_testf, 2,4);
	
	Function fn(fn_1, fn_2);
	//fn(11, 22, 33);
	//fn(11, 22);
	//TYPE_ID(
	//	N_Function::I_Function_Valid_Data<decltype(fn_1), decltype(fn_2)>::request_args);
		//N_Function::Function_Core<decltype(fn_1), decltype(fn_2)>::function);
		//N_Function::I_Function_Single_Helper<decltype(fn_1), decltype(fn_2)>::judge);
	using t1 = tuple_t<int, float, double>;

	TYPE_ID(
	N_Function::Function_Core<decltype(&Expand_zip_test), int>::superficial::function);
	int n = 3;

	int* np = &n;

	int nr = *np;
	//static int n = __LINE__;

	vec4a vec4_test(vec3a(vec2a(1, 2), 3), 4);

	//C_OUT("a");

	//TYPE_ID();

	N_Tuple::Apply(&Expand_zip_testa, vec4_test);
	
	Array<int,3> ary_0(1, 3, 5);

	using ary_0t = Array<int, 3>;
	using ary_1t = Array<float, 3>;
	

	Array<float, 3> ary_1(1.0f, 3.0f, 5.0f);
	using vec_4 = decltype(vec4_test);
	//N_Tuple::U_Expand_All<ary_0t>;

	//N_Tuple::Apply<std::array<Array<int, 3>, 2>>(ary_0, ary_1);
	//static constexpr int a =
	//N_Tuple::N_Apply::I_Type_Chack<tuple_t<
		//vec_4, vec_4, vec_4, ary_0t>,
		//N_Tuple::N_Apply::S_Infinite_Args<ary_0t>>, 
		//tuple_t<ary_0t, vec_4, vec_4, vec_4>>::type::value;

	//>::type::value;

	//N_Tuple::I_Zip<int, int, int, int, int, double, float, float, float, float, float>::;

	//N_Tuple::Apply<Array<Array<int,3>,6>>(ary_0, ary_1, vec4_test, vec4_test, vec4_test);

	Array ary_2(ary_0, vec4_test, ary_1, vec4_test, 3,vec4_test,3,0);
	//Array ary_2(ary_0, ary_1, vec4_test, vec4_test, vec4_test);


	//std::cout << std::endl;
	for (int i = 0; i < 7; i++)
	{

		for (int j = 0; j < 3; j++)
		{
			//C_OUT(ary_2[i][j]);
		}
		std::cout << std::endl;
	}



	//C_OUT(1, 3, 5, 7, 9);

	//TYPE_ID(

	//using tu= N_Tuple::N_Apply::S_Infinite_Args<int>;

	//TYPE_ID(tu);

	//using t_test = N_Tuple::N_Apply::I_Convert_Order<tuple_t<N_Tuple::N_Apply::S_Infinite_Args<int>>, tuple_t<ary_0t,ary_1t>>::type::request::

	//TYPE_ID(t_test);
	//std::cout<< typeid(t_test).name();

	//convertible_from_C<Array<int,3> , int>::
	//Array ary_2(ary_0,ary_1);
	
	

	//N_Tuple::Apply(&Expand_zip_testa, vec4_test);
	//using n_ = N_Tuple::N_Apply::I_Convert_Order<tuple_t<std::array<ary_0t, 2>, std::array<ary_1t, 2>>, tuple_t<ary_0t, ary_1t,ary_1t, ary_0t>>::type;
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