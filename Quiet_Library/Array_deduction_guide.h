#pragma once

#include"Tuple.h"
#include"Function_Args_Chack.h"

namespace quiet::N_Array
{

	template<class T_Array_Type, class ...T_Args>
	static constexpr int args_size =
		N_Tuple::N_Apply::I_Type_Chack<
		tuple_t<N_Tuple::N_Apply::S_Infinite_Args<T_Array_Type>>,
		tuple_t<T_Args...>>::value;

	template<class T_Base_Type, class ...T_Args>
	struct I_deduction_guide
	{
	private:

		template<class T_Array_Type>
		static constexpr int args_size =
			N_Array::args_size<T_Array_Type, T_Base_Type, T_Args...>;


		template<class T_Array_Type, size_t t_size = args_size<T_Array_Type>>
		struct S_deduction_guide
		{
			static constexpr size_t size = t_size;
			using type = T_Array_Type;
		};

		template<class T_Array_Type>
			requires requires
		{
			std::tuple_size_v<T_Array_Type>;
		}
		struct S_deduction_guide<T_Array_Type,-1>:
			S_deduction_guide<std::tuple_element_t<0, T_Array_Type>>
		{};

		template<class T_Array_Type>
		struct S_deduction_guide<T_Array_Type, -1>:
			S_deduction_guide<invalid_t,-1>
		{};

	public:

		static constexpr size_t size = S_deduction_guide<T_Base_Type>::size;

		using type = S_deduction_guide<T_Base_Type>::type;
	};

}