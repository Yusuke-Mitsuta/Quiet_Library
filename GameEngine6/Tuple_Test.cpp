#include "Tuple_Test.h"
#include"main.h"

#include"Quick_Sort.h"

#include"If_Type.h"

using namespace N_Tuple;

using Tuple_v5 = tuple_v<0, 1, 2, 3, 4>;

using Tuple_vp5 = U_Create_p<Tuple_v5>;

using Tuple_t5 = tuple_t<char, short, int, float, double>;

using Tuple_tp5 = U_Create_p<Tuple_t5>;

template<N_Constexpr::String t_operator>
using Tuple_Calculate = I_Tuple_Calculate<Tuple_v5, t_operator, 5>;

template<int n>
using Tuple_Select = U_Select<n, Tuple_v5>;

template<int n>
using Tuple_Range = U_Range<Tuple_vp5, n>;

namespace N_Tuple::Test
{

	template<class T,class ...T1>
	struct MyStruct
	{

		using type = T;
	};



}


void Tuple_Test()
{

	////TYPE_ID(Tuple_t5);
	////TYPE_ID(Tuple_v5);
	////TYPE_ID(Tuple_tp5);
	//TYPE_ID(Tuple_vp5);
	//TYPE_ID(Tuple_vp5::Next);
	//TYPE_ID(Tuple_vp5::Next::Next);
	//TYPE_ID(Tuple_vp5::Next::Next::Next);
	//TYPE_ID(Tuple_vp5::Next::Next::Next::Next);
	//TYPE_ID(Tuple_vp5::Next::Next::Next::Next::Next);
	//TYPE_ID(Tuple_vp5::Next::Next::Next::Next::Next::Next);
	//TYPE_ID(Tuple_vp5::Back);
	//TYPE_ID(Tuple_vp5::Back::Prev);
	//TYPE_ID(Tuple_vp5::Back::Prev::Prev);
	//TYPE_ID(Tuple_vp5::Back::Prev::Prev::Prev);
	//TYPE_ID(Tuple_vp5::Back::Prev::Prev::Prev::Prev);
	//TYPE_ID(Tuple_vp5::Back::Prev::Prev::Prev::Prev::Prev);
	//TYPE_ID(Tuple_vp5::Back::Prev::Prev::Prev::Prev::Prev::Prev);
	//TYPE_ID(Tuple_vp5::Back::Prev::Prev::Prev::Prev::Prev::Prev::Flnot);

	//std::cout << std::endl;
	//TYPE_ID(Tuple_Select<-1>);
	//TYPE_ID(Tuple_Select<0>);
	//TYPE_ID(Tuple_Select<1>);
	TYPE_ID(Tuple_Select<2>);
	//TYPE_ID(Tuple_Select<3>);
	//TYPE_ID(Tuple_Select<4>);
	//TYPE_ID(Tuple_Select<5>);

	//std::cout << std::endl;
	//
	//using Tuple_merge = U_Merge<Tuple_Select<3>, Tuple_t5>;
	//TYPE_ID(Tuple_merge);

	//using Tuple_insert = U_Insert<Tuple_Select<3>, Tuple_t5>;
	//TYPE_ID(Tuple_insert);
	//std::cout << std::endl;
	//using Tuple_v_merge = U_Merge<Tuple_Select<3>, Tuple_v5>;
	//TYPE_ID(Tuple_v_merge);

	//using Tuple_v_insert = U_Insert<Tuple_Select<3>, Tuple_v5>;
	//TYPE_ID(Tuple_v_insert);

	//std::cout << std::endl;

	//using remove_t = U_Remove_p<Tuple_tp5>;
	//TYPE_ID(remove_t);
	//using remove_v = U_Remove_p <Tuple_vp5 > ;
	//TYPE_ID(remove_v);

	std::cout << std::endl;

	using range = N_Tuple::U_Range<Tuple_tp5, 2, 4>;



	TYPE_ID(range);


	std::cout << std::endl;
	TYPE_ID(Tuple_Calculate<"+">::type);
	TYPE_ID(Tuple_Calculate<"-">::type);
	TYPE_ID(Tuple_Calculate<"*">::type);
	TYPE_ID(Tuple_Calculate<"/">::type);

	









	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
	

}
