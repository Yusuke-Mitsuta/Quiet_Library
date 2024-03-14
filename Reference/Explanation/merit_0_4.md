### [README](../../README.md)/[quietを利用するメリット](merit_0_0.md)/関数の引数に互換性を持たせる場合

***
## [ quiet::Function ]内での型変換について

6. 先ほどは整数型を例にしましたが**ユーザー定義型**等、他の型であっても`std::convertible_to<_Ty1,_Ty2>`が`true`であれば同様に使用できます。


``` C++
#include"Quiet_Library.h"

struct Class_A {};

struct Class_B :
    Class_A {};

struct Class_C
{
    operator Class_A()
    {
        return Class_A{};
    }
};

void Hoge_A(Class_A a) {}

void Hoge_B(Class_B a) {}

void Hoge_C(Class_C a) {}

int main()
{
    Class_A a;
    Class_B b;
    Class_C c;

    quiet::Function fn_A(&Hoge_A);
    fn_A(a);
    fn_A(b);
    fn_A(c);

    quiet::Function fn_B(&Hoge_B);
    //fn_B(a); //[Class_A]から[Class_B]は変換不可の為
    fn_B(b);
    //fn_B(c); //[Class_C]から[Class_B]は変換不可の為

    quiet::Function fn_C(&Hoge_C);
    //fn_C(a); //[Class_A]から[Class_C]は変換不可の為
    //fn_C(b); //[Class_B]から[Class_C]は変換不可の為
    fn_C(c);

    return 0;
}
``` 
要するにキャストが可能であれば、引数に取ることが出来ます。

## [Back](merit_0_2.md)　[Home](merit_0_0.md)
