#include "MousePoints.h"

const double MousePoints::epsilon = std::numeric_limits<float>().epsilon();
const std::numeric_limits<double> MousePoints::DOUBLE;
const double MousePoints::MAX = DOUBLE.max();
const double MousePoints::MIN = DOUBLE.min();

MousePoints::MousePoints(){}
MousePoints::~MousePoints(){}

MousePoints& MousePoints::instance() {
	static MousePoints _self;
	return _self;
}

void MousePoints::initialise() {
	m_MouseButtonIsPressed = false;
}

void MousePoints::Display() {
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_LINES);
	for (int i = 1; i < m_MousePoints.size(); ++i) {
		glColor3f(0.0f, 0.0f, 0.0f); // The color of the painted points
		if (std::find(m_MouseReleaseIndices.begin(), m_MouseReleaseIndices.end(), i) != m_MouseReleaseIndices.end()) {
			glVertex3f(m_MousePoints[i][0], m_MousePoints[i][1], m_MousePoints[i][2]);
			if (i < m_MousePoints.size() - 1)
				glVertex3f(m_MousePoints[i + 1][0], m_MousePoints[i + 1][1], m_MousePoints[i + 1][2]);
		}
		else {
			glVertex3f(m_MousePoints[i][0], m_MousePoints[i][1], m_MousePoints[i][2]);
			glVertex3f(m_MousePoints[i - 1][0], m_MousePoints[i - 1][1], m_MousePoints[i - 1][2]);
		}
	}
	glEnd();
}

void MousePoints::Clear() {
	m_MousePoints.clear();
	m_MouseReleaseIndices.clear();
}

bool MousePoints::GetMouseButtonIsPressed() const { return m_MouseButtonIsPressed; }
void MousePoints::SetMouseButtonIsPressed(bool boolean) {
	m_MouseButtonIsPressed = boolean;
}

void MousePoints::AddMousePoint(std::vector<GLfloat> point) {
	m_MousePoints.push_back(point);
}

void MousePoints::AddReleaseIndex() {
	m_MouseReleaseIndices.push_back(m_MousePoints.size());
}

void MousePoints::PopBackReleaseIndex() {
	m_MouseReleaseIndices.pop_back();
}

bool MousePoints::IsInside(Engine::Model model) {
	int numberOfPointsInsideEntity = 0;
	std::vector<std::vector<GLfloat>> polygones = model.GetVertices();
	std::vector<unsigned int> indices = model.GetIndices();

	// Release button mouse at the beginning to select "Enable Draw" => entity.GetNumberOfReleasePossible() + 1
	if (model.GetNumberOfReleasePossible() + 1 < m_MouseReleaseIndices.size()) {
		Engine::Logger::GetAppLogger()->info("You release the left button too many time");
		return false;
	}

	if (!AllModelIsFill(model)) {
		Engine::Logger::GetAppLogger()->info("You didn't fill the model entirely");
		return false;
	}

	for (unsigned i = 0; i < indices.size(); i = i + 3) {
		std::vector<GLfloat> polygone;
		for (unsigned j = i; j < i + 3; ++j) {
			polygone.push_back(polygones[indices[j]][0]);
			polygone.push_back(polygones[indices[j]][1]);
			polygone.push_back(polygones[indices[j]][2]);
		}
		numberOfPointsInsideEntity += IsInsidePolygone(polygone);
			
	}
	if ((numberOfPointsInsideEntity * 100) / m_MousePoints.size() >= 95)
		return true;
	return false;
}

bool MousePoints::AllModelIsFill(Engine::Model model) {
	std::vector<std::vector<GLfloat>> modelVertices = model.GetVertices();
	for (unsigned i = 0; i < modelVertices.size(); ++i) {
		bool mousePointIsNear = false;
		for (unsigned j = 0; j < m_MousePoints.size(); ++j) {
			if (m_MousePoints[j][0] <= modelVertices[i][0] + 0.07f && m_MousePoints[j][0] >= modelVertices[i][0] - 0.07f &&
				m_MousePoints[j][1] <= modelVertices[i][1] + 0.07f && m_MousePoints[j][1] >= modelVertices[i][1] - 0.07f) {
				mousePointIsNear = true;
				break;
			}
		}
		if (!mousePointIsNear)
			return false;
	}
	return true;
}

int MousePoints::IsInsidePolygone(std::vector<GLfloat> polygonePoints) {
	int numberOfPointInsideThisPolygone = 0;
	for (unsigned i = 0; i < m_MousePoints.size(); ++i) {
		if (PointIsInsidePolygone(polygonePoints, m_MousePoints[i]))
			++numberOfPointInsideThisPolygone;
	}

	return numberOfPointInsideThisPolygone;
}

bool MousePoints::PointIsInsidePolygone(std::vector<GLfloat> polygonePoints, std::vector<GLfloat> mousePoint) {
	int count = 0;
	for (unsigned i = 0; i < polygonePoints.size() - 3; i = i + 3) {
		if (PointIsIntersectWithSegment(polygonePoints[i], polygonePoints[i + 1], polygonePoints[i + 3],
			polygonePoints[i + 4], mousePoint[0], mousePoint[1]))
			++count;
	}
	if (PointIsIntersectWithSegment(polygonePoints[polygonePoints.size() - 3], polygonePoints[polygonePoints.size() - 2], 
		polygonePoints[0], polygonePoints[1], mousePoint[0], mousePoint[1]))
	
		++count;

	if (count % 2 == 0)
		return false;
	return true;
}

bool MousePoints::PointIsIntersectWithSegment(GLfloat segmentX1, GLfloat segmentY1, GLfloat segmentX2, GLfloat segmentY2,
	GLfloat mousePointX, GLfloat mousePointY) {
	if (segmentY1 > segmentY2) 
		return PointIsIntersectWithSegment(segmentX2, segmentY2, segmentX1, segmentY1, mousePointX, mousePointY);
	if (mousePointY == segmentY1 || mousePointY == segmentY2)
		return PointIsIntersectWithSegment(segmentX1, segmentY1, segmentX2, segmentY2, mousePointX, mousePointY + epsilon);
	if (mousePointY > segmentY2 || mousePointY < segmentY1 || mousePointX > std::max(segmentX1, segmentX2)) 
		return false;
	if (mousePointX < std::min(segmentX1, segmentX2)) return true;
	auto blue = abs(segmentX1 - mousePointX) > MIN ? (mousePointY - segmentY1) / (mousePointX - segmentX1) : MAX;
	auto red = abs(segmentX1 - segmentX2) > MIN ? (segmentY2 - segmentY1) / (segmentX2 - segmentX1) : MAX;
	return blue >= red;
}

bool MousePoints::IsEmpty() {
	return m_MousePoints.empty();
}