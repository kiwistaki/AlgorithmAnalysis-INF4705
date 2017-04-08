#include "Lieu.h"

Lieu::Lieu()
{
	int typeDeLieu = 0;
	int nbSentiersMax = 0;
	bool lieuRempli = false;

}

Lieu::Lieu(int type, int maxSommets, bool full)
{
	m_type = type;
	m_maxSommets = maxSommets;
	m_rempli = full;
}

Lieu::~Lieu(){}

bool Lieu::SentiersMaxUtilises()
{
	bool sentiersMax = true;
	return sentiersMax;
}