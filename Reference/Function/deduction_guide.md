### [README](../../README.md)/[quiet](../quiet.md)/[Function](Function.md)/推論補助

# quiet::Function::推論補助
``` C++
template<class T_Front_Parts, class ...T_Parts>
Function(T_Front_Parts&&, T_Parts&&...) -> Function<
	typename quiet::N_Function::I_Function_Helper<T_Front_Parts, T_Parts...>::judge, T_Parts...>;
```

## 概要
受け取った引数の型から[Function::constructor](constructor.md)が呼び出せるか判定する
不可な場合先頭の型が[invalid_t](../invalid_t.md)となり[Function](Function.md)の**コンセプトがエラー**となる。
***
## 例
```　C++
#include"Function.h"
using namespace quiet;
struct My_Class
{
    void Args_int3(int x, int y, int z);
    void Args_int2(int x, int y);
};

void Args_int3(int x, int y, int z);
void Args_int2(int x, int y);

int main()
{
    Function fn_int3_1(&Args_Int_3);
    Function fn_int3_2(&Args_Int_3, 1);
    Function fn_int3_3(&fn_int3_2, 2);
    //Function fn_int3_4(&Args_Int_3, 1,2,3,4);
    //Function fn_int3_4(&Args_Int_3, std::string{});
    Function fn_3(fn_int3_1, fn_int3_2, fn_int3_3);

    My_Class* p = new My_Class();

    Function fn_int2_Class(&My_Class::Args_int2);
    Function fn_int2_Class_p_1(p, &My_Class::Args_int2);
    //Function fn_int2_Class_p_2(new int(0), &My_Class::Args_int2);
    Function fn_int23_Class_p(p, &My_Class::Args_int2, &My_Class::Args_int3);
    return 0;
}
```
***
## 関連
[Function](Function.md) 
[Function::constructor](constructor.md) 