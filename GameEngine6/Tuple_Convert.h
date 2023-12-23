#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{


	//d—l
	//[std::tuple_size],[std::tuple_element]‚ª“Áê‰»‚³‚ê‚Ä‚¢‚éê‡A
	//	[T_Convert_Type]‚©‚ç[tuple_t]‚ğ¶¬‚·‚é
	template<class T_Convert_Type>
	struct I_Convert
	{

		template<class T_Convert_Tuple_Number>
		struct S_Convert
		{
			using type = I_Extract<T_Convert_Type, T_Convert_Tuple_Number>::type;
		};


		template<bool t_Convert_Fg = std::tuple_size_v<T_Convert_Type>>
		struct S_Convert_Chack
		{
			using type = S_Convert<tuple_v<>>::type;
		};

		template<>
		struct S_Convert_Chack<true>
		{
			using elements_number = I_index_sequence<std::tuple_size_v<T_Convert_Type>>::type;

			using type = S_Convert<elements_number>::type;
		};

		using type = S_Convert_Chack<>::type;

	};

	//template<class T_Convert_Type, size_t ...t_element_number>
	//constexpr auto Convert(T_Convert_Type&& convert_type,tuple_v<t_element_number...> element_number)
	//{
	//	return tuple_t(std::get<t_element_number>(std::forward<T_Convert_Type>(convert_type))...);
	//}
	//
	//template<class T_Convert_Type>
	//constexpr auto Convert(T_Convert_Type&& convert_type)
	//{
	//	return Convert(std::forward<T_Convert_Type>(convert_type),
	//		I_index_sequence<N_Tuple::S_Parameter<T_Convert_Type>::size>::type());
	//}

}