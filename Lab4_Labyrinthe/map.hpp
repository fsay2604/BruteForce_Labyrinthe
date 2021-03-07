/// Auteur: Francois Charles Hebert
/// Date: 14 septembre 2020
/// Creation d<une classe map generique qui servira lorsqu'une matrice carre devra etre manipule

#pragma once
#include <cassert>
#include <iostream>
#include <fstream>

template <class TYPE>
class map
{
private:
	char* _name;				// Pointeur sur le nom de la map
	TYPE** _map;				// La map dynamique en ligne et en colonne
	int _nbLine,				// nombre de ligne de la matrice
		_nbCol;					// nombre  de colonne pour la matrice
public:
	map();
	map(const char* name, int line = 0, int col = 0);
	map(const map<TYPE>& map);
	~map();
	void clear();				// clear la map + _name
	void clearMap();			// clear la map et les dimensions sont remise a 0
	void clearName();			// clear le _name

	int get_nbLine()const;
	int get_nbCol()const;
	void resize(int nbLine, int nbCol);
	const char* get_name()const;
	void set_name(const char* name);
	bool isNULL()const;

	TYPE& at(int i, int j)const;
	TYPE* operator[](int index)const;

	void print(std::ostream& out)const;
	void read(std::istream& in);

	const map<TYPE>& operator=(const map<TYPE>& map);
};
template <class TYPE>
std::ostream& operator<<(std::ostream& out, const map<TYPE>& map);
template <class TYPE>
std::istream& operator>>(std::istream& in, map<TYPE>& map);

//	Constructeur
template <class TYPE>
map<TYPE>::map()
{
	_map = nullptr;
	_nbLine = _nbCol = 0;
	_name = nullptr;
}

// Constructeur avec parametre
template <class TYPE>
map<TYPE>::map(const char* name, int line, int col)
{
	assert(line >= 0 && col >= 0);
	assert(!(line == 0 && col != 0));
	assert(!(col == 0 && line != 0));


	_nbLine = line;
	_nbCol = col;

	_name = nullptr;
	int nameSize = strlen(name);
	if (nameSize)
	{
		_name = new char[nameSize + 1];			//+1 a cause du '\0' a la fin
		strcpy_s(_name, nameSize + 1, name);
	}

	if (_nbLine > 0 && _nbCol > 0)
	{
		//creation de la matrice
		_map = new (TYPE * [_nbLine]);
		for (int i = 0; i < _nbLine; i++)
			*(_map + i) = new TYPE[_nbCol];
	}
	else
	{
		_nbLine = _nbCol = 0;
		_map = nullptr;
	}
}

// Copieur
template<class TYPE>
inline map<TYPE>::map(const map<TYPE>& map)
{
	_nbCol = map._nbCol;
	_nbLine = map._nbLine;
	_map = nullptr;
	_name = nullptr;

	int nameSize = strlen(map._name);;
	if (nameSize)
	{
		_name = new char[nameSize + 1];			//+1 a cause du '\0' a la fin
		strcpy_s(_name, nameSize + 1, map._name);
	}

	if (_nbCol > 0 && _nbLine > 0)
	{
		_map = new (TYPE * [_nbLine]);

		for (int i = 0; i < _nbLine; i++)
		{
			*(_map + i) = new (TYPE[_nbCol]);
		}

		if (!map._map)
		{
			for (int i = 0; i < _nbLine; i++)
				for (int j = 0; j < _nbCol; j++)
					*(*(_map + i) + j) = *(*(map._map + i) + j);
		}

	}
}

// Destructeur
template <class TYPE>
map<TYPE>::~map() {
	clear();
}

//Fonction qui supprime toute la map.
template<class TYPE>
inline void map<TYPE>::clear()
{
	clearMap();
	clearName();
}

//Fonction qui efface le contenu de la _map
template<class TYPE>
inline void map<TYPE>::clearMap()
{
	for (int i = 0; i < _nbLine; i++)
		delete[] * (_map + i);

	delete[] _map;
	_map = nullptr;
	_nbCol = _nbLine = 0;
}

//Fonction qui supprime le _name de la map.
template<class TYPE>
inline void map<TYPE>::clearName()
{
	delete[] _name;
	_name = nullptr;
}

//Renvoit le nombre de ligne de la matrice
template<class TYPE>
inline int map<TYPE>::get_nbLine() const
{
	return _nbLine;
}

//Renvoit le nombre de colonne dans chaque ligne de la matrice.
template<class TYPE>
inline int map<TYPE>::get_nbCol() const
{
	return _nbCol;
}

//Fonction qui resize la map selon les parametres
//param int nbLine	Correspond au nombre de ligne voulu dans la matrice.
//param int nbCol	Correspond au nombre de colonne voulu dans la matrice.
//Return void;
template<class TYPE>
inline void map<TYPE>::resize(int nbLine, int nbCol)
{
	assert(nbLine >= 0 && nbCol >= 0);
	assert(!(nbLine == 0 && nbCol != 0));
	assert(!(nbCol == 0 && nbLine != 0));

	if (nbLine == 0 && nbCol == 0)
	{
		clearMap();
		return;
	}
	else
	{
		TYPE** newMap = new(TYPE * [nbLine]);

		//creation de la matrice
		for (int i = 0; i < nbLine; i++)
			*(newMap + i) = new TYPE[nbCol];

		for (int i = 0; i < nbLine && i < _nbLine; i++)
			for (int j = 0; j < nbCol && j < _nbCol; j++)
				*(*(newMap + i) + j) = *(*(_map + i) + j);		// copie les valeurs s	

		delete[] _map;											// Delete le contenu
		_map = newMap;											// Copie le contenu
		_nbLine = nbLine;
		_nbCol = nbCol;
	}
}

//Fonction qui retourne le nom de la map
template<class TYPE>
inline const char* map<TYPE>::get_name() const
{
	if (_name == nullptr)
		return "";
	return _name;
}

//Fonction qui set un nom a l'objet map
template<class TYPE>
inline void map<TYPE>::set_name(const char* name)
{
	clearName();

	int nameSize = strlen(name);
	if (nameSize)
	{
		_name = new char[nameSize + 1];			//+1 a cause du '\0' a la fin
		strcpy_s(_name, nameSize + 1, name);
	}
}

/// Fonction qui verifie si la map est NULL
/// return TRUE si la map est NULL
/// return FALSE si la map n'est pas NULL
template<class TYPE>
inline bool map<TYPE>::isNULL()const
{
	return _map == nullptr;
}

//Fonction qui renvoit le contenu a la position map[i][j]
template<class TYPE>
inline TYPE& map<TYPE>::at(int i, int j) const
{
	assert(i >= 0 && i < _nbLine);
	assert(j >= 0 && j < _nbCol);

	if (_map)
		return *(*(_map + i) + j);
}

//Fonction qui retourne le contenu de _map[index]
template<class TYPE>
inline TYPE* map<TYPE>::operator[](int index) const
{
	assert(index >= 0 && index < _nbLine);
	if (_map)
		return *(_map + index);
}

//Fonction qui imprine le contenu objet.
template <class TYPE>
void map<TYPE>::print(std::ostream& out)const
{
	for (int i = 0; i < _nbLine; i++)
	{
		for (int j = 0; j < _nbCol; j++)
		{
			out << *(*(_map + i) + j);
		}
		out << std::endl;
	}

}

// Fonction qui lit un stream et qui remplit la map.
// param: std::ifstream& in	Le stream dans lequel lire.
// return void;
template<class TYPE>
inline void map<TYPE>::read(std::istream& in)
{
	for (int i = 0; i < _nbLine; i++)
	{
		for (int j = 0; j < _nbCol; j++)
		{
			in >> *(*(_map + i) + j);			//met la valeur lu dans la colonne
		}
	}

}

//Operator = surcharger
template<class TYPE>
inline const map<TYPE>& map<TYPE>::operator=(const map<TYPE>& map)
{
	if (this == &map)										//si les objet on la meme adresse memoire
		return *this;

	_nbCol = map._nbCol;
	_nbLine = map._nbLine;
	_map = nullptr;

	set_name(map.get_name());

	if (_nbCol > 0 && _nbLine > 0)
	{
		_map = new (TYPE * [_nbLine]);

		for (int i = 0; i < _nbLine; i++)
		{
			*(_map + i) = new (TYPE[_nbCol]);
			for (int j = 0; j < _nbCol; j++)
				*(*(_map + i) + j) = *(*(map._map + i) + j);
		}

	}
	return *this;
}

//operator << surcharger
template<class TYPE>
inline std::ostream& operator<<(std::ostream& out, const map<TYPE>& map)
{
	map.print(out);
	return out;
}

//operator >> surcharger
template<class TYPE>
inline std::istream& operator>>(std::istream& in, map<TYPE>& map)
{
	map.read(in);
	return(in);
}
