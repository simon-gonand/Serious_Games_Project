#pragma once

#include <vector>
#include <map>

#include <GL/glew.h>

class ModelsResources {

private:
	ModelsResources();
	~ModelsResources();

	static std::map<const char*, float*> models;
	static std::vector<unsigned int*> modelsIndices;
	static std::vector<unsigned int> nbOfAuthorizeRelease;
	static std::vector<size_t> modelsSizes;
	static std::vector<size_t> modelsIndicesSizes;

	static GLfloat rectangleVertices[4 * 3];
	static unsigned int rectangleIndices[6];
	static unsigned int rectangleAuthorizeRelease;

	static GLfloat muKatakanaVertices[12 * 3];
	static unsigned int muKatakanaIndices[18];
	static unsigned int muKatakanaAuthorizeRelease;

public:
	ModelsResources(ModelsResources const&) = delete;
	void operator=(ModelsResources const&) = delete;

	static void Initialise();

	static std::map<const char*, float*> GetModels();
	static std::vector<unsigned int*> GetModelIndices();
	static std::vector<unsigned int> GetModelReleaseNb();
	static size_t GetModelSize(int index);
	static size_t GetModelIndicesSize(int index);
};