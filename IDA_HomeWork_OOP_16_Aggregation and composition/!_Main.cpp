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
	
		//Функции фабрики выполняет класс TreeLocation через:
		//  1. TreeLocation(int trees_number) - конструктор создания контейнера с рандомными деревьями
		//	2. void Get_fruit(int tree_index, BackPack_Player_Interface* back_pack) - метод сбора плодов, связывающий Классы Fruit, MohterPlant и BackPack


		//создаем локацию с от 30 до 100 рандомными деревьями		
		TreeLocation Location_1;
				
		
		//Получим сводку по локации
		std::cout << "\n--- Location_1.Info_categorized():\n";
		Location_1.Info_categorized();
						
		
		// Перебор деревьев

		// Способ 1 - []
		std::cout << "\n--- iterating through the elements []:\n";
		for (int i = 0; i < Location_1.size(); ++i)
			std::cout << Location_1[i].Get_Name() << " | ";

		// Способ 2 - iterator
		std::cout << "\n--- iterating through the iterator:\n";
		for (auto iter = Location_1.begin(); iter != Location_1.end(); iter++)
			std::cout << (*iter).Get_Name() << " | ";
		

		std::cout << "\n\nEsc - exit | any key to continue";
	} while (_getch() != 27);
}

//Task 2 Base_Friut
void Task_2(std::string name_of_task)

{
	do
	{
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";

		
		BackPack main_back_pack;
		TreeLocation Location_2(5);

		std::cout << "\n--- Location_2.ShowTrees():";
		Location_2.ShowTrees();
		

		Base_MotherPlant* tree_ptr = &Location_2[0];
		//Сорвем с Дерева 1 плод: 
		Base_Fruit* base_fruit_ptr = tree_ptr->Get_fruit();
		//опросим его методами класса Base_Fruit
		std::cout << "\n\n--- Base_Fruit methods through class pointer";
		std::cout << "\n\nName: " << base_fruit_ptr->Get_name();
		std::cout << "\nweight: " << base_fruit_ptr->Get_weight();
		std::cout << "\n color: " << base_fruit_ptr->Get_color();
		//Уберем сорванный плод в рюкзак (используя dynamic_cast, потому что backpack хранит указатели Fruit* и не принимает указатель Base_Fruit*)
		//main_back_pack.AddItem(base_fruit_ptr); // Error(active)	E0167	argument of type "Base_Fruit *" is incompatible with parameter of type "Fruit *"
		Fruit* fruit_ptr = dynamic_cast<Fruit*>(base_fruit_ptr);
		main_back_pack.AddItem(fruit_ptr);


		//Переходим к сбору урожая
		//соберем все плоды с дерева 1 и дерева 2 и 50 (или все) с дерева 3
		std::cout << "\n\nTree 1 & Tree 2 full harvesting, Tree 3 - 100 fruit (or all) harvesting";

		//Собираем все плоды с Деревьев 1 и 2. 
		//Вообще в классе TreeLocation есть метод Get_fruit(tree_index, &back_pack) который выполняет сбор плодов и укладку в рюкзак
		//но в целях демонстрации работы через виртуальные методы абстрактных базовых классов сделан этот код ниже:
		int tree_index = 1;		
		while (tree_index>=0)
		{
			tree_ptr = &Location_2[tree_index];
			for (int i = 0; i < Location_2[tree_index].Get_max_fruits(); ++i)
			{
				base_fruit_ptr = tree_ptr->Get_fruit();
				main_back_pack.AddItem(dynamic_cast<Fruit*>(base_fruit_ptr));
			}
			--tree_index;
		}
		//Собираем 100 плодов с Дерева 3
		tree_index = 2;
			tree_ptr = &Location_2[tree_index];
			for (int i = 0; i < 50; ++i)
			{
				base_fruit_ptr = tree_ptr->Get_fruit();
				main_back_pack.AddItem(dynamic_cast<Fruit*>(base_fruit_ptr));
			}
		
		//Осмотрим локацию после сбора урожая
		std::cout << "\n\n--- Location_2.ShowTrees():";
		Location_2.ShowTrees();

		//Получим короткую сводку по рюкзаку
		std::cout << "\n\n--- main_back_pack.ShortInfo():\n";
		main_back_pack.ShortInfo();

		//Получим полную сводку по рюкзаку
		std::cout << "\n\n\nGet ready to watch full BackPack info!";
		_getch();
		main_back_pack.Info();



//Fruit fruit_obj("apple", 0.2, Color::red);
//fruit_obj.Info();



//Base_Fruit* fruit_obj_ptr = &fruit_obj;
//fruit_obj_ptr->Get_name();



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

