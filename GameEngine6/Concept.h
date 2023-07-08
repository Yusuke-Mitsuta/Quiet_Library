#pragma once
#include<concepts>
#include<tuple>

template <bool t_Fg>
concept Fg = t_Fg;

using std::same_as;

template <class _Ty1,class _Ty2>
concept not_same_as = !(same_as<_Ty1, _Ty2>);

using std::convertible_to;

template <class _From, class T_To>
concept not_convertible_to = !(convertible_to<_From,T_To>);

using std::derived_from;

template <class _Derived, class _Base>
concept not_derived_from = !(derived_from<_Derived, _Base>);