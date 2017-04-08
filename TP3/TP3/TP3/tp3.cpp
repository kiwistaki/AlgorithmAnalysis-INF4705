#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

const int ASCII_OFFSET = 48;

int main(int argc, char** argv) {

	if (argc != 3) {
		std::cout << "Wrong number of arguments..." << std::endl;
		return EXIT_FAILURE;
	}

	std::string e = argv[1];
	if (e != "-e") {
		std::cout << "Wrong argument..." << std::endl;
		return EXIT_FAILURE;
	}
	std::string path = argv[2];
	std::ifstream myFile;
	myFile.open(path);

	int nb_points = 0;
	std::vector<int> points;
	std::vector<int> max_trail;
	typedef std::vector<std::vector<double>> matrix;
	matrix cost_matrix;
	std::string::size_type sz;

	if (myFile.is_open()) {
		// get first line for number of points
		std::string str;
		std::getline(myFile, str);
		nb_points = std::stoi(str, &sz);
		cost_matrix = matrix(nb_points, std::vector<double>(nb_points));

		// get second line for points type
		std::getline(myFile, str);
		for (int i = 0; i < (int)str.size(); i++) {
			if (str[i] != ' ') {
				points.push_back(str[i] - ASCII_OFFSET);
			}
		}
		for (int x = 0; x < nb_points; x++) {
			std::cout << points[x] << " ";
		}
		std::cout << std::endl;

		// get third line for points max trail link
		std::getline(myFile, str);
		for (int i = 0; i < (int)str.size(); i++) {
			if (str[i] != ' ') {
				max_trail.push_back(str[i] - ASCII_OFFSET);
			}
		}
		for (int x = 0; x < nb_points; x++) {
			std::cout << max_trail[x] << " ";
		}
		std::cout << std::endl;

		int i = 0;
		while (!myFile.eof()) {
			std::getline(myFile, str);
			if (str == "") {
				break;
			}
			int j = 0;
			size_t pos = 0;
			std::string delimiter = " ";
			std::string token;
			while ((pos = str.find(delimiter)) != std::string::npos) {
				token = str.substr(0, pos);
				cost_matrix[i][j] = atof(token.c_str());
				str.erase(0, pos + delimiter.length());
				j++;
			}
			cost_matrix[i][j] = atof(str.c_str());
			
			i++;
		}

		for (int i = 0; i < nb_points; i++) {
			for (int j = 0; j < nb_points; j++) {
				std::cout << cost_matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;		
	}
	myFile.close();

	system("pause");
	
	return EXIT_SUCCESS;
}