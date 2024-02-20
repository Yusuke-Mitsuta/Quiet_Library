#pragma once

#include"SwapType.h"
#include"Tuple.h"

namespace quiet::N_Function
{
	template<class ...T_Parts>
	struct I_Function_Valid_Data;
	

	//仕様
	//[T_Parts...]で[Function]が使用出来るか判定し、成功すれば[Function_Core]に纏められる
	// 
	//テンプレート
	//[T_Parts...]:
	//	メソッドに使用する共通のポインターの型(省略可能)
	//	関数オブジェクトの型
	//	それに対する引数の型(並びの一番後ろの型が、関数の引数型の一番後ろと判定される)
	template<class ...T_Parts>
	struct I_Function_Single_Helper
	{
	private:
		using Lapping_Fn = I_Function_Valid_Data<T_Parts...>;

		template<class T_True>
		using Fn_Judge = U_Judge_t<T_True,is_invalid_not<typename Lapping_Fn::request_args>>;

	public:

		//仕様
		//纏められた[Function_Core]
		using type = typename I_Function_Valid_Data<T_Parts...>::type;

		//仕様
		//纏められた関数オブジェクトに対応した、使用した型の番号を[tupel_t<tuple_v<>>]に入れる
		using access_number = tuple_t<Fn_Judge<
			N_Tuple::U_Select<
			same_as<typename Lapping_Fn::function,
			typename I_Function_Valid_Data<N_Tuple::U_Element_t<1,tuple_t<T_Parts...>>>::function>,
			typename N_Tuple::U_index_sequence<sizeof...(T_Parts)>>>>;
		
		//仕様
		//纏め作業が成功すれば、[T_Parts...]の先頭の型が、失敗すれば、[invalid_t]を返す
		using judge = Fn_Judge<typename tuple_t<T_Parts...>::front_t>;


	};

};

