#ifndef ARTIFACTOUTPUT_H_
#define ARTIFACTOUTPUT_H_
#include <string>
#include <vector>
#include <queue>

struct GeneratedArtifacts {
	std::string artifactName;
	std::vector<std::string> artifactFeatures;
	std::string ArtifactText;
	void AddArtifactName(std::vector<std::string> nameList);
	void AddArtifactStats(std::vector<int> statsList, std::vector<std::string> attributeList, int startingPoints);
	void ConsolidateDuplicates(std::vector<int>& duplicateNumber, std::vector<std::string>& duplicateString);
	std::string GenerateArtifactText(std::string finalName, std::vector<std::string> finalAttributes);
};
#endif

class FinalArtifactList {
private:
	std::queue<std::string> finalListQueue;
	std::string saveFileName = "Output.txt";
public:
	void AddArtifactToList(std::string artifactText);
	void SaveFile();
};