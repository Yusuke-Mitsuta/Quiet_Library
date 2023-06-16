#pragma once
#include<concepts>

template <bool t_Fg>
concept Fg = t_Fg;

using std::same_as;

template <class _Ty1,class _Ty2>
concept not_same_as = !(same_as<_Ty1, _Ty2>);

using std::convertible_to;

template <class _From, class _To>
concept not_convertible_to = !(convertible_to<_From,_To>);

using std::derived_from;