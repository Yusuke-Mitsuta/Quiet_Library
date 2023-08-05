#pragma once
//
////#include"Parameter_Element.h"
//
//template<class ...T_Parameters>
//struct S_Parameter
//{
//private:
//	template<int _Index, class T_Flont_Parameter, class ...T_Remaining_Parameters>
//	struct S_Material :
//		public S_Material<_Index - 1, T_Remaining_Parameters...>
//	{
//		using Type = S_Material<_Index - 1, T_Remaining_Parameters...>::Type;
//
//		T_Flont_Parameter flont_parameter;
//
//		S_Material(T_Flont_Parameter set_Flont_parameter, T_Remaining_Parameters... set_Parameters) :
//			flont_parameter(set_Flont_parameter),S_Material<_Index - 1, T_Parameters...>(set_Parameters...){}
//
//		constexpr auto Get(int number);
//	};
//
//	template<class T_Flont_Parameter, class ...T_Remaining_Parameters>
//	struct S_Material<1, T_Flont_Parameter,T_Remaining_Parameters...>
//	{
//		using Type = T_Flont_Parameter;
//
//		T_Flont_Parameter flont_parameter;
//
//		S_Material(T_Flont_Parameter set_Flont_parameter) :
//			flont_parameter(set_Flont_parameter) {}
//
//		constexpr auto Get(int number)
//		{
//			return flont_parameter;
//		}
//	};
//
//	S_Material<sizeof...(T_Parameters), T_Parameters...> parameters;
//
//public:
//
//
//	//using Element = S_Material<_Index+1, T_Parameters...>::Type;
//
//	static constexpr size_t Size = sizeof...(T_Parameters);
//
//	template<class ...MT_Parameters>
//	constexpr S_Parameter(MT_Parameters... set_Parameters) :
//		parameters(set_Parameters...) {}
//
//	constexpr auto operator[](int number);
//};
//
//template<class ...T_Parameters>
//constexpr auto S_Parameter<T_Parameters...>::operator[](int number)
//{
//	return parameters.Get(number);
//}
//
//
//template<class ...T_Parameters>
//template<int _Index, class T_Flont_Parameter, class ...T_Remaining_Parameters>
//constexpr auto S_Parameter<T_Parameters...>::S_Material<_Index, T_Flont_Parameter, T_Remaining_Parameters...>::Get(int number)
//{
//	if(number)
//	{
//		return S_Material<_Index - 1, T_Remaining_Parameters...>::Get(number - 1);
//	}
//	return parameters;
//}
