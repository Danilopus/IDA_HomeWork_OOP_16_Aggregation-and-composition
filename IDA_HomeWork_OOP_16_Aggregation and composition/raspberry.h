#pragma once
#include "Fruit.h";


class raspberry : public Fruit
{
public:
	raspberry(float weight, Color color) : Fruit("Raspberry", weight, color) {}
	
	std::string Get_name() { return Fruit::_name; }
	float Get_weight() override { return _weight; }
	int Get_color() { return int(_color); }
};