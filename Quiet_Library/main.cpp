#include<compare>

#include"Array.h"
#include"Float3.h"
#include"Tuple.h"
#include"Vector.h"
#include"Function.h"

int main()
{
    quiet::Array float3(1.0f, 2.0f, 3.0f);
    quiet::Array float2(1.0f, 2.0f);

    Vector3 vec3(1.0f, 2.0f, 3.0f);

    quiet::Function fn(&Output);
    
    quiet::Array<float, 0> ary_0 = {};
    quiet::Array<float, 1> ary_1 = {3.0f};


    //quiet::N_Tuple::I_Calculation<quiet::Array<float, 3>, quiet::Array<float, 3>>::type::Sum(float3, float3);

    float3 += float3;



    fn(float3);

    fn(3, 4, 5);

    fn(3, float2);

    fn(3, float2);

    return 0;
}