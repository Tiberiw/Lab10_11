#include "service.h"
#include <assert.h>
#include <iostream>
#include <algorithm>


void Service::add(string titlu, string autor, string gen, string an) {

	Carte carte{ titlu,autor,gen,an };
	//carte.valid();
	repository.adauga(carte);

	//UNDO
	UndoList.push_back(new UndoAdauga{ repository,carte });
}

TElement Service::del(string titlu, string autor) {

	Carte carte = repository.cauta(titlu,autor);

	//UNDO
	UndoList.push_back(new UndoSterge{ repository,carte });

	return repository.sterge(titlu,autor);
}

TElement Service::mod(string titlu, string autor, string new_ty, string new_da) {

	Carte carte = repository.cauta(titlu,autor);
	Carte new_carte{ titlu,autor,new_ty,new_da };

	//UNDO
	UndoList.push_back(new UndoModifica{ repository,carte });

	return repository.modifica(titlu,autor, new_carte);
}

TElement Service::search(string titlu, string autor) const {
	return repository.cauta(titlu, autor); }

vector<TElement> Service::get_filtered(string filter_type, string filter="") const {
	
	vector<TElement> all = repository.get_all();

	if (filter_type == "")
		return all;

	vector<TElement> rez;

	for (auto el : all){
			if (filter_type == "titlu" && el.get_titlu() == filter)
				rez.push_back(el);
			if (filter_type == "an" && el.get_an_aparitie() == filter)
				rez.push_back(el);

	}

	return rez;
}


vector<TElement> Service::Gsort(bool (*relation)(const TElement& x, const TElement& y)) const{
	
	auto all = repository.get_all();
	sort(all.begin(), all.end(), relation);

	return all;
}

map<string, int> Service::GenerateRaportType() {

	auto all = repository.get_all();
	map<string, int> raport;

	for (const auto& el : all) {
		string gen = el.get_gen();

		if (raport.find(gen) == raport.end()) {
			// not found
			raport[gen] = 1;
		}
		else {
			// found
			raport[gen]++;
		}
	}

	return raport;
}

void Service::undo() {
	if (UndoList.empty()) {
		throw std::exception("Undo Error!");}

	UndoOperation* und = UndoList.back();
	und->doUndo();
	UndoList.pop_back();

	delete und;
}


void testService() {
	Repository RepoTest;
	Service ServiceTest{ RepoTest };
	Carte carte1{ "aa","bb","cc","1.1.1900" };
	try {
		ServiceTest.del("aa", "bb");
		//assert(false);
	}
	catch (std::exception& ex) {
		assert(strcmp(ex.what(), "Element inexistent!") == 0);
	}

	try {
		TElement el = ServiceTest.search("aa", "bb"); }
	catch (std::exception& ex) {
		assert(strcmp(ex.what(), "Element inexistent!") == 0);
	}

	try {
		ServiceTest.mod("aa", "bb", "zz", "10.10.2010");
		//assert(false);
	}
	catch (std::exception& ex) {
		assert(strcmp(ex.what(), "Element inexistent!") == 0);
	}


	ServiceTest.add("aa", "bb", "cc", "1.1.2001");
	ServiceTest.add("aa", "zz", "dd", "1.2.2003");
	ServiceTest.add("ex", "yz", "le", "1.2.2003");
	ServiceTest.add("l", "l", "w", "1.2.2001");

	auto sorted = ServiceTest.Gsort(cmpByTitle);
	auto el = sorted[0];
	auto el2 = sorted[3];
	assert(el.get_titlu() == "aa");
	assert(el2.get_titlu() == "l");

	sorted = ServiceTest.Gsort(cmpByAuthor);
	el = sorted[0];
	el2 = sorted[3];
	assert(el.get_autor() == "bb");
	assert(el2.get_autor() == "zz");

	sorted = ServiceTest.Gsort(cmpByYear);
	el = sorted[0];
	el2 = sorted[3];
	assert(el.get_an_aparitie() == "1.1.2001");
	assert(el2.get_an_aparitie() == "1.2.2003");

	sorted = ServiceTest.Gsort(cmpByTypeANDYear);
	el = sorted[0];
	el2 = sorted[3];
	assert(el.get_gen() == "cc");
	assert(el2.get_gen() == "w");




	try {
		ServiceTest.add("l", "l", "l", "1.1.2001");
		//assert(false);
	}
	catch (std::exception& ex) {
		assert(strcmp(ex.what(), "Element existent!") == 0);
	}
	
	ServiceTest.add("l", "w", "w", "1.1.2001");

	assert(RepoTest.dimensiune() == 5);

	auto toti = ServiceTest.get_filtered("", "");
	assert(toti.size() == 5);
	
	toti = ServiceTest.get_filtered("titlu", "aa");
	assert(toti.size() == 2);

	toti = ServiceTest.get_filtered("titlu", "ex");
	assert(toti.size() == 1);

	toti = ServiceTest.get_filtered("titlu", "abecedar");
	assert(toti.size() == 0);

	toti = ServiceTest.get_filtered("an", "10.06.2003");
	assert(toti.size() == 0);

	toti = ServiceTest.get_filtered("an", "1.2.2003");
	assert(toti.size() == 2);

	ServiceTest.del("l", "w");
	assert(RepoTest.dimensiune() == 4);

	ServiceTest.mod("l", "l", "zz", "1.4.1890");
	TElement elm = ServiceTest.search("l", "l");
	assert(elm.get_an_aparitie() == "1.4.1890");
	assert(elm.get_gen() == "zz");

	ServiceTest.add("ee", "ff", "cc", "12.12.1912");
	sorted = ServiceTest.Gsort(cmpByTypeANDYear);
	el = sorted[0];
	auto el1 = sorted[1];
	el2 = sorted[4];
	assert(el.get_gen() == "cc" && el.get_an_aparitie() == "12.12.1912");
	assert(el1.get_gen() == "cc" && el1.get_an_aparitie() == "1.1.2001");
	assert(el2.get_gen() == "zz");

	ServiceTest.del("l","l");
	ServiceTest.del("ee", "ff");
	ServiceTest.del("aa", "bb");
	ServiceTest.del("aa", "zz");
	ServiceTest.del("ex", "yz");
	assert(RepoTest.dimensiune() == 0);

	ServiceTest.add("l", "l","l","1.2.3004");
	ServiceTest.add("ee", "ff","gg","1.3.2233");
	ServiceTest.add("aa", "bb","cc","4.4.2004");
	ServiceTest.add("aa", "zz","l","10.10.2010");
	ServiceTest.add("ex", "yz","gg","3.10.1330");
	assert(RepoTest.dimensiune() == 5);
	auto rap = ServiceTest.GenerateRaportType();
	
	testUndo();

}

void testUndo() {
	Repository RepoTest;
	Service ServiceTest{ RepoTest };


	ServiceTest.add("l", "l", "l", "1.2.3004");
	ServiceTest.add("ee", "ff", "gg", "1.3.2233");
	ServiceTest.add("aa", "bb", "cc", "4.4.2004");
	ServiceTest.add("aa", "zz", "l", "10.10.2010");
	ServiceTest.add("ex", "yz", "gg", "3.10.1330");
	assert(RepoTest.dimensiune() == 5);

	ServiceTest.undo();
	assert(RepoTest.dimensiune() == 4);
	ServiceTest.del("aa", "zz");
	ServiceTest.undo();
	assert(RepoTest.dimensiune() == 4);

	ServiceTest.mod("l", "l", "ll", "1.1.1111");
	ServiceTest.undo();
	ServiceTest.undo();
	ServiceTest.undo();
	ServiceTest.undo();
	ServiceTest.undo();
	try {
		ServiceTest.undo();
	}
	catch (std::exception&) {
	}



}