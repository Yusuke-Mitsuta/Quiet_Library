#include"main.h"
#include<iostream>
#include<initializer_list>
#include<compare>

#include"Constexpr_Array.h"
#include"Constexpr_String.h"
#include"Game_Engine.h"
#include"Object.h"
#include"Args_Type.h"
#include"Game_Object.h"
#include"Scene.h"
#include"Manager_Scene.h"
#include"Timer.h"
#include"tuple_convertible_to.h"
#include"Parameter.h"
#include<list>
#include<type_traits>
#include"Quick_Sort.h"
#include"Parameter_Value.h"
#include"Parameter_Change.h"
#include"Parameter_Get.h"
#include"Parameter_Merge.h"

#include<tuple>
#include<optional>
#include<utility>

#include"Function.h"

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

void H::Args_4(int a, int b, int c, int d)
{
	Args_3(a, b, c);
	C_OUT(d);

}

void H::Args_5(int a, int b, int c, int d, int e)
{
	Args_4(a, b, c, d);
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
}

void H::Static_Args_2(int a, int b)
{
	C_OUT(a);
	C_OUT(b);
}

void H::Static_Args_3(int a, int b, int c)
{
	Static_Args_2(a, b);
	C_OUT(c);
}

void H::Static_Args_4(int a, int b, int c, int d)
{
	Static_Args_3(a, b, c);
	C_OUT(d);

}

void H::Static_Args_5(int a, int b, int c, int d, int e)
{
	Static_Args_4(a, b, c, d);
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


//template<class T>
void Hogege(int t) {}

#include"Function_Single_Data.h"
#include"Function_Args_Chack.h"
#include"Function_Multiple_Helper.h"
#include"Tuple.h"
#include"Tuple_Value.h"
#include"Size_T.h"
#include"Tuple_index_sequence.h"
#include"Function_Single_Data.h"

template<>
struct S_Zip<H>
{
	using type = tuple_t<int,int>;
};
#include"Tuple.h"
#include"Tuple_Test.h"
#include"Function_Operator.h"

#include"Function_Core.h"
template<class ...T>
class TEST<N_Function::Method_Core<T...>>
{
public:
	using type = tuple_t<T...>;

};




int main()
{



	Function fn_test(&H::Static_Args_4,3);

	Function fn_test2(fn_test,2);

	Function fn_test3(fn_test2,1);
	Function fn_test4(fn_test2,fn_test3);

	//fn_test4(4,3);
	//fn_test4(999);

	//fn_test2()
	//Function fn_test5(fn_test4,fn_test2);

	
	using mlti =typename N_Function::I_Function_Multiple_Helper<decltype(fn_test), int
		, decltype(fn_test), int, int>::type;

	using T=
		//N_Function::Function_Core<mlti>::request_pointer;

		N_Function::I_Function_Operator_Helper<
		  decltype(fn_test),int
		, decltype(fn_test),int,int
		//, decltype(fn_test),int,int,int
		>::type;
		//decltype(fn_test2);
		//decltype(fn_test5);
		//N_Function::I_Function_Base_Data<decltype(fn_test2)>::type::function;
		//N_Function::I_Function_Multiple_Helper<decltype(fn_test2), decltype(fn_test2)>::type;
	//N_Function::I_Function_Multiple_Helper<decltype(fn_test2)>::type;
	TYPE_ID(mlti);
	TYPE_ID(T);
	//TYPE_ID(T::next_t);
	//TYPE_ID(T::next::next_t);
	//fn_test4();
	//fn_test2.a();
	//using n = N_Function::I_Function_Multiple_Helper<decltype(fn_test), int>::type;

//TYPE_ID(n);

	
	//Function fn_test2(fn_test,3);


	//std::get<0>(fn_test2.data)(2, 4, 5);

	//fn_test2();


	//fn_test2();

	//fn_test2(5);

	//C_OUT(sizeof(fn_test));
	//);
	//fn_test2(4);
	
	//type_id(fn_test);
	//fn_test();
	//fn_test(3,5,1);
	
	//using FF_1 = N_Function::Function_Core<decltype(& H::Static_Args_4),int,int>;


		//N_Function::I_Function_Single_Data<H*, decltype(&H::Args_4), int>::core;
	//using FF_1 = N_Function::I_Function_Single_Data<H*, decltype(&H::Args_4), int>::request_pointer;

	//using FF_2 = N_Function::I_Function_Single_Data<decltype(&H::Args_3), int>::core;
	

	//using FF_3 = N_Function::I_Function_Single_Data<H*,Function<tuple_t<FF_1,FF_2>>,int,int>::request_pointer;




	//using FF_2 = N_Function::I_Function_Single_Data<>::request_args;

//	using FF_2= N_Function::I_Function_Base_Data<FF_1::function,int>;

	//TYPE_ID(FF_1);
	//TYPE_ID(FF_1::type);
	//TYPE_ID(FF_1::request_args);
	//TYPE_ID(FF_1::request_args::type);
	//TYPE_ID(FF_2);

	//using FF_1= N_Function::I_Function_Base_Data<int>::type;

	//using FF_1_1= N_Function::I_Function_Base_Data<FF_1,int>::type;
	//
	//using FF_2= N_Function::I_Function_Base_Data<decltype(&H::Args_3), int>::type;
	//
	//using FF_3 = N_Function::I_Function_Base_Data<H*,N_Function::Function_Core<tuple_t<FF_1_1, FF_2>>,int >::type;
	//
	//
	//
	//
	//
	////using r_t= N_Function::I_Function_Base_Data< decltype(&H::Args_3), int, int>::type;
	//
	//TYPE_ID(FF_1::request_pointer);
	//
	////TYPE_ID(FF_3);
	//TYPE_ID(FF_3::function);
	//TYPE_ID(FF_3::request_pointer);
	//TYPE_ID(FF_3::request_args);
	////TYPE_ID(FF_3::function);
	//
	//using ii = U_Parts_Search<"aiueo",  Parts<"aieo", int>,Parts<"aiueo", int>>::type;
	//
	//
	//TYPE_ID(ii);
	//
	////TYPE_ID(r_t::bind_args);
	////TYPE_ID(r_t::function);
	//
	//using tup= tuple_t<int, float, double>;
	//using t= N_Tuple::U_Range<tup,1,0>;
	//TYPE_ID(t);
	////Function fn_test2(&H::Static_Args_3, 2);
	//
	//
	//
	////Function fn_test3(fn_test, fn_test2);
	//
	//
	//
	//TYPE_ID(N_Tuple::U_index_sequence<0>);
	//using fn_test_h = 
	//	typename
	//	N_Function::I_Function_Multiple_Helper<H*,
	//	decltype(&H::Args_3), int,
	//	decltype(&H::Args_2), int
	//	>::type;
	//
	//
	//using aaa = typename N_Function::I_Function_Operator_Helper<fn_test_h>::type;

	

	//TYPE_ID(aaa);


//	TYPE_ID(fn_test_h);
//	TYPE_ID(fn_test_h::next::type);
//	TYPE_ID(fn_test_h::next::type);
//	TYPE_ID(fn_test_h::next::type::next);
//	TYPE_ID(fn_test_h::next::type::next::next);
//
//	//using op= N_Function::I_Function_Operator< fn_test_h, tuple_t<decltype(&H::Args_2), int,
//	//	decltype(&H::Args_2), int>>;
//
//
//
//
//
//
//	using invalid_tuple = tuple_t<invalid_t, invalid_t, invalid_t>;
//
//	using invalid_tuple_1 = invalid_tuple::front;
//	using invalid_tuple_2 = invalid_tuple_1::next;
//	using invalid_tuple_3 = invalid_tuple_2::next;
//	TYPE_ID(invalid_tuple);
//	TYPE_ID(invalid_tuple_1);
//	TYPE_ID(invalid_tuple_2);
//	TYPE_ID(invalid_tuple_3);
//
//	//Tuple_Test();
//	using nnn = N_Tuple::U_range_index_sequence<9, 14>;
//
//	TYPE_ID(nnn);
//
//	//using Fn = //N_Function::I_Function_Args_Chack<tuple_t<int, int>::back, tuple_t<H>>::request_args;
//		//N_Function::I_Function_Base_Data<H*, N_Function::Method_Core<decltype(&H::Args_2)>,H>::request_args;
//
//		//typename N_Function::IS_Function_Multiple_Helper<decltype(&H::Args_5), int, int, int
//		//, decltype(&H::Args_7), int, int>::type1;// ::type2::type3::type4::T1;// ::type3::type4;
//
//
//	C_OUT(std::is_member_function_pointer<decltype(&H::Args_2)>::value);
//	C_OUT(std::is_member_function_pointer<decltype(&H::Static_Args_2)>::value);
//	using Te = tuple_tp<tuple_t<int, float, double>, char, tuple_t<>>;
//	using ins =
//		N_Tuple::U_Insert<Te, int, 0>;
//	using ins_1 = N_Tuple::I_Insert<Te, int, 0>::type;
//	using FF = //typename N_Function::I_Function_Base_Data<decltype(&H::Static_Args_2), int>::type::function;
//
//		typename
//		N_Function::I_Function_Multiple_Helper<
//		decltype(&H::Static_Args_5), int,
//		decltype(&H::Static_Args_5),
//		//decltype(&H::Static_Args_2), int,
//		H*, decltype(&H::Args_3), int,int,int
//
//		>::type;
//
//	using FFF = N_Function::I_Function_Base_Data<N_Function::Method_Core<decltype(&H::Args_3), int, int>,float>;
//
//	TYPE_ID(FFF::function);
//
//	TYPE_ID(FF);
//	//using int_0=typename N_Function::I_Function_Base_Data<N_Function::Function_Core<FF>>::request_args;
//
//
//
//	using int_1 = N_Function::Method_Core <N_Function::Method_Core<N_Function::Method_Core<decltype(&H::Args_4)>>>;
//
//
//
//
//
//
//	using FF_test =
//		N_Function::Method_Core<
//	N_Function::Method_Core
//	<
//		tuple_t
//		<
//			N_Function::Method_Core<decltype(&H::Args_4)>,
//			N_Function::Method_Core<decltype(&H::Args_3)>,
//			N_Function::Function_Core<decltype(&H::Static_Args_3)>,
//			N_Function::Method_Core
//			<
//				tuple_t
//				<
//					N_Function::Method_Core<decltype(&H::Args_4)>,
//					N_Function::Method_Core<decltype(&H::Args_2)>
//				>
//			>
//
//		>
//	>>;
//	//N_Function::Method_Core<decltype(&H::Args_4)>;
//	
//	using fnc= N_Function::Function_Core<N_Function::Function_Core<N_Function::Function_Core<void(__cdecl*)(int, int, //int,int,int,int), int>,int>,int,int>;
//
//	using int_2 = typename N_Function::I_Function_Base_Data<FF_test>;
//
//	using int_5 = typename N_Function::I_Function_Base_Data<decltype(&H::Static_Args_2), int>::function;
//	using int_4 = typename N_Function::I_Function_Base_Data<fnc,int>::request_args;
//	using ff = typename N_Function::I_Function_Base_Data< 
//		H*,decltype(&H::Static_Args_2)>;
//		//decltype(&H::Static_Args_2)>;
//
//
//	TYPE_ID(int_2::function);
//	TYPE_ID(int_2::request_args);
//	TYPE_ID(typename N_Function::I_Function_Base_Data<decltype(&H::Static_Args_1)>::S_Function_Data<decltype(&H::Args_1)>::c_name);
//
//	//return 0;
//
//	//TYPE_ID(int_0);
//	TYPE_ID(int_1);
//
//	TYPE_ID(int_2::function);
//
//	TYPE_ID(FF);
//	//TYPE_ID(FF_1);
//	C_OUT("");
//	TYPE_ID(int_5);
//	C_OUT("");
//	TYPE_ID(int_4);
//	
//
//
//		//method_range_t<N_Tuple::U_Select<0, tuple_t<int, decltype(&H::Args_2)>>>;
//
//	//using Fn0T = Fn::T;
//	//using Fn1T =typename Fn::type2::type3::type4::T;
//
//	//using Fn0chack_tuple = typename
//		//N_Tuple::U_Range<Fn0T, Fn0::head_size>::reverse;
//
//	//using Fn1chack_tuple = typename N_Tuple::U_Range<Fn1T, Fn1::head_size>::reverse;
//
//	//using Test_T =
//
//		//N_Tuple::I_Remove_Pointer<
//		//tuple_tp<tuple_t<double, short, int>, float, tuple_t<double, short>>
//		//>::type;
//
//		//typename N_Tuple::I_Range<tuple_tp<tuple_t<double,short,int>,float,tuple_t<double,short>>,0,1>::type;
//
//
//		//N_Tuple::S_Action_Tuple_t<TEST,
//		//tuple_tp<tuple_t<double, short, int>, float, tuple_t<double, short>>>::type;
//
//	//TYPE_ID(TEST<typename FF::back_t>::type);
//	//TYPE_ID(decltype(H::Static_Args_2));
//	//TYPE_ID(decltype(H::Args_2));
//	
//	//std::is_member_function_pointer_v
//	
//	C_OUT(std::is_class_v<std::remove_pointer_t<decltype(&H::Static_Args_2)>>);
//	C_OUT(std::is_class_v<std::remove_pointer_t<decltype(&H::Args_2)>>);
//	C_OUT(std::is_class_v<std::remove_pointer_t<N_Function::Function_Core<void(__cdecl*)(int, int, int, int, int, int)>>>);
//	C_OUT(std::is_class_v<invalid_t>);
//	C_OUT(std::is_class_v<H*>);
//
//	using t =fnc;
//	C_OUT(
//	(!
//		(
//			(std::is_class_v<std::remove_pointer_t<t>>) &&
//			(std::is_pointer_v<t>)
//		)
//	)
//	
//	);

	//TYPE_ID(FF::type);
	//TYPE_ID(FF::next_t);
	//TYPE_ID(FF::next::next_t);
	//TYPE_ID(FF::next::next::next_t);

	//TYPE_ID(FF::type_1);
	//TYPE_ID(FF::type_2);
	//TYPE_ID(FF::type_3);
	//using ins_3 = N_Tuple::U_Insert<FF::type_2, FF::type_3, 0>;
	//TYPE_ID(ins_1);

	//C_OUT(Fn0::head_size);
	//C_OUT(Fn0::size);
	//C_OUT(Fn1::head_size);
	//C_OUT(Fn1::size);
	//TYPE_ID(Fn0);
	//TYPE_ID(Fn1);
	//TYPE_ID(Fn0T);
	//TYPE_ID(Fn1T);
	

	//using T_ = typename N_Tuple::I_Select<8, tup>::Type::Type;

//
//
//	static constexpr int n = 2Ui64;
//
//	//using tT = typename N_Tuple::I_Pointer<2, T_>::Type;
//
//
//	//using sT = typename N_Tuple::I_Pointer<2, tup>::Type;
//
//	using tua = typename N_Tuple::tuple_v<0, 3, 4, 7, 2.0f>;
//
//	
//
//	
//
//
//
//
//
//
//	//Tuple b(3, 4, '8', 3.0f);
//
//	Size_t ss = -3;
//	constexpr Size_t sss = 7;
//	constexpr int ssss = 6;
//	//int n = ss - 1;
//	constexpr unsigned long long so = 3;
//
//	bool te = (ss == sizeof(so));// == 3);
//
//
//
//
//	//decltype(b)::
//
//	//auto h2 = new H2;
//
//	//using Tu = N_Function::IS_Function_Multiple_Helper<decltype(&H::Args_3), int, int, H*, decltype(&H::Args_3), int>::Pointer_Judge;
//
//
//	//static constexpr bool Tuu = not_is_invalid<typename  N_Function::S_Function_Single_Data<H*, decltype(&H::Args_3),int, int>::Method>;
//
//	//using Tt = N_Function::I_Function_Args_Chack<S_Parameter<int>, S_Parameter<int>>::IS_Zip_Expand<1, S_Parameter<S_Zip<float>>, double>::Change;
//
//	//using TTt= N_Function::I_Function_Args_Chack<S_Parameter<int>, S_Parameter<int>>::IS_Zip_Expand<0,Tt, double>::Change;
//
//
//
//
//	//using Tn = typename N_Function::I_Function_Args_Chack<S_Parameter<int, int, int>,
//	//	S_Parameter<int, int>>::Type;
//
//
//	using Tnaa = typename IS_Parameter_Merge<S_Parameter<N<1>, N<2>, N<3>>, N<4>, N<6>,N<7>>::Type;
//
//
//
//
//	//TYPE_ID(TTt);
//
//
//	//C_OUT();
//
//	//using n = U_Element_t<0, Tu>;
//
//	
//
//		//IS_Range_Parameters<S_Parameter<N<1>,N<2>,N<3>>, 0,2>::Type;
//
//	//using TT4 = N_Function::I_Function_Args_Chack<S_Parameter<int,int,int>,S_Parameter<int>>::
//	//using Tfa = N_Function::IS_Function_Multiple_Helper<H*, decltype(&H::Args_3), int, decltype(&H::Args_3), int, int>::Type::Fns;
//
//
//
//	//using Tfa = N_Function::IS_Function_Multiple_Operator<H*, decltype(&H::Args_3), int>::Type;
//
//	//auto b = Tfa(h, &H::Args_3, 2);
//
//	//auto f = N_Function::Function_Single(h, &H::Args_3, 1);
//
//	//static constexpr auto ff = N_Function::Function_Single_Static<&H::Args_3, 1, 3,3>();
//
//
//
//	//auto f3 = N_Function::Function_Multiple(&H::Static_Args_3, 3, h, & H::Args_3, 22, 2, 2);
//
//	//auto f3 = N_Function::Function_Single(&Hogege);
//
//	//auto f5 = N_Function::Function_Single(h, &H::Args_3, 3);
//
//	
//
//	//type_id(&H::Static_Args_3);
//
//	//auto f2 = N_Function::Function_Multiple(h
//	//	,&H::Args_5, 5, 4, 3, 2, 1
//	//	,&H::Args_5,5,4,3,2
//	//	,&H::Args_5,5,4,3
//	//	,&H::Args_5,5,4
//	//	,&H::Args_5,5
//	//	,&H::Args_5
//	//);
//
////	f2.
//	
//	//f2(6, 7, 8, 9, 0);
//	//f2(6, 7, 8, 9);
//	//f2(6, 7, 8);
//	//f2(6, 7);
//	//f2(6);
//	//f2();
//	//
//
//	//f2(2, 3);
//	//TYPE_ID(Tfa);
//	N_Sort<N<3>, N<5>>::Judge;
//
//	using TPN_1 = S_Parameter<N<1>>;
//	using TPN_2 = S_Parameter<N<5>, N<3>>;
//	using TPN_3 = S_Parameter<N<1>, N<3>, N<5>>;
//	using TPN_4 = S_Parameter<N<2>, N<1>, N<4>, N<3>>;
//	//using TPN_4 = S_Parameter<N<14>,N<18>,N<7>,N<9>>;
//	//using TPN_4 = S_Parameter<N<14>,N<18>, N<9>, N<7>>;
//	//using TPN_4 = S_Parameter<N<14>,N<18>, N<9>, N<7>, N<23>, N<15>>;
//	//using TPN_4 = S_Parameter<N<2>, N<1>, N<4>, N<3>, N<6>, N<5>,N<14>,N<18>, N<9>, N<7>, N<23>,N<15>>;
//	//using TPN_4 = S_Parameter<N<2>, N<1>, N<4>, N<3>, N<6>, N<5>>;
//	//using TPN_4 = S_Parameter<N<0>,N<1>, N<2>, N<3>, N<4>, N<5>,N<6>,N<14>,N<8>,N<9>,N<10>,N<11>,N<12>>;
//
//	using Q_Sort_1 =typename IS_Quick_Sort<N_Sort, TPN_4>::Type;
//
//	using T_5 = S_Parameter_Value<0, 1, 3, 5, 7, 9>;
//	//using T_6 = U_Get_Element_P_v<T_5, S_Parameter_Value<0, 1, 3>>;
//	using TTTTT = N < U_Element_vp<3, T_5>>;
//
//	//using TTTT = U_Get_Element_P_t<Q_Sort_1, S_Parameter_Value<1, 3, 5>>;
//
//	TYPE_ID(Q_Sort_1);
//
//
//
//
//	using T = S_Parameter<short,int, float, char>;
//	//using T1 = U_Insert_Element_t<T, 1, T>;
////	using T2 = S_Parameter<T,T,T>;
//	//using Tva= S_Parameter_Value<0, 1>;
//	//using Tvb= S_Parameter_Value<2, 3>;
//
//	//using Tvc= S_Parameter_Value<7, 5>;
//	//using Tv2 = S_Parameter_Value < Tva{}, Tvb{}, Tvc{} > ;
//	//using Tv3 = Tv2::Parameter_Type;
//	//using Tv4 = U_Change_Element_v<0, 4, Tv2>;
//		//IS_Parameter_Class_Change_Value<typename IS_Insert_Parameters<typename Tv2::Parameter_Type,4, integral_constant<4>, integral_constant<4>, integral_constant<4>, integral_constant<4>>::Type>::Type;
//	
//
////using Tvv = S_Parameter_Element_Variable<1, Tv2>::Type;
//
//	//constexpr auto Tvvv = S_Parameter_Element_Variable<4, Tv2>::value;
//
//	//using Tf = IS_Insert_Parameters<T, 1, float>::Type;
//
//	//using Tr = IS_Remove_Parameters<T, 1,3>::Type;
//	//using Tr = U_Remove_Element_t<T, 1, 3>;
//	
//	//IS_Change_Parameters
//	//using Tcr = IS_Change_Parameters<0, 3, T>::Type;
//
//	//using Sort = IS_Quick_Sort<N_Sort, S_Parameter<N<2>, N<5>, N<7>>>::Type::Type;
//
//	//TYPE_ID(Sort);
//
//
//	//using t = U_Element_t<2, int, int, char, int, int, char>;
//
//	//IS_Parameter_Element<1,int, float, char>::Next::Next::
//
//	//Function::Single mt(&H::Args_5, 1,3,54,2);
//
//	//TYPE ab;
//
//	//N_Function::Function_Single mt2(h,&H::Args_3);
//	//using T = N_Function::IS_Function_Single_Helper<H*, decltype(&H::Args_3), int>::Judge;
//	//TYPE_ID(T);
//
//	//N_Function::S_MethodData<decltype(&H::Args_3),int>::
//	//mt2(2, 4);
//	//auto mt3= AUTO();
//
//	//mt3();
//
//	//Function::Single mt2(ab.mt);
//	//mt2();
////	mt2();
//
//
//	//for (int i = 0; i < ma.Size; i++)
//	//{
//	//	C_OUT(ma[i]);
//	//}
//	
//	




	//Function::Single b(&H::Args_2, 1);
	//Function::Single c(b,6);
	//
	////c();
	//static constexpr Function::Single_Static<&H::Args_2, 1> bb;

	//Function::Single_Static<bb,2> cc;
	//cc();

	
	
	//
	//static constinit auto BB = Function::Create<&H::Args_4, 9999>();
	//static constexpr N_Function::Function_Single_Static<&H::Args_3,1> aa = {};

	//static constexpr N_Function::Function_Multiple_Static<aa,aa,2,aa,2,3> aa = {};


	//static constexpr N_Function::Function_Single_Static<aa, 2> aaa = {};


	//


	//

	//auto B = Function::Create<&H::Args_2, 3, 4, &H::Args_2, 3>();

	//B(3);
	//


	//Function::Multiple a(&H::Args_3, 1, 2, &H::Args_3, 1);

	//a(33,2);
	//Function::Single b(&H::Args_3, 1, 2);
	_CrtDumpMemoryLeaks();
	return 0;

}


















