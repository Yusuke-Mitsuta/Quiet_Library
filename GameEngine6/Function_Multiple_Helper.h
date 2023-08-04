#pragma once
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"

#define FUNCTION_MULTIPLE(Variable,...)\
S_MoveTupleInnerType<FunctionMultiple,decltype(std::tuple(__VA_ARGS__))>::Type Variable = { __VA_ARGS__ };\

namespace N_Function
{

	template<class T_Method, class ...T_Args>
	struct S_MethodData;

	template<not_same_as<std::nullopt_t> T_Method, class ...TP_Args>
	class Function_Single;


	//�d�l
	//�֐��|�C���^�[�ɑ΂��āA�����̒l�����������A�����v�Ŕ��肷��
	//
	//�e���v���[�g
	//T_Fn_Args::�֐��|�C���^�[�A�w�肷������A��Tuple
	//
	//�⑫
	//T_Fn_Args�͊֐��|�C���^�[�A����Ɏw�肷������A���̊֐��|�C���^�[�A�ƂȂ�悤�ɂ��鎖
	// //SetJudge::�֐��ɑ΂��āA�u���ɑ��������̌^�A�֐��Ƀo�C���h�ς݂̈����̌^�v���֐��ɑ΂�������̌^�̌�������ƌ݊��������邩���肷��
	//Fns::�֐��|�C���^�[or[Function_Single]�ƁA���ɑ��������̌^��[Function_Single]�Ƃ��Ă܂Ƃ߁A���̓����[T_Fn_Args...]���Ȃ��Ȃ�܂ŌJ��Ԃ�
	template<class T_FlontFn,class ...T_Fn_Args>
	struct IS_Function_Multiple_Helper
	{
	private:
		using T_Tuple = std::tuple<T_FlontFn, T_Fn_Args... >;

		static constexpr int tuple_size = std::tuple_size<T_Tuple>::value;

		template<int _Index>
		using tuple_element = std::tuple_element_t<
			(_Index-1) %tuple_size, T_Tuple>;

		//�d�l
		//�֐��ɑ΂��āA�u���ɑ��������̌^�A�֐��Ƀo�C���h�ς݂̈����̌^�v���֐��ɑ΂�������̌^�̌�������ƌ݊��������邩���肵�A�݊����������[Function_Single]�ɂ܂Ƃ߂�
		//
		//�e���v���[�g
		//t_FunctionNumber::�����𐸍�����֐��|�C���^�[or[Function_Single]�̔ԍ�+�P
		//...T_BoundFns::[Function_Single]�ł܂Ƃ߂��^
		template<int t_FunctionNumber=1,class ...T_BoundFns>
		struct S_CorrectType
		{

			using Method = N_Function::S_MethodData<tuple_element<t_FunctionNumber>>;

			//�d�l
			//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
			template<class TP_Args, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_Judge
			{
				using Type = S_Judge<tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1, t_ArgsNumber..., t_TupleNumber>::Type;
			};


			//�d�l
			//Function�ɑ΂��Ĉ����𔻒肷��
			template<class T_CName, class T_RType, class ...TP_Args, int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_Judge<T_RType(T_CName::*)(TP_Args...), t_MethodTupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge =
					tuple_back_part_convertible_to<typename IS_TupleUnzip<tuple_element<t_ArgsNumber>...>::Type, typename Method::Args>;

				using Type = S_CorrectType<t_MethodTupleNumber* judge,
					T_BoundFns...,
					Function_Single<tuple_element<t_FunctionNumber>, tuple_element<t_ArgsNumber>...>>::Type;

			};

			//�d�l
			//Function�ɑ΂��Ĉ����𔻒肷��
			template<class ...T_FunctionInner,int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_Judge<Function_Single<T_FunctionInner...>, t_MethodTupleNumber, t_ArgsNumber...>
			{

				//�d�l
				//�������֐��ɑ΂��āA�����������肷��
				static constexpr bool judge = 
					tuple_back_part_convertible_to<typename IS_TupleUnzip<tuple_element<t_ArgsNumber>..., typename Method::BoundArgs>::Type, typename Method::Args>;

				using Type = S_CorrectType<t_MethodTupleNumber* judge,
					T_BoundFns...,
					Function_Single<tuple_element<t_FunctionNumber>, tuple_element<t_ArgsNumber>...>>::Type;

			};
			using Type = S_Judge<tuple_element<t_FunctionNumber + 1>, t_FunctionNumber + 1>::Type;

		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������������Ȍ^�������ꍇ
		template<class ...T_BoundFns>
		struct S_CorrectType<0,T_BoundFns...>
		{
			using Type = S_CorrectType;
			using Judge = std::nullopt_t;
		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������̑S�Ă����������ꍇ
		template<class ...T_BoundFns>
		struct S_CorrectType<tuple_size+1, T_BoundFns...>
		{
			using Type = S_CorrectType;
			using Judge = T_FlontFn;
			using Fns = std::tuple<T_BoundFns...>;
		};
	public:
		using Judge= S_CorrectType<>::Type::Judge;

		using Fns= S_CorrectType<>::Type::Fns;

	};

}