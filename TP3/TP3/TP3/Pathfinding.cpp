#include <stdlib.h>
#include "Pathfinding.h"
#include "Lieu.h"

const int VUE = 1;
const int ENTREE = 2;
const int ETAPE = 3;
const double INF = 999999;


Pathfinding::Pathfinding()
{

}


Pathfinding::Pathfinding(std::vector<Lieu> points, bool affichage)
{
	listePoints = points;
	m_affichage = affichage;
}

Pathfinding::~Pathfinding()
{
}

std::vector<std::tuple<int, int>> Pathfinding::trouverParcoursInitial()
{
	std::vector<std::tuple<int, int>> arcs;

	for (int i = 0; i < (int)listePoints.size(); i++)
	{
		//Etape 1, lier les entrees a  l'intersection la moins chere
		if (listePoints[i].m_type == ENTREE)
		{
			double minCost = INF;
			int idIntersection = -1;
			listePoints[i].m_lienAvecEntree = true;
			//Lier le point a l'intersection la moins chere
			for (int j = 0; j < (int)listePoints[i].m_costs.size(); j++)
			{
				if (listePoints[i].m_costs[j] < minCost && listePoints[i].m_costs[j] != 0
					&& listePoints[j].m_type == ETAPE && !listePoints[j].m_rempli)
				{
					minCost = listePoints[i].m_costs[j];
					idIntersection = j;
				}
			}
			remplirSommetAvecSentiers(i, idIntersection);
			listePoints[idIntersection].m_lienAvecEntree = true;

			arcs.push_back(std::tuple<int, int>(i, idIntersection));
		}
	}

	//Etape 2, lier les points d'intersection a l'entree ou autre pt d'int la moins chere
	for (int i = 0; i < (int)listePoints.size(); i++)
	{
		if (listePoints[i].m_type == ETAPE && !listePoints[i].m_rempli)
		{
			double minCost = INF;
			int idIntersection = -1;
			//Lier le point a l'intersection la moins chere
			for (int j = 0; j < (int)listePoints[i].m_costs.size(); j++)
			{
				if (listePoints[i].m_costs[j] < minCost && listePoints[i].m_costs[j] != 0
					&& listePoints[j].m_type == ETAPE && !listePoints[j].m_rempli && !listePoints[j].m_lienAvecEntree)
				{
					minCost = listePoints[i].m_costs[j];
					idIntersection = j;
				}
			}
			
			if (idIntersection <= 0)
			{
				if (!listePoints[i].m_lienAvecEntree)
				{
					for (int j = 0; j < (int)listePoints[i].m_costs.size(); j++)
					{
						if (listePoints[i].m_costs[j] < minCost && listePoints[i].m_costs[j] != 0
							&& listePoints[j].m_type == ENTREE && !listePoints[j].m_rempli)
						{
							minCost = listePoints[i].m_costs[j];
							idIntersection = j;
						}
					}
				}
			}

			if (idIntersection >= 0)
			{
				remplirSommetAvecSentiers(i, idIntersection);

				if (listePoints[idIntersection].m_lienAvecEntree)
				{
					listePoints[i].m_lienAvecEntree = true;
				}

				arcs.push_back(std::tuple<int, int>(i, idIntersection));
				misAJourLienAvecEntree(arcs);
			}
		}
	}
	//Etape 2.2
	arcs = supprimerDoublon(arcs);
	

	//Etape 4, lier les points d'intersection a une intersection qui touche a une entree, si ce n'est pas le cas
	for (int i = 0; i < (int)listePoints.size(); i++)
	{
		if (listePoints[i].m_type == ETAPE && !listePoints[i].m_lienAvecEntree && !listePoints[i].m_rempli)
		{
			double minCost = INF;
			int idIntersection = -1;
			//Lier le point a l'intersection la plus proche
			bool entreeTrouve = false;
			for (int j = 0; j < (int)listePoints[i].m_costs.size(); j++)
			{

				if (listePoints[i].m_costs[j] < minCost && listePoints[i].m_costs[j] != 0
					&& listePoints[j].m_type == ETAPE && listePoints[j].m_lienAvecEntree
					&& !listePoints[j].m_rempli && !entreeTrouve)
				{
					minCost = listePoints[i].m_costs[j];
					idIntersection = j;
					entreeTrouve = true;
				}

			}

			if (idIntersection <= 0)
			{
				for (int j = 0; j < (int)listePoints[i].m_costs.size(); j++)
				{
					if (listePoints[i].m_costs[j] < minCost && listePoints[i].m_costs[j] != 0
						&& listePoints[j].m_type == ENTREE && !listePoints[j].m_rempli)
					{
						minCost = listePoints[i].m_costs[j];
						idIntersection = j;
					}
				}
			}


			if (idIntersection >= 0)
			{

				remplirSommetAvecSentiers(i, idIntersection);
				listePoints[i].m_lienAvecEntree = true;
				//TODO: Lier vue i et inter j
				arcs.push_back(std::tuple<int, int>(i, idIntersection));

				misAJourLienAvecEntree(arcs);
			}
		}
	}

	//Etape 4.2, supprimer les liens en double
	arcs = supprimerDoublon(arcs);

	for (int i = 0; i < (int)listePoints.size(); i++)
	{
		// Etape 3: On lie les points de vue a l'intersection la moins chere
		if (listePoints[i].m_type == VUE && !listePoints[i].m_rempli)
		{
			double minCost = INF;
			int idIntersection = -1;

			for (int j = 0; j < (int)listePoints[i].m_costs.size(); j++)
			{
				if (listePoints[i].m_costs[j] < minCost && listePoints[i].m_costs[j] != 0
					&& listePoints[j].m_type == ETAPE && !listePoints[j].m_rempli)
				{
					minCost = listePoints[i].m_costs[j];
					idIntersection = j;
				}
			}

			if (idIntersection <= 0)
			{
				for (int j = 0; j < (int)listePoints[i].m_costs.size(); j++)
				{
					if (listePoints[i].m_costs[j] < minCost && listePoints[i].m_costs[j] != 0
						&& listePoints[j].m_type == ENTREE && !listePoints[j].m_rempli)
					{
						minCost = listePoints[i].m_costs[j];
						idIntersection = j;
					}
				}
			}

			if (idIntersection >= 0)
			{

				remplirSommetAvecSentiers(i, idIntersection);

				if (listePoints[idIntersection].m_lienAvecEntree)
				{
					listePoints[i].m_lienAvecEntree = true;
				}
				arcs.push_back(std::tuple<int, int>(i, idIntersection));
				misAJourLienAvecEntree(arcs);
			}
		}
	}
	//Etape 3.2
	arcs = supprimerDoublon(arcs);

	//Etape 5, lier les points étape ayant un seul sentier a un autre point étape.
	for (int i = 0; i < (int)listePoints.size(); i++)
	{
		if (listePoints[i].m_type == ETAPE && listePoints[i].m_nbDeSentiers <= 1 && !listePoints[i].m_rempli)
		{
			double maxCost = 0;
			int idIntersection = -1;
			//Lier le point a l'intersection la plus proche
			for (int j = 0; j < (int)listePoints[i].m_costs.size(); j++)
			{
				//On ne veut PAS qu'il soit lié a un point ayant un minCost
				if (listePoints[i].m_costs[j] > maxCost && listePoints[i].m_costs[j] != 0
					&& listePoints[j].m_type != VUE && listePoints[j].m_lienAvecEntree
					&& !listePoints[j].m_rempli)
				{
					maxCost = listePoints[i].m_costs[j];
					idIntersection = j;

				}

			}

			if (idIntersection >= 0)
			{

				remplirSommetAvecSentiers(i, idIntersection);
				listePoints[i].m_lienAvecEntree = true;

				arcs.push_back(std::tuple<int, int>(i, idIntersection));

				misAJourLienAvecEntree(arcs);
			}
		}
	}

	return arcs;

}

void Pathfinding::remplirSommetAvecSentiers(int depart, int fin)
{
	listePoints[depart].m_nbDeSentiers++;
	if (listePoints[depart].m_nbDeSentiers == listePoints[depart].m_maxSentiers)
	{
		listePoints[depart].m_rempli = true;
	}

	listePoints[fin].m_nbDeSentiers++;
	if (listePoints[fin].m_nbDeSentiers == listePoints[fin].m_maxSentiers)
	{
		listePoints[fin].m_rempli = true;
	}
}


void Pathfinding::ameliorerParcours(std::vector<std::tuple<int, int>> arcs, std::vector<std::vector<double>> cost_matrix)
{
	double cout = calculerCout(arcs, cost_matrix);
	if(verifierSolution())
		printSolution(arcs);

	while (1)
	{
		// Copie les arcs dans un tampon
		std::vector<std::tuple<int, int>> tmp;
		for (int i = 0; i < (int)arcs.size(); i++) {
			int id1 = std::get<0>(arcs.at(i));
			int id2 = std::get<1>(arcs.at(i));
			tmp.push_back(std::tuple<int, int>(id1, id2));
		}

		// Copie des parametres
		std::vector<Lieu> tmpList;
		for (int i = 0; i < listePoints.size(); i++) 
		{
			tmpList.push_back(listePoints[i]);
		}

		// Choisir 2 arcs au hasard
		int arc1 = 0;
		int arc2 = 0;
		while (arc1 == arc2)
		{
			arc1 = rand() % (int)arcs.size();
			arc2 = rand() % (int)arcs.size();
		}
		int id11 = std::get<0>(arcs.at(arc1));
		int id12 = std::get<1>(arcs.at(arc1));
		int id21 = std::get<0>(arcs.at(arc2));
		int id22 = std::get<1>(arcs.at(arc2));


		// Met à jour les liens avec l'entree
		if(tmpList[id11].m_type != ENTREE)
			tmpList[id11].m_lienAvecEntree = false;
		if (tmpList[id12].m_type != ENTREE)
			tmpList[id12].m_lienAvecEntree = false;
		if (tmpList[id21].m_type != ENTREE)
			tmpList[id21].m_lienAvecEntree = false;
		if (tmpList[id22].m_type != ENTREE)
			tmpList[id22].m_lienAvecEntree = false;

		// On enleve les arcs choisis
		if (arc2 > arc1) 
		{
			tmp.erase(tmp.begin() + arc2);
			tmp.erase(tmp.begin() + arc1);
		}
		else
		{
			tmp.erase(tmp.begin() + arc1);
			tmp.erase(tmp.begin() + arc2);
		}
		
		// Si les valeurs des arcs ne sont pas les memes
		if (id11 != id22 && id21 != id12)
		{
			// On ajoute les nouveaux arcs
			tmp.push_back(std::tuple<int, int>(id11, id22));
			tmp.push_back(std::tuple<int, int>(id21, id12));

			// On met a jour les liens avec l'entree
			misAJourLienAvecEntreeOpt(tmp, tmpList);

			// Verifier solution et cout
			if (verifierSolutionOpt(tmpList)) 
			{
				double cout_tmp = calculerCout(tmp, cost_matrix);
				// Si on obtient un meilleur cout, on actualise le graphe et le cout a comparer
				if (cout_tmp < cout)
				{
					if (m_affichage)
					{
						printSolution(tmp);
					}
					arcs = tmp;
					cout = cout_tmp;
				}
			}
		}
	}

}

bool Pathfinding::verifierSolution() 
{
	bool estUneSolution = true;
	for (int i = 0; i < (int)listePoints.size(); i++)
	{
		if (listePoints[i].m_type == VUE) {
			estUneSolution &= (listePoints[i].m_nbDeSentiers == 1);
		}
		if (listePoints[i].m_type == ENTREE) {
			estUneSolution &= ((listePoints[i].m_nbDeSentiers <= listePoints[i].m_maxSentiers) && (listePoints[i].m_nbDeSentiers >= 1));
		}
		if (listePoints[i].m_type == ETAPE) {
			estUneSolution &= ((listePoints[i].m_nbDeSentiers <= listePoints[i].m_maxSentiers) && (listePoints[i].m_nbDeSentiers >= 2));
		}
		estUneSolution &= (listePoints[i].m_lienAvecEntree);
	}
	return estUneSolution;
}

double Pathfinding::calculerCout(std::vector<std::tuple<int, int>> out, std::vector<std::vector<double>> cost_matrix)
{
	double cost = 0.0;
	for (int i = 0; i < (int)out.size(); i++)
	{
		cost += cost_matrix[std::get<0>(out.at(i))][std::get<1>(out.at(i))];
	}
	return cost;
}

std::vector<std::tuple<int, int>> Pathfinding::supprimerDoublon(std::vector<std::tuple<int, int>> in)
{
	for (int i = 0; i < (int)in.size()-1; i++) {
		int id11 = std::get<0>(in.at(i));
		int id12 = std::get<1>(in.at(i));

		for (int j = i + 1; j < (int)in.size(); j++)
		{
			int id21 = std::get<0>(in.at(j));
			int id22 = std::get<1>(in.at(j));

			if (id11 == id22 && id12 == id21) {
				listePoints[id21].m_nbDeSentiers--;
				listePoints[id22].m_nbDeSentiers--;
				if (listePoints[id21].m_rempli) {
					listePoints[id21].m_rempli = false;
				}
				if (listePoints[id22].m_rempli) {
					listePoints[id22].m_rempli = false;
				}

				in.erase(in.begin() + j);
				j = i;
			}
		}
	}
	return in;
}

void Pathfinding::misAJourLienAvecEntree(std::vector<std::tuple<int, int>> arcs)
{
	for (int k = 0; k < (int)arcs.size(); k++)
	{
		int id1 = std::get<0>(arcs.at(k));
		int id2 = std::get<1>(arcs.at(k));
		if (listePoints[id1].m_lienAvecEntree != listePoints[id2].m_lienAvecEntree)
		{
			if (listePoints[id1].m_lienAvecEntree)
			{
				listePoints[id2].m_lienAvecEntree = true;
			}
			else
			{
				listePoints[id1].m_lienAvecEntree = true;
			}
			k = 0;
		}
	}
}

void Pathfinding::printSolution(std::vector<std::tuple<int, int>> out)
{
	for (int i = 0; i < (int)out.size(); i++)
	{
		std::cout << std::get<0>(out.at(i)) << " ";
		std::cout << std::get<1>(out.at(i)) << std::endl;
	}
	std::cout << "fin" << std::endl;
}

void Pathfinding::misAJourLienAvecEntreeOpt(std::vector<std::tuple<int, int>> arcs, std::vector<Lieu> &list)
{
	for (int k = 0; k < (int)arcs.size(); k++)
	{
		int id1 = std::get<0>(arcs.at(k));
		int id2 = std::get<1>(arcs.at(k));
		if (list[id1].m_lienAvecEntree != list[id2].m_lienAvecEntree)
		{
			if (list[id1].m_lienAvecEntree)
			{
				list[id2].m_lienAvecEntree = true;
			}
			else
			{
				list[id1].m_lienAvecEntree = true;
			}
			k = 0;
		}
	}
}

bool Pathfinding::verifierSolutionOpt(std::vector<Lieu> &list)
{
	bool estUneSolution = true;
	for (int i = 0; i < (int)list.size(); i++)
	{
		if (listePoints[i].m_type == VUE) {
			estUneSolution &= (list[i].m_nbDeSentiers == 1);
		}
		if (listePoints[i].m_type == ENTREE) {
			estUneSolution &= ((list[i].m_nbDeSentiers <= list[i].m_maxSentiers) && (list[i].m_nbDeSentiers >= 1));
		}
		if (listePoints[i].m_type == ETAPE) {
			estUneSolution &= ((list[i].m_nbDeSentiers <= list[i].m_maxSentiers) && (list[i].m_nbDeSentiers >= 2));
		}
		estUneSolution &= (list[i].m_lienAvecEntree);
	}
	return estUneSolution;
}

