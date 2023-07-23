#pragma once

#include"Concept.h"
#include<optional>
#include"Function.h"

namespace N_Function
{

	//仕様
	//複数の[Function]から[T_Args...]で呼び出せる関数オブジェクトを探す
	//
	//template
	//T_TupleFns::tupleにラッピングされた複数の[Function]
	//T_Args...::引数の型
	template<class T_TupleFns, class ...T_Args>
	class IS_MethodSearch
	{
	private:
		template<int t_MethodNumber = 1, bool t_hitFg = true>
		struct S_MethodSearch
		{
			static constexpr bool judge = tuple_convertible_to<typename IS_TupleUnzip<T_Args..., typename tuple_element_t_overflow<t_MethodNumber - 1, T_TupleFns>::BoundArgs>::Type, typename tuple_element_t_overflow<t_MethodNumber - 1, T_TupleFns>::Args>;

			static constexpr bool range = (t_MethodNumber + 1 <= std::tuple_size_v<T_TupleFns>);

			using Type = S_MethodSearch<(t_MethodNumber + 1)* (judge || range), (!judge)* range>::Type;
		};

		template<int t_MethodNumber>
		struct S_MethodSearch<t_MethodNumber, false>
		{
			using Type = S_MethodSearch;
			using Judge = std::bool_constant<(t_MethodNumber)>;
			static constexpr size_t MethodNumber = t_MethodNumber - 2;
		};

		using Type = S_MethodSearch<>::Type;

	public:

		//仕様
		//呼び出せる[Function]が存在するか
		using Judge = typename Type::Judge;

		//仕様
		//呼び出せる[Function]が存在する場合の番号
		static constexpr size_t MethodNumber = Type::MethodNumber;
	};
}