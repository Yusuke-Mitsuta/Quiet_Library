#pragma once
#include"Function_Address.h"
#include<tuple>
#include<optional>
#include<utility>

namespace N_Function
{

	template<class T_Fn_Args>
	struct IS_BindArgs
	{
	//private:

		
		template<size_t _Index>
		using tuple_element_type = std::tuple_element<_Index % std::tuple_size<T_Fn_Args>::value, T_Fn_Args>::type;

		template<int t_MethodNumber,class ...T_BoundFn>
		struct S_BoundArgs
		{

			template<class T_Args, int t_NextMethodNumber, class ...T_NewSetArgs>
			struct S_BindArgs
			{


				static constexpr int a = t_MethodNumber;
				static constexpr int b = t_NextMethodNumber;
				static constexpr int c = std::tuple_size<T_Fn_Args>::value - 1;

				using Type = S_BindArgs<tuple_element_type<t_NextMethodNumber + 1>, t_NextMethodNumber + 1, T_NewSetArgs..., T_Args>::Type;

				using Bind = S_BoundArgs::End;

				using End = S_BoundArgs::End;
			};

			template< class ...T_NewSetArgs>
			struct S_BindArgs<tuple_element_type<0>, std::tuple_size<T_Fn_Args>::value, T_NewSetArgs...>
			{
				static constexpr int a = t_MethodNumber;
				static constexpr int c = std::tuple_size<T_Fn_Args>::value - 1;
				using Type = S_BindArgs<tuple_element_type<t_MethodNumber>, -1, T_NewSetArgs...>::End;
			};

			template<class C_Name, class R_Type, class ...T_Args,int t_NextMethodNumber, class ...T_NewSetArgs>
				requires not_same_as<tuple_element_type<t_MethodNumber>,R_Type(C_Name::*)(T_Args...)> ||
			tuple_back_part_convertible_to<std::tuple<T_NewSetArgs...>, std::tuple<T_Args...>>
			struct S_BindArgs<R_Type(C_Name::*)(T_Args...), t_NextMethodNumber,T_NewSetArgs...>
			{

				static constexpr int a = t_MethodNumber;
				static constexpr int b = t_NextMethodNumber;
				static constexpr int c = std::tuple_size<T_Fn_Args>::value - 1;
				using BoundArgs = S_BoundArgs<t_NextMethodNumber, T_BoundFn..., S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_NewSetArgs...>>>;

				using Type = S_BindArgs<tuple_element_type<t_MethodNumber>, t_NextMethodNumber, T_NewSetArgs...>::Bind;

				using Bind = BoundArgs::Type;

				using End = BoundArgs::End;
			};


			template<class C_Name, class R_Type, class ...T_Args, class ...T_DefaultSetArgs, int t_NextMethodNumber, class ...T_NewSetArgs>
				requires not_same_as<tuple_element_type<t_MethodNumber>, S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_DefaultSetArgs...>>> ||
			tuple_back_part_convertible_to<std::tuple<T_NewSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>
			struct S_BindArgs<S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_DefaultSetArgs...>>, t_NextMethodNumber,T_NewSetArgs...>
			{
				using BoundArgs = S_BoundArgs<t_NextMethodNumber, T_BoundFn..., S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_NewSetArgs..., T_DefaultSetArgs...>>>;

				using Type = S_BindArgs<tuple_element_type<t_MethodNumber>, t_NextMethodNumber, T_NewSetArgs...>::Bind;

				using Bind = BoundArgs::Type;

				using End = BoundArgs::End;
			};


			using Type = S_BindArgs<tuple_element_type<t_MethodNumber + 1>, t_MethodNumber + 1>::Type;

			using End = S_BoundArgs;

			using TupleType = std::tuple<T_BoundFn...>;

			using Judge = std::bool_constant<!(t_MethodNumber - std::tuple_size<T_Fn_Args>::value)>;
		};

		using Type = S_BoundArgs<0>::Type;

		//using TupleType =Type::TupleType;

		//using Judge = Type::Judge;

	};



}

//template<size_t _Index>
//using tuple_element_type = std::tuple_element<_Index% std::tuple_size<T_Fn_Args>::value, T_Fn_Args>::type;
//
//template<int t_MethodNumber, class ...T_BoundFn>
//struct S_BoundArgs
//{
//
//	template<class T_Args, int t_NextMethodNumber, class ...T_NewSetArgs>
//	struct S_BindArgs
//	{
//
//
//		static constexpr int a = t_MethodNumber;
//		static constexpr int b = t_NextMethodNumber;
//		static constexpr int c = std::tuple_size<T_Fn_Args>::value - 1;
//
//		using Type2 = S_BindArgs<tuple_element_type<t_NextMethodNumber + 1>, t_NextMethodNumber + 1, T_NewSetArgs..., T_Args>;
//
//		using Bind2e = S_BoundArgs;
//
//		using End2e = S_BoundArgs;
//	};
//
//	template< class ...T_NewSetArgs>
//	struct S_BindArgs<tuple_element_type<0>, std::tuple_size<T_Fn_Args>::value, T_NewSetArgs...>
//	{
//		static constexpr int a = t_MethodNumber;
//		static constexpr int b = t_NextMethodNumber;
//		static constexpr int c = std::tuple_size<T_Fn_Args>::value - 1;
//		using Type5e = S_BindArgs<tuple_element_type<t_MethodNumber>, -1, T_NewSetArgs...>;
//	};
//
//	template<class C_Name, class R_Type, class ...T_Args, int t_NextMethodNumber, class ...T_NewSetArgs>
//		requires not_same_as<tuple_element_type<t_MethodNumber>, R_Type(C_Name::*)(T_Args...)> ||
//	tuple_back_part_convertible_to<std::tuple<T_NewSetArgs...>, std::tuple<T_Args...>>
//		struct S_BindArgs<R_Type(C_Name::*)(T_Args...), t_NextMethodNumber, T_NewSetArgs...>
//	{
//
//		static constexpr int a = t_MethodNumber;
//		static constexpr int b = t_NextMethodNumber;
//		static constexpr int c = std::tuple_size<T_Fn_Args>::value - 1;
//		using BoundArgs = S_BoundArgs<t_NextMethodNumber, T_BoundFn..., S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_NewSetArgs...>>>;
//
//		using Type3b = S_BindArgs<tuple_element_type<t_MethodNumber>, t_NextMethodNumber, T_NewSetArgs...>;
//
//		using Bind3t = BoundArgs;
//
//		using End3e = BoundArgs;
//	};
//
//
//	template<class C_Name, class R_Type, class ...T_Args, class ...T_DefaultSetArgs, int t_NextMethodNumber, class ...T_NewSetArgs>
//		requires not_same_as<tuple_element_type<t_MethodNumber>, S_Address<R_Type(C_Name::*)(T_Args...)>> ||
//	tuple_back_part_convertible_to<std::tuple<T_NewSetArgs..., T_DefaultSetArgs...>, std::tuple<T_Args...>>
//		struct S_BindArgs<S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_DefaultSetArgs...>>, t_NextMethodNumber, T_NewSetArgs...>
//	{
//		using BoundArgs = S_BoundArgs<t_NextMethodNumber, T_BoundFn..., S_Address<R_Type(C_Name::*)(T_Args...), std::tuple<T_NewSetArgs..., T_DefaultSetArgs...>>>;
//
//		using Type4b = S_BindArgs<tuple_element_type<t_MethodNumber>, t_NextMethodNumber, T_NewSetArgs...>;
//
//		using Bind4t = BoundArgs;
//
//		using End4e = BoundArgs;
//	};
