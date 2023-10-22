#pragma once

#include"Tuple.h"
#include"SwapType.h"
#include"Select_Type.h"
#include"Function_Single_Data.h"


namespace N_Function
{

	//仕様
	//関数ポインターに対して、引数の値が正しいか、後方一致で判定する
	//
	//テンプレート
	//TP_Fns::関数ポインター、指定する引数、のTuple
	//
	//補足
	//T_Fn_Argsは関数ポインター、それに指定する引数、次の関数ポインター、となるようにする事
	// //SetJudge::関数に対して、「後ろに続く引数の型、関数にバインド済みの引数の型」が関数に対する引数の型の後方部分と互換性があるか判定する
	//Fns::関数ポインターor[Function_Single]と、後ろに続く引数の型を[Function_Single]としてまとめ、その動作を[TP_Fns...]がなくなるまで繰り返す
	template<class ...T_Fn_Parts>
	struct IS_Function_Multiple_Helper
	{
	private:

	public:
		//using commond_point = std::tuple_element_t<0, tuple_t<T_Fn_Parts...>>;


		template<class T_Tuple, class T_method = typename I_Function_Single_Data<typename T_Tuple::type>::method>
		struct S_Method_Search
		{
			using type = T_Tuple;
		};

		template<class T_Tuple>
		struct S_Method_Search<T_Tuple, invalid_t>
		{
			using type = S_Method_Search<typename T_Tuple::next>::type;
		};

		template<class T_Tuple>
			requires is_invalid<typename T_Tuple::type>
		struct S_Method_Search<T_Tuple, invalid_t>
		{
			using type = typename T_Tuple::back;
		};



		template<class T_Tuple, class T_Tuple_Method_Bound = tuple_t<>>
		struct S_Method_Bound
		{
			template<class T_Method_Point>
			struct S_Method_Chack
			{
				using chack_tuple = typename
					N_Tuple::U_Range<T_Tuple, T_Method_Point::head_size>::reverse;

				using type = I_Function_Single_Data<chack_tuple>::method;
			};

			template<class T_Args_Start_Point = T_Tuple>
			struct S_Args_Start_Point
			{


				template<class T_Method_Point = typename S_Method_Search<T_Args_Start_Point>::type,
					class T_Args_Chack =typename S_Method_Chack<T_Method_Point>::type>
				struct S_Method_Args_Chack
				{
					using type4 =// T_Tuple;
						//typename T_Method_Point::next;
						S_Method_Bound<typename T_Method_Point::next,
						N_Tuple::U_Insert<T_Tuple_Method_Bound, typename S_Method_Chack<T_Method_Point>::chack_tuple>>;
				};
				
				using T = T_Tuple;
				using type3 = S_Method_Args_Chack<>;

			};
			using T = T_Tuple;
			using T1 = typename S_Method_Search<T_Tuple>::type;

			using type2 = S_Args_Start_Point<>;

		};

		template<class T_Head,class T_Tail,class T_Tuple_Method_Bound>
		struct S_Method_Bound<tuple_tp<T_Head,invalid_t,T_Tail>,T_Tuple_Method_Bound>
		{
			using type2 = T_Tuple_Method_Bound;


		};


		


	public:

		using type1 = S_Method_Bound<
			typename tuple_t<T_Fn_Parts...>::reverse::front>;

		

		//仕様
		//全ての関数オブジェクトにおいて適切なクラスポインターがセットされているか判定する
		//using Pointer_Judge = S_CorrectType<>::type;


		//using type1_1 = S_CorrectType<>;

		//using type1 = S_CorrectType<0>;

		//仕様
		//判定の項目からクラスポインターがセットされているかを除外する
		//using Not_Pointer_Judge = S_CorrectType<0>::type;

		//using Fns = Type::Fns;

	};

}