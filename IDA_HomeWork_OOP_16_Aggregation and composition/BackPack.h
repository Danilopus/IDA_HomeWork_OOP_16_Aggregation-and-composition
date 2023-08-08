#pragma once
#include "Fruit.h"
#include <memory>
#include <vector>
#include <cassert>
#include <map>

class BackPack_Player_Interface
{
public:
	virtual ~BackPack_Player_Interface() = default;
	//virtual void AddItem(const Fruit& new_fruit) = 0;
	virtual void AddItem(Fruit* new_fruit) = 0;
	virtual void DeleteItem() = 0;
	virtual void Info() = 0;
	virtual void operator << (const Fruit& new_fruit) = 0;
	virtual void operator << (Fruit& new_fruit) = 0;

};


class BackPack_TheGame_Interface
{
public:
	virtual ~BackPack_TheGame_Interface() = default;
	virtual void Info() = 0;
};


class BackPack : virtual public BackPack_Player_Interface, virtual public BackPack_TheGame_Interface
{
	//std::vector<std::unique_ptr<Fruit>> _items_list;
	std::vector<Fruit*> _items_list;

public:

	BackPack() {};

	//void AddItem(const Fruit& new_fruit) override
	void AddItem(Fruit* new_fruit) override
	{
	if(new_fruit) _items_list.push_back(new_fruit);
	//if (!new_fruit) _items_list.emplace_back(new_fruit);
	}

	void DeleteItem() override
	{
		_items_list.pop_back();
	}

	void Info() override
	{
		if (_items_list.size() == 0)
		{
			std::cout << "No items";
			return;
		}
		for (int i = 0; i < _items_list.size(); i++)
		{
			std::cout << "\n\nItem " << i + 1;
			_items_list[i]->Info();
		}
	}
	void ShortInfo()
	{
		//определяем какие есть в рюкзаке категории и сколько в каждой категории экземпляров
		std::map <std::string, int> ingroup_count;
		std::map <std::string, double> ingroup_weight;

		double total_weight = 0;
		for (int i = 0; i < _items_list.size(); ++i)
		{
			++ingroup_count[_items_list[i]->Get_name()];
			ingroup_weight[_items_list[i]->Get_name()] += _items_list[i]->Get_weight();
			total_weight += _items_list[i]->Get_weight();
		}
		//выводим категорированную информацию о содержимом рюкзака			
		for (auto iter = ingroup_count.begin(); iter != ingroup_count.end(); iter++)
		{
			std::cout << iter->first << ": " << iter->second << "\t weight: " << ingroup_weight[iter->first] << " kg\n";
		}
		std::cout << "\nTotal items  " << _items_list.size();
		std::cout << "\nTotal weight " << total_weight << " kg";

	}

	 void operator << (const Fruit& new_fruit) override
	{		 
		//_items_list.push_back(std::make_unique<Fruit>(std::move(new_fruit)));
		 assert(true);
	}
	 void operator << (Fruit& new_fruit) 
	 {
		// _items_list.push_back(std::make_unique<Fruit>(std::move(new_fruit)));
		// _items_list.push_back(&new_fruit);
		 _items_list.emplace_back(&new_fruit);
	 }

};