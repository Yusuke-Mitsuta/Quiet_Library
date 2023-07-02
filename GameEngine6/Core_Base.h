#pragma once
#include"Core_Name.h"


namespace N_Core_Control
{
	class Parentage;
}

template<Core_Name className="Base">
class Core
{
protected:

public:

	virtual N_Core_Control::Parentage* Get_Parentage()=0;

	template<N_Constexpr::String order>
	void Order();

	//virtual void Order(N_Constexpr::String order) {}


	virtual void Order() {}

	template<>
	constexpr void Order<"Start">() { Start(); }

	template<>
	constexpr void Order<"Update">() { Update(); }

	template<>
	constexpr void Order<"Draw">() { Draw(); }

	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}

};

template<Core_Name className>
template<N_Constexpr::String order>
inline void Core<className>::Order()
{
	Order();
}



