#include "Wizard.h"

Wizard::Wizard() : m_Life(100){}

Wizard::~Wizard(){}

int Wizard::GetLife() const { return m_Life; }

void Wizard::ReduceLife(int lifePoints) {
	m_Life -= lifePoints;
}

void Wizard::ResetLife() {
	m_Life = 100;
}