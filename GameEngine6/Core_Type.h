
#include"Core_Base.h"
#include"Concept.h"

enum class E_Core_Type
{
	Engine,
	Scene,
	Object,
	Component
}; 

template<class T>
constexpr E_Core_Type Select_Core_Type()
{
	if (derived_from<T,Core<"Scene">>)
	{
		return E_Core_Type::Scene;
	}

	if (derived_from<T,Core<"Object">>)
	{
		return E_Core_Type::Object;
	}

	return E_Core_Type::Component;
}