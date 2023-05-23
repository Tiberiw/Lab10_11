#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;


class Carte {
private:
	string titlu;
	string autor;
	string gen;
	string an;

public:
	/* Constructor default */
	Carte() = default;

	/* Constructor explicit */
	Carte(string title, string author, string type, string year)
		:titlu{ title }, autor{ author }, gen{ type }, an{ year } {};
	
	/* Constructor de copiere (default) */
	Carte(const Carte& oth) = default;

	/* Returneaza titlul obiectului
	* return : string
	*/
	string get_titlu() const;

	/* Returneaza autorul obiectului
	* return : string
	*/
	string get_autor() const;

	/* Returneaza genul obiectului
	* return : string
	*/
	string get_gen() const;

	/* Returneaza anul aparitiei obiectului (an,luna,zi)
	* return : string
	*/
	string get_an_aparitie() const;

	/* Returneaza luna aparitiei obicetului
	* return : int
	*/
	int get_luna() const;

	/* Returneaza ziua aparitiei obiectului
	* return : int
	*/
	int get_zi() const;

	/* Returneaza anul aparietiei obiectului
	* return : int
	*/
	int get_an() const;

	bool operator== (Carte other) {

		return this->titlu == other.titlu && this->autor == other.autor;
	}

	Carte& operator= (const Carte& other) {
		this->titlu = other.titlu;
		this->autor = other.autor;
		this->gen = other.gen;
		this->an = other.an;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Carte& carte);
	friend std::istream& operator>>(std::istream& strea, Carte& carte);
};

/* Testeaza metodele din clasa Carte */
void testDomain();

vector<string> ConvertString(string full_string);

bool cmpByTitle(const Carte& x, const Carte& y);

bool cmpByAuthor(const Carte& x, const Carte& y);

bool cmpByYear(const Carte& x, const Carte& y);

bool cmpByTypeANDYear(const Carte& x, const Carte& y);
