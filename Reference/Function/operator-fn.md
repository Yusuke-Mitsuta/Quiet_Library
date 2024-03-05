### [README](../../README.md)/[quiet](../quiet.md)/[Function](Function.md)/operator()

# quiet::Function::operator()
``` C++
constexpr auto operator()( T_request_args... args);

constexpr auto operator()(T_request_pointer* p, T_request_args... args);

template<class ...T_Args>				
    requires is_invalid_not<function_operator_search<T_Args...>>
constexpr auto operator()(T_Args... args);
```

## 概要
関数オブジェクト、引数から適切な`operator()`を定義する
***
## 仕様
1. バインドしている値から、残りの要求するを受け取る`operator()`を定義する
2. [Apply](../Tuple/N_Tuple/Apply.md)と同条件で、要求する引数を判定する`operator()`を定義する
***
## 例

#### 複数の関数オブジェクトの使い分け
```　C++
#include"Function.h"
using namespace quiet;
void Args_Int_3(int x, int y, int z)
{
	std::cout << "x = " << x<<  " , y = " << y << " , z = " << z << std::endl;
}

int main()
{
  Function fn_int3_1(&Args_Int_3);
  fn_int3_1(1, 2, 3);

  Function fn_int3_2(&Args_Int_3, 10);
  fn_int3_2(2, 3);

  Function fn_int3_3(&fn_int3_2, 20);
  fn_int3_3(3);
  std::cout << std::endl;

  Function fn_3(fn_int3_1, fn_int3_2, fn_int3_3);
  fn_3(0);
  fn_3(0, 0);
  fn_3(0, 0, 0);  
  
  return 0;
}
```
###### 出力
 ```　C++
x = 1 , y = 2 , z = 3
x = 10 , y = 2 , z = 3
x = 10 , y = 20 , z = 3

x = 10 , y = 20 , z = 0
x = 10 , y = 0 , z = 0
x = 0 , y = 0 , z = 0
 ```
***
#### 参照、ポインターによる値変更
 ```　C++
#include"Array.h"
#include"Function.h"
using namespace quiet;
void Args_Int_3_ref(int& x, int& y, int z)
{
	x++;
	y+=10;
    z+=100;
}
void Args_Int_3_p(int* x, int* y, int* z)
{
	(*x)++;
	(*y) += 10;
	(*z) += 100;
}

int main()
{
  int x = 0;
  int y = 0;
  int z = 0;

  Function fn_int3_ref_1(&Args_Int_3_ref, x);
  fn_int3_ref_1(y, z);
  std::cout << "x = " << x << " , y = " << y << " , z = " << z << std::endl;

  Function fn_int3_p(&Args_Int_3_p);
  Array<int*, 3> ary_int3_p(&x, &y, &z);
  fn_int3_p(ary_int3_p);
  std::cout << "x = " << x << " , y = " << y << " , z = " << z << std::endl;
  return 0;
}
```
 ###### 出力
```　C++
x = 1 , y = 10 , z = 0
x = 2 , y = 20 , z = 100
```
***

#### メンバー関数の呼び出し
```　C++
#include"Function.h"
using namespace quiet;
struct My_Class
{
	void Args_int3(int x, int y, int z);
	void Args_int2(int x, int y);
};
void My_Class::Args_int3(int x, int y, int z)
{
	std::cout << "My_Class::Args_int3" << std::endl;
}
void My_Class::Args_int2(int x, int y)
{
	std::cout << "My_Class::Args_int2" << std::endl;
}

void Args_int3(int x, int y, int z)
{
	std::cout << "Args_int3" << std::endl;
}
void Args_int2(int x, int y) 
{
	std::cout << "Args_int2" << std::endl;
}

int main()
{
	My_Class* p = new My_Class();

	Function fn_int2(&My_Class::Args_int2);
	Function fn_int2_p(p, &My_Class::Args_int2);
	fn_int2(p, 0, 1);
	fn_int2_p(0, 1);

	std::cout << std::endl;

	Function fn_int3_2(p, &My_Class::Args_int2, &My_Class::Args_int3);
	fn_int3_2(0, 0, 0);
	fn_int3_2(0, 0);

	std::cout << std::endl;

	Function fn_int3_3(&My_Class::Args_int2, &Args_int2, &My_Class::Args_int3, &Args_int3);
	fn_int3_3(p, 0, 0);
	fn_int3_3(0, 0);
	fn_int3_3(p, 0, 0, 0);
	fn_int3_3(0, 0, 0);

	delete p;
	return 0;
}
```
 ###### 出力
```　C++
My_Class::Args_int2
My_Class::Args_int2

My_Class::Args_int3
My_Class::Args_int2

My_Class::Args_int2
Args_int2
My_Class::Args_int3
Args_int3
```
***
## 関連
[Function](Function.md)	
[Apply](../Tuple/N_Tuple/Apply.md)	