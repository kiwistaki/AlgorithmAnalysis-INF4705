#include <iostream>
#include <string>
#include <vector>

#ifndef LIEU_H
#define LIEU_H



class Lieu
{
public:
	Lieu();
	~Lieu();
	Lieu(int id, int type, int maxSommets, std::vector<double> couts);
	int m_type;
	int m_maxSentiers;
	int m_id;
	bool m_rempli;
	bool m_lienAvecEntree;
	int m_nbDeSentiers = 0;
	std::vector<double> m_costs;
};

#endif