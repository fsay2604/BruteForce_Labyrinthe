// Francois Charles Hebert
// Laboratoire 4 du cours de structure de données dans les jeux.
// 30 septembre 2020

#include "labyrinthe.h"

int main()
{
	labyrinthe labyrinthe;

	labyrinthe.init();

	cout << "Voici le labyrinthe non solutionner: " << endl;
	labyrinthe.print(cout);
	cout << endl;

	labyrinthe.findPath();
	system("pause");
	labyrinthe.print(cout);
}


