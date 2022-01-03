#include "artifactclasses.h"
#include "artifactoutput.h"
#include "sortingmethods.h"
#include "mainmenu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// All AddAttribute add name and related stats
// All GenerateITEM get all attributes, randomize them and return text
void ItemGeneric::AddAttribute(std::string& newAttribute, int& newAttributeCost)
{
	attributeGeneric.push_back(newAttribute);
	statsGeneric.push_back(newAttributeCost);
}

void ItemWeapon::AddAttribute(std::string& newAttribute, int& newAttributeCost)
{
	attributeWeapon.push_back(newAttribute);
	statsWeapon.push_back(newAttributeCost);
}

std::string ItemWeapon::GenerateWeapon(int minimumPoint, int maximumPoint)
{
	doublequicksort(statsWeapon, 0, statsWeapon.size() -1, attributeWeapon, 0, attributeWeapon.size() - 1);
	int availablePoints = rand() % maximumPoint + minimumPoint;
	GeneratedArtifacts generatedArtifact;
	generatedArtifact.AddArtifactName(nameWeapon);
	generatedArtifact.AddArtifactStats(statsWeapon, attributeWeapon, availablePoints);
	return generatedArtifact.GenerateArtifactText(generatedArtifact.artifactName, generatedArtifact.artifactFeatures);
}

void ItemWeapon::AddItemType(std::string newWeapon)
{
	if (nameWeapon.size() == 0) nameWeapon.push_back(newWeapon);
	for (size_t i = 0; i < nameWeapon.size(); i++) {
		if (nameWeapon.at(i) == newWeapon) break;
		nameWeapon.push_back(newWeapon);
	}
}

void ItemArmor::AddAttribute(std::string& newAttribute, int& newAttributeCost)
{
	attributeArmor.push_back(newAttribute);
	statsArmor.push_back(newAttributeCost);
}

std::string ItemArmor::GenerateArmor(int minimumPoint, int maximumPoint)
{
	doublequicksort(statsArmor, 0, statsArmor.size() - 1, attributeArmor, 0, attributeArmor.size() - 1);
	int availablePoints = rand() % maximumPoint + minimumPoint;
	GeneratedArtifacts generatedArtifact;
	generatedArtifact.AddArtifactName(nameArmor);
	generatedArtifact.AddArtifactStats(statsArmor, attributeArmor, availablePoints);
	return generatedArtifact.GenerateArtifactText(generatedArtifact.artifactName, generatedArtifact.artifactFeatures);
}

void ItemArmor::AddItemType(std::string newArmor)
{
	if (nameArmor.size() == 0) nameArmor.push_back(newArmor);
	for (size_t i = 0; i < nameArmor.size(); i++) {
		if (nameArmor.at(i) == newArmor) break;
		nameArmor.push_back(newArmor);
	}
}

void ItemMiscelanous::AddAttribute(std::string& newAttribute, int& newAttributeCost)
{
	attributeMiscelanous.push_back(newAttribute);
	statsMiscelanous.push_back(newAttributeCost);
}

std::string ItemMiscelanous::GenerateMiscelanous(int minimumPoint, int maximumPoint)
{
	doublequicksort(statsMiscelanous, 0, statsMiscelanous.size() - 1, attributeMiscelanous, 0, attributeMiscelanous.size() - 1);
	int availablePoints = rand() % maximumPoint + minimumPoint;
	GeneratedArtifacts generatedArtifact;
	generatedArtifact.AddArtifactName(nameMiscelanous);
	generatedArtifact.AddArtifactStats(statsMiscelanous, attributeMiscelanous, availablePoints);
	return generatedArtifact.GenerateArtifactText(generatedArtifact.artifactName, generatedArtifact.artifactFeatures);
}

void ItemMiscelanous::AddItemType(std::string newMiscelanous)
{
	if (nameMiscelanous.size() == 0) nameMiscelanous.push_back(newMiscelanous);
	for (size_t i = 0; i < nameMiscelanous.size(); i++) {
		if (nameMiscelanous.at(i) == newMiscelanous) break;
		nameMiscelanous.push_back(newMiscelanous);
	}
}

int readItems(ItemArmor& arm, ItemWeapon& weap, ItemMiscelanous& misc)
{
	std::ifstream itemInput{};
	itemInput.open("itemlist.txt");
	if (!itemInput) {
		std::cerr << "Problem opening file" << std::endl;
		return 0;
	}
	std::string itemType;
	std::string currentItem;
	while (itemInput.good()) {
		std::getline(itemInput, itemType, ':');
		std::getline(itemInput, currentItem, '\n');
		if (itemType == "WEAPON") {
			weap.AddItemType(currentItem);
		}
		else if (itemType == "ARMOR") {
			arm.AddItemType(currentItem);
		}
		else if (itemType == "MISCELLANEOUS") {
			misc.AddItemType(currentItem);
		}
		else std::cerr << "Item type unknown\n";
	}
	itemInput.close();
	return 0;
}

int readAttributes(ItemArmor& arm, ItemWeapon& weap, ItemMiscelanous& misc, ItemGeneric& gen)
{
	std::ifstream attributeInput{};
	attributeInput.open("attributelist.txt");
	if (!attributeInput) {
		std::cerr << "Problem opening file" << std::endl;
		return EXIT_FAILURE;
	}
	std::string attributeType;
	std::string currentAttribute;
	std::string attributeCostString;
	int attributeCostInt;
	while (attributeInput.good()) {
		std::getline(attributeInput, attributeType, ':');
		std::getline(attributeInput, currentAttribute, ':');
		std::getline(attributeInput, attributeCostString, '\n');
		attributeCostInt = stoi(attributeCostString);
		if (attributeType == "WEAPON") {
			weap.AddAttribute(currentAttribute, attributeCostInt);
		}
		else if (attributeType == "ARMOR") {
			arm.AddAttribute(currentAttribute, attributeCostInt);
		}
		else if (attributeType == "MISCELLANEOUS") {
			misc.AddAttribute(currentAttribute, attributeCostInt);
		}
		else if (attributeType == "GENERIC") {
			// Generic attribute is added for every item kind
			weap.AddAttribute(currentAttribute, attributeCostInt);
			arm.AddAttribute(currentAttribute, attributeCostInt);
			misc.AddAttribute(currentAttribute, attributeCostInt);
		}
		else std::cerr << "attribute type unknown\n";
	}
	attributeInput.close();
}

void GenerateArtifacts(int itemAmount, int min, int max)
{
	FinalArtifactList finalList;
	ItemArmor armor;
	ItemWeapon weapon;
	ItemMiscelanous miscellaneous;
	ItemGeneric generic;
	readItems(armor, weapon, miscellaneous);
	readAttributes(armor, weapon, miscellaneous, generic);
	srand(time(NULL));
	for (int i = 0; i < itemAmount; i++) {
		int choice = rand() % 3;
		switch (choice) {
		case 0:
		{
			finalList.AddArtifactToList(weapon.GenerateWeapon(min, max));
			break;
		}
		case 1:
		{
			finalList.AddArtifactToList(armor.GenerateArmor(min, max));
			break;
		}
		case 2:
		{
			finalList.AddArtifactToList(miscellaneous.GenerateMiscelanous(min, max));
			break;
		}
		default:
			std::cerr << "Couldn't generate an item\n";
		}
	}
	finalList.SaveFile();
}

