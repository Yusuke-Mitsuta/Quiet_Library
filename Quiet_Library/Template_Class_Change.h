#pragma once

#include<tuple>


namespace quiet::N_Template
{

	//�d�l
	//[T_Old]�̃e���v���[�g�p�����[�^��[T_New_Outer]�Ɉڂ�
	//
	//�e���v���[�g
	// 
	//[T_Old]::�e���v���[�g�p�����[�^�����o���N���X
	//[T_New_Outer]::�e���v���[�g�p�����[�^���ڂ��N���X
	//
	//�⑫
	//[T_Old]��[std::tuple_size,std::tuple_element]�ɑΉ����Ă��Ȃ��ꍇ�A
	//	[invalid_t]��Ԃ�
	template<class T_Old, template<class...> class T_New_Outer>
	struct S_Class_Change
	{
	private:

		template<class T_Old>
		struct S_Index_Sequence
		{
			using type = invalid_t;
		};

		template<class T_Old>
			requires requires
		{
			requires std::tuple_size_v<T_Old> >= 0;
			{ typename std::tuple_element_t<0, T_Old> };
		}
		struct S_Index_Sequence<T_Old>
		{
			using type = N_Tuple::I_index_sequence<std::tuple_size_v<T_Old>>::type;
		};

		template<class T_Indexs = typename S_Index_Sequence<T_Old>::type >
		struct S_Tuple_Create
		{
			using type = invalid_t;
		};

		template<size_t ...t_indexs>
		struct S_Tuple_Create<tuple_v<t_indexs...>>
		{
			using type = T_New_Outer<std::tuple_element_t<t_indexs, T_Old>...>;
		};

	public:

		using type = typename S_Tuple_Create<>::type;
	};

	//�d�l
	//[T_Old]�̃e���v���[�g�p�����[�^��[T_New_Outer]�Ɉڂ�
	//
	//�e���v���[�g
	// 
	//[T_Old]::�e���v���[�g�p�����[�^�����o���N���X
	//[T_New_Outer]::�e���v���[�g�p�����[�^���ڂ��N���X
	//
	//�⑫
	//[T_Old]��[std::tuple_size,std::tuple_element]�ɑΉ����Ă��Ȃ��ꍇ�A
	//	[invalid_t]��Ԃ�
	template<class T_Old, template<class...> class T_New_Outer>
	using U_Class_Change =typename S_Class_Change<T_Old, T_New_Outer>::type;
	
}