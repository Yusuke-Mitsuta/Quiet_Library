#include"main.h"
#include<compare>

#include"Array.h"
#include"Function.h"
#include"Tuple.h"

#include"Output_Message.h"

#include"Array.h"

#include"Function.h"


#include<iostream>

#include"Function.h"
#include"Vector.h"
using namespace quiet;


#include<iostream>

#include"Function.h"
//#include"Vector.h"

using namespace quiet; 





int main()
{
    //Tuple vec2(2.0f, 3.0f);
    Vector2a vec2(2.0f, 3.0f);
    
    Vector3 vec3_0(1.0f, 2.0f, 3.0f);
    Vector3 vec3_1(1.0f,vec2);
    Vector3 vec3_2(vec2,3.0f);
    Vector3 vec3_3(vec3_0);
    return 0;
}