// Francois Charles hebert
// Lab 4 partie 2 : Creation de la structure Stack.
// 05 octobre 2020


#include <cassert>

template <class TYPE>
class stack
{
private:
	struct cellule
	{
		TYPE element;							// element de la cellule
		cellule* next;							// pointeur vers la prochaine cellule

		cellule(const TYPE& elem, cellule* n = nullptr)	// constructeur de la structure
		{
			element = elem;
			next = n;
		}
	};

	cellule* _top;								// premier element de la stack

	// Méthode Private
	stack(const stack& s);						// Mettre la methode dans le private avec aucune instruction a pour effet de la desactiver

	// Fonction qui copie une cellule
	// param: cellule* cell		correspond a la position dans la stack
	// return cellule *
	cellule* copyCell(cellule* cell)
	{
		if (cell == nullptr)					// Si le ptr est null, on est a la derniere cellule de la stack. (condition d'arret)
			return nullptr;

		return new cellule(cell->element, copyCell(cell->next));	// Recursive
	}

public:
	stack();
	~stack();

	void push(const TYPE& e);
	void pop();

	const TYPE& top() const;
	TYPE& top();
	int size()const;

	bool empty()const;
	void clear();


	const stack<TYPE>& operator=(const stack<TYPE>& s); //affectateur 

	bool operator==(const stack<TYPE>& s)const;
};

// Copieur, desactive ne retourne rien.
template<class TYPE>
inline stack<TYPE>::stack(const stack& s)
{
	return;
}

// Constructeur par defaut.
template<class TYPE>
inline stack<TYPE>::stack()
{
	_top = nullptr;
}

// Destructeur par defaut.
template<class TYPE>
inline stack<TYPE>::~stack()
{
	clear();
}

// Methode qui ajoute un element sur la stack.
// param: TYPE& e	Correspond a l'element a ajouter sur la stack.
template<class TYPE>
inline void stack<TYPE>::push(const TYPE& e)
{
	_top = new cellule(e, _top);	// appelle le contructeur de la structure en private
}

// Fonction qui enleve l'element sur le top de la stack.
template<class TYPE>
inline void stack<TYPE>::pop()
{
	assert(!empty());		// Le vecteur ne doit pas etre vide.

	cellule* newTop = _top->next;
	delete _top;
	_top = newTop;
}

// Fonction qui renvoit la valeur sur le dessus de la stack.
template<class TYPE>
inline const TYPE& stack<TYPE>::top() const
{
	assert(!empty());			// La stack ne doit pas etre vide.
	return _top->element;
}

// Methode qui retourne la valeur du dessus de la stack. (en setteur)
template<class TYPE>
inline TYPE& stack<TYPE>::top()
{
	assert(!empty());			// La stack ne doit pas etre vide.
	return _top->element;
}

// Methode qui passe au travers de la stack avec un iterateur et renvoit le size de la stack.
template<class TYPE>
inline int stack<TYPE>::size() const
{
	int size = 0;
	cellule* iterator = _top;
	while (iterator != nullptr)
	{
		size++;
		iterator = iterator->next;
	}
	return size;
}

// Vide le contenu de la stack.
template<class TYPE>
inline bool stack<TYPE>::empty()const
{
	return _top == nullptr;
}

// Methode qui efface le contenu de la stack.
template<class TYPE>
inline void stack<TYPE>::clear()
{
	while (!empty())
		pop();
}

/*
// Affectateur personnalisé a l'objet
// Return une stack
// Methode Iterative
template<class TYPE>
inline const stack<TYPE>& stack<TYPE>::operator=(const stack<TYPE>& s)
{
	if (this == &s)																	// si c'est la meme adresse implicite et explicite return
		return *this;

	clear();																		// vide la stack implicite pour le copier

	if (!s.empty())																	// tant que le stack explicite n'est pas vide
	{
		// Initialisation des iterateurs
		cellule* itExplicite = s._top;
		cellule* itImplicite = nullptr;

		itImplicite = _top = new cellule(s._top->element);							// changement de la valeur _top de l'implicite pour la valeur de _top de l'explicite
		itExplicite = itExplicite->next;											// pointe sur une cellule plus loin de la stack explicite

		while (itExplicite != nullptr)
		{
			itImplicite = itImplicite->next = new cellule(itExplicite->element);	// On cree une nouvelle cellule pareille comme dans la stack explicite, on l'affecte une case plus loin dans la stack implicite et on affecte cette position dans l'iterator.
			itExplicite = itExplicite->next;										// Avance d'une case dans la stack explicite.
		}
	}
	return *this;
}*/


// Affectateur personnalisé a l'objet
// Return une stack
// Methode recursive
template<class TYPE>
inline const stack<TYPE>& stack<TYPE>::operator=(const stack<TYPE>& s)
{
	if (this == &s)																	// si c'est la meme adresse implicite et explicite return
		return *this;

	clear();																		// vide la stack implicite pour le copier

	_top = copyCell(s._top);														// methode recursive qui copie les elements d'une stack dans la stack implicite.

	return *this;
}

template<class TYPE>
inline bool stack<TYPE>::operator==(const stack<TYPE>& s) const
{
	// Iterateur
	cellule* itImplicite = _top;
	cellule* itExplicite = s._top;

	while (itImplicite != nullptr && itExplicite != nullptr)		// Tant qu'on arrive pas au bout de la stack les iterateurs ne seront pas nullptr.
	{
		if (itImplicite->element != itExplicite->element)			// si le contenu des adresses dans les iterateurs sont differents, alors on les stacks ne sont pas egale
			return false;

		itImplicite = itImplicite->next;							// Avance d'une position dans la stack implicite
		itExplicite = itExplicite->next;							// Avance d'une position dans la stack explicite
	}

	return true;
}
