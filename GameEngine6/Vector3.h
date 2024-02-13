#pragma once

#define PropertyAlias(base,name,...)\
__declspec(property(get = get_##base, put = set_##base)) __VA_ARGS__ name;\
__VA_ARGS__ & get_##base(){return base;}\
void set_##base(const __VA_ARGS__& value){base = value;}

#include"Constexpr_Array.h"

class Vector3
	: public Array<float,3>
{
public:
	

	//float x, y, z, w;

	//‘‚­‚Ì‚ª‚ß‚ñ‚Ç‚­‚¹‚¦‚Ì‚Å‚Æ‚è‚ ‚¦‚¸ƒ}ƒNƒ‚Å‹–‚µ‚Ä
	//PropertyAlias(x, r, float)
	//PropertyAlias(y, g, float)
	//PropertyAlias(z, b, float)
	//PropertyAlias(w, a, float)

	//float& x = Array::get<0>();
	//float& y = Array::get<1>();
	//float& z = Array::get<2>();
	
	using Array::Array;

};

