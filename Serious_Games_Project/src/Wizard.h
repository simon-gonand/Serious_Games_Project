#pragma once
class Wizard
{
private:
	int m_Life;
public:
	Wizard();
	~Wizard();

	int GetLife() const;

	void ReduceLife(int lifePoints);
	void ResetLife();
};

