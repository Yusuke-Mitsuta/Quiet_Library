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

	};


	//�d�l
	//�����l������
	inline constexpr invalid_t invalid = invalid_t{};


}
