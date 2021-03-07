// Francois CHarles Hebert
// Laboratoire 4 du cours de structure de données dans les jeux.
// Objet Labyrinthe qui consiste a trouver un chemin pour résoudre un labyrinthe.

#include "labyrinthe.h"

void labyrinthe::init()
{
	// Remplir la map du labyrinthe
	string input, nomFichier;
	string suffixe = ".txt";
	string prefixe = "labyrinthe";

	do {
		if (!_map.isNULL())
			_map.clear();

		cout << "Entrer le numero du labyrinthe a resoudre: ";
		cin >> input;

		nomFichier = prefixe + input + suffixe;						// Concatene le nom du fichier pour la lecture.
		readFile(_map, nomFichier.c_str(), _startPos, _finishPos);	// Lecture et remplissage de la map + position

	} while (_map.isNULL());										// On demande la map tant qu'elle est vide.

	// Definit la position de depart et darrive dans la map
	_map[_finishPos.posLine][_finishPos.posCol] = 'F';
	_map[_startPos.posLine][_startPos.posCol] = 'D';

	// init du debut du chemin
	_startPos.direction = 'N';										// Direction Autre
	_finishPos.direction = 'A';
	_path.push(_startPos);											// Ajoute la position de départ a la pile
}

// Fonction qui cherche un chemin vers la position finale
void labyrinthe::findPath()
{
	moves next, current;

	while (!_path.empty())											// Tant que la stack n'est pas vide.
	{
		current = _path.top();
		_path.pop();												// Désempiler la position actuelle

		while (current.direction != 'A')							// Tant que la position n'est pas autre.
		{
			next = nextMove(current);								// Déterminer la nouvelle position selon la direction de la position actuelle 

			if (next.posLine == _finishPos.posLine && next.posCol == _finishPos.posCol)		// Si nouvelle position est celle de l’arrivée 
			{
				_map[current.posLine][current.posCol] = 'V';		// on marque l'endroit comme visiter
				_path.push(current);								// Empiler la position actuelle
				_path.push(_finishPos);								// Empiler la position de l'arrivée
				savePath();											// Enregistre le chemin final
				return;
			}

			if (_map[next.posLine][next.posCol] == '0')				// Sinon si on peut avancer (la nouvelle position rencontre un 0) 
			{
				_map[next.posLine][next.posCol] = 'V';				// on marque l'endroit comme visiter
				_path.push(current);								// On empile la position actuelle
				next.direction = 'N';								// Modifie la direction de la nouvelle position pour Nord
				_path.push(next);									// Empile la nouvelle position (avance)
				current = next;										// Mettre la nouvelle position dans la position actuelle 
			}
			else
				current = changeDirection(current);					// Tourner à partir de la position actuelle
		}
	}
	cout << "Impossible de sortir du labyrinthe." << endl;
}

//Fonction qui set le prochain move
//param:	moves current	Correspond a la position actuelle 
//return:	moves			Correspond au prochain move.
moves labyrinthe::nextMove(moves current)
{
	moves nextMove = current;

	// En fonction de la position actuelle, on verifie la position apres (line,col) => N,E,S,O
	switch (current.direction)
	{
	case 'N':
		nextMove.posLine -= 1;
		break;

	case 'E':
		nextMove.posCol += 1;
		break;

	case 'S':
		nextMove.posLine += 1;
		break;

	case 'O':
		nextMove.posCol -= 1;
		break;
	}

	return nextMove;
}

//Fonction qui sert a changer la direction d'un move
// param: moves current		Correspond au a la position actuelle que l'on veut tourner.
//return: moves		Retourne un move par valeur avec une nouvelle direction.
moves labyrinthe::changeDirection(moves current)
{
	moves nextMove = current;

	// En fonction de la position actuelle, on verifie la position apres (line,col) => N,E,S,O
	switch (current.direction)
	{
	case 'N':
		nextMove.direction = 'E';
		break;

	case 'E':
		nextMove.direction = 'S';
		break;

	case 'S':
		nextMove.direction = 'O';
		break;

	case 'O':
		nextMove.direction = 'A';
		break;
	}

	return nextMove;
}

// Fonction qui change la valeur de la map pour C quand on a trouver le chemin gagnant
void labyrinthe::savePath()
{
	// Boucle qui depile le stack contenant le chemin
	while (!_path.empty())
	{
		if (_path.top().posLine == _startPos.posLine && _path.top().posCol == _startPos.posCol)
			_map[_path.top().posLine][_path.top().posCol] = 'D';										// change la valeur dans la map
		else if (_path.top().posLine == _finishPos.posLine && _path.top().posCol == _finishPos.posCol)
			_map[_path.top().posLine][_path.top().posCol] = 'F';										// change la valeur dans la map
		else
			_map[_path.top().posLine][_path.top().posCol] = 'C';										// change la valeur dans la map

		_path.pop();																					// on depile le chemin.
	}
}

// Fonction qui imprime en console 
void labyrinthe::print(ostream& out) const
{
	for (int i = 0; i < _map.get_nbLine(); i++)
	{
		for (int j = 0; j < _map.get_nbCol(); j++)
		{
			if (_map[i][j] == '1')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	// colorie en bright blue
				out << '\xFE' << ' ';
			}
			else if (_map[i][j] == 'D')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	// colorie en blanc
				out << 'D' << ' ';
			}
			else if (_map[i][j] == 'F')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);	// colorie en blanc
				out << 'F' << ' ';
			}
			else if (_map[i][j] == 'C')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);	// colorie en rouge
				out << '\xFE' << ' ';
			}
			else
			{
				out << ' ' << ' ';
			}
		}
		out << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);				// colorie en blanc
}



