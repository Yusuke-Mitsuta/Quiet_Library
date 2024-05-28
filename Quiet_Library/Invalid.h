/*!
 * Invalid.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

namespace quiet
{

	//�d�l
	//�����l�̌^������
	struct invalid_t
	{

		constexpr invalid_t() {}

		using type = invalid_t;

		constexpr operator size_t()
		{
			return size_t(-1);
		}

	};

	//�d�l
	//�����l������
	inline  invalid_t invalid = invalid_t{};


}
