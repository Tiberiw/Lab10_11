#pragma once
#include "domain.h"
//#include <iostream>

typedef Carte TElement;

class Repository {
private:
	vector<TElement> all;
	
public:
	Repository() = default;
	Repository(const Repository& other) = delete;

	virtual void adauga(const TElement& el) ;

	virtual TElement sterge(string titlu, string autor);

	virtual TElement modifica(string titlu, string autor, const TElement& el); //id = titlu //INTREABA DC MERGE CU CONST

	TElement cauta(string titlu, string autor) const;

	const vector<TElement>& get_all() const;

	size_t dimensiune() const;
};

class RepositoryFisier : public Repository {
private:
	string pathFisier;
	void loadFromFile();
	void storeToFile();
public:
	RepositoryFisier(string path) : Repository() {
		pathFisier = path;
		loadFromFile();
	};
	RepositoryFisier(const RepositoryFisier& ot) = delete;
	~RepositoryFisier() = default;
	void adauga(const TElement& el) override {
		Repository::adauga(el);
		storeToFile();
	}

	TElement sterge(string titlu, string autor) override {
		TElement element_del = Repository::sterge(titlu, autor);
		storeToFile();
		return element_del;
	}

	TElement modifica(string titlu, string autor, const TElement& el) override {
		TElement element_mod = Repository::modifica(titlu, autor, el);
		storeToFile();
		return element_mod;
	}
};

void testRepository();
void testRepositoryFisier();
