#pragma once

#include "GL/glew.h"
#include <vector>

class MousePoints
{
private:
	MousePoints();
	virtual ~MousePoints();

	bool m_MouseButtonIsPressed;
	std::vector<std::vector<GLfloat>> m_MousePoints;
	std::vector<int> m_MouseReleaseIndices;

public:
	MousePoints(MousePoints const&) = delete;
	void operator=(MousePoints const&) = delete;

	static MousePoints& instance();
	void initialise();
	void Display();
	void Clear();

	bool GetMouseButtonIsPressed() const;
	void SetMouseButtonIsPressed(bool boolean);

	void AddMousePoint(std::vector<GLfloat> point);
	void AddReleaseIndex();
};

