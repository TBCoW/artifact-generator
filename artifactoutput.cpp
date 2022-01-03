#include "artifactoutput.h"
#include "artifactclasses.h"
#include "sortingmethods.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>


void GeneratedArtifacts::AddArtifactName(std::vector<std::string> nameList)
{
	int randomedName = rand() % (nameList.size() - 1);
	artifactName = nameList.at(randomedName);
}

void GeneratedArtifacts::AddArtifactStats(std::vector<int> statsList, std::vector<std::string> attributeList, int startingPoints)
{
	int randLimit = startingPoints;
	std::vector<int> pointsTable{};
	// Iterate through all stats and add features randomly
	for (size_t i = statsList.size()-1, finish = statsList.front(); i != finish; i--) {
		if (statsList[i] <= randLimit) {
			int currentValue = rand() % i;
			pointsTable.push_back(statsList[currentValue]);
			artifactFeatures.push_back(attributeList[currentValue]);
			randLimit -= statsList[currentValue];
			i = statsList.size()-1;
		}
	}
	// Sort features by points
	doublequicksort(pointsTable, 0, (pointsTable.size() - 1), artifactFeatures, 0, (artifactFeatures.size() - 1));
	// Sort same-point features by name to new vector
	std::vector<std::string> namesToSort = {};
	for (size_t i = 0; i+1 < pointsTable.size(); i++) {
		// Both elements are the same - first place
		if (pointsTable[i] == pointsTable[i + 1] && i == 0) {
			namesToSort.push_back(artifactFeatures[i]);
			namesToSort.push_back(artifactFeatures[i + 1]);
		}
		// Both elements are the same
		else if (pointsTable[i] == pointsTable[i + 1] && i != 0) {
			namesToSort.push_back(artifactFeatures[i + 1]);
		}
		// Different elements
		else if ((pointsTable[i] != pointsTable[i + 1]) && (namesToSort.size() > 1)) {
			std::sort(namesToSort.begin(), namesToSort.end());
			namesToSort.push_back(" ");
			for (size_t j = 0, k = i; j < namesToSort.size() - 1; j++, k--) {
				artifactFeatures[k].swap(namesToSort[j]);
			}
			namesToSort.clear();
			namesToSort.push_back(artifactFeatures[i + 1]);
		}
	}
	ConsolidateDuplicates(pointsTable, artifactFeatures);
	// Sort by points again so duplicates get to top of list
	doublequicksort(pointsTable, 0, (pointsTable.size() - 1), artifactFeatures, 0, (artifactFeatures.size() - 1));
}

void GeneratedArtifacts::ConsolidateDuplicates(std::vector<int>& duplicateNumber, std::vector<std::string>& duplicateString)
{
	// Places of neighbouring words
	int firstNumber = 0;
	int secondNumber = 1;
	std::string deletedWord = "";
	int deletedWordValue = 0;
	while (secondNumber != duplicateNumber.size()) {
		// If names are the same add value and erase duplicate
		if (duplicateString[firstNumber] == duplicateString[secondNumber]) {
			deletedWord = duplicateString[firstNumber];
			deletedWordValue += duplicateNumber[firstNumber];
			duplicateString.erase(duplicateString.begin() + secondNumber);
			duplicateNumber.erase(duplicateNumber.begin() + secondNumber);
		}
		// If name is different but duplicate is in memory change string and clear duplicate memory
		else if ((duplicateString[firstNumber] != duplicateString[secondNumber]) && (deletedWord != "")) {
			std::string timesAppeared = std::to_string(deletedWordValue / duplicateNumber[firstNumber] + 1);
			duplicateString.at(firstNumber) = duplicateString.at(firstNumber) + " x " + timesAppeared;
			duplicateNumber[firstNumber] = deletedWordValue;
			deletedWord = "";
			deletedWordValue = 0;
		}
		// If name is different and memory is clean proceed
		else {
			firstNumber++;
			secondNumber++;
		}
	}
}

std::string GeneratedArtifacts::GenerateArtifactText(std::string finalName, std::vector<std::string> finalAttributes)
{
	std::string finalText = {};
	finalText.append(finalName);
	finalText += '\n';
	// Adding generated attributes in reverse order - from highest to lowest
	for (int i = (finalAttributes.size() - 1); i >= 0; i--) {
		finalText.append(finalAttributes[i]);
		finalText += '\n';
	}
	return finalText;
}

void FinalArtifactList::AddArtifactToList(std::string artifactText)
{
	finalListQueue.push(artifactText);
}

void FinalArtifactList::SaveFile()
{
	std::ofstream save{ saveFileName };
	if (!save) {
		std::cerr << "Error creating file" << std::endl;
		EXIT_FAILURE;
	}
	while (!finalListQueue.empty()) {
		save << finalListQueue.front() << std::endl;
		//std::cerr << finalListQueue.front() << '\n';
		finalListQueue.pop();
	}
}