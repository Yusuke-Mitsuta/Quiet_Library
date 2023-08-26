#pragma once
#include<concepts>
#include<tuple>

template <bool t_Fg>
concept Fg = t_Fg;

template <template<class...>class T_Concept>
concept is_Concept = requires
{
	T_Concept<int, int>::Concept;
};

using std::same_as;

template <class _Ty1, class _Ty2>
struct same_as_S
{
	static constexpr bool Concept = same_as<_Ty1, _Ty2>;
};

template <class _Ty1,template<class...>class _Ty2>
struct template_class_concept;

template <class _Ty1,class _Ty2>
concept not_same_as = !(same_as<_Ty1, _Ty2>);

template <class _Ty1, class _Ty2>
struct not_same_as_S
{
	static constexpr bool Concept = !same_as<_Ty1, _Ty2>;
};

using std::convertible_to;


template <class _To,class _From>
concept convertible_from = convertible_to<_From, _To>;

template <class _To,class _From>
concept not_convertible_from = !convertible_to<_From, _To>;

template <class _From, class _To>
struct convertible_to_S
{
	static constexpr bool Concept = convertible_to<_From, _To>;
};

template <class _From, class T_To>
concept not_convertible_to = !(convertible_to<_From,T_To>);

template <class _From, class _To>
struct not_convertible_to_S
{
	static constexpr bool Concept = !convertible_to<_From, _To>;
};

using std::derived_from;

template <class _Derived, class _Base>
concept not_derived_from = !(derived_from<_Derived, _Base>);

using std::constructible_from;

template <class T>
concept is_pointer = std::is_pointer_v<T>;

template <class T>
concept not_is_pointer = !std::is_pointer_v<T>;

template <class T>
concept is_reference = std::is_reference_v<T>;

template <class T>
concept not_is_reference = !std::is_reference_v<T>;

template <class T>
concept is_member_function_pointer = std::is_member_function_pointer_v<T>;

template <class _Ty1, template<class...>class _Ty2>
struct template_class_concept;

//仕様
//テンプレートを持つクラスのアウタークラスを比較する
template <template<class...>class _Ty1, class ..._Ty1_Inner, template<class...>class _Ty2>
struct template_class_concept<_Ty1<_Ty1_Inner...>,_Ty2>
{
	using T1 = _Ty1<_Ty1_Inner...>;
	using T2 = _Ty1<_Ty1_Inner...>;

	static constexpr bool same_as = std::same_as <T1, T2>;
	static constexpr bool convertible_to = std::convertible_to <T1, T2>;

};

//仕様
//テンプレートを持つクラスのアウタークラスを[same_as]で判定する
template <class _Ty1,template<class...> class _Ty2>
concept same_as_template_class = (template_class_concept<_Ty1, _Ty2>::same_as);

//仕様
//テンプレートを持つクラスのアウタークラスを[convertible_to]で判定する
template <class _Ty1, template<class...> class _Ty2>
concept convertible_to_template_class = (template_class_concept<_Ty1, _Ty2>::convertible_to);

template <class _Ty1, template<class...> class _Ty2>
concept not_convertible_to_template_class = !(template_class_concept<_Ty1, _Ty2>::convertible_to);