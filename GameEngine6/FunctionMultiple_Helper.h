#pragma once
//#include"Function_BindFn.h"
#include"tuple_convertible_to.h"
#include"Tuple_Unzip.h"
#include"Function.h"
#include"tuple_Helper.h"
#include<tuple>
#include<optional>

namespace N_Function
{
	template<int t_Fn,int ...t_Args>
	struct S_MethodExecution
	{
		template<class ...T_TupleType>
		static constexpr auto Execution(std::tuple<T_TupleType...>& fnsData,auto&... args)
		{
			return std::get<t_Fn>(fnsData)(args..., std::get<t_Args>(fnsData)...);
		}
	};

	//�d�l
	//�֐��|�C���^�[�ɑ΂��āA�����̒l�����������A�����v�Ŕ��肷��
	//
	//�e���v���[�g
	//T_Fn_Args::�֐��|�C���^�[�A�w�肷������A��Tuple
	//
	//�⑫
	//T_Fn_Args�͊֐��|�C���^�[�A����Ɏw�肷������A���̊֐��|�C���^�[�A�ƂȂ�悤�ɂ��鎖
	template<class T_FlontArgs,class T_Data,class ...T_Fn_Args>
	struct IS_FunctionMultiple_Helper
	{
		using T_Tuple = std::tuple <T_Data, T_Fn_Args... >;

		static constexpr int tuple_size = std::tuple_size<T_Tuple>::value;

		template<int _Index>
		using reverse_tuple_element = std::tuple_element<
			tuple_size - _Index, T_Tuple>::type;

		template<int _Index>
		using tuple_element = std::tuple_element_t<
			_Index %tuple_size, T_Tuple>;

		enum class E_Mode
		{
			MethodSearch = 0,
			SetJudge = 2,
		};


		//�d�l
		//���̃��[�h������A[t_Mode]�Ő؂�ւ�����
		//[t_Mode = E_Mode::SetJudge]::�֐��ɑ΂��āA�u���ɑ��������̌^�A�֐��Ƀo�C���h�ς݂̈����̌^�v���֐��ɑ΂�������̌^�̌�������ƌ݊��������邩���肷��
		//[t_Mode = E_Mode::MethodSearch]::�֐��̌^�ɑ΂��āA�u[T_FlontArgs]�A���ɑ��������̌^�A�֐��Ƀo�C���h�ς݂̈����̌^�v�Ŋ֐��ɑ΂�������̌^���݊��������邩���肷��
		//
		//�e���v���[�g
		//t_Mode:�F����̕��@
		//t_FunctionNumber::���݁A������T�����̊֐��̔ԍ�
		//...t_Datas::[ E_Mode::MethodSearch]���Ɉ����̌^�̔ԍ����擾����̂Ɏg�p����
		template<E_Mode t_Mode,bool t_LoopFg=true,int t_FunctionNumber=0,int ...t_Datas>
		struct S_CorrectType
		{

			using Fn = Function<tuple_element<t_FunctionNumber>>;

			//�d�l
			//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
			template<class T_Args, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_Judge
			{
				using NextClass = S_Judge<tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1,t_ArgsNumber..., t_TupleNumber>;

				using Type = NextClass::Type;

				using NextMethod = NextClass::NextMethod;
			};

			//�d�l
			//Function�ɑ΂��Ĉ����𔻒肷��
			template<class T_CName, class T_RType, class ...T_Args, int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_Judge<T_RType(T_CName::*)(T_Args...), t_MethodTupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge =
					same_as<typename IS_tuple_convertible_to<typename IS_TupleUnzip<T_FlontArgs,tuple_element<t_ArgsNumber>...>::Type,
					typename Fn::Args, static_cast<int>(t_Mode)>::Select,std::bool_constant<static_cast<int>(t_Mode)>>;
					
				using NextClass = S_CorrectType<t_Mode,judge,t_MethodTupleNumber>;

				using NextMethod = S_Judge;

				using Type =NextClass::Type;

			};

			//�d�l
			//Function�ɑ΂��Ĉ����𔻒肷��
			template<class ...T_FunctionInner,int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_Judge<Function<T_FunctionInner...>, t_MethodTupleNumber, t_ArgsNumber...>
			{

				//�d�l
				//�������֐��ɑ΂��āA�����������肷��
				static constexpr bool judge = 
					std::same_as<typename IS_tuple_convertible_to<typename IS_TupleUnzip<T_FlontArgs,tuple_element<t_ArgsNumber>...,typename Fn::BoundArgs>::Type, 
					typename Fn::Args,static_cast<int>(t_Mode)>::Select, std::bool_constant<static_cast<int>(t_Mode)>>;

				using NextClass = S_CorrectType<t_Mode,judge,t_MethodTupleNumber>;
				using NextMethod = S_Judge;

				using Type = NextClass::Type;

			};
			using NextClass = S_Judge<tuple_element<t_FunctionNumber+1>, t_FunctionNumber+1>;

			using Type = NextClass::Type;

			//�d�l			
			//�p�����[�^�p�b�N���̊֐��̌^�܂ňړ�����
			using NextMethod = NextClass::NextMethod;

		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������������Ȍ^�������ꍇ
		template<int t_FunctionNumber,int ...t_Datas>
		struct S_CorrectType<E_Mode::SetJudge,0,t_FunctionNumber,t_Datas...>
		{
			using Type = std::nullopt_t;
		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������̑S�Ă����������ꍇ
		template<int ...t_Datas>
		struct S_CorrectType<E_Mode::SetJudge,1,tuple_size, t_Datas...>
		{
			using Type = T_Data;

		};


		//�d�l
		//Functions�ɑ΂���[T_FlontArgs]�ŌĂяo����֐������݂���ꍇ
		template<int t_FunctionNumber, int ...t_FnArgsNumber>
		struct S_CorrectType<E_Mode::MethodSearch, 0, t_FunctionNumber, t_FnArgsNumber...>
		{
			using Type = S_MethodExecution<t_FunctionNumber,t_FnArgsNumber...>;

		};

		//�d�l
		//Functions�ɑ΂���[T_FlontArgs]�ŌĂяo����֐������������ꍇ
		template<int ...t_FnArgsNumber>
		struct S_CorrectType<E_Mode::MethodSearch,1, tuple_size, t_FnArgsNumber...>
		{
			using Type = std::nullopt_t;

		};


		using SetJudge= S_CorrectType<E_Mode::SetJudge>::Type;

		using MethodSearch= S_CorrectType<E_Mode::MethodSearch>::Type;


	};

}