#include "domain.h"
#include <sstream>
#include <assert.h>

string Carte::get_titlu() const {
	return this->titlu;
}

string Carte::get_autor() const {
	return this->autor;
}

string Carte::get_gen() const {
	return this->gen;
}

string Carte::get_an_aparitie() const {
	return this->an;
}

int Carte::get_an() const {
	//Avem stringul initial
	string full = this->an;

	//Vectorul cu striguri delimitate dupa(".")
	vector<string> segmented = ConvertString(full);

	string an_string = segmented.at(2);

	int an_int = stoi(an_string);

	return an_int;

}

int Carte::get_luna() const {
	//Avem stringul initial
	string full = this->an;

	//Vectorul cu striguri delimitate dupa(".")
	vector<string> segmented = ConvertString(full);

	string luna_string = segmented.at(1);

	int luna_int = stoi(luna_string);

	return luna_int;

}

int Carte::get_zi() const {
	//Avem stringul initial
	string full = this->an;

	//Vectorul cu striguri delimitate dupa(".")
	vector<string> segmented = ConvertString(full);

	string zi_string = segmented.at(0);

	int zi_int = stoi(zi_string);

	return zi_int;

}


bool cmpByTitle(const Carte& x, const Carte& y) {
	return x.get_titlu() < y.get_titlu();
}

bool cmpByAuthor(const Carte& x, const Carte& y) {
	return x.get_autor() < y.get_autor();
}

bool cmpByYear(const Carte& x, const Carte& y) {
	if (x.get_an() == y.get_an()) {
		if (x.get_luna() == y.get_luna())
			return x.get_zi() < y.get_zi();
		return x.get_luna() < y.get_luna();
	}
	return x.get_an() < y.get_an();
}

bool cmpByTypeANDYear(const Carte& x, const Carte& y) {
	if (x.get_gen() == y.get_gen())
		return cmpByYear(x, y);
	return x.get_gen() < y.get_gen();
}



void testDomain() {

	Carte Carte1{ "Abc","Bca","Cab","01.02.2003" };
	assert(Carte1.get_titlu() == "Abc");
	assert(Carte1.get_autor() == "Bca");
	assert(Carte1.get_gen() == "Cab");
	assert(Carte1.get_an_aparitie() == "01.02.2003");
	assert(Carte1.get_zi() == 1);
	assert(Carte1.get_luna() == 2);
	assert(Carte1.get_an() == 2003);
}

vector<string> ConvertString(string full_string) {

	//Vectorul in care avem separat an,luna,zi
	vector<string> sol;

	//Creeam obiectul de tip stringstream
	std::stringstream stringuri(full_string);

	//Cat timp mai putem face prelucrari.
	while (stringuri.good()) {

		//Declaram un string in care punem substringul
		string substring;

		//Adaugam in substring an/luna/zi
		getline(stringuri, substring, '.');

		//Adaugam in solutie substringurile
		sol.push_back(substring);
	}
	
	//Returnam solutia
	return sol;
}

std::ostream& operator<<(std::ostream& stream, const Carte& carte) {

	stream << carte.get_titlu() << " " << carte.get_autor() << " ";
	stream << carte.get_gen() << " " << carte.get_an_aparitie() << "\n";

	return stream;
}

std::istream& operator>>(std::istream& stream, Carte& carte) {

	stream >> carte.titlu >> carte.autor >> carte.gen >> carte.an;

	return stream;
}