#include "repository.h"
#include <exception>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <ios>

void Repository::adauga(const TElement& element) {

	try {
		TElement el = cauta(element.get_titlu(), element.get_autor());
	}
	catch (std::exception&) {
		all.push_back(element);
		return;}

	throw std::exception("Element existent!");
}

TElement Repository::sterge(string title, string author) {
	TElement el = cauta(title, author);

	vector<TElement>::iterator it;

	it = remove(all.begin(), all.end(), el);
	all.erase(it);

	
	
	return el;
}

TElement Repository::modifica(string title, string author, const TElement& el) {

	TElement el_vechi = sterge(title,author);
	all.push_back(el);

	return el_vechi;
}

TElement Repository::cauta(string title, string author) const{

	for(auto it : all)
		if ((it).get_titlu() == title && (it).get_autor() == author)
			return (it);

	throw std::exception("Element inexistent!");}

const vector<TElement>& Repository::get_all() const{
	return all;
}

size_t Repository::dimensiune() const {
	return all.size();
}

void RepositoryFisier::loadFromFile() {

	std::ifstream in(pathFisier);

	if (in.fail()) {
		//Nu s-a deschis fisierul
		throw std::exception("Nu s-a deschis fisierul!");
	}
	while (in.good()) {

		Carte a;
		in >> a;
		
		if (a.get_titlu() == "")
			break;
		
		Repository::adauga(a);
	}

	in.close();
}


void RepositoryFisier::storeToFile() {

	std::ofstream out(pathFisier);
	/*if (!out.is_open()) {
		string Error("Error open" + pathFisier);
		throw std::exception(Error.c_str());
	}*/


	for (auto& carte : get_all())
		out << carte;

	out.close();
}



void testRepository() {

	Repository testRepo;

	Carte Carte1{ "aa","bb","cc","01.03.2006" };
	try {
		testRepo.modifica("aa", "bb", Carte1);
		//assert(false);
	}
	catch (std::exception& ex) {
		assert(strcmp(ex.what(),"Element inexistent!") == 0);
	}

	try {
		testRepo.cauta("aa", "bb");
		//assert(false);
	}
	catch (std::exception& ex) {
		assert(strcmp(ex.what(), "Element inexistent!") == 0);
	}

	try {
		testRepo.sterge("aa", "bb");
		//assert(false);
	}
	catch (std::exception& ex) {
		assert(strcmp(ex.what(), "Element inexistent!") == 0);
	}

	testRepo.adauga(Carte1);

	try {
		testRepo.adauga(Carte1);
		//assert(false);
	}
	catch (std::exception& ex) {
		assert(strcmp(ex.what(), "Element existent!") == 0);
	}
	assert(testRepo.dimensiune() == 1);

	TElement copie = testRepo.cauta("aa", "bb");
	assert(copie == Carte1);

	Carte Carte1_nou{ "aa","bb","zz","5.5.1980" };
	auto el = testRepo.modifica("aa", "bb", Carte1_nou);
	assert(el == Carte1);

	copie = testRepo.cauta("aa", "bb");
	assert(copie.get_titlu() == "aa");
	assert(copie.get_autor() == "bb");
	assert(copie.get_gen() == "zz");
	assert(copie.get_an_aparitie() == "5.5.1980");

	testRepo.adauga(Carte{ "qq","qq","qq","1.1.1900" });

	auto toate_cartile = testRepo.get_all();

	assert(toate_cartile.size() == 2);

	testRepo.sterge("qq", "qq");

	toate_cartile = testRepo.get_all();

	assert(toate_cartile.size() == 1);

	testRepo.sterge("aa", "bb");

	toate_cartile = testRepo.get_all();

	assert(toate_cartile.size() == 0);
	
	assert(testRepo.dimensiune() == 0);

	try {
		testRepo.sterge("aa", "bb");
		//assert(false);
	}
	catch (std::exception& ex) {
		assert(strcmp(ex.what(), "Element inexistent!") == 0);
	}

}

void testRepositoryFisier() {
	{
	RepositoryFisier* repofisierTest = new RepositoryFisier("testrepo.txt");

	Carte c{ "aa","bb","cc","dd" };
	Carte c1{ "ee","ff","cc","dd" };
	Carte c2{ "ee","gg","cc","dd" };
	repofisierTest->adauga(c);
	repofisierTest->adauga(c1);
	repofisierTest->adauga(c2);
	assert(repofisierTest->dimensiune() == 3);
	try {
		repofisierTest->adauga(c2);
	}
	catch (std::exception&) {}
	repofisierTest->sterge(c2.get_titlu(), c2.get_autor());
	assert(repofisierTest->dimensiune() == 2);
	try {
		repofisierTest->sterge(c2.get_titlu(), c2.get_autor());
	}
	catch (std::exception&) {}
	Carte new_c1{ c1.get_titlu(),c1.get_autor(),"ee","1.1.2001" };
	repofisierTest->modifica(c1.get_titlu(), c1.get_autor(), new_c1);
	auto all = repofisierTest->get_all();
	assert(all[0].get_titlu() == "aa");
	assert(all[1].get_titlu() == "ee");
	assert(all[1].get_gen() == "ee" && all[1].get_an_aparitie() == "1.1.2001");
	delete repofisierTest;
	
	}

	RepositoryFisier repo2Tets("testrepo.txt");

	assert(repo2Tets.dimensiune() == 2);
	auto elementREP = repo2Tets.cauta("aa", "bb");
	assert(elementREP.get_an_aparitie() == "dd" && elementREP.get_gen() == "cc");
	elementREP = repo2Tets.cauta("ee", "ff");
	assert(elementREP.get_an_aparitie() == "1.1.2001" && elementREP.get_gen() == "ee");
	repo2Tets.sterge("aa", "bb");
	repo2Tets.sterge("ee", "ff");
	assert(repo2Tets.dimensiune() == 0);
	try {
		RepositoryFisier repo2Test("asdf.txt"); }
	catch (std::exception&) {}



}

