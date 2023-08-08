#pragma once

#include "Fruit.h"

class Base_MotherPlant
{
public:
	virtual ~Base_MotherPlant() = default;	
	virtual int Get_size() = 0;
	virtual int Get_color() = 0;
	virtual int Get_max_fruits() = 0;
	virtual Fruit* Get_fruit() = 0;


};

