#pragma once

#include"Array.h"

namespace N_Vector
{
	//�d�l
	//Array�̗v�f��(2�`4)�ɑΉ����ĕϐ�[x,y,z,w]��
	// union�Œ�`����
	template<class T, size_t t_vec>
	struct S_Storge
	{
		Array<T, t_vec> elems;
	};

	template<class T>
	struct S_Storge<T, 2>
	{
		union 
		{
			Array<T, 2> elems;

			struct
			{
				T x;
				T y;
			};
		};
	};

	template<class T>
	struct S_Storge<T, 3>
	{
		union
		{
			Array<T, 3> elems;

			struct
			{
				T x;
				T y;
				T z;
			};
		};

	};

	template<class T>
	struct S_Storge<T, 4>
	{
		union
		{
			Array<T, 4> elems;

			struct
			{
				T x;
				T y;
				T z;
				T w;
			};
		};
	};
}
