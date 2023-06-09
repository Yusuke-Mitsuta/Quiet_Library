#pragma once

#include<iostream>
#include<concepts>
#include<optional>


//template <class...Args>
//struct arg_type_impl
//{
//	template<unsigned int N>
//	using Type = typename std::tuple_element<N, std::tuple<Args...>>::type;
//};
//
//// 可変個引数テンプレート
//template < class... Args>
//struct arg_type
//{
//	using Args = typename arg_type_impl<Args...,std::nullopt_t>;
//};
//
//// 関数
//template < typename R, typename ... Args>
//struct arg_type< R(*)(Args...)>
//{
//	using Args = typename arg_type_impl<Args..., std::nullopt_t>;
//};
//
//// メンバー関数
//template <typename C, typename R, typename ... Args>
//struct arg_type< R(C::*)(Args...)>
//{
//	using Args = typename arg_type_impl<Args..., std::nullopt_t>;
//};
//
//// メンバー関数（const）
//template <typename C, typename R, typename ... Args>
//struct arg_type<R(C::*)(Args...) const>
//{
//	using Args = typename arg_type_impl<Args..., std::nullopt_t>;
//};
//
//template<unsigned int N,class Args_1, class Args_2, class Args_1_First=Args_1::Type<N>,class Args_2_First = Args_2::Type<N>>
//class Type_Judge
//{
//public:
//	using Judge = Type_Judge<N + 1,Args_1,Args_2>::Judge;
//};
//
//template<unsigned int N, class Args_1, class Args_2, class Args_2_First>
//class Type_Judge<N,Args_1,Args_2,std::nullopt_t,Args_2_First>
//{
//public:
//	using Judge = Type_Judge<N + 1, Args_1, Args_2>::Judge;
//};
//
//template<unsigned int N, class Args_1, class Args_2>
//class Type_Judge<N, Args_1,Args_2, std::nullopt_t,std::nullopt_t>
//{
//public:
//	using Judge = Type_Judge<N + 1, Args_1, Args_2>::Judge;
//};