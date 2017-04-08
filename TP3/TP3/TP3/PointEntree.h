#pragma once
#include "Lieu.h"
class PointEntree :
	public Lieu
{
public:
	PointEntree();
	~PointEntree();
	virtual bool SentiersMaxUtilises();

private:
	bool m_maxAtteint;
};

