#include <vector>
#include <tuple>
#include "Lieu.h"


class Pathfinding
{
public:
	Pathfinding();
	Pathfinding(std::vector<Lieu> points, bool affichage);
	~Pathfinding();
	std::vector<std::tuple<int, int>> trouverParcoursInitial();
	void ameliorerParcours(std::vector<std::tuple<int, int>> out, std::vector<std::vector<double>> cost_matrix);
	bool verifierSolution();
	bool verifierSolutionOpt(std::vector<Lieu> &list);
	double calculerCout(std::vector<std::tuple<int, int>> out, std::vector<std::vector<double>> cost_matrix);
	std::vector<std::tuple<int, int>> supprimerDoublon(std::vector<std::tuple<int, int>> in);
	void misAJourLienAvecEntree(std::vector<std::tuple<int, int>> arcs);
	void misAJourLienAvecEntreeOpt(std::vector<std::tuple<int, int>> arcs, std::vector<Lieu> &list);
	void printSolution(std::vector<std::tuple<int, int>> out);
	void remplirSommetAvecSentiers(int depart, int fin);


private:
	std::vector<Lieu> listePoints;
	bool m_affichage;
};

