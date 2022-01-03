#ifndef MAINMENU_H
#define MAINMENU_H_

class MainMenu
{
private:
	unsigned int option{};
	int minPoint = 4;
	int maxPoint = 9;
	int itemAmount = 10;
public:
	void CreateArtifact();
	void ChangeAmount();
	void ChangeMin();
	void ChangeMax();
	void ShowMenu();
	void ShowHelp();
};

#endif