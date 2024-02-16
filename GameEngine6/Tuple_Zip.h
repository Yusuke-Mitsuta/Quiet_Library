#pragma once

#include"Tuple_Class_Declare.h"

namespace N_Tuple
{

	//仕様
	//圧縮されているTupleを示す
	template<class _Ty1,size_t N>
	struct tuple_zip
	{
		using tuple = I_Repeat_Multiple<_Ty1, N>::type;
	};

	//仕様
	//パラメータパック[Ts...]から連続する型を{tuple_zip< T, N >}に圧縮する
	template<class ...Ts>
	struct I_Zip
	{
	private:
		template<size_t N>
		using element = I_Element<N, tuple_t<Ts...>>::type;

		template<size_t t_select_point, class T_Base = element<t_select_point>,
			bool t_zip_fg = same_as<T_Base, element<t_select_point>> >
		struct S_Zipper
		{
			static constexpr size_t value = 0;
		};

		template<size_t t_select_point,class T_Base>
		struct S_Zipper<t_select_point,T_Base,true>
		{
			static constexpr size_t value = S_Zipper<t_select_point + 1,T_Base>::value + 1;
		};


		template<class T_Result = tuple_t<>, size_t t_select_point = 0,
			size_t t_zip_size = S_Zipper<t_select_point + 1, element<t_select_point>>::value + 1,
			bool t_loop_fg = (t_select_point + t_zip_size) < sizeof...(Ts) > 
		struct S_Zip 
		{
			using type = T_Result;
		};

		template<class ...T_Result, size_t t_select_point, size_t t_zip_size>
		struct S_Zip<tuple_t<T_Result...>, t_select_point, t_zip_size,false>
		{
			using type = tuple_t<T_Result..., tuple_zip<element<t_select_point>, t_zip_size>>;
		};

		template<class ...T_Result, size_t t_select_point, size_t t_zip_size>
		struct S_Zip<tuple_t<T_Result...>, t_select_point, t_zip_size,true>
		{
			using type = S_Zip<tuple_t<T_Result..., tuple_zip<element<t_select_point>, t_zip_size>>, t_select_point + t_zip_size>::type;
		};

		template<class ...T_Result, size_t t_select_point>
		struct S_Zip<tuple_t<T_Result...>, t_select_point, 1, false>
		{
			using type = tuple_t<T_Result..., element<t_select_point>>;
		};

		template<class ...T_Result, size_t t_select_point>
		struct S_Zip<tuple_t<T_Result...>, t_select_point, 1,true>
		{
			using type = S_Zip<tuple_t<T_Result..., element<t_select_point>>, t_select_point + 1>::type;
		};
	public:
		using type = S_Zip<>::type;

	};


	//仕様
	//タプル内の要素から連続する型を{tuple_zip< T, N >}に圧縮する
	template<class T_Tuple>
	struct I_Zip_Tuple
	{
	private:
		template<class T_Tuple>
		struct S_Zip_Action
		{
			using type = I_Move_Template<I_Zip, T_Tuple>::type::type;
		};
	public:
		using type = S_Tuple_t_Change_Action<S_Zip_Action, T_Tuple>::Return_not_p;
	};

}