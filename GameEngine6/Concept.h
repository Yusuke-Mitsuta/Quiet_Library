#pragma once
#include<concepts>
#include<tuple>

template <bool t_Fg>
concept Fg = t_Fg;

using std::same_as;

template <class _Ty1,template<class...>class _Ty2>
struct template_class_concept;

template <class _Ty1,class _Ty2>
concept not_same_as = !(same_as<_Ty1, _Ty2>);

using std::convertible_to;

template <class _From, class T_To>
concept not_convertible_to = !(convertible_to<_From,T_To>);

using std::derived_from;

template <class _Derived, class _Base>
concept not_derived_from = !(derived_from<_Derived, _Base>);

using std::constructible_from;

template <class _Ty1, template<class...>class _Ty2>
struct template_class_concept;


template <template<class...>class _Ty1, class ..._Ty1_Inner, template<class...>class _Ty2>
struct template_class_concept<_Ty1<_Ty1_Inner...>,_Ty2>
{
	using T1 = _Ty1<_Ty1_Inner...>;
	using T2 = _Ty1<_Ty1_Inner...>;

	static constexpr bool same_as = std::same_as <T1, T2>;
	static constexpr bool convertible_to = std::convertible_to <T1, T2>;

};

template <class _Ty1,template<class...> class _Ty2>
concept same_as_template_class = (template_class_concept<_Ty1, _Ty2>::same_as);

template <class _Ty1, template<class...> class _Ty2>
concept convertible_to_template_class = (template_class_concept<_Ty1, _Ty2>::convertible_to);