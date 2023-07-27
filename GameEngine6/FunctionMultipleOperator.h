#pragma once

#include"Function.h"
#include"FunctionMultiple_Helper.h"
#include"SwapType.h"

namespace N_Function
{
	
	//�d�l
	//[FunctionMultiple]��Operator�����̎���
	//template
	//...T_Fns::�����̊֐��|�C���^�[�A�y�т���ɑ΂������
	//
	//�⑫
	//IS_FunctionMultipleOperator�̎��̉��͋֎~�Ƃ���
	//IS_FunctionMultipleOperator::Type�����̉����鎖
	template <class ...T_Fns>
	struct IS_FunctionMultipleOperator
	{
	
		//�d�l
		//������[Function]��operator����������
		//
		//T_TupleFns::[Function]�������A�i�[����Ă�Tuple
		//t_Even::��������operator()()�������̏��ԂɂȂ�悤�ɂ���t���O
		template<class T_TupleFns,bool t_Even = !((sizeof...(T_Fns)+std::tuple_size_v<T_TupleFns>) % 2)>
		struct S_FunctionMultipleOperator;

		template<class T_FlontFn, class ...T_BindArgs,bool t_Even>
		struct S_FunctionMultipleOperator<std::tuple<Function<T_FlontFn, T_BindArgs...>>,t_Even> :
			public Function<T_FlontFn, T_BindArgs...>
		{
			using Function<T_FlontFn, T_BindArgs...>::operator();


			constexpr S_FunctionMultipleOperator(T_FlontFn fn, T_BindArgs... args) :
				Function<T_FlontFn, T_BindArgs...>(fn, args...) {}
		};


		template<class T_FlontFn, class ...T_BindArgs, class ...T_Fns,bool t_Even>
		struct S_FunctionMultipleOperator<std::tuple<Function<T_FlontFn, T_BindArgs...>,T_Fns...>,t_Even> : 
			public Function<T_FlontFn, T_BindArgs...>,
			public S_FunctionMultipleOperator<std::tuple<T_Fns...>>
		{
			//�d�l
			//��������operator()()�������̏��ԂɂȂ�悤�ɂ���
			//�������������A�c���[Function]�������A���͑���������A�c���[Function]����Ȃ�T_1��T_2�����ւ���
			using SwapType =typename IS_SwapType<
				S_FunctionMultipleOperator<std::tuple<T_Fns...>>, 
				Function<T_FlontFn, T_BindArgs...>, 
				t_Even>;

			using SwapType::Type_1::operator();
			using SwapType::Type_2::operator();

			template<class ...MT_Fns>
			constexpr S_FunctionMultipleOperator(T_FlontFn fn,T_BindArgs... args,MT_Fns... fns):
				Function<T_FlontFn, T_BindArgs...>(fn,args...),
				S_FunctionMultipleOperator<std::tuple<T_Fns...>>(fns...) {}
		};


		using Type = typename S_FunctionMultipleOperator<typename IS_FunctionMultiple_Helper<T_Fns...>::Fns>;

	};


}