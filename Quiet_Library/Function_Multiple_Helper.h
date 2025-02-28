/*!
 * Function_Multiple_Helper.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

#include"Tuple.h"
#include"SwapType.h"

namespace quiet::N_Function
{
	template<class ...T_Parts>
	struct Function_Core;

	template<class ...T_Parts>
	struct I_Function_Superficial_Data;

	//仕様
	//関数に対して、次の関数オブジェクトが出てくるまでの間の型が引数の型と互換性があるか判定する
	//メソッドに対しては、上記に加え、メソッドの前の型がポインターの型と互換性があるか判定し、
	//	失敗すれば、テンプレートの先頭の型がポインターの型と互換性があるか判定する
	//この操作を繰り返し、全て成功すれば、[Function_Core]事に纏められた後、[tuple_t]に纏められる。
	//
	//テンプレート
	//[T_Fn_Leftovers_Parts...]:
	//	メソッドに使用する共通のポインターの型(省略可能)
	//	関数オブジェクトの型
	//	それに対する引数の型(並びの一番後ろの型が、関数の引数型の一番後ろと判定される)
	//	次のメソッドに対する専用のポインターの型(次にメソッドを使用する場合)
	//	関数オブジェクトの型
	// と続く
	// 
	//補足
	//関数に対する引数の型として関数の型を取る場合
	//その間の型と引数の型に互換性があれば、引数として取ろうとしてる関数の型が次の関数として見なされる為、
	//	単体の関数として処理をする事
	template<class ...T_Fn_Parts>
	struct I_Function_Multiple_Helper
	{
	private:

		using front_t =typename tuple_t<T_Fn_Parts...>::type;

		template<class T_Tuple, class T_method = typename Function_Core<typename T_Tuple::type>::function>
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


		//仕様
		//結果を返すクラス
		//
		//テンプレート
		//[T_Tuple_Method_Bound]::[Function_Core]が纏められた[tuple_t]
		//[T_Tuple_Access_Number]::纏められた関数オブジェクト一つに対して、使用した型の番号をが纏められた[tupel_t]
		template<class T_Tuple_Method_Bound, class T_Tuple_Access_Number>
		struct S_Result
		{
			using type = T_Tuple_Method_Bound;

			using access_number = T_Tuple_Access_Number;

		};


		template<class T_Tuple_Method_Start_Point,class T_Tuple_Method_Bound = tuple_t<>,class T_Tuple_Access_Number = tuple_t<>>
		struct S_Method_Bound
		{
			template<class T_Method_Select = typename S_Method_Search<T_Tuple_Method_Start_Point>::type>
			struct S_Method_Point
			{

				template<class T_Method_Point>
				using chack_Data = typename
					N_Tuple::U_Range<T_Tuple_Method_Start_Point, T_Method_Point::head_size +1 - (T_Method_Point::head_size == T_Method_Point::size)>::reverse;

				template<class T_Method_Point>
				using access_numbers =
					N_Tuple::U_range_index_sequence<T_Method_Point::tail_size, T_Tuple_Method_Start_Point::tail_size + 1>;

				template<class T_Tuple, class T_Method, class T_access_numbers>
				using Method_Bound = typename S_Method_Bound<typename T_Tuple::next,
					N_Tuple::U_Insert<T_Tuple_Method_Bound, typename T_Method::type>,
					N_Tuple::U_Insert<T_Tuple_Access_Number, T_access_numbers>>::type;

				template<class T_Tuple>
				using Function_Data =
					typename N_Tuple::I_Move_Template<I_Function_Superficial_Data, T_Tuple>::type;

				template<class T_chack>
				static constexpr bool pointer_chack =
					std::is_pointer_v<std::remove_reference_t<T_chack>>
						&& std::is_class_v<std::remove_pointer_t<std::remove_reference_t<T_chack>>>;

				//仕様
				//指定されたポインターをが必要か判定する。
				// 
				// テンプレート
				//[T_Function]:引数がBindされた関数オブジェクト
				//[T_Dedicated_Point_Check]:指定された引数の型と、関数の次に設定されているポインターを判定する
				//[T_Commond_Point_Check]:指定された引数の型と、共通で設定されたポインターを判定する
				//[T_Method_Check]:指定された引数の型を受け取るか判定する
				template<class T_Function = Function_Data<chack_Data<T_Method_Select>>,
					class T_Dedicated_Point_Check = Function_Data<chack_Data<typename T_Method_Select::next>>,
					class T_Commond_Point_Check = Function_Data<N_Tuple::U_Insert<typename chack_Data<T_Method_Select>::front, front_t>>>
				struct S_Pointer_Chack
				{
					using type =
						Method_Bound<T_Method_Select,
						T_Function, 
						typename access_numbers<T_Method_Select>::create_p>;
				};

				//仕様
				//専用で設定されたポインターを判定する
				template<class T_Function, class T_Dedicated_Point_Check, class T_Commond_Point_Check>
					requires pointer_chack<typename T_Method_Select::next_t> &&
					requires
				{
					requires same_as_not<typename T_Function::request_pointer, typename T_Dedicated_Point_Check::request_pointer>;
				}
				struct S_Pointer_Chack<T_Function, T_Dedicated_Point_Check, T_Commond_Point_Check>
				{
					using type =
						Method_Bound<typename T_Method_Select::next,
						T_Dedicated_Point_Check,
						typename access_numbers<typename T_Method_Select::next>::next>;
				};

				//仕様
				//共通で設定されたポインターを判定する
				template<class T_Function, class T_Dedicated_Point_Check, class T_Commond_Point_Check>
					requires pointer_chack<front_t> &&
					requires
				{
					requires is_invalid<typename T_Dedicated_Point_Check::function> ||
					 same_as<typename T_Function::request_pointer, typename T_Dedicated_Point_Check::request_pointer>;

					requires same_as_not<typename T_Function::request_pointer, typename T_Commond_Point_Check::request_pointer>;
				}
				struct S_Pointer_Chack<T_Function, T_Dedicated_Point_Check, T_Commond_Point_Check>
				{
	
					using type = Method_Bound<T_Method_Select,
						T_Commond_Point_Check,
						typename N_Tuple::U_Next<typename N_Tuple::U_Insert_v<access_numbers<T_Method_Select>,
						static_cast<size_t>(0)>>>;
				};

				//仕様
				//関数に対しては、指定された引数の型を受け取るか判定する
				// 
				// テンプレート
				//[T_Function_Check]:指定された引数の型を受け取るか判定する
				template<class T_Args_chack = typename Function_Data<chack_Data<T_Method_Select>>::request_args>
				struct S_Callable_Check
				{
					using type = S_Pointer_Chack<>::type;
				};


				//仕様
				//関数に対して、引数のが不一致な場合、次の関数を探索する
				template<>
				struct S_Callable_Check<invalid_t>
				{
					using type = S_Method_Point<typename S_Method_Search<typename T_Method_Select::next>::type>::type;
				};

				using type = S_Callable_Check<>::type;
			};

			//仕様
			//関数に対して、引数の型が不一致であり、全ての探索が終わった場合
			template<class T_Head>
			struct S_Method_Point<tuple_tp<T_Head, invalid_t, tuple_t<>>>
			{
				using type = S_Result<invalid_t, invalid_t>;

			};

			using type = S_Method_Point<>::type;
		};

		//仕様
		//全ての型の探査が正常に終了した場合、結果を出力する
		template<class T_Head, class T_Fns, class T_Tuple_Access_Number>
			requires is_class_pointer <std::remove_reference_t<front_t>>
		struct S_Method_Bound<tuple_tp<T_Head, front_t, tuple_t<>>, T_Fns, T_Tuple_Access_Number>
		{
			using type = S_Result<T_Fns, T_Tuple_Access_Number>;
		};

		//仕様
		//全ての型の探査が正常に終了した場合、結果を出力する
		template<class T_Head,  class T_Fns, class T_Tuple_Access_Number>
		struct S_Method_Bound<tuple_tp<T_Head, invalid_t, tuple_t<>>, T_Fns, T_Tuple_Access_Number>
		{
			using type = S_Result<T_Fns, T_Tuple_Access_Number>;
		};


		using start_tuple = typename tuple_t<T_Fn_Parts...>::reverse::front;

		using result = S_Method_Bound<start_tuple>::type;

	public:

		//仕様
		//[Function_Core]が纏められた[tuple_t]
		using type = result::type;

		//仕様
		//纏められた関数オブジェクト一つ一つに対応した、使用した型の番号をが纏められた[tupel_t]
		using access_number = result::access_number;

		//仕様
		//纏め作業が成功すれば、[T_Fn_Leftovers_Parts...]の先頭の型が、失敗すれば、[invalid_t]を返す
		using judge = U_Judge_t<front_t, is_invalid_not<type>>;
	};


}