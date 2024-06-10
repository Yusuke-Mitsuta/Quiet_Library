
#include"main.h"
#include"Tag.h"
#include"Vector.h"
#include"Tuple.h"
#include"Template_Control.h"
#include"Template_Class_Change.h"
#include"Change_Tuple.h"
#include"Change_Tuple_Action_Helper.h"
#include<tuple>

using namespace quiet;

#include"Change_Tuple_Action_Helper.h"

int main()
{
    using T = N_Tuple::N_Tuple_Convert_Action::I_Tuple_Convert_Action_Helper::L_Target::Target_Tuple_t::Return_Convert_Skip::Set_StartPoint

    using Tuple_t = tuple_t<int>;
    
    //using T = N_Tuple::U_Change_Tuple_t<tuple_v<0, 1, 2>>;

    std::cout << typeid(T).name();

    return 0;
}