#pragma once

#include"Tuple.h"
#include"SwapType.h"
#include"Select_Type.h"
#include"Function_Single_Data.h"


namespace N_Function
{

	
	//仕様
	//関数に対して、次の関数又はメソッドが出てくるまでの間の型が引数の型と互換性があるか判定する
	//メソッドに対しては、上記に加え、メソッドの前の型がポインターの型と互換性があるか判定し、
	//	失敗すれば、テンプレートの先頭の型がポインターの型と互換性があるか判定する
	//この操作を繰り返し、全て成功すれば、関数、メソッドオブジェクト事に纏められた後、[tuple_t]に纏められる。
	//
	//テンプレート
	//[T_Fn_Parts...]:
	//	メソッドに使用する共通のポインターの型(省略可能)
	//	関数、又はメソッドの型
	//	それに対する引数の型(並びの一番後ろの型が、関数の引数型の一番後ろと判定される)
	//	次のメソッドに対する専用のポインターの型(次にメソッドを使用する場合)
	//	関数、又はメソッドの型
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


		using commond_point = std::tuple_element_t<0, tuple_t<T_Fn_Parts...>>;


		template<class T_Tuple, class T_method = typename I_Function_Single_Data<typename T_Tuple::type>::function>
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


		template<class T_Tuple, bool t_function_check_fg, bool t_method_check_fg, 
			class T_Tuple_Method_Bound = tuple_t<>,
			class T_Tuple_Access_Number = tuple_t<>>
		struct S_Method_Bound
		{


			template<class T_Method_Point = typename S_Method_Search<T_Tuple>::type>
			struct S_Method_Point
			{


				template<class T_Method_Point>
				using chack_tuple = typename
					N_Tuple::U_Range<T_Tuple, T_Method_Point::head_size - (T_Method_Point::head_size == T_Method_Point::size)>::reverse;

				template<class T_Method_Point>
				using access_numbers =
					N_Tuple::U_range_index_sequence<T_Method_Point::tail_size, T_Tuple::tail_size+1>;
				

				template<class T_Tuple,class T_Method,class T_Access_Number>
				using Method_Bound =typename S_Method_Bound<typename T_Tuple::next,t_function_check_fg,t_method_check_fg,
					N_Tuple::U_Insert<T_Tuple_Method_Bound,T_Method>,
					N_Tuple::U_Insert<T_Tuple_Access_Number, T_Access_Number>
				>::type;

				//仕様
				//関数に対しては、指定された引数の型を受け取るか判定する、
				//メソッドに対しては、指定された引数の型と、クラスポインターを受け取るか判定する、
				// 
				// テンプレート
				//[T_Function_Check]:指定された引数の型を受け取るか判定する
				//[T_Dedicated_Point_Check]:指定された引数の型と、関数の次に設定されているポインターを判定する
				//[T_Commond_Point_Check]:指定された引数の型と、共通で設定されたポインターを判定する
				//[T_Method_Check]:指定された引数の型を受け取るか判定する
				template<class T_Function_Check = typename I_Function_Single_Data<chack_tuple<T_Method_Point>>::function,
						 class T_Dedicated_Point_Check = typename I_Function_Single_Data<chack_tuple<typename T_Method_Point::next>>::function,
						 class T_Commond_Point_Check = typename I_Function_Single_Data<N_Tuple::U_Insert<chack_tuple<T_Method_Point>,commond_point,0>>::function
				
				>
				struct S_Callable_Check
				{

					using type = Method_Bound<T_Method_Point,T_Function_Check
						,access_numbers<T_Method_Point>>;
				};	

				//仕様
				//指定された引数の型を受け取るか判定する
				template<class ...T_Function_Check,class ...T_Dedicated_Point_Check, class T_Commond_Point_Check>
				struct S_Callable_Check<Method_Core<T_Function_Check...>,Function_Core<T_Dedicated_Point_Check...>, T_Commond_Point_Check>
				{
					using type = 
						Method_Bound<typename T_Method_Point::next, Function_Core<T_Dedicated_Point_Check...>,
						access_numbers<typename T_Method_Point::next>>;
				};

				//仕様
				//指定された引数の型と、共通で設定されたポインターを判定する
				template<class ...T_Function_Check, class ...T_Dedicated_Point_Check, class ...T_Commond_Point_Check>
				struct S_Callable_Check<Method_Core<T_Function_Check...>, Method_Core<T_Dedicated_Point_Check...>,Function_Core<T_Commond_Point_Check...>>
				{
					using type = Method_Bound<T_Method_Point, Function_Core<

						T_Commond_Point_Check...>,access_numbers<T_Method_Point>>;
				};


				//仕様
				//関数に対して、引数のが不一致な場合、次の関数を探索する
				template<>
				struct S_Callable_Check<invalid_t, invalid_t, invalid_t>
				{
					using type = S_Method_Point<typename S_Method_Search<typename T_Method_Point::next>::type>::type;
				};


				using type = U_if_t1<S_Callable_Check<>, S_Callable_Check<invalid_t,invalid_t,invalid_t>,t_function_check_fg>::type;

			};

			//仕様
			//関数に対して、引数の型が不一致であり、全ての探索が終わった場合
			template<class T_Head>
			struct S_Method_Point<tuple_tp<T_Head,invalid_t,tuple_t<>>>
			{
				using type = invalid_t;
			};

			using type = S_Method_Point<>::type;

		};

		//仕様
		//全ての型の探査が正常に終了した場合、結果を出力する
		template<class T_Head,class T_Tail, bool t_function_check_fg, bool t_method_check_fg,class T_Tuple_Method_Bound, class T_Tuple_Access_Number>
		struct S_Method_Bound<tuple_tp<T_Head,invalid_t,T_Tail>, t_function_check_fg,t_method_check_fg, T_Tuple_Method_Bound,T_Tuple_Access_Number>
		{
			using type = tuple_t<T_Tuple_Method_Bound, T_Tuple_Access_Number>;


		};

		using start_tuple = typename tuple_t<T_Fn_Parts...>::reverse::front;

	public:

		//仕様
		//ファンクションとして判定し、失敗すれば、メソッドとして判定する
		using type = S_Method_Bound<start_tuple,true,true>::type;
		
		//仕様
		//ファンクションとして判定する
		using function_check= S_Method_Bound<start_tuple, true, false>::type;

		//仕様
		//メソッドとして判定する
		using method_check = S_Method_Bound<start_tuple, false, true>::type;

	};

}