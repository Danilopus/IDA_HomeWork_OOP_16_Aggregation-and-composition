#pragma once
#include <string>

class Base_Fruit
{
public:
	virtual ~Base_Fruit() = default;
	virtual std::string Get_name() = 0;
	virtual float Get_weight() = 0;
	virtual int Get_color() = 0;
};

