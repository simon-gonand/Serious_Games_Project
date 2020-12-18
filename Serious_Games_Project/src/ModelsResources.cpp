#include "ModelsResources.h"

std::map<const char*, float*> ModelsResources::models;
std::vector<unsigned int*> ModelsResources::modelsIndices;
std::vector<unsigned int> ModelsResources::nbOfAuthorizeRelease;
std::vector<size_t> ModelsResources::modelsSizes;
std::vector<size_t> ModelsResources::modelsIndicesSizes;

GLfloat ModelsResources::rectangleVertices[4 * 3] = {
		0.0f, 0.0f, 0.0f,	// Bottom left
		0.3f, 0.1f, 0.0f,	// Top right
		0.0f, 0.1f, 0.0f,	// Top left
		0.3f, 0.0f, 0.0f,	// Bottom right
};
unsigned int ModelsResources::rectangleIndices[6] = { 0, 2, 1, 1, 3, 0 };
unsigned int ModelsResources::rectangleAuthorizeRelease = 0;

GLfloat ModelsResources::muKatakanaVertices[12 * 3] = {
	// Rectangle 1
	 0.13f,  0.5f,  0.0f, // Top right
	 0.17f,  0.47f,  0.0f, // Bottom right
	 0.0f,  0.01f,  0.0f, // Top left
	 0.03f,  -0.02f,  0.0f, // Bottom left
	// Rectangle 2
	-0.05f,  0.01f, 0.0f, // Top left
	-0.05f, -0.04f, 0.0f, // Bottom left
	 0.27f,  0.01f, 0.0f, // Top right
	 0.27f, -0.04f, 0.0f, // Bottom right
	 // Rectangle 3
	 0.22f,  0.11f, 0.0f, // Top left
	 0.255f,  0.12f,  0.0f, // Top right
	 0.28f,  -0.12f,  0.0f, // Bottom left
	 0.315f,  -0.11f, 0.0f  // Bottom right
};
unsigned int ModelsResources::muKatakanaIndices[18] = {
	0, 3, 1, 2, 3, 0,    // Rectangle 1
	4, 6, 5, 7, 6, 5,    // Rectangle 2
	8, 9, 10, 11, 9, 10  // Rectangle 3
};
unsigned int ModelsResources::muKatakanaAuthorizeRelease = 2;

ModelsResources::ModelsResources(){}
ModelsResources::~ModelsResources(){}

void ModelsResources::Initialise() {
	models.insert(std::pair<const char*, float*> ("Rectangle", rectangleVertices));
	modelsIndices.push_back(rectangleIndices);
	nbOfAuthorizeRelease.push_back(rectangleAuthorizeRelease);
	modelsSizes.push_back(sizeof(rectangleVertices));
	modelsIndicesSizes.push_back(sizeof(rectangleIndices));

	models.insert(std::pair<const char*, float*>("Katakana Mu", muKatakanaVertices));
	modelsIndices.push_back(muKatakanaIndices);
	nbOfAuthorizeRelease.push_back(muKatakanaAuthorizeRelease);
	modelsSizes.push_back(sizeof(muKatakanaVertices));
	modelsIndicesSizes.push_back(sizeof(muKatakanaIndices));
}

std::map<const char*, float*> ModelsResources::GetModels() { return models; }
std::vector<unsigned int*> ModelsResources::GetModelIndices() { return modelsIndices; }
std::vector<unsigned int> ModelsResources::GetModelReleaseNb() { return nbOfAuthorizeRelease; }
size_t ModelsResources::GetModelSize(int index) { return modelsSizes[index]; }
size_t ModelsResources::GetModelIndicesSize(int index) { return modelsIndicesSizes[index]; }