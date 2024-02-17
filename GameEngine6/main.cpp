#include"main.h"
#include<compare>
#include<initializer_list>
#include<iostream>

#include"Array.h"
#include"Function.h"
#include"Tuple.h"

#include"Output_Message.h"

#include"Test_Code.h"

int main()
{
	Test_Code::Array_Test();

	Test_Code::Function_Test();


	_CrtDumpMemoryLeaks();
	return 0;
}