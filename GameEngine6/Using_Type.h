#pragma once

using Size_Type = size_t;

//�d�l
//�����l�̌^������
struct invalid_t
{
	constexpr invalid_t() {}

	using type = invalid_t;

};

//�d�l
//�����l������
static constexpr invalid_t invalid = invalid_t{};

struct S_Empty
{
};

