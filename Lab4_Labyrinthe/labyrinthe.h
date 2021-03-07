// Francois CHarles Hebert
// Laboratoire 4 du cours de structure de données dans les jeux.
// Objet Labyrinthe qui consiste a trouver un chemin pour résoudre un labyrinthe.

#pragma once
#include <iostream>
#include "stack.hpp"
#include "map.hpp"
#include <Windows.h>
using namespace std;

struct moves
{
	int posLine, posCol;
	char direction;
};

class labyrinthe
{
private:
	stack<moves> _path;					// contient l'ensemble des déplacements.
	map<char> _map;						// contient la map de labyrinthe.

	moves _startPos;					// contient la position de départ.
	moves _finishPos;					// contient la position de fin

public:
	void init();

	void findPath();
	moves nextMove(moves current);
	moves changeDirection(moves current);
	void savePath();
	void print(ostream& out)const;
};

// Fonction pour ecrire dans un fichier
// Fonction qui permet d'ecrire dans un fichier la solution de la map
// param	mapSolutionner	Correspond a la map dont on veut ecrire les informations dans le fichier
// param	nomFichier		Correspond au nom du fichier dans lequel on veut ecrire. (sera cree si inexistant)
// return	void
template<class TYPE>
void writeFile(map<TYPE>& mapSolutionner, const char* nomFichier)
{
	string path = "./solution/";
	path += nomFichier;

	ofstream solutionFile(path.c_str());
	if (solutionFile.good())
	{
		solutionFile << "Solution du labyrinthe : " << mapSolutionner.get_name() << endl;
		solutionFile << mapSolutionner;
		solutionFile.close();
	}
	else
		cout << "Erreur d'ecriture de fichier.";
}


// Fonction pour lire dans le fichier et remplir la map.
//	fonction d’ouverture du ficher contenant la matrice 
//	param: mapLue			correspond a la map dans laquelle on insere les elements
//	param: nomFichier		correspond au nom du fichier a lire qui contient les elements
//  param: moves& start		correspond a la position de départ du labyrinthe
//  param: moves& finish	correspond a la position finale du labyrinthe
//	return void;
template<class TYPE>
inline void readFile(map<TYPE>& mapLue, const char* nomFichier, moves& start, moves& finish)
{
	string path = "./Labyrinthe/";
	path += nomFichier;

	ifstream fichier(path.c_str());							//ouverture du ficher.
	int nbLine, nbCol;

	if (fichier.is_open())
	{
		fichier.seekg(0, SEEK_END);
		if (fichier.tellg() == 0)							// si fichier vide.
		{
			cout << "Cette map est vide." << endl;
		}
		else
		{
			fichier.seekg(0, SEEK_SET);						// Retour au debut du fichier si il n'est pas vide.

			mapLue.set_name(nomFichier);
			fichier >> nbLine >> nbCol;						// capture les dimension de la map
			mapLue.resize(nbLine, nbCol);					// resize avec les dimensions capturé.
			mapLue.read(fichier);							// Lecture de la matrice et insertion dans la map

			fichier >> start.posLine >> start.posCol;		// init la position de départ
			fichier >> finish.posLine >> finish.posCol;		// init la position de fin

			fichier.close();
		}

	}
	else
		cout << "Fichier : " << nomFichier << " innexistant!" << endl;
}