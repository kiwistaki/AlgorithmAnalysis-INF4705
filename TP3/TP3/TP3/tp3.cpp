#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <tuple>
#include "Lieu.h"
#include "Pathfinding.h"

const int ASCII_OFFSET = 48;

void print(std::vector<std::tuple<int, int>> out);

int main(int argc, char** argv)
{

	if (argc < 3)
	{
		std::cout << "Wrong number of arguments..." << std::endl;
		return EXIT_FAILURE;
	}

	std::string e = argv[1];
	if (e != "-e")
	{
		std::cout << "Wrong argument..." << std::endl;
		return EXIT_FAILURE;
	}

	std::string path = argv[2];
	std::ifstream myFile;

	std::string option1;
	if (argc > 3) {
		option1 = argv[3];
	}
	std::string option2;
	if (argc > 4) {
		option2 = argv[4];
	}
	bool affichage = false;
	bool tempsExec = false;
	if (option1 == "-p" || option2 == "-p")
	{
		affichage = true;
	}
	if (option1 == "-t" || option2 == "-t")
	{
		tempsExec = true;
	}


	int nb_points = 0;
	std::vector<int> points;
	std::vector<int> max_trail;
	typedef std::vector<std::vector<double>> matrix;
	matrix cost_matrix;
	std::string::size_type sz;

	myFile.open(path);
	if (myFile.is_open()) 
	{
		// get first line for number of points
		std::string str;
		std::getline(myFile, str);
		nb_points = std::stoi(str, &sz);
		cost_matrix = matrix(nb_points, std::vector<double>(nb_points));

		// get second line for points type
		std::getline(myFile, str);
		for (int i = 0; i < (int)str.size(); i++) 
		{
			if (str[i] != ' ') 
			{
				points.push_back(str[i] - ASCII_OFFSET);
			}
		}

		// get third line for points max trail link
		std::getline(myFile, str);
		for (int i = 0; i < (int)str.size(); i++) 
		{
			if (str[i] != ' ') 
			{
				max_trail.push_back(str[i] - ASCII_OFFSET);
			}
		}

		int i = 0;
		while (!myFile.eof()) 
		{
			std::getline(myFile, str);
			if (str == "") 
			{
				break;
			}
			int j = 0;
			size_t pos = 0;
			std::string delimiter = " ";
			std::string token;
			while ((pos = str.find(delimiter)) != std::string::npos) 
			{
				token = str.substr(0, pos);
				cost_matrix[i][j] = atof(token.c_str());
				str.erase(0, pos + delimiter.length());
				j++;
			}
			cost_matrix[i][j] = atof(str.c_str());			
			i++;
		}	
	}
	myFile.close();

	std::vector<Lieu> listPts;
	for (int i = 0; i < nb_points; i++)
	{
		std::vector<double> costs;
		for (int j = 0; j < nb_points; j++)
		{
			costs.push_back(cost_matrix[i][j]);
		}

		listPts.push_back(Lieu(i, points.at(i), max_trail.at(i), costs));
	}

	Pathfinding paths = Pathfinding(listPts, affichage);
	std::vector<std::tuple<int, int>> arcs;
	arcs = paths.trouverParcoursInitial();
	// Do heuristic and/or metaheuristic
	paths.ameliorerParcours(arcs, cost_matrix);

	return EXIT_SUCCESS;
}

void print(std::vector<std::tuple<int, int>> out)
{
	for (int i = 0; i < (int)out.size(); i++)
	{
		std::cout << std::get<0>(out.at(i)) << " ";
		std::cout << std::get<1>(out.at(i)) << std::endl;
	}
	std::cout << "fin" << std::endl;
}
