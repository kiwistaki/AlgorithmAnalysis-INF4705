#include <iostream>
#include <string>

#ifndef LIEU_H
#define LIEU_H



class Lieu
{
public:
	Lieu();
	~Lieu();
	Lieu(int type, int maxSommets, bool full);
	virtual bool SentiersMaxUtilises();
	

protected:
		
	int m_type;
	int m_maxSommets;
	bool m_rempli;
};

#endif