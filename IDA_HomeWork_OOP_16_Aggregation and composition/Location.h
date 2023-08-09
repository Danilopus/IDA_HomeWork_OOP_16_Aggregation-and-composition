#pragma once
#include <vector>
#include "MotherPlant.h"
#include "Service functions.h"
#include "AppleTree.h"
#include "Raspberry_bush.h"
#include "BackPack.h"
#include "PearTree.h"

//#include "Fruit.h"




class Location_Player_Interface
{
public:
	virtual ~Location_Player_Interface() {}; // надо ли объявлять вирутальный деструктор при витруальном наследовании?
	virtual void ShowTrees() = 0;
	virtual void Get_fruit(int tree_index, BackPack_Player_Interface* back_pack) = 0;
};

class Location_TheGame_Interface
{
public:
	virtual ~Location_TheGame_Interface() {}; // надо ли объявлять вирутальный деструктор при витруальном наследовании?
	virtual MotherPlant* AddNewTree() = 0;
	virtual void DeleteTree() = 0;
};

class TreeLocation : virtual public Location_TheGame_Interface, virtual public Location_Player_Interface
{
	std::vector<MotherPlant*> _plants_list;
	int const TREES_MIN_RANDOM = 30; //по заданию 
	int const TREES_MAX_RANDOM = 100;
public:
	TreeLocation(int trees_number)
	{
		MotherPlant* new_tree = nullptr;
		for (int i = 0; i < trees_number; i++)
		{				
			new_tree = Get_Random_Tree();
			_plants_list.push_back(new_tree);
		}
	}
	TreeLocation()
	{
		int trees_number = Get_Random(TREES_MIN_RANDOM, TREES_MAX_RANDOM);
		for (int i = 0; i < trees_number; i++)
		{
			_plants_list.push_back(Get_Random_Tree());
		}
	}
	~TreeLocation()
	{
		for (int i = 0; i < _plants_list.size(); i++)
			delete _plants_list[i];
		_plants_list.clear();
	}

	MotherPlant* AddNewTree() override
	{		
		MotherPlant* new_tree = Get_Random_Tree();
		_plants_list.push_back(new_tree);
		return new_tree;
	}
	MotherPlant* Get_Random_Tree()
	{
		MotherPlant* new_tree = nullptr;
		int size = Get_Random(0, 3);
		Color parametr = static_cast<Color>(Get_Random(0, int(Color::_end_of_enum_)));
		size_t max_fruits = Get_Random(20 * (size + 1), 50 * (size + 1));
		int random_tree_choice = Get_Random(0, int(MotherPlant::treeTypes::_end_of_enum_));
		switch (random_tree_choice)
		{
		case 0:  new_tree = new AppleTree(size, parametr, max_fruits); break;
		case 1:  new_tree = new Raspberry_bush(size, parametr, max_fruits); break;
		case 2:  new_tree = new PearTree(size, parametr, max_fruits); break;
		}
		return new_tree;
	}
	void DeleteTree() override
	{
		_plants_list.pop_back();
	}
	void ShowTrees() override
	{
		for (int i = 0; i < _plants_list.size(); i++)
		{
			std::cout << "\nTree " << i + 1;
			std::cout << " " << _plants_list[i]->Get_Name();
			std::cout << " Fruits remain: " << _plants_list[i]->Get_fruits_remain();			
		}				
	}
	void Get_fruit(int tree_index, BackPack_Player_Interface* back_pack) override
	{
		if (tree_index <= _plants_list.size() && tree_index >= 0)
		{
			Fruit* new_fruit = _plants_list[tree_index]->Get_fruit();
			if (new_fruit) back_pack->AddItem(new_fruit);
		}
	}
	size_t size() { return _plants_list.size(); }

	void Info()
	{
		for (int i = 0; i < _plants_list.size(); i++)
		{
			std::cout << "\n\nTree " << i + 1;
			_plants_list[i]->Info();
		}
	}
	void Info_categorized()
	{
		//определяем какие есть в локации категории деревьев и сколько в каждой категории экземпляров
		std::map <std::string, int> ingroup_count;
		std::map <std::string, double> ingroup_fruits;

		double total_fruits = 0;

		for (int i = 0; i < _plants_list.size(); ++i)
		{
			++ingroup_count[_plants_list[i]->Get_Name()];
			ingroup_fruits[_plants_list[i]->Get_Name()] += _plants_list[i]->Get_fruits_remain();
			total_fruits += _plants_list[i]->Get_fruits_remain();

		}
		//выводим категорированную информацию о содержимом локации			
		for (auto iter = ingroup_count.begin(); iter != ingroup_count.end(); iter++)
		{
			std::cout << "\n" << iter->first << ": " << iter->second << "\tFruits: " << ingroup_fruits[iter->first];
		}
		std::cout << "\n\nTotal trees  " << _plants_list.size();
		std::cout << "\nTotal fruits " << total_fruits << "\n\n";
	}

	class iterator
	{
		//MotherPlant* _data_iterator; // так чот не очень работает
		MotherPlant** _data_iterator; // в предположении, что в итераторе должен быть тип указателя на тип основного класса, в нашем случае получается MotherPlant**

	public:
		//iterator() = default;
		iterator() = delete;
		iterator(MotherPlant** data) : _data_iterator(data) {}

		iterator& operator++()
		{
			_data_iterator++;
			return *this;
		}

		iterator& operator++(int)
		{
			iterator tmp(*this);
			_data_iterator++;
			return tmp;
		}

		iterator& operator--()
		{
			_data_iterator--;
			return *this;
		}

		iterator& operator--(int)
		{
			iterator tmp(*this);
			_data_iterator--;
			return tmp;
		}

		MotherPlant& operator*()
		{
			//return *_data_iterator;
			return **_data_iterator;
		}
		bool operator != (const iterator& obj)
		{
			return (this->_data_iterator != obj._data_iterator);
		}
		bool operator == (const iterator& obj)
		{
			return this->_data_iterator == obj._data_iterator;
		}

	};
	iterator begin() { return &_plants_list[0]; }
	iterator end() { return &_plants_list[0] + _plants_list.size(); }

	MotherPlant& operator [ ] (int index) { return *_plants_list[index]; }
	auto at(size_t index) const -> const MotherPlant&
	{
		return *_plants_list.at(index);
	}
	
	

};