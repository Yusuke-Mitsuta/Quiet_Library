#pragma once

#include "Tuple_Declare.h"

template<is_invalid_not T_Front_Parts, class ...T_Parts>
class Function;

template <typename _Ty1, size_t N>
class Array;

namespace N_Tuple::N_Apply {

    enum class E_Type {
        NONE,
        FN,
        ARRAY,
        CLASS,
        CLASS_NEW,
    };

    template <typename T>
    struct S_Select_Type : std::integral_constant<E_Type, E_Type::NONE> {};

    template <typename T>
        requires std::is_class<T>::value
    struct S_Select_Type<T> : std::integral_constant<E_Type, E_Type::CLASS> {};

    template <typename T>
    struct S_Select_Type<T*> : std::integral_constant<E_Type, E_Type::CLASS_NEW> {};

    template <typename T>
    struct S_Select_Type<T&> : S_Select_Type<T> {};

    template <typename T, size_t N>
    struct S_Select_Type<T[N]> : std::integral_constant<E_Type, E_Type::ARRAY> {};

    template <typename T>
        requires is_function_pointer<T>
    struct S_Select_Type<T> : std::integral_constant<E_Type, E_Type::FN> {};

    template <typename... T_Parts>
    struct S_Select_Type<Function<T_Parts...>> : std::integral_constant<E_Type, E_Type::FN> {};

    template <typename T>
    inline constexpr E_Type Select_Type_v = S_Select_Type<T>::value;

    template <typename T, E_Type t_type>
    concept is_apply_type = (t_type == S_Select_Type<T>::value);

}
