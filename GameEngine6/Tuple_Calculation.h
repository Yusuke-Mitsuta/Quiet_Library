#pragma once

#include"Tuple_Declare.h"
#include"Tuple_Get.h"
#include"If_Type.h"

namespace N_Tuple
{


	template<class T_Left,class T_Right>
	struct I_Calculation
	{
		template<class T>
		struct S_Size_Chack
		{
			static constexpr size_t value = 0;
		};

		template<class T>
			requires requires
		{
			std::tuple_size<T>::value;
		}
		struct S_Size_Chack<T>
		{
			static constexpr size_t value = std::tuple_size<T>::value;
		};

		static constexpr size_t l_size = S_Size_Chack<T_Left>::value;

		static constexpr size_t r_size= S_Size_Chack<T_Right>::value;

		using return_type = U_if_t1<T_Left, T_Right, (l_size >= r_size)>;
		
		static constexpr size_t min = std::min(l_size, r_size);
		static constexpr size_t max = std::max(l_size, r_size);
		
		template<class T_Calculation_Element_Number = U_index_sequence<min>,
			class T_Copy_Element_Number =U_Calculate_plus< U_index_sequence<max - min>,min>>
		struct S_Calculation {};

		template<size_t... t_Calculation_Element_Number, size_t... t_Copy_Element_Number>
		struct S_Calculation<tuple_v<t_Calculation_Element_Number...>, tuple_v<t_Copy_Element_Number...>>
		{

			template<class T_Left, class T_Right>
			static constexpr auto Plus( T_Left* l,T_Right* r)
			{
				return T_Left{ std::get<t_Calculation_Element_Number>(l) +std::get<t_Calculation_Element_Number>(r)..., std::get<t_Copy_Element_Number>(l)...};
			}
			
			template<class T_Left, class T_Right>
				requires requires(T_Left* l, T_Right* r)
			{
				{std::get<sizeof...(t_Calculation_Element_Number) - 1>(l)};
				{std::get<sizeof...(t_Calculation_Element_Number) - 1>(r)};
				requires std::tuple_size_v<T_Left> >= std::tuple_size_v<T_Right>;
			}
			static constexpr auto Plus(T_Left* l, T_Right* r)
			{
				return T_Left{ std::get<t_Calculation_Element_Number>(l) + std::get<t_Calculation_Element_Number>(r)...,std::get<t_Copy_Element_Number>(l)... };
			}

			template<class T_Left, class T_Right>
				requires requires(T_Left l, T_Right r)
			{
				{std::get<sizeof...(t_Calculation_Element_Number) - 1>(l)};
				{std::get<sizeof...(t_Calculation_Element_Number) - 1>(r)};
				requires std::tuple_size_v<T_Left> < std::tuple_size_v<T_Right>;
			}
			static constexpr auto Plus(T_Left* l, T_Right* r)
			{
				return T_Right{ std::get<t_Calculation_Element_Number>(l) + std::get<t_Calculation_Element_Number>(r)...,std::get<t_Copy_Element_Number>(r)... };
			}

			template<class T_Left, class T_Right>
				requires requires(T_Left l, T_Right r)
			{
				{std::get<sizeof...(t_Calculation_Element_Number) - 1>(r)};
			} && !(requires(T_Left l, T_Right r)
			{
				{std::get<sizeof...(t_Calculation_Element_Number) - 1>(l)};
			})
			static constexpr auto Plus(T_Left* l, T_Right* r)
			{
				return T_Left{ std::get<t_Calculation_Element_Number>(l) + r ...,std::get<t_Copy_Element_Number>(l)... };
			}

			template<class T_Left, class T_Right>
				requires requires(T_Left l, T_Right r)
			{
				{std::get<sizeof...(t_Calculation_Element_Number) - 1>(l)};
			} && !(requires(T_Left l, T_Right r)
			{
				{std::get<sizeof...(t_Calculation_Element_Number) - 1>(r)};
			})
			static constexpr auto Plus(T_Left* l, T_Right* r)
			{
				return T_Right{ l + std::get<t_Calculation_Element_Number>(r)...,std::get<t_Copy_Element_Number>(r)... };
			}

		};

		using type = S_Calculation<>;
		
	};

}

template<class T_Left, class T_Right>
	requires requires(T_Left& l, T_Right& r)
{
	{N_Tuple::I_Calculation<T_Left, T_Right>::type::Plus(&l, &r)};
}
static constexpr auto operator+(T_Left& l, T_Right& r)
{
	return N_Tuple::I_Calculation<T_Left, T_Right>::type::Plus(&l, &r);
}

