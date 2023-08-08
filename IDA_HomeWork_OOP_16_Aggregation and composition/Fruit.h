#pragma once
#include <string>
#include <iostream>
#include "Base_Fruit.h"


enum class Color { red, green, yellow, black, brown, white, _end_of_enum_ };


class Fruit : public Base_Fruit
{
protected:
	std::string _name;
	float _weight = 0; //kg
	Color _color  = Color::black;
public:
	Fruit(std::string name, float weight, Color color) : _name(name), _weight(weight), _color(color) {}
	//Fruit() = delete;
	//Fruit() = default;
	//Fruit();
	//Fruit(const Fruit& fruit) = default;
	//Fruit(Fruit& fruit) = default;
	//Fruit(Fruit&&) = default;
	//Fruit(Fruit&);
	//Fruit(Fruit&&);
	//Fruit(Fruit&) = default;
	//Fruit(const Fruit& fruit) {}
	//Fruit(const Fruit& fruit) {}
	//Fruit(Fruit& fruit) {}

	//virtual ~Fruit();
	virtual ~Fruit() {};

	//Как еще можно запретить создание экземпляров класса, не делая класс абстрактным?
	// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	// В данном конкретном проекте я бы сделал Fruit абстрактным, чтобы не было возможности созавать такие неопределенные объекты, 
	// но возникают ошибки с unique_ptr
	//std::string Get_name() override = 0;

	std::string Get_name() { return Fruit::_name; }
	float Get_weight() override { return _weight; }	
	int Get_color() { return int(_color); }

	virtual void Info()
	{
		std::cout << "\n_name   " << _name;
		std::cout << "\n_weight " << _weight;
		std::cout << "\n_color  " << int(_color);
	}

};