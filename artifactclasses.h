#ifndef ARTIFACTCLASSES_H_
#define ARTIFACTCLASSES_H_
#include <string>
#include <vector>
#include <fstream>

extern int itemAmount;

class ItemGeneric
{
protected:
	std::vector<std::string> attributeGeneric = {};
	std::vector<int> statsGeneric = {};
public:
	virtual void AddAttribute(std::string& newAttribute, int& newAttributeCost);
};

class ItemWeapon : public ItemGeneric
{
private:
	std::vector<std::string> nameWeapon = {};
	std::vector<std::string> attributeWeapon = {};
	std::vector<int> statsWeapon = {};
public:
	virtual void AddAttribute(std::string& newAttribute, int& newAttributeCost); 
	void AddItemType(std::string newWeapon);
	std::string GenerateWeapon(int minimumPoint, int maximumPoint);
};

class ItemArmor : public ItemGeneric
{
private:
	std::vector<std::string> nameArmor = {};
	std::vector<std::string> attributeArmor = {};
	std::vector<int> statsArmor = {};
public:
	virtual void AddAttribute(std::string& newAttribute, int& newAttributeCost); 
	void AddItemType(std::string newArmor);
	std::string GenerateArmor(int minimumPoint, int maximumPoint);
};

class ItemMiscelanous : public ItemGeneric
{
private:
	std::vector<std::string> nameMiscelanous = {};
	std::vector<std::string> attributeMiscelanous = {};
	std::vector<int> statsMiscelanous = {};
public:
	virtual void AddAttribute(std::string& newAttribute, int& newAttributeCost); 
	void AddItemType(std::string newMiscelanous);
	std::string GenerateMiscelanous(int minimumPoint, int maximumPoint);
};

int readItems(ItemArmor& arm, ItemWeapon& weap, ItemMiscelanous& misc);
int readAttributes(ItemArmor& arm, ItemWeapon& weap, ItemMiscelanous& misc, ItemGeneric& gen);
void GenerateArtifacts(int amount, int min, int max);

#endif