#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	//�d�l
	//���k����Ă���Tuple������
	template<class _Ty1,size_t N>
	struct tuple_zip
	{
		using tuple = I_Repeat_Multiple<_Ty1, N>::type;
	};

	//�d�l
	//�p�����[�^�p�b�N[Ts...]����A������^��{tuple_zip< T, N >}�Ɉ��k����
	template<class ...Ts>
	struct I_Zip
	{
		template<size_t N>
		using element = I_Element<N, tuple_t<Ts...>>::type;

		template<size_t t_select_point, class T_Base = element<t_select_point>>
		struct S_Zipper
		{
			static constexpr size_t value = 0;
		};

		template<size_t t_select_point,class T_Base>
			requires requires
		{
			requires same_as<T_Base, element<t_select_point>>;
		}
		struct S_Zipper<t_select_point,T_Base>
		{
			static constexpr size_t value = S_Zipper<t_select_point + 1,T_Base>::value + 1;
		};


		template<class T_Result = tuple_t<>, size_t t_select_point = 0,
			size_t t_zip_size = S_Zipper<t_select_point+1, element<t_select_point>>::value+1>
		struct S_Zip 
		{
			using type = T_Result;
		};

		template<class ...T_Result, size_t t_select_point, size_t t_zip_size>
			requires requires
		{
			requires (t_select_point + t_zip_size) >= sizeof...(Ts);
		}
		struct S_Zip<tuple_t<T_Result...>, t_select_point, t_zip_size>
		{
			using type = tuple_t<T_Result..., tuple_zip<element<t_select_point>, t_zip_size>>;
		};

		template<class ...T_Result, size_t t_select_point, size_t t_zip_size>
			requires requires
		{
			requires (t_select_point + t_zip_size) < sizeof...(Ts);
		}
		struct S_Zip<tuple_t<T_Result...>, t_select_point, t_zip_size>
		{

			using type = S_Zip<tuple_t<T_Result..., tuple_zip<element<t_select_point>, t_zip_size>>, t_select_point + t_zip_size>::type;
		};


		template<class ...T_Result, size_t t_select_point>
			requires requires
		{
			requires t_select_point < sizeof...(Ts);
		}
		struct S_Zip<tuple_t<T_Result...>, t_select_point, 1>
		{
			using type = S_Zip<tuple_t<T_Result..., element<t_select_point>>, t_select_point + 1>::type;
		};

		template<class ...T_Result, size_t t_select_point>
			requires requires
		{
			requires t_select_point  >= sizeof...(Ts);
		}
		struct S_Zip<tuple_t<T_Result...>, t_select_point, 1>
		{
			using type = tuple_t<T_Result..., element<t_select_point>>;
		};

		using type = S_Zip<>::type;

	};

	//�d�l
	//�^�v�����̗v�f����A������^��{tuple_zip< T, N >}�Ɉ��k����
	template<class T_Tuple>
	struct I_Zip_Tuple
	{
		template<class T_Tuple>
		struct S_Zip_Action
		{
			using type = I_Move_Template<I_Zip, T_Tuple>::type::type;
		};

		using type = S_Tuple_t_Change_Action<S_Zip_Action, T_Tuple>::Return_not_p;
	};

}