#pragma once
#include "repository.h"
#include <map>

using std::map;

class UndoOperation;

class Service {
private:
	Repository& repository;
	vector< UndoOperation* > UndoList;
public:
	Service() = delete;
	Service(Repository& repo) : repository{ repo } {};
	Service(const Service& other) = delete;
	void add(string title, string author, string type, string date);
	TElement mod(string title, string autor, string new_ty, string new_da);
	TElement del(string title, string autor);
	TElement search(string title, string autor) const;
	vector<TElement> get_filtered(string filter_type, string filter) const;
	
	vector<TElement> Gsort(bool (*relation)(const TElement& x,const TElement& y)) const;

	map<string,int> GenerateRaportType();

	void undo();
};	




class UndoOperation {

public:
	//UndoOperation();
	virtual ~UndoOperation() {};
	virtual void doUndo() = 0;
};

class UndoAdauga : public UndoOperation {

public:
	UndoAdauga(Repository& repo, const Carte& carte) : repository{ repo }, carteAdaugata{ carte } {}
	void doUndo() {
		repository.sterge(carteAdaugata.get_titlu(), carteAdaugata.get_autor());
	};

private:
	Carte carteAdaugata;
	Repository& repository;
};

class UndoSterge : public UndoOperation {
public:
	UndoSterge(Repository& repo, const Carte& carte) : repository{ repo }, carteStearsa{ carte } {}
	void doUndo() {
		repository.adauga(carteStearsa);
	}
private:
	Repository& repository;
	Carte carteStearsa;
};

class UndoModifica : public UndoOperation {

public:
	UndoModifica(Repository& repo, const Carte& carte) : repository{ repo }, carteVeche{ carte } {}
	void doUndo() {
		repository.modifica(carteVeche.get_titlu(), carteVeche.get_autor(), carteVeche);
	}
private:
	Repository& repository;
	Carte carteVeche;
};








void testService();
void testUndo();
