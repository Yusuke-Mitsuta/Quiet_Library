#pragma once

#include"Parameter.h"
#include"SwapType.h"
#include"Function_Single_Data.h"


namespace N_Function
{

	template<class ...T_Fn_Parts>
	struct S_Function_Single_Data;

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
	template<class T_FlontFn, class ...TP_Fns>
	struct IS_Function_Multiple_Helper
	{
	private:


		using Parameter = S_Parameter<T_FlontFn, TP_Fns...>;

		template<int _Index>
		using Element_t = U_Element_t< (Parameter::Size * 2 - _Index) % Parameter::Size, Parameter>;

		//�d�l
		//�֐��ɑ΂��āA�u���ɑ��������̌^�A�֐��Ƀo�C���h�ς݂̈����̌^�v���֐��ɑ΂�������̌^�̌�������ƌ݊��������邩���肵�A�݊����������[Function_Single]�ɂ܂Ƃ߂�
		//
		//�e���v���[�g
		//t_SearchNumber::���݂̒T�����̗v�f�ԍ�
		//...TP_BoundFns::[Function_Single]�ł܂Ƃ߂��^
		template<int t_Search_Number = 1, class TP_BoundFns = S_Parameter<>,
			bool t_Pointer_Judge_Fg=true,
			bool t_Loop_Fg = static_cast<bool>(t_Search_Number % (Parameter::Size + 1))>
		struct S_CorrectType;

		template<int t_Search_Number, bool t_Pointer_Judge_Fg, class ...TP_BoundFns>
		struct S_CorrectType<t_Search_Number, S_Parameter<TP_BoundFns...>, t_Pointer_Judge_Fg, true>
		{

			//�d�l
			//[Element<t_Pointer_Number>]��[Element<t_Method_Number>]�ƌ݊��������邩���肷��
			//
			//����
			//1:[Element<t_Pointer_Number>]���|�C���^�[�ł���
			//2:[Element<t_Method_Number>]�������o�[�֐��|�C���^�[�ł���
			//3:[Element<t_Pointer_Number>]��[Element<t_Method_Number>]���Ăяo���鎖
			template<int t_Pointer_Number, int t_Method_Number>
			static constexpr bool p_Judge = is_pointer<Element_t<t_Pointer_Number>>
				&& convertible_to<std::remove_pointer_t<Element_t<t_Pointer_Number>>, typename S_Function_Single_Data<Element_t<t_Method_Number>>::CName>
				&& (!static_cast<bool>(S_Function_Single_Data<Element_t<t_Method_Number>>::Lelve));


			//�d�l
			//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
			template<int t_TP_Number = t_Search_Number, class TP_ArgsNumbers = S_Parameter_Value<>, bool t_Create_Fg =
				not_same_as<typename S_Function_Single_Data<Element_t<t_TP_Number>>::Method, std::nullopt_t>>
				struct S_Function_Single_Create;

			template<int t_TP_Number, int ...tP_ArgsNumbers>
			struct S_Function_Single_Create<t_TP_Number, S_Parameter_Value<tP_ArgsNumbers...>, false>
			{
				//�d�l
				//�֐��|�C���^�[�ɑ΂��Ĉ������Z�b�g����
				using Type = S_Function_Single_Create<t_TP_Number + 1, S_Parameter_Value<t_TP_Number, tP_ArgsNumbers...>>::Type;
				using Type2 = S_Function_Single_Create<t_TP_Number + 1, S_Parameter_Value<t_TP_Number, tP_ArgsNumbers...>>;
			};

			template<int t_Method_Number, int ...tP_ArgsNumbers>
			struct S_Function_Single_Create<t_Method_Number, S_Parameter_Value<tP_ArgsNumbers...>, true>
			{
				using MethodData = N_Function::S_Function_Single_Data<Element_t<t_Method_Number>>;

				static constexpr bool judge_Pointer=
					p_Judge<t_Method_Number + 1, t_Method_Number> ||
					p_Judge<Parameter::Size, t_Method_Number> ||
					static_cast<bool>(MethodData::Lelve) ||
					same_as<typename MethodData::CName, std::nullopt_t>;

				//�d�l
				//�擪�̋��ʂ̃|�C���^�[���A�擪�̗v�f���g�p���Ȃ��ꍇ������X�L�b�v����ׂ̃t���O
				static constexpr bool first_Element_Not_Pointer = is_pointer<Element_t<t_Method_Number + 1>> && static_cast<bool>(MethodData::Lelve) && (t_Method_Number == Parameter::Size - 1);

				template<bool t_Point_Set_Fg>
				struct S_Judge_Return_Type
				{
					using Pointer_Type = U_Swap_t1<Element_t<Parameter::Size>, Element_t<t_Method_Number + 1>, p_Judge<t_Method_Number + 1, t_Method_Number>>;
					using Type = S_Function_Single_Data<Pointer_Type,Element_t<t_Method_Number>,Element_t<tP_ArgsNumbers>...>;
				};

				template<>
				struct S_Judge_Return_Type<false>
				{
					using Type = S_Function_Single_Data<Element_t<t_Method_Number>, Element_t<tP_ArgsNumbers>...>;
				};

				using Return = typename S_Judge_Return_Type<p_Judge<t_Method_Number + 1, t_Method_Number> ||
					p_Judge<Parameter::Size, t_Method_Number>>::Type;

				static constexpr bool judge = not_is_nullopt<typename Return::Method> && (judge_Pointer || !t_Pointer_Judge_Fg);

				//�d�l
				//�����𐸍����A���b�s���O����
				using Type = S_CorrectType<(t_Method_Number + 1 +
					(p_Judge<t_Method_Number + 1, t_Method_Number> || first_Element_Not_Pointer))* judge,
					S_Parameter<Return, TP_BoundFns...>>::Type;
				using Type3 = S_CorrectType<(t_Method_Number + 1 +
					(p_Judge<t_Method_Number + 1, t_Method_Number> || first_Element_Not_Pointer))* judge,
					S_Parameter<Return, TP_BoundFns...>>;

			};

			using Type = S_Function_Single_Create<>::Type;
			using Type1 = S_Function_Single_Create<>;

		};

		//�d�l
		//Function�ɑ΂��ăZ�b�g���������̑S�Ă����������ꍇ�͂��̌��ʂ��A���s�����[std::nullopt_t]���Ԃ�
		template<int t_Search_Number, bool t_Pointer_Judge_Fg, class ...TP_BoundFns>
		struct S_CorrectType<t_Search_Number, S_Parameter<TP_BoundFns...>,t_Pointer_Judge_Fg,false>
		{
			using Type = S_CorrectType;

			using Judge = U_Judge_t<T_FlontFn, t_Search_Number>;

			using Fns = U_Judge_t<S_Parameter<TP_BoundFns...>, t_Search_Number>;
		};

	public:

		//�d�l
		//�S�Ă̊֐��I�u�W�F�N�g�ɂ����ēK�؂ȃN���X�|�C���^�[���Z�b�g����Ă��邩���肷��
		using Pointer_Judge = S_CorrectType<>::Type;

		//�d�l
		//����̍��ڂ���N���X�|�C���^�[���Z�b�g����Ă��邩�����O����
		using Not_Pointer_Judge= S_CorrectType<1,S_Parameter<>,0>::Type;

		//using Fns = Type::Fns;

	};

}