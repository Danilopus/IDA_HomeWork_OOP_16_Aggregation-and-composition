#pragma once
#include <string>
#include <iostream>
//#include "Fruit.h"
#include "Base_MotherPlant.h"

class MotherPlant : public Base_MotherPlant
{
protected:
	enum plant_size { smalll, medium, tall } _size;
	Color _color;
	size_t _max_fruits;

public:
	enum class treeTypes { AppleTree, Raspberrybush, PearTree, _end_of_enum_ }; //для целей учета сколько у нас всего классов деревьев

	//MotherPlant(plant_size size, Color plant_color, size_t max_fruits): _size(size), _color(plant_color), _max_fruits(max_fruits){}
	MotherPlant(size_t size, Color plant_color, size_t max_fruits) : _size(plant_size(size)), _color(plant_color), _max_fruits(max_fruits) {}
	virtual ~MotherPlant() {}

	//int Get_size() override { return int(_size); }
	int Get_size() override = 0;
	int Get_color() override { return int(_color); }
	int Get_max_fruits() override { return _max_fruits; }

	virtual void Info()
	{
		std::cout << "\n_size " << _size;
		std::cout << "\n_color " << int(_color);
		std::cout << "\n_max_fruits " << _max_fruits;
	}
	virtual void Info() const
	{
		std::cout << "\n_size " << _size;
		std::cout << "\n_color " << int(_color);
	}

	//virtual Fruit* Get_fruit() = 0;
	Fruit* Get_fruit() override = 0;

	virtual size_t Get_fruits_remain() = 0;
	virtual std::string Get_Name() = 0;


	friend std::ostream& operator << (std::ostream& out, const MotherPlant& MotherPlant_obj)
	{
		out << "\n_size " << MotherPlant_obj._size;
		out << "\n_color " << int(MotherPlant_obj._color);
		out << "\n_max_fruits " << MotherPlant_obj._max_fruits;
		return out;
	}

};