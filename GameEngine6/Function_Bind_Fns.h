#pragma once
//#include"Function_BindFn.h"
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"Function.h"
#include<tuple>
#include<optional>

namespace N_Function
{
	//�d�l
	//�֐��|�C���^�[�ɑ΂��āA�����̒l�����������A�����v�Ŕ��肷��
	//
	//�e���v���[�g
	//T_Fn_Args::�֐��|�C���^�[�A�w�肷������A��Tuple
	//
	//�⑫
	//T_Fn_Args�͊֐��|�C���^�[�A����Ɏw�肷������A���̊֐��|�C���^�[�A�ƂȂ�悤�ɂ��鎖
	template<class ...T_Fn_Args>
	struct IS_BindFns
	{
		using T_Tuple = IS_TupleUnzip<T_Fn_Args...>::Type;

		static constexpr int tuple_size = std::tuple_size<T_Tuple>::value;

		template<int _Index>
		using tuple_element = std::tuple_element<
			tuple_size - _Index, T_Tuple>::type;

		//�d�l
		//�����̃o�C���h�ς݊֐��|�C���^�[���i�[���A�Ō�̊֐��Ȃ�i�[�������I������
		//
		//�e���v���[�g
		//t_TupleNumber::���݁A���������^�v���̗v�f��
		//...T_BoundFns::�����̃o�C���h�ς݊֐��|�C���^�[
		//�⑫
		//t_TupleNumber�͌�납�牽�ԖڂɃA�N�Z�X���邩������
		template<int t_TupleNumber=1, class ...T_BoundFns>
		struct S_BoundFns
		{
			//�d�l
			//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
			template<class T_Args, int t_TupleNumber=0, int ...t_ArgsNumber>
			struct S_BindFns
			{
				using Type = S_BindFns<tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1, t_TupleNumber, t_ArgsNumber...>::Type;
			};

			//�d�l
			//Function�ɑ΂��Ĉ������Z�b�g����
			template<class T_CName, class T_RType, class ...T_Args, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<T_RType(T_CName::*)(T_Args...), t_TupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge = tuple_back_part_convertible_to<std::tuple<tuple_element<t_ArgsNumber>...>, std::tuple<T_Args...>>;

				using Type =
					S_BoundFns<(t_TupleNumber + 1)* judge,
					Function<std::tuple<T_RType(T_CName::*)(T_Args...), tuple_element<t_ArgsNumber>...>>,
					T_BoundFns...>::Type;
			};

			//�d�l
			//Function�ɑ΂��Ĉ������Z�b�g����
			template<class T_CName, class T_RType, class ...T_Args, class ...T_DefaultSetArgs, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<Function<std::tuple<T_RType(T_CName::*)(T_Args...), T_DefaultSetArgs...>>, t_TupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge = tuple_back_part_convertible_to<std::tuple<tuple_element<t_ArgsNumber>..., T_DefaultSetArgs...>,std::tuple<T_Args...>>;

				using Type = S_BoundFns<(t_TupleNumber + 1)* judge,
					Function<std::tuple<T_RType(T_CName::*)(T_Args...), tuple_element<t_ArgsNumber>..., T_DefaultSetArgs...>>,
					T_BoundFns...>::Type;
			};

			using Type = S_BindFns<tuple_element<t_TupleNumber>, t_TupleNumber>::Type;
		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������������Ȍ^�������ꍇ
		template<class T_FlontBoundFn,class ...T_BoundFns>
		struct S_BoundFns<0,T_FlontBoundFn,T_BoundFns...>
		{
			using Type = S_BoundFns;
			using Judge = std::false_type;
			using FnsType = std::nullopt_t;
		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������̑S�Ă����������ꍇ
		template<class ...T_BoundFns>
		struct S_BoundFns<tuple_size+1,T_BoundFns...>
		{
			using Type = S_BoundFns;
			using Judge = std::true_type;
			using FnsType = std::tuple<T_BoundFns...>;
		};

		using Type = S_BoundFns<1>::Type;
		using Judge = Type::Judge;
		using FnsType = Type::FnsType;

		//FnsType fns;

		//IS_BindFns(T_Fn_Args... fn_Args){}

	};
}