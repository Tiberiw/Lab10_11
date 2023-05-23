#include "ServiceCos.h"
#include <assert.h>
#include <random>
#include <iostream>
#include <fstream>

using std::shuffle;

void ServiceCos::add(string title) {
	auto all = repository.get_all();
	for (const auto& el : all) {
		if (el.get_titlu() == title)
			COS.push_back(el);
	}
}

void ServiceCos::clear() {
	COS.clear();
}

int ServiceCos::genereaza(int nr) {
	auto all = repository.get_all();
	shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (COS.size() < nr && all.size() > 0) {
		COS.push_back(all.back());
		all.pop_back();
	}

	return COS.size();
}

vector<TElement> ServiceCos::get_all() {
	return COS;
}

void ServiceCos::exportCOS(string path) {

	std::ofstream out;

	out.open(path, std::ios::out | std::ios::trunc);


	string extensie = path.substr(path.size() - 4, path.size());
	if (extensie == ".csv") {
		out << "Cos de cumparaturi:\n";
		for (auto& carte : COS) {
			out << carte.get_titlu() << ";" << carte.get_autor() << ";";
			out << carte.get_gen() << ";" << carte.get_an_aparitie() << "\n";
		}
	
	}
	else
		for (auto& carte : COS)
			out << carte;
	
		
	out.close();
}

void testServiceCos() {
	Repository testRepo;
	ServiceCos service{ testRepo };

	Carte Carte1{ "aa","bb","cc","01.03.2006" };
	testRepo.adauga(Carte1);
	testRepo.adauga(Carte{ "qq","qq","qq","1.1.1900" });
	service.add("aa");
	service.add("qq");
	auto all = service.get_all();
	assert(all.size() == 2);
	service.clear();

	all = service.get_all();
	assert(all.size() == 0);

	int nr = service.genereaza(2);
	assert(nr == 2);

	service.exportCOS("exporttest.csv");
	service.exportCOS("exporttest.txt");

	testRepo.sterge("aa", "bb");
	testRepo.sterge("qq", "qq");

}