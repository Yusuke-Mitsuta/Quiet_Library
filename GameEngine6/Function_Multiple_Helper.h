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

		using commond_point = std::tuple_element_t<0, tuple_t<T_Fn_Parts...>>;


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
			using type = T_Tuple;
		};


		template<class T_Tuple, class T_Tuple_Method_Bound = tuple_t<>>
		struct S_Method_Bound
		{

			template<class T_Method_Point>
			using chack_tuple = typename
				N_Tuple::U_Range<T_Tuple, T_Method_Point::head_size-(T_Method_Point::head_size== T_Method_Point::size)>::reverse;


			template<class T_Method_Point = typename S_Method_Search<T_Tuple>::type>
			struct S_Method_Point
			{

				template<class T_Tuple,class T_Method_Group>
				using Method_Bound =typename S_Method_Bound<typename T_Tuple::next,
					N_Tuple::U_Insert<T_Tuple_Method_Bound,typename T_Method_Group::remove_p>>::type;

				//仕様
				//関数及び、引数の型に対して、適切にポインターをセットする
				// 
				// テンプレート
				//[T_Function_Check]:取得した関数、及び引数が、既に使用出来る状態
				//[T_Dedicated_Point_Check]:取得した関数、及び引数が、関数の次に設定されているポインターで使用出来る状態
				//[T_Commond_Point_Check]:取得した関数、及び引数が、共通で設定されたポインターで使用出来る状態
				template<class T_Function_Check = typename I_Function_Single_Data<chack_tuple<T_Method_Point>>::function,
						 class T_Dedicated_Point_Check = typename I_Function_Single_Data<chack_tuple<typename T_Method_Point::next>>::function,
						 class T_Commond_Point_Check = typename I_Function_Single_Data<N_Tuple::U_Insert<chack_tuple<T_Method_Point>,commond_point,0>>::function>
				struct S_Function_Check
				{
					using type = Method_Bound<T_Method_Point, chack_tuple<T_Method_Point>>;
				};

				//仕様
				//取得した関数、及び引数が、関数の次に設定されているポインターで使用出来る状態
				template<class T_Dedicated_Point_Check, class T_Commond_Point_Check>
				struct S_Function_Check<invalid_t, T_Dedicated_Point_Check, T_Commond_Point_Check>
				{
					using type = Method_Bound<typename T_Method_Point::next, chack_tuple<typename T_Method_Point::next>>;
				};

				//仕様
				//取得した関数、及び引数が、共通で設定されたポインターで使用出来る状態
				template<class T_Commond_Point_Check>
				struct S_Function_Check<invalid_t, invalid_t, T_Commond_Point_Check>
				{
					using type = Method_Bound<T_Method_Point, N_Tuple::U_Insert<chack_tuple<T_Method_Point>, commond_point, 0>>;

				};

				//仕様
				//関数に対して、引数の方が不一致な場合、次の関数を探索する
				template<>
				struct S_Function_Check<invalid_t, invalid_t, invalid_t>
				{

					using type = S_Method_Point<typename S_Method_Search<typename T_Method_Point::next>::type>::type;
				};

				using type = S_Function_Check<>::type;

			};

			//仕様
			//関数に対して、引数の方が不一致であり、全ての探索が終わった場合
			template<class T_Head>
			struct S_Method_Point<tuple_tp<T_Head,invalid_t,tuple_t<>>>
			{
				using type = invalid_t;
			};

			using type = S_Method_Point<>::type;

		};

		//仕様
		//全ての型の探査が正常に終了した場合、結果を出力する
		template<class T_Head,class T_Tail,class T_Tuple_Method_Bound>
		struct S_Method_Bound<tuple_tp<T_Head,invalid_t,T_Tail>,T_Tuple_Method_Bound>
		{
			using type = T_Tuple_Method_Bound;

		};

	public:

		using type = S_Method_Bound<
			typename tuple_t<T_Fn_Parts...>::reverse::front>::type;

		

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