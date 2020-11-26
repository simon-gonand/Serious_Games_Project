#pragma once

#include "GL/glew.h"
#include "Engine/Entity.h"
#include "Engine/Logger.h"

#include <vector>
#include <memory>
#include <limits>

class MousePoints
{
private:
	MousePoints();
	virtual ~MousePoints();

	bool m_MouseButtonIsPressed;
	std::vector<std::vector<GLfloat>> m_MousePoints;
	std::vector<int> m_MouseReleaseIndices;
	
	static const double epsilon;
	static const std::numeric_limits<double> DOUBLE;
	static const double MIN;
	static const double MAX;

	/* Check if the points are inside a polygon. Those functions are inspired by this algorithm 
	   https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/ */
	int IsInsidePolygone(std::vector<GLfloat> polygonePoints);
	bool PointIsInsidePolygone(std::vector<GLfloat> polygonePoints, std::vector<GLfloat> mousePoint);
	/* Using Ray-Casting algorithm from 
	https://rosettacode.org/wiki/Ray-casting_algorithm#C.2B.2B */
	bool PointIsIntersectWithSegment(GLfloat segmentX1, GLfloat segmentY1, GLfloat segmentX2, GLfloat segmentY2,
		GLfloat mousePointX, GLfloat mousePointY);

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

	bool IsInside(Engine::Entity entity);
	bool IsEmpty();
};

