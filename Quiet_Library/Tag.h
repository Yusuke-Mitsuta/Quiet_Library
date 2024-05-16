#pragma once

#include"String.h"
#include"Tuple_Class_Declare.h"

namespace quiet
{
	//仕様
	//任意の型[T]に文字列型のタグを付けるクラス
	//
	//補足
	//推論補助を伴う型に関しては非対応
	template<class T, String t_tag , String... t_tags>
	struct Tag :
		public T
	{
		using T::T;

		using tag_list = tuple_v<t_tag, t_tags...>;
	};



}