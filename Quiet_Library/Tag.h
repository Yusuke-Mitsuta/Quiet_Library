#pragma once

#include"String.h"
#include"Tuple_Class_Declare.h"

namespace quiet
{
	//�d�l
	//�C�ӂ̌^[T]�ɕ�����^�̃^�O��t����N���X
	//
	//�⑫
	//���_�⏕�𔺂��^�Ɋւ��Ă͔�Ή�
	template<class T, String t_tag , String... t_tags>
	struct Tag :
		public T
	{
		using T::T;

		using tag_list = tuple_v<t_tag, t_tags...>;
	};



}