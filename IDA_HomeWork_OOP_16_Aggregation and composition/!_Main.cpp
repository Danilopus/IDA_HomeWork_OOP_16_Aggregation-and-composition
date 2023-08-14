// HomeWork template project v 6.0 // 27.06.2023 //

/*

Наследование - Композиция, Агрегация

Задание на композицию

Для реализованных семейств классов Растений и Плодов создать классы - контейнеры:

Локация:
- при создании создаёт внутри себя от 30 до 100 различных объёктов
- наследников растений хранящихся в одной коллекции;
- позволяет пользователю узнавать скольно ростений есть на локации
- позволяет пользователю перебрать все растения для сбора с них плодов

Рюкзак:
- позволяет хранить в себе любых наследников класса Плоды
- позволяет пользователю перебрать своё содержимое
- при необходимости должен быть механизм изъятия любого плода из рюкзака

В функции мэйн продемонстрируйте возможность сбора пользователем всех плодов со всех
деревьев с локации и последующую работу с рюкзаком в виде сообщения об общем
количестве плодов и их суммарном весе. 
Показать что если выкинуть из рюкзака все плоды
какого либо типа результат предыдущего алгоритма изменяется.

*/

#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <algorithm>
#include <conio.h>
//My own headers
#include "Service functions.h"
#include "MainMenu.h"
#include "Location.h"
#include "BackPack.h"



// Homework OOP 16 ----------------------------------------------------	


//Task 1 Location
void Task_1(std::string name_of_task)
{	
	do
	{		
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";					
	
		//создаем локацию с от 30 до 100 рандомными деревьями		
		TreeLocation Location_1;				
		
		//Получим категоризированную сводку по локации
		std::cout << "\n--- Location_1.Info_categorized():\n";
		Location_1.Info_categorized();
		//Это  короткая сводка, вообще еще есть две по степени детализации:
		//Location_1.Info(); // полная сводка по каждому дереву
		//Location_1.ShowTrees(); // краткая сводка по каждому дереву
						
		
		// Перебор деревьев

		// Способ 1 - []
		std::cout << "\n\n--- iterating through the elements []:\n";
		for (int i = 0; i < Location_1.size(); ++i)
			std::cout << Location_1[i].Get_Name() << " | ";

		// Способ 2 - iterator
		std::cout << "\n\n--- iterating through the iterator:\n";
		for (auto iter = Location_1.begin(); iter != Location_1.end(); iter++)
			std::cout << (*iter).Get_Name() << " | ";
		
		// Способ 2.1 - for-each
		std::cout << "\n\n--- iterating through the ranged-based for loop:\n";
		//for (auto iter : Location_1)
		for (auto& iter : Location_1)
			std::cout << iter.Get_Name() << " | ";


		// Способ 3 - at()
		std::cout << "\n\n--- iterating through the at():\n";
			for (int i = 0; i < Location_1.size(); ++i)
				std::cout << Location_1.at(i).Get_Name() << " | ";

		//Сбор всех плодов в рюкзак
		std::cout << "\n\n\n--- Harvesting all fruits from all trees in location\n";
		BackPack temp_back_pack;
		
		for (auto iter = Location_1.begin(); iter != Location_1.end(); iter++)
			while ((*iter).Get_fruits_remain())
				temp_back_pack << *(*iter).Get_fruit();

		// без ссылки не работает -> хочет экземпляры MotherPlant создавать, а он абстрактный
		//* 
		//for (auto iter : Location_1) 
		for (auto& iter : Location_1) 
		while (iter.Get_fruits_remain())
			temp_back_pack << *(iter.Get_fruit());
		//*/
		
		//Заглянем в рюкзак
		std::cout << "\n\n--- temp_back_pack.ShortInfo():\n";
		temp_back_pack.ShortInfo();
		
		//Осмотрим локацию
		std::cout << "\n\n--- Location_1.Info_categorized():";
		Location_1.Info_categorized();	
			
		//Удаление всех плодов одного типа
		std::cout << "\n--- Delete all Pears:\n";
		temp_back_pack.DeleteItem(Fruit::fruitTypes::Pear);
				
		std::cout << "\n\n--- ShortInfo():\n";
		temp_back_pack.ShortInfo();

		std::cout << "\n\nEsc - exit | any key to continue";
	} while (_getch() != 27);
}

//Task 2 BackPack
void Task_2(std::string name_of_task)

{
	do
	{
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";
				
		BackPack main_back_pack;
		
		//Создадим несколько деревьев, чтобы собрать с них фрукты в рюкзак
		std::vector<MotherPlant*> trees_vec = { new AppleTree(2, Color::white, 50), new Raspberry_bush(1, Color::green, 70), new PearTree(2, Color::brown, 30) };
		
		//соберем в рюкзак по 5 разных фруктов
		std::cout << "\n\n--- Harvesting 5 Apples, 5 Pears, 5 Raspberrys:\n";
		for ( int tree = trees_vec.size(); tree; --tree)
			for (int i = 0; i < 5; ++i)		
				main_back_pack.AddItem(trees_vec[tree-1]->Get_fruit());
						
		// Еще есть такой вариант метода положить в рюкзак
		Fruit& new_fruit = *new Apple(0.2, Color::green);
		main_back_pack << new_fruit;

		std::cout << "\n\n--- ShortInfo():\n";
		main_back_pack.ShortInfo();
		//Перебор элементов Способ 1 []
		std::cout << "\n\n--- iterating through the elements []:\n";
		for (int i = 0; i < main_back_pack.size(); ++i)
		{
			//std::cout << "\nItem " << i + 1;
			//main_back_pack[i]->Info();
			std::cout << i + 1 <<":" << main_back_pack[i]->Get_name() <<" | ";
		}

		// удаление 1-го элемента
		std::cout << "\n\n\n--- DeleteItem(1):\n";
		main_back_pack.DeleteItem(1); 
		
		std::cout << "\n\n--- ShortInfo():\n";
		main_back_pack.ShortInfo();
		//Перебор элементов Способ 2 at()
		std::cout << "\n\n--- iterating through the at():\n";
		for (int i = 0; i < main_back_pack.size(); ++i)
		{
			//std::cout << "\nItem " << i + 1;
			//main_back_pack.at(i).Info();
			std::cout << i + 1 << ":" << main_back_pack.at(i).Get_name() << " | ";

		}
				
		// удаление элементов в диапазоне
		std::cout << "\n\n\n--- DeleteItem(3,5):\n";
		main_back_pack.DeleteItem(3,5); 
		
		std::cout << "\n\n--- ShortInfo():\n";
		main_back_pack.ShortInfo();
		//Перебор элементов Способ 3 iterator
		std::cout << "\n\n--- iterating through the iterator:\n";
		int i=0;
		for (auto iter : main_back_pack)			
			std::cout << ++i << ":" << iter.Get_name() << " | ";


		//Удаление всех плодов одного типа
		std::cout << "\n\n\n--- Delete all Apples:\n";
		main_back_pack.DeleteItem(Fruit::fruitTypes::Apple);

		std::cout << "\n\n--- ShortInfo():\n";
		main_back_pack.ShortInfo();



		std::cout << "\n\n\nGet ready to watch full BackPack info:";
		_getch();
		main_back_pack.Info();

		std::cout << "\n\nEsc - exit | any key to continue";
	} while (_getch() != 27);
}

//Task 3 
void Task_3() {}

//Task 4
void Task_4() {}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	srand(time(NULL));
	//setlocale(LC_CTYPE, "Russian");
	//system("mode con cols=60 lines=40"); 
	Main_menu MainMenu;	
	MainMenu.AddElement("OOP Home Work 16: Aggregation and composition");	// Homework name
	MainMenu.AddElement("Location container class demo");
	MainMenu.AddElement("BackPack container class demo");

	do 
	{		
		MainMenu.Show_menu();
		if (!MainMenu.User_Choice_Handle(_getch()))	break;
	} while (true);
	return 0;
}

