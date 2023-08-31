#pragma once

#include<iostream>
#include<tuple>
#include"Parameter_Element.h"
#include"Function_Single_Static.h"
namespace N_Function
{

	template<class T_Method, class ...T_Args>
	struct S_MethodData;

	//�d�l
	//[Function_Multiple_Static]��Operator�����̎���
	//
	//template
	//t_Fns...::�֐��|�C���^�[or[Function_Single_Static]�A����ɑ΂�������A�̌J��Ԃ�
	//
	//�⑫
	//[IS_Function_Multiple_Static_Operator::Type]���p�����鎖
	//t_Fns��[Function_Single_Static]���Z�b�g����ۂ�[static constexpr]�ŏC�����鎖
	template <auto ...t_Fns>
	struct IS_Function_Multiple_Static_Operator
	{
		using Fns = typename IS_Function_Multiple_Helper<std::remove_const_t<decltype(t_Fns)>...>::Fns;

		template<size_t _Index>
		using Fns_element = std::tuple_element_t<_Index, Fns>;
		
		template<size_t _Index>
		static constexpr auto Parameter_Element_v = U_Element_v<_Index, t_Fns...>;
		
		template<size_t t_Parameter_FnNumber,size_t ...t_Parameter_ArgsNumber>
		using Fn_Static =Function_Single_Static<Parameter_Element_v<t_Parameter_FnNumber>,
		Parameter_Element_v<(t_Parameter_FnNumber+1)+t_Parameter_ArgsNumber>...>;

		static constexpr int Fns_Num = std::tuple_size_v<Fns>;

		template<size_t _Index>
		static constexpr int Bind_Args_Num= std::tuple_size_v<typename 
			S_MethodData<Fns_element<_Index>>::ParentFn::BindArgs>;


		template<class T_Fn_Static = std::tuple<>, int t_FnCount = 0, int t_Parameter_Number = 0,class T_Bind_ArgsNum= std::make_index_sequence<Bind_Args_Num<t_FnCount>>>
		struct S_CreateFunctionStatic;

		//�d�l
		//[t_fns...]����[Function_Single_Static]���\������
		//
		//template
		//T_Fn_Static::�\������[Function_Single_Static]��tuple
		//t_FnCount::���ݍ쐬����[Function_Single_Static]�̔ԍ�
		//t_Parameter_Number::[t_FnCount]�Ԗڂ�[Function_Single_Static]���쐬����חv�f��[t_Fns...]�̉��Ԗڂ��玦���ԍ�
		template<class ...T_Fn_Static,int t_FnCount, int t_Parameter_Number ,
			size_t ...t_Bind_ArgsNum>
		struct S_CreateFunctionStatic<std::tuple<T_Fn_Static...>,t_FnCount, t_Parameter_Number,
			std::index_sequence<t_Bind_ArgsNum...>>
		{
			using T_FnStatic_Add = std::tuple<Fn_Static<t_Parameter_Number, t_Bind_ArgsNum...>, T_Fn_Static...>;

			using Type = S_CreateFunctionStatic<T_FnStatic_Add, t_FnCount + 1, t_Parameter_Number + 1 + Bind_Args_Num<t_FnCount>>::Type;
		};

		template<class ...T_Fn_Static,int t_Parameter_Number,
			size_t ...t_Bind_ArgsNum>
		struct S_CreateFunctionStatic<std::tuple<T_Fn_Static...>, Fns_Num-1, t_Parameter_Number,
			std::index_sequence<t_Bind_ArgsNum...>>
		{
			using Type = std::tuple<
				Fn_Static<t_Parameter_Number, t_Bind_ArgsNum...>, 
				T_Fn_Static...>;

		};

		template<class T_FnsStatic>
		struct S_FunctionMultipleOperatorStatic;

		//�d�l
		//�\������[Function_Single_Static]��S�Čp������
		template<class ...T_FnsStatic>
		struct S_FunctionMultipleOperatorStatic<std::tuple<T_FnsStatic...>> :
			public T_FnsStatic...
		{
			using T_FnsStatic::operator()...;
			using T_FnsStatic::Execution...;
		};

		using Type =
			S_FunctionMultipleOperatorStatic<typename S_CreateFunctionStatic<>::Type>;
	};

}