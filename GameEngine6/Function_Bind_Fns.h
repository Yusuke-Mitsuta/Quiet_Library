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
			template<class T_Args, int t_TupleNumber, int ...t_ArgsNumber>
			struct S_BindFns
			{
				using NextClass = S_BindFns<reverse_tuple_element<t_TupleNumber + 1>, t_TupleNumber + 1, t_TupleNumber, t_ArgsNumber...>;

				using Type = NextClass::Type;

				using NextMethod = NextClass::NextMethod;
			};

			//�d�l
			//Function�ɑ΂��Ĉ������Z�b�g����
			template<class T_CName, class T_RType, class ...T_Args, int t_MethodTupleNumber, int ...t_ArgsNumber>
			struct S_BindFns<T_RType(T_CName::*)(T_Args...), t_MethodTupleNumber, t_ArgsNumber...>
			{
				static constexpr bool judge = tuple_back_part_convertible_to<std::tuple<reverse_tuple_element<t_ArgsNumber>...>, std::tuple<T_Args...>>;

				using NextClass = S_BoundFns<(t_MethodTupleNumber + 1)* judge,
					Function<std::tuple<T_RType(T_CName::*)(T_Args...), reverse_tuple_element<t_ArgsNumber>...>>,
					T_BoundFns...>;

				using NextMethod = S_BindFns;

				using Type =NextClass::Type;

				template<class T_InputTuple>
				static constexpr void BindFns(T_InputTuple& inputTuple, auto& tuple)
				{
					std::get<(std::tuple_size_v<T_InputTuple>-1) - sizeof...(T_BoundFns)>(inputTuple).emplace(std::get<tuple_size - t_MethodTupleNumber>(tuple), std::get<tuple_size - t_ArgsNumber>(tuple)...);
				}
			};

			//�d�l
			//Function�ɑ΂��Ĉ������Z�b�g����
			template<class T_FunctionInner, int t_MethodTupleNumber>
			struct S_BindFns<Function<T_FunctionInner>, t_MethodTupleNumber>
			{
				using Fn = Function<T_FunctionInner>;

				using NextClass = S_BoundFns<(t_MethodTupleNumber + 1),
					Fn, T_BoundFns...>;

				using NextMethod = S_BindFns;

				using Type = NextClass::Type;

				template<class T_InputTuple>
				static constexpr void BindFns(T_InputTuple& inputTuple, auto& tuple)
				{
					std::get<(std::tuple_size_v<T_InputTuple>-1) - sizeof...(T_BoundFns)>(inputTuple).emplace(std::get<tuple_size - t_MethodTupleNumber>(tuple));
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

				using NextClass = S_BoundFns<(t_MethodTupleNumber + 1)* judge,Function<std::tuple<Fn,reverse_tuple_element<t_ArgsNumber>...>>,
					T_BoundFns...>;

				using NextMethod = S_BindFns;

				using Type = NextClass::Type;

				template<class T_InputTuple>
				static constexpr void BindFns(T_InputTuple& inputTuple, auto& tuple)
				{
					std::get<(std::tuple_size_v<T_InputTuple>-1) - sizeof...(T_BoundFns)>(inputTuple).emplace(std::get<tuple_size - t_MethodTupleNumber>(tuple), std::get<tuple_size - t_ArgsNumber>(tuple)...);

				}
			};
			using NextClass = S_BindFns<reverse_tuple_element<t_TupleNumber>, t_TupleNumber>;

			using Type = NextClass::Type;

			//�d�l			
			//�p�����[�^�p�b�N���̊֐��̌^�܂ňړ�����
			using NextMethod = NextClass::NextMethod;

			//�d�l			
			//�֐��ɑ΂��āA�������Z�b�g����
			static constexpr void BoundFns(auto& inputTuple, auto& tuple)
			{
				NextMethod::BindFns(inputTuple, tuple);
				NextMethod::NextClass::BoundFns(inputTuple, tuple);
			}
		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������������Ȍ^�������ꍇ
		template<class T_FlontBoundFn,class ...T_BoundFns>
		struct S_BoundFns<0,T_FlontBoundFn,T_BoundFns...>
		{
			using Type = S_BoundFns;
			using Judge = std::false_type;
			using FnsType = std::nullopt_t;

			static constexpr void BoundFns(auto& inputTuple, auto& tuple){}
		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������̑S�Ă����������ꍇ
		template<class ...T_BoundFns>
		struct S_BoundFns<tuple_size+1,T_BoundFns...>
		{
			using Type = S_BoundFns;
			using Judge = std::true_type;
			using FnsType = std::tuple<T_BoundFns...>;

			static constexpr void BoundFns(auto& inputTuple, auto& tuple) {}
		};

		using Type = S_BoundFns<1>::Type;
		using Judge = Type::Judge;
		using FnsType = Type::FnsType;

		FnsType fns;

		//�d�l
		//[FnsType]�ɑ΂��āA[fn_Args...]���֐����Ƃɕ����i�[����
		template<size_t ...t_DivideOptionalTuple>
		static constexpr auto BindFns(std::index_sequence<t_DivideOptionalTuple...>,auto&... fn_Args)
		{
			typename S_EnvelopOptional<FnsType>::Type optionalTuple;
			IS_TupleUnzip unzipTuple(fn_Args...);

			S_BoundFns<1>::BoundFns(optionalTuple,unzipTuple.tuple);
			return FnsType(std::get<t_DivideOptionalTuple>(optionalTuple).value()...);
		}

		//�d�l
		//�����̊֐��̂Ƃ���ɑ΂���������Z�b�g����
		//
		//����
		//fn_Args::�֐��Ƃ���ɑ΂�������̃p�����[�^�p�b�N
		constexpr IS_BindFns(T_Fn_Args... fn_Args)
			:fns(BindFns(std::make_index_sequence<std::tuple_size_v<FnsType>>(), fn_Args...)){}

		operator FnsType()
		{
			return fns;
		}

	};

}