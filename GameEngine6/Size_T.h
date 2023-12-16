#pragma once


#include<concepts>
#include<compare>

#define DECLARATION_ASSIGNMENT_OPERATOR_SIZE_T(_sign) \
template<std::convertible_to<Size_t> T> \
constexpr Size_t& operator _sign(const T& size_2) const; \

#define ASSIGNMENT_OPERATOR_SIZE_T(_sign) \
template<std::convertible_to<Size_t> T> \
constexpr Size_t& Size_t::operator _sign (const T& size_2) const \
{ \
	size _sign size_2.size; \
	return *this; \
}\

#define DECLARATION_ARITHMETIC_OPERATOR_SIZE_T(_sign) \
template<std::convertible_to<Size_t> T> \
constexpr Size_t operator _sign(const T& size_2) const; \

#define ARITHMETIC_OPERATOR_SIZE_T(_sign) \
template<std::convertible_to<Size_t> T> \
constexpr Size_t Size_t::operator _sign (const T& size_2) const \
{ \
	return Size_t(size _sign size_2.size); \
}\


struct Size_t
{
	friend struct Size_t;

	long long size;
public:

	constexpr Size_t(long long set_Size) :
		size(set_Size) {}

public:

	template<std::integral N>
	constexpr Size_t(const N& set_Size) :
		size((set_Size < 0 ? -1 : set_Size)) {}

	constexpr Size_t(const Size_t& copy_size) :
		size(copy_size.size) {}

	template<std::integral N>
	constexpr operator N()
	{
		return size;
	}

	constexpr operator size_t()
	{
		return size;
	}

	//<=>をpublicで定義しておくことで、その他の演算子が導出される
	constexpr auto operator<=>(const Size_t&) const = default;

	template<std::integral N>
	constexpr bool operator ==(const N& n) const;

	DECLARATION_ARITHMETIC_OPERATOR_SIZE_T(+)
	DECLARATION_ARITHMETIC_OPERATOR_SIZE_T(-)
	DECLARATION_ARITHMETIC_OPERATOR_SIZE_T(*)
	DECLARATION_ARITHMETIC_OPERATOR_SIZE_T(/)

	DECLARATION_ASSIGNMENT_OPERATOR_SIZE_T(+=)
	DECLARATION_ASSIGNMENT_OPERATOR_SIZE_T(-=)
	DECLARATION_ASSIGNMENT_OPERATOR_SIZE_T(*=)
	DECLARATION_ASSIGNMENT_OPERATOR_SIZE_T(/=)

}; 

template<std::integral N>
inline constexpr bool Size_t::operator==(const N& n) const
{
	return (size == n);
}

ARITHMETIC_OPERATOR_SIZE_T(+)
ARITHMETIC_OPERATOR_SIZE_T(-)
ARITHMETIC_OPERATOR_SIZE_T(*)
ARITHMETIC_OPERATOR_SIZE_T(/)

ASSIGNMENT_OPERATOR_SIZE_T(+=)
ASSIGNMENT_OPERATOR_SIZE_T(-=)
ASSIGNMENT_OPERATOR_SIZE_T(*=)
ASSIGNMENT_OPERATOR_SIZE_T(/=)

