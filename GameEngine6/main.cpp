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
void Expand_zip_testf(float n1, int n2, int n3, int n4)
{
	C_OUT(n1, n2, n3, n4);
	//H::Static_Args_88(n1, n2, n3, n4);
}

void Expand_zip_test(int n1,int n2,int n3,int n4)
{
	C_OUT(n1, n2, n3, n4);
	//H::Static_Args_88(n1, n2, n3, n4);
}

struct H
{
	std::vector<int> v;

	H(int, int) {}

};

union MyUnion
{
	int n=0;
	float f;
};

#include"Vector.h"

int main()
{
	//Array<int, 4> aa;
	int i = 4;
	
	Array ary_1(2, 4, 6);
	Array<int,7> ary_2(i,ary_1,ary_1);

	//N_Tuple::N_Apply::I_Args_Convert_Action<tuple_t<int, int, int, int, int, int, int>, tuple_t<int, Array<int, 3>, Array<int, 3> > >
	//	::I_Args_Expand<tuple_t<int, Array<int, 3>, Array<int, 3> >, tuple_t<N_Tuple::N_Apply::S_Conversion_Expand<Array<int, 3>, 2>, N_Tuple::N_Apply::S_Conversion_Expand<Array<int, 3>, 1> > >
	//	::S_Args_Expand<>::Apply();
		//S_Args_Expand<tuple_v<0, 1, 2>, tuple_tp<tuple_t<int>, Array<int, 3>, tuple_t<Array<int, 3> > > >::Apply(&c, i, ary_1, ary_1);

		
	Vector3 v3(3, 6, 9);
	//auto sum = N_Tuple::I_Calculation<Vector3, Vector3>::type::Plus(ve_3, ve_3);
	//H h(2, 4);
	//ary_1 *= h;
	
	//v3 = ary_1;

	C_OUT(v3[0], v3[1], v3[2]);

	//for (int i = 0; i < 7; i++)
		//C_OUT(ary_2[i]);
	//C_OUT(sum[0],
	//	sum[1],
	//	sum[2]
		//sum[3],
		//sum[4],
//		//sum[5],
//		//sum[6]
	//) ;
	
	//Function fn(&Expand_zip_test, aa);

	//C_OUT(n,n2);

	//std::bool_constant< std::convertible_to<Vector3, int>>::value;


	//std::bool_constant< std::convertible_to<Array<int,2>,Vector3>>::value;
	//std::bool_constant< std::convertible_to<int,Vector3>>::value;
	//Array<int, 3> ary(3);


	
	//Array<int, 3> ary(3);

	//Vector3 ve{};
	//N_Vector::S_Core<int, 2> ve2(3, 4);
	
	


	//SIZE_OF(ve);
	
	//C_OUT(ve.x, ve.y, ve.z);

	//Vector3_b ve(1, 4, 8);

	//std::array<int, 4> ary({ 3, 4 });


	//Array<MyUnion, 3> ary(y,z);

	//Vector3 ve(3);

	//Vector3 ary(3);

	//ary.elems._Elems

	//C_OUT(ary[0],ary[1],ary[2]);

	//ary = 4;

	//C_OUT(ary[0],ary[1],ary[2]);


	//C_OUT(ve.x,ve.y,ve.z);

	
	//H h(3, 4);

	//N_Vector::S_Core<H, 3> core(h,h);

	//Vector3 ary(3, 4);


	//C_OUT(ary[0],ary[1],ary[2]);

	//C_OUT(ve.x);

	//MicroTime m_time = 1000;
	//
	//Time time(5);
	//
	//Time timea(m_time);

	//C_OUT(time, timea);
	

	//TYPE_ID(
		//N_Function::I_Function_Args_Chack<tuple_t<int, int, float>, tuple_t<int, float,int>>::type
	//);

	//Function a(&Expand_zip_test, &Expand_zip_testa);

	//TYPE_ID(decltype(a)::vaild::function);
		//N_Function::I_Function_Base_Data<
		//decltype(&Expand_zip_test),
		//decltype(&Expand_zip_test)>::type;

	//Function fn_1(&Expand_zip_test, 1);
	//Function fn_2(&Expand_zip_testf, 2,4);

	//Function fn_3(&MyStruct::get<0>);
	
	//MyStruct te(90, 10);

	//fn_3(&te);

	//Function fn(fn_1, fn_2);
	//fn(11, 22, 33);
	//fn(11, 22);
	//TYPE_ID(
	//	N_Function::I_Function_Valid_Data<decltype(fn_1), decltype(fn_2)>::request_args);
		//N_Function::Function_Core<decltype(fn_1), decltype(fn_2)>::function);
		//N_Function::I_Function_Single_Helper<decltype(fn_1), decltype(fn_2)>::judge);
	//using t1 = tuple_t<int, float, double>;

	//TYPE_ID(
	//N_Function::Function_Core<decltype(&Expand_zip_test), int>::superficial::function);


	//static int n = __LINE__;

	//vec4a vec4_test(vec3a(vec2a(1, 2), 3), 4);

	//C_OUT("a");

	//TYPE_ID();

	//N_Tuple::Apply(&Expand_zip_testa, vec4_test);
	
	//Array<int,3> ary_0(1, 3, 5);

//	using ary_0t = Array<int, 3>;
//	using ary_1t = Array<float, 3>;
	

	//Array<float, 3> ary_1(1.0f, 3.0f, 5.0f);
	//using vec_4 = decltype(vec4_test);
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

	//Array ary_2(ary_0, vec4_test, ary_1, vec4_test, 3,vec4_test,3,0);
	//Array ary_2(ary_0, ary_1, vec4_test, vec4_test, vec4_test);


	//std::cout << std::en


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