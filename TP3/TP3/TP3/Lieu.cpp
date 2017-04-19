#include "Lieu.h"

Lieu::Lieu()
{
	m_type = 0;
	m_maxSentiers = 0;
	m_rempli = false;
	m_id = 0;
	m_nbDeSentiers = 0;
	m_lienAvecEntree = false;

}

Lieu::Lieu(int id, int type, int maxSommets, std::vector<double> couts)
{
	m_type = type;
	m_maxSentiers = maxSommets;
	m_rempli = false;
	m_id = id;
	m_costs = couts;
	m_lienAvecEntree = false;
}

Lieu::~Lieu(){}
