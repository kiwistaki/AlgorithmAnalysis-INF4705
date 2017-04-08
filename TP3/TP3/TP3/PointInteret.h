#pragma once
#include "Lieu.h"
class PointInteret :
	public Lieu
{
public:
	PointInteret();
	~PointInteret();
	bool isLieAvecEntree();

private:
	bool m_lieAvecEntree;
};

