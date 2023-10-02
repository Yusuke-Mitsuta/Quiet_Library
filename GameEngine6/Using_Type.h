#pragma once

using Size_Type = size_t;

//仕様
//無効値の型を示す
struct invalid_t
{
	constexpr invalid_t() {}

	using type = invalid_t;

};

//仕様
//無効値を示す
static constexpr invalid_t invalid = invalid_t{};

struct S_Empty
{
};

