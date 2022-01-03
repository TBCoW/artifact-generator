#include "mainmenu.h"
#include "artifactclasses.h"
#include "artifactoutput.h"
#include <iostream>

void MainMenu::CreateArtifact()
{
	GenerateArtifacts(itemAmount, minPoint, maxPoint);
}

void MainMenu::ChangeAmount()
{
	std::cout << "Amount of generated items: " << itemAmount << '\n';
	std::cout << "Enter new number of generated artifacts: ";
	std::cin >> itemAmount;
	std::cout << std::endl;
	ShowMenu();
}
void MainMenu::ChangeMin()
{
	std::cout << "Minimum value of generated items: " << minPoint << '\n';
	std::cout << "Enter new minimum of generated artifacts: ";
	std::cin >> minPoint;
	std::cout << std::endl;
	ShowMenu();
}

void MainMenu::ChangeMax()
{
	std::cout << "Maximum value of generated items: " << maxPoint << '\n';
	std::cout << "Enter new maximum of generated artifacts: ";
	std::cin >> maxPoint;
	std::cout << std::endl;
	ShowMenu();
}

void MainMenu::ShowHelp()
{
	std::cout << "Welcome to th Artifact Generator!\n"
		<< "This program allows you to randomly generate any amount of items with selected features.\n"
		<< "You can add more items and features yourself in itemslist.txt and attributelist.txt\n"
		<< "Format for items is: WEAPON/ARMOR/MISCELLANEOUS:ITEM_NAME\n"
		<< "example: WEAPON:SWORD\n"
		<< "Format for attributes is: WEAPON/ARMOR/MISCELLANEOUS/GENERIC:ATTRIBUTE_NAME:POINTS\n"
		<< "example: WEAPON:FLAMING:4 (note that GENERIC applies to all items)\n"
		<< "All generated artifacts are saved in Output.txt\n";
	std::cout << std::endl;
	ShowMenu();
}

void MainMenu::ShowMenu()
{
	using namespace std;
	do {
		cout << "Welcome to Artifact Generator\n";
		cout << "Amount: " << itemAmount << " Min Val: " << minPoint << " Max Val: " << maxPoint;
		cout << "\nEnter a number to proceed\n";
		cout << "1 - Create artifacts.\n";
		cout << "2 - Change amount of created artifacts.\n";
		cout << "3 - Change minimum number of points artifact will have.\n";
		cout << "4 - Change maximum number of points artifact will have.\n";
		cout << "5 - Show help.\n";
		cout << "0 - Quit\n";
		cout << "Enter your option: ";
		cin >> option;
	} while (option > 5);
	switch (option) {
	case 1:
		CreateArtifact();
		break;
	case 2:
		ChangeAmount();
		break;
	case 3:
		ChangeMin();
		break;
	case 4:
		ChangeMax();
		break;
	case 5:
		ShowHelp();
		break;
	default:
		exit;
	}
}