#pragma once

#include "Fruit.h";


class Pear : public Fruit
{
public:
	Pear(float weight, Color color) : Fruit("Pear", weight, color) {}

	std::string Get_name() { return Fruit::Get_name(); }
	//std::string Get_name() { return Fruit::_name; }
	//auto Get_name() -> std::string { return _name; } // tail

	float Get_weight() override { return _weight; }
	int Get_color() { return int(_color); }

};