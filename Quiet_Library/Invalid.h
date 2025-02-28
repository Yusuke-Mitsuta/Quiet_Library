/*!
 * Invalid.h
 *
 * (C) 2024 Mitsuta Yusuke
 *
 */

#pragma once

namespace quiet
{

	//仕様
	//無効値の型を示す
	struct invalid_t
	{

		constexpr invalid_t() {}

		using type = invalid_t;

	};


	//仕様
	//無効値を示す
	inline constexpr invalid_t invalid = invalid_t{};


}
