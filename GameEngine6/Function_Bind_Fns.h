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
		using reverse_tuple_element = std::tuple_element<
			tuple_size - _Index, T_Tuple>::type;

		//�d�l
		//�����̃o�C���h�ς݊֐��|�C���^�[���i�[���A�Ō�̊֐��Ȃ�i�[�������I������
		//
		//�e���v���[�g
		//t_MethodTupleNumber::���݁A���������^�v���̗v�f��
		//...T_BoundFns::�����̃o�C���h�ς݊֐��|�C���^�[
		//�⑫
		//t_TupleNumber�͌�납�牽�ԖڂɃA�N�Z�X���邩������
		template<int t_TupleNumber=1, class ...T_BoundFns>
		struct S_BoundFns
		{
			//�d�l
			//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
			template<class T_Args, int t_TupleNumber = 0, int ...t_ArgsNumber>
			struct S_BindFns
			{
				using Type = S_BindFns<reverse_tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1, t_TupleNumber, t_ArgsNumber...>::Type;

				void BindFns(auto& inputTuple, T_Tuple& outputTuple)
				{
					
				}
			};

			//�d�l
			//Function�ɑ΂��Ĉ������Z�b�g����
			template<class T_CName, class T_RType, class ...T_Args, int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<T_RType(T_CName::*)(T_Args...), t_MethodTupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge = tuple_back_part_convertible_to<std::tuple<reverse_tuple_element<t_ArgsNumber>...>, std::tuple<T_Args...>>;

				using Type = 
					S_BoundFns<(t_MethodTupleNumber + 1) * judge,
					Function<std::tuple<T_RType(T_CName::*)(T_Args...), reverse_tuple_element<t_ArgsNumber>...>>,
					T_BoundFns...>::Type;

				template<size_t ...N>
				static constexpr void BindFns(auto& inputTuple, T_Tuple& outputTuple,std::index_sequence<N...>)
				{
					//std::get<std::tuple_size<decltype(inputTuple)>::value - 1 - sizeof...(T_BoundFns)>(inputTuple) =
					//	Function(std::tuple(std::get<tuple_size - t_TupleNumber - N>(outputTuple)...));
				}

				static constexpr void BindFns(auto& inputTuple,auto& outputTuple)
				{
					//S_BindFns::BindFns(inputTuple, outputTuple, std::make_index_sequence<t_MethodTupleNumber - t_TupleNumber>//());
				}
			};

			//�d�l
			//Function�ɑ΂��Ĉ������Z�b�g����
			template<class T_FunctionInner,int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<Function<T_FunctionInner>, t_MethodTupleNumber, t_ArgsNumber...>
			{
				using Fn = Function<T_FunctionInner>;

				//����
				//Default�̈����Ɛݒ肵�������𕪂���
				static constexpr bool judge = tuple_back_part_convertible_to<typename 
					IS_TupleUnzip<std::tuple<reverse_tuple_element<t_ArgsNumber>..., 
					typename Fn::SetArgs>>::Type,typename Fn::Args>;

				using Type = S_BoundFns<(t_MethodTupleNumber + 1)* judge,
					Function<Fn,std::tuple<reverse_tuple_element<t_ArgsNumber>...>>,
					T_BoundFns...>::Type;

				template<size_t ...N>
				static constexpr void BindFns(auto& inputTuple, T_Tuple& outputTuple, std::index_sequence<N...>)
				{
					//std::get<std::tuple_size<decltype(inputTuple)>::value - 1 - sizeof...(T_BoundFns)>(inputTuple) =
					//	Function(std::tuple(std::get<tuple_size - t_TupleNumber - N>(outputTuple)...));
				}

				static constexpr void BindFns(auto& inputTuple, T_Tuple& outputTuple)
				{
					//S_BindFns::BindFns(inputTuple, outputTuple, std::make_index_sequence<t_MethodTupleNumber - t_TupleNumber>());
				}

			};

			using Type = S_BindFns<reverse_tuple_element<t_TupleNumber>, t_TupleNumber>::Type;
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

		FnsType fns;

		constexpr IS_BindFns(T_Fn_Args... fn_Args)
		{
			IS_TupleUnzip unzipTuple(fn_Args...);
			S_BoundFns<1>::BindFns(fns, unzipTuple.tuple);
		}

		operator FnsType()
		{
			return fns;
		}

	};
}