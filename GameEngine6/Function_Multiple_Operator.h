#pragma once

#include"Function_Multiple_Helper.h"
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
	//IS_Function_Multiple_Operator::Type�����̉����鎖
	template <class ...T_Fns>
	struct IS_Function_Multiple_Operator
	{



		//template<class T_Methods>
		//struct S_Function_Multiple_Chip;
		//
		//template<class T_Method,class ...TP_BindArgs,class T_Methods>
		//struct S_Function_Multiple_Chip<Function_Single<T_Method,TP_BindArgs...>> :
		//	public S_Function_Multiple_Chip
		//{











		//};












	
		//�d�l
		//������[Function_Single]��operator����������
		//
		//T_TupleFns::[Function_Single]�������A�i�[����Ă�Tuple
		//t_Even::��������operator()()�������̏��ԂɂȂ�悤�ɂ���t���O
		template<class T_TupleFns,bool t_Even = !((sizeof...(T_Fns)+std::tuple_size_v<T_TupleFns>) % 2)>
		struct S_Function_Multiple_Operator;

		template<class T_FlontFn, class ...T_BindArgs,bool t_Even>
		struct S_Function_Multiple_Operator<std::tuple<Function_Single<T_FlontFn, T_BindArgs...>>,t_Even> :
			public Function_Single<T_FlontFn, T_BindArgs...>
		{
			using Function_Single<T_FlontFn, T_BindArgs...>::operator();

			constexpr S_Function_Multiple_Operator(T_FlontFn fn, T_BindArgs... args) :
				Function_Single<T_FlontFn, T_BindArgs...>(fn, args...) {}
		};


		template<class T_FlontFn, class ...T_BindArgs, class ...T_Fns,bool t_Even>
		struct S_Function_Multiple_Operator<std::tuple<Function_Single<T_FlontFn, T_BindArgs...>,T_Fns...>,t_Even> : 
			public Function_Single<T_FlontFn, T_BindArgs...>,
			public S_Function_Multiple_Operator<std::tuple<T_Fns...>>
		{
			//�d�l
			//��������operator()()�������̏��ԂɂȂ�悤�ɂ���
			//�������������A�c���[Function_Single]�������A���͑���������A�c���[Function_Single]����Ȃ�T_1��T_2�����ւ���
			using SwapType =typename IS_Swap_Type<
				S_Function_Multiple_Operator<std::tuple<T_Fns...>>, 
				Function_Single<T_FlontFn, T_BindArgs...>, 
				t_Even>;

			using SwapType::Type_1::operator();
			using SwapType::Type_2::operator();

			template<class ...MT_Fns>
			constexpr S_Function_Multiple_Operator(T_FlontFn fn,T_BindArgs... args,MT_Fns... fns):
				Function_Single<T_FlontFn, T_BindArgs...>(fn,args...),
				S_Function_Multiple_Operator<std::tuple<T_Fns...>>(fns...) {}
		};


		using Type = typename S_Function_Multiple_Operator<typename IS_Function_Multiple_Helper<T_Fns...>::Fns>;

	};


}