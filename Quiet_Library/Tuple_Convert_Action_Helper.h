#pragma once


namespace quiet::N_Tuple::N_Tuple_Convert_Action
{

	template<template<class...>class T_Action,
		class T_Convert_Tuple,
		bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip>
	struct I_Tuple_Convert_Action_Core;

	template<template<class...>class T_Action,
		class T_Convert_Tuple,
		bool t_is_Target_Tuple_p,
		bool t_is_Target_Tuple_t,
		bool t_Return_p_Convert_Skip,
		bool t_Return_tv_Convert_Skip,
		size_t t_Start_Point,
		bool t_Return_p_Back>
	struct I_Set_StartPoint;


	template<
		auto t_is_Target_Tuple_p ,
		auto t_is_Target_Tuple_t>
	struct I_Helper
	{
		//�d�l
		//�ϊ��̑Ώۂɑ΂��āA�v�����鍀�ڂ�ݒ肷��
		//
		//�e���v���[�g
		//[t_Return_p_Convert_Skip_Fg]::[T_Action]���[Tuple_p]�Ɋւ���ϊ����X�L�b�v����
		//[t_Return_tv_Convert_Skip_Fg]::[T_Action]���[Tuple_t��v,v��t]�Ɋւ���ϊ����X�L�b�v����
		//[t_is_Set_StartPoint_Fg]::[T_Action]�O��[Tuple_p]�̈ʒu��ύX����
		//[t_Return_p_Back_Fg]::[T_Action]���[Tuple_p]�̈ʒu�����ɖ߂�
		template<
			short t_Return_p_Convert_Skip_Fg,
			short t_Return_tv_Convert_Skip_Fg,
			short t_is_Set_StartPoint_Fg,
			short t_Return_p_Back_Fg>
		struct S_Helper;

		//�d�l
		//�p�����[�^�ʂ�Ɍ^��ϊ����A[T_Action]�����s����
		template<
			short t_Return_p_Convert_Skip_Fg,
			short t_Return_tv_Convert_Skip_Fg>
			requires requires
		{
			requires t_Return_p_Convert_Skip_Fg* t_Return_tv_Convert_Skip_Fg != 0;
		}
		struct S_Helper<t_Return_p_Convert_Skip_Fg, t_Return_tv_Convert_Skip_Fg, -1, -1>
		{
			template<template<class...>class T_Action, class T_Convert_Tuple>
			using type = I_Tuple_Convert_Action_Core<
				T_Action,
				T_Convert_Tuple,
				t_is_Target_Tuple_p,
				t_is_Target_Tuple_t,
				t_Return_p_Convert_Skip_Fg,
				t_Return_tv_Convert_Skip_Fg>::type;
		};

		//�d�l
		//�|�C���g�̈ʒu�ύX�𔺂��ϊ������{����
		template<
			short t_Return_p_Convert_Skip_Fg,
			short t_Return_tv_Convert_Skip_Fg,
			short t_Return_p_Back_Fg>
			requires requires
		{
			requires t_Return_p_Convert_Skip_Fg* t_Return_tv_Convert_Skip_Fg* t_Return_p_Back_Fg != 0;
		}
		struct S_Helper<t_Return_p_Convert_Skip_Fg, t_Return_tv_Convert_Skip_Fg, 1,t_Return_p_Back_Fg>
		{
			template<template<class...>class T_Action, class T_Convert_Tuple, size_t t_StartPoint>
			using type = I_Set_StartPoint<
				T_Action,
				T_Convert_Tuple,
				t_is_Target_Tuple_p,
				t_is_Target_Tuple_t,
				t_Return_p_Convert_Skip_Fg,
				t_Return_tv_Convert_Skip_Fg,
				t_StartPoint,
				t_Return_p_Back_Fg>::type;
		};

		
		template<>
		struct S_Helper<0, 0, 0, 0>
		{
			using Default = S_Helper<-1, -1, -1, -1>;

			using Return_p_Convert_Skip = S_Helper<1, -1, 0, 0>;

			using Return_tv_Convert_Skip = S_Helper<-1, 1, 0, 0>;

			using Return_Convert_Skip = S_Helper<1, 1, 0, 0>;

			using Set_StartPoint = S_Helper<0, 0, 1, 0>;
		};

		template<
			short t_Return_p_Convert_Skip_Fg,
			short t_Return_tv_Convert_Skip_Fg>
		struct S_Helper<t_Return_p_Convert_Skip_Fg, t_Return_tv_Convert_Skip_Fg, 0, 0>
		{
			using Default = S_Helper<t_Return_p_Convert_Skip_Fg, t_Return_tv_Convert_Skip_Fg, -1, -1>;

			using Set_StartPoint = S_Helper<t_Return_p_Convert_Skip_Fg, t_Return_tv_Convert_Skip_Fg, 1, 0>;
		};

		template<
			short t_Return_p_Convert_Skip_Fg,
			short t_Return_tv_Convert_Skip_Fg>
		struct S_Helper<t_Return_p_Convert_Skip_Fg, t_Return_tv_Convert_Skip_Fg, 1, 0>
		{

			using Default = S_Helper<t_Return_p_Convert_Skip_Fg, t_Return_tv_Convert_Skip_Fg, 1, -1>;

			using Reset_ReturnPoint = S_Helper<t_Return_p_Convert_Skip_Fg, t_Return_tv_Convert_Skip_Fg, 1, 1>;
		};

		template<>
		struct S_Helper<0, 0, 1, 0>
		{
			using Default = S_Helper<-1, -1, 1, -1>;

			using Return_p_Convert_Skip = S_Helper<1, -1, 1, 0>;

			using Return_tv_Convert_Skip = S_Helper<-1, 1, 1, 0>;

			using Return_Convert_Skip = S_Helper<1, 1, 1, 0>;

			using Reset_ReturnPoint = S_Helper<0, 0, 1, 1>;

		};

		template<short t_is_Set_StartPoint_Fg,
			short t_Return_p_Back_Fg>
		struct S_Helper<0, 0, t_is_Set_StartPoint_Fg, t_Return_p_Back_Fg>
		{

			using Default = S_Helper<-1, -1, t_is_Set_StartPoint_Fg, t_Return_p_Back_Fg>;

			using Return_p_Convert_Skip = S_Helper<1, -1, t_is_Set_StartPoint_Fg, t_Return_p_Back_Fg>;

			using Return_tv_Convert_Skip = S_Helper<-1, 1, t_is_Set_StartPoint_Fg, t_Return_p_Back_Fg>;

			using Return_Convert_Skip = S_Helper<1, 1, t_is_Set_StartPoint_Fg, t_Return_p_Back_Fg>;
		};

		using type = S_Helper<0, 0, 0, 0>;

	};


}