#pragma once

#include"Parameter_Element.h"

template<class ...T_Parameters>
struct S_Parameter
{
protected:

	template<int _Index, size_t t_Size, class T_Flont_Parameter, class ...T_Remaining_Parameters>
	struct S_Material :
		public S_Material<_Index - 1,t_Size+1, T_Remaining_Parameters...>
	{
		using Next = S_Material<_Index - 1, t_Size + 1, T_Remaining_Parameters...>;

		static constexpr size_t Size = Next::Size;

		T_Flont_Parameter flont_parameter;

		constexpr S_Material(T_Flont_Parameter set_Flont_parameter, T_Remaining_Parameters... set_Parameters) :
			flont_parameter(set_Flont_parameter),Next(set_Parameters...){}

		constexpr auto Get(int& number)
		{
			return (number) ? Next::Get(number-=1) : flont_parameter;
		}
	};

	template<int _Index,size_t t_Size,class ...T_Lapping_Parameter ,class ...T_Remaining_Parameters>
	struct S_Material<_Index,t_Size,S_Parameter<T_Lapping_Parameter...>, T_Remaining_Parameters...> :
		public S_Material<_Index - 1, t_Size+ S_Parameter<T_Lapping_Parameter...>::Size, T_Remaining_Parameters...>
	{
		using Flont_Parameter = S_Parameter<T_Lapping_Parameter...>;
		using Next = S_Material<_Index - 1, t_Size + S_Parameter<T_Lapping_Parameter...>::Size, T_Remaining_Parameters...>;

		Flont_Parameter parameters;

		static constexpr size_t Size = Next::Size;

		constexpr S_Material(S_Parameter<T_Lapping_Parameter...> set_parameters,T_Remaining_Parameters... remaining_Parameters) :
			parameters(set_parameters), 
			Next(remaining_Parameters...){}

		constexpr S_Material(T_Lapping_Parameter... set_parameters, T_Remaining_Parameters... remaining_Parameters) :
			parameters(set_parameters...),
			Next(remaining_Parameters...) {}

		constexpr auto Get(int& number)
		{
			auto get = parameters.Get(number);
			return (number) ? Next::Get(number-=1) : get;
		}
	};

	template<size_t t_Size, class ...T_Lapping_Parameter>
	struct S_Material<0,t_Size, S_Parameter<T_Lapping_Parameter...>>
	{
		using Flont_Parameter = S_Parameter<T_Lapping_Parameter...>;

		Flont_Parameter parameters;

		static constexpr size_t Size = t_Size + Flont_Parameter::Size;

		constexpr S_Material(S_Parameter<T_Lapping_Parameter...> set_parameters) :
			parameters(set_parameters) {}

		constexpr S_Material(T_Lapping_Parameter... set_parameters) :
			parameters(set_parameters...){}

		constexpr auto Get(int& number)
		{
			return parameters.Get(number);
		}
	};

	template< size_t t_Size, class T_Flont_Parameter>
	struct S_Material<0 ,t_Size,T_Flont_Parameter>
	{
		T_Flont_Parameter flont_parameter;

		static constexpr size_t Size = t_Size+1;

		constexpr S_Material(T_Flont_Parameter set_Flont_parameter) :
			flont_parameter(set_Flont_parameter) {}

		constexpr auto Get(int number)
		{
			return flont_parameter;
		}
	};

	S_Material<sizeof...(T_Parameters)-1,0, T_Parameters...> parameters;

	constexpr auto Get(int& number);

public:

	static constexpr size_t Size = S_Material<sizeof...(T_Parameters) - 1, 0, T_Parameters...>::Size;

	template<class ...MT_Parameters>
	constexpr S_Parameter(MT_Parameters... set_Parameters) 
		: parameters(set_Parameters...) 
	{}

	S_Parameter(T_Parameters... set_Parameters) 
		: parameters(set_Parameters...) 
	{}

	constexpr auto operator[](int number);
};

template<class ...MT_Parameters>
S_Parameter(MT_Parameters...) -> S_Parameter<MT_Parameters...>;

template<class ...T_Parameters>
constexpr auto S_Parameter<T_Parameters...>::Get(int& number)
{
	return parameters.Get(number);
}

template<class ...T_Parameters>
constexpr auto S_Parameter<T_Parameters...>::operator[](int number)
{
	return parameters.Get(number);
}

