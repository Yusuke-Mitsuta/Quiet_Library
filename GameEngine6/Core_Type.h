
#include"Concept.h"
#include"Core_Base.h"


enum class E_Core_Type
{
	Engine,
	Scene,
	Object,
	Component
}; 

template<class T>
requires derived_from<T,Core<"Scene">>
E_Core_Type Select_Type();

template<class T>
inline E_Core_Type Select_Type()
{
	return E_Core_Type::Scene;
}
