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
	virtual void DeleteItem(size_t) = 0;
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

	// это закрытая функция, возможности стирать произволную строчку не будет, только через вызов с enum fruitTypes
	void DeleteItem(std::string type)
	{
		//for (auto iter : _items_list)
		for (int i=0; i< _items_list.size(); ++i)
		{
			if (_items_list[i]->Get_name() == type)
			{
				delete _items_list[i]; // удаляем объект из кучи, перед удалением указателя из вектора
				_items_list.erase(_items_list.begin() + i);
				--i; // изза erase все элементы сдвигаются и надо еще раз проверить i-ый
			}
		}
	}
public:

	BackPack() {};

	//void AddItem(const Fruit& new_fruit) override
	void AddItem(Fruit* new_fruit) override
	{
	if(new_fruit) _items_list.push_back(new_fruit);
	//if (!new_fruit) _items_list.emplace_back(new_fruit);
	}
	void DeleteItem(size_t index) override
	{
		if (index < 0 || index >= _items_list.size()) assert(true && "Deleting index out of range");
		delete _items_list[index];
		_items_list.erase(_items_list.begin() + index);		
	}
	void DeleteItem(size_t begin_index, size_t end_index)
	{
		if (begin_index < 0 || begin_index >= _items_list.size()) assert(true && "Deleting index out of range");
		if (end_index < 0 || end_index >= _items_list.size()) assert(true && "Deleting index out of range");
		if (begin_index > end_index) std::swap(begin_index, end_index);
		
		for (int i = begin_index; i < end_index; ++i)
			delete _items_list[i];

		_items_list.erase(_items_list.begin() + begin_index, _items_list.begin() + end_index);
	}
	void DeleteItem(Fruit::fruitTypes type)
	{
		switch (type)
		{
		case Fruit::fruitTypes::Apple:
			DeleteItem("Apple"); break;
		case Fruit::fruitTypes::Raspberry:
			DeleteItem("Raspberry"); break;
		case Fruit::fruitTypes::Pear:
			DeleteItem("Pear"); break;
		}		
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
		 AddItem(&new_fruit);
	 }

	 Fruit* operator [] (int index)
	 {
		 if (index < 0 || index >= _items_list.size()) assert(true && "Index out of range");
		 return _items_list[index];
	 }
	 size_t size() { return _items_list.size(); }
	 auto at(size_t index) const -> Fruit&
	 {
		 return *_items_list.at(index);
	 }

	 class iterator
	 {
		 Fruit** _data_iterator; // в предположении, что в итераторе должен быть тип указателя на тип основного класса

	 public:
		 iterator() = delete;
		 iterator(Fruit** data) : _data_iterator(data) {}

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

		 Fruit& operator*()
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
	 iterator begin() { return &_items_list[0]; }
	 iterator end() { return &_items_list[0] + _items_list.size(); }


};