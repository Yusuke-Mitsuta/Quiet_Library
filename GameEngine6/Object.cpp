#include "Object.h"

S_MoveTupleInnerType<FunctionMultiple, std::tuple<decltype(&Core<"Object">::Test)>>::Type Core<"Object">::aaa = { &Core<"Object">::Test };
