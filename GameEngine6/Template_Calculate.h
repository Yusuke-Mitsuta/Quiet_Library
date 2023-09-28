#pragma once

template<class T_Type_1,char t_operator, class T_Type_2>
struct Calculate
{
	using type = T_Type_1;
};

template<class T_Type_1,class T_Type_2>
struct Calculate<T_Type_1,'+',T_Type_2>
{
	using type = T_Type_1;
};