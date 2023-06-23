#pragma once

class A {};

template<char c>
class Name
{


};

template<>
class Name<'A'>
{
	using _char = A;
};