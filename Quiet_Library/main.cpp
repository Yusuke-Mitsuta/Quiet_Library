
#include"main.h"
#include"Tag.h"
#include"Vector.h"
#include"Tuple.h"
#include"Template_Control.h"
#include"Template_Class_Change.h"
#include"Change_Tuple.h"
#include<tuple>

using namespace quiet;

int main()
{
    
    using T = tuple_t<int, float>::next;
    using TT= N_Tuple::U_Change<T, double, 1>;



    //using T = N_Tuple::U_Change_Tuple_t<tuple_v<0, 1, 2>>;

    std::cout << typeid(TT).name();

    return 0;
}