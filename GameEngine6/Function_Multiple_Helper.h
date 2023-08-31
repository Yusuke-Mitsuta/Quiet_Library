#pragma once
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"Parameter.h"
#include"SwapType.h"

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
	//TP_Fns::�֐��|�C���^�[�A�w�肷������A��Tuple
	//
	//�⑫
	//T_Fn_Args�͊֐��|�C���^�[�A����Ɏw�肷������A���̊֐��|�C���^�[�A�ƂȂ�悤�ɂ��鎖
	// //SetJudge::�֐��ɑ΂��āA�u���ɑ��������̌^�A�֐��Ƀo�C���h�ς݂̈����̌^�v���֐��ɑ΂�������̌^�̌�������ƌ݊��������邩���肷��
	//Fns::�֐��|�C���^�[or[Function_Single]�ƁA���ɑ��������̌^��[Function_Single]�Ƃ��Ă܂Ƃ߁A���̓����[TP_Fns...]���Ȃ��Ȃ�܂ŌJ��Ԃ�
	template<class T_FlontFn,class ...TP_Fns>
	struct IS_Function_Multiple_Helper
	{
	private:
		
		using Parameter = S_Parameter<T_FlontFn, TP_Fns...>;
		
		template<int _Index>
		using Element_t =U_Element_t< (_Index-1 ) % Parameter::Size, Parameter>;

		//�d�l
		//�֐��ɑ΂��āA�u���ɑ��������̌^�A�֐��Ƀo�C���h�ς݂̈����̌^�v���֐��ɑ΂�������̌^�̌�������ƌ݊��������邩���肵�A�݊����������[Function_Single]�ɂ܂Ƃ߂�
		//
		//�e���v���[�g
		//t_FunctionNumber::�����𐸍�����֐��|�C���^�[or[Function_Single]�̔ԍ�+�P
		//...TP_BoundFns::[Function_Single]�ł܂Ƃ߂��^
		template<int t_FunctionNumber=1,class ...TP_BoundFns>
		struct S_CorrectType
		{

			using MethodData = N_Function::S_MethodData<Element_t<t_FunctionNumber>>;

			//�d�l
			//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
			template<class T, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_Judge
			{	
				//�d�l
				//�������֐��ɑ΂��āA�����������肷��
				static constexpr bool judge =
					tuple_back_part_convertible_to<typename IS_TupleUnzip<Element_t<t_ArgsNumber>..., typename MethodData::BoundArgs>::Type, typename MethodData::Args>;

				//�d�l
				//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
				using Args_Search = S_Judge<Element_t<t_TupleNumber + 1>, t_TupleNumber + 1, t_ArgsNumber..., t_TupleNumber>;

				//�d�l
				//Function�ɑ΂��Ĉ����𔻒肷��
				using Hit_Method=S_CorrectType<t_TupleNumber* judge,TP_BoundFns...,
					Function_Single<Element_t<t_FunctionNumber>, Element_t<t_ArgsNumber>...>>;


				//�d�l
				//���̃N���X���w�肷��
				//�����ł���΃Z�b�g���A���̌^�̔���Ɉڂ�A�֐��ł���Έ����𐸍����A���b�s���O����
				using Swap = U_Swap_t1<Args_Search, Hit_Method, not_same_as<typename S_MethodData<T>::Method, std::nullopt_t>>;

				using Type = Swap::Type;


			};

			//�d�l
			//Function�ɑ΂��ăZ�b�g���������̑S�Ă����������ꍇ�͂��̌��ʂ��A���s�����[std::nullopt_t]���Ԃ�
			struct S_Result
			{
				using Type = S_Result;

				using Judge = U_Judge_t<T_FlontFn, t_FunctionNumber>;

				using Fns = U_Judge_t<S_Parameter<TP_BoundFns...>, t_FunctionNumber>;

			};

			using NextMethod= S_Judge<Element_t<t_FunctionNumber + 1>, t_FunctionNumber + 1>;

			using Swap = U_Swap_t1<S_Result, NextMethod, t_FunctionNumber % (Parameter::Size + 1)>;

			using Type = Swap::Type;

		};

	public:
		using Judge= S_CorrectType<>::Type::Judge;

		using Fns= S_CorrectType<>::Type::Fns;

	};

}