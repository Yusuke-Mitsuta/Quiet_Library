### [README](../../README.md)/[quiet](../quiet.md)/[Function](Function.md)/constructor

# quiet::Function::constructor

``` C++
template<class MT_Front_Parts, class ...MT_Parts>
constexpr Function(MT_Front_Parts && front_parts, MT_Parts&&... fn_Parts)
    :N_Function::I_Function_Operator<T_Front_Parts, T_Parts...>::type
    (std::forward<MT_Front_Parts>(front_parts),
    std::forward<MT_Parts>(fn_Parts)...)
    {}
```

## 仕様
####`Function`の引数は以下の様に定義される
1.受け取る全ての関数オブジェクトに適応されるクラスポインター
2.関数オブジェクト
3.`2`で受け取る関数オブジェクトに対する、バインドを実施する引数
4.次に受け取る関数オブジェクトに適応されるクラスポインター
**以後2~4の繰り返し**
***
## 備考
1.関数オブジェクトに対する、ポインター、引数は省くことが出来る
2.`3`でバインドされる引数は、関数の前から順番に設定される
3.引数の判定に関しては、[Apply](../Tuple/N_Tuple/Apply.md)と同条件である
***
## 例

#### 複数の関数オブジェクトの使い分け
```　C++
void Args_Int_3(int x, int y, int z);
struct My_Class
{
	void Args_int3(int x, int y, int z);
	void Args_int2(int x, int y);
};
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
    delete p;
    return 0;
}
```
## 関連
[Function](Function.md) 
[Function::推論補助](deduction_guide.md)   