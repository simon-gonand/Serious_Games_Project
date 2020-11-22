#include "MousePoints.h"

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
		glColor3f(0.0f, 0.0f, 0.0f);//The color of the painted points
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