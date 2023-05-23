#include "console.h"
#include <iostream>
#include <stdlib.h>

using std::cin;
using std::cout;


void Console::console_print_menu() const{
	cout << "Meniu:\n";
	cout << "(1) Adauga carte.\n(2) Sterge carte.\n(3) Modifica carte.\n";
	cout << "(4) Cauta carte.\n(5) Afiseaza carti.\n";
	cout << "(6) Filtreaza carti.\n(7) Sorteaza carti.\n";
	cout << "(8) Undo.\n(9) Raport dupa gen.\n(10) Print menu\n";
	cout << "\nMeniu Cos:\n";
	cout << "(11) Goleste cos.\n(12) Adauga carte.\n";
	cout << "(13) Genereaza cos.\n(14) Export.\n";
	cout << "\n\n(100) Exit.\n";
}

void Console::console_add() {
	cout << "Introduceti:\n";

	string titlu;
	cout << "Titlu: ";
	cin >> titlu;

	string autor;
	cout << "\nAutor: ";
	cin >> autor;

	string gen;
	cout << "\nGen: ";
	cin >> gen;

	string an;
	cout << "\nAn (FORMAT <-> {zi.luna.an}): ";
	cin >> an;
	if (titlu == "" || autor == "" || gen == "" || an == "") {
		cout << "\nDate invalide!\n";
		return;
	}

	Carte el{ titlu,autor,gen,an };
	if (el.get_zi() < 1 && el.get_zi() > 31) {
		cout << "Zi invalida!";
		return;
		}
			
		if (el.get_luna() < 1 && el.get_luna() > 12) {
			cout << "Luna invalida!";
			return;
		}
		if (el.get_an() < 0 && el.get_an() > 2025) {
			cout << "An invalid!";
			return;
		}





	service.add(titlu, autor, gen, an);
	cout << "\nCarte adaugata cu succes!\n\n";

}

void Console::console_del() {

	cout << "Introduceti:\n";

	string titlu;
	cout << "Titlu: ";
	cin >> titlu;

	string autor;
	cout << "\nAutor: ";
	cin >> autor;

	if (titlu == "" || autor == "") {
		cout << "\nDate invalide!\n";
		return;
	}

	service.del(titlu, autor);

	cout << "\nCarte stearsa cu succes!\n\n";

}

void Console::console_mod() {
	cout << "Introduceti:\n";

	string titlu;
	cout << "Titlu: ";
	cin >> titlu;

	string autor;
	cout << "\nAutor: ";
	cin >> autor;

	string new_gen;
	cout << "\nNoul gen: ";
	cin >> new_gen;

	string new_an;
	cout << "\nNoul an (FORMAT <-> {zi.luna.an}): ";
	cin >> new_an;
	if (titlu == "" || autor == "" || new_gen == "" || new_an == "") {
		cout << "\nDate invalide!\n";
		return;
	}
	service.mod(titlu, autor, new_gen, new_an);



	Carte el{ titlu,autor,new_gen,new_an };
	if (el.get_zi() < 1 && el.get_zi() > 31) {
		cout << "Zi invalida!";
		return;
	}

	if (el.get_luna() < 1 && el.get_luna() > 12) {
		cout << "Luna invalida!";
		return;
	}
	if (el.get_an() < 0 && el.get_an() > 2025) {
		cout << "An invalid!";
		return;
	}



	cout << "\nCarte modificata cu succes!\n\n";

}

void Console::console_search() const {
	cout << "Introduceti:\n";

	string titlu;
	cout << "Titlu: ";
	cin >> titlu;

	string autor;
	cout << "\nAutor: ";
	cin >> autor;

	if (titlu == "" || autor == "") {
		cout << "\nDate invalide!\n";
		return;
	}
	auto carte = service.search(titlu, autor);

	cout << "\nCartea cautata este: ";

	//DE SUPRASCRIS OPERATORUL;
	cout << carte.get_titlu() << " " << carte.get_autor() << " " << carte.get_gen() << " " << carte.get_an_aparitie() << "\n";
	cout << "\n\n";
}

void print_header() {
	cout << std::endl;
	cout.width(10);
	cout << "TITLU";
	cout.width(10);
	cout << "AUTOR";
	cout.width(10);
	cout << "GEN";
	cout.width(20);
	cout << "AN";
	cout << std::endl << std::endl;
}

void Console::console_print_all() const {

	auto allCarti = service.get_filtered("", "");
	if (allCarti.size() == 0) {
		cout << "\nNu exista carti!\n\n";
		return;
	}
	cout << "\nCarti: " << allCarti.size() << std::endl;
	print_header();
	for (auto carte : allCarti) {
		
		cout.width(10);
		cout << carte.get_titlu();
		cout.width(10);
		cout << carte.get_autor();
		cout.width(10);
		cout << carte.get_gen();
		cout.width(20);
		cout << carte.get_an_aparitie();
		cout << std::endl;
	}
	
}

void Console::console_filter() const {
	cout << "\nIntroduceti:\n";

	string tip_filtru;
	cout << "Tipul filtrului ( titlu \\ an ):";
	cin >> tip_filtru;
	if (tip_filtru != "titlu" && tip_filtru != "an") {
		cout << "\nTip filtru inexistent!\n";
		return;
	}

	string filtru;
	cout << "\nIntruceti " << tip_filtru << " :";
	cin >> filtru;
	
	auto filtered = service.get_filtered(tip_filtru, filtru);
	if (filtered.size() == 0) {
		cout << "\n Nu au fost gasite carti!\n";
		return;
	}
	cout << "\nRezultat filtrare:\n";
	for(const auto& carte : filtered) 
		cout << carte.get_titlu() << " " << carte.get_autor() << " " << carte.get_gen() << " " << carte.get_an_aparitie() << "\n";

	cout << "\n\n";
		
}

void Console::console_sort() const {
	cout<<"\nIntroduceti:\n";

	string tip_sort;
	cout << "Tipul sortarii:\n";
	cout << "1. Titlu\n2. Autor\n3. Gen+An\n";
	cin >> tip_sort;
	if (tip_sort != "1" && tip_sort != "2" && tip_sort != "3") {
		cout << "Tip de sortare invalid!\n";
		return;
	}
	vector<TElement> rez;
	if (tip_sort == "1")
		rez = service.Gsort(cmpByTitle);
	if (tip_sort == "2")
		rez = service.Gsort(cmpByAuthor);
	if (tip_sort == "3")
		rez = service.Gsort(cmpByTypeANDYear);

	if (rez.size() == 0) {
		cout << "\nNu exista carti!\n\n";
		return;
	}
	cout << "\nCarti sortate: \n";
	for (const auto& carte : rez) {
		cout << carte.get_titlu() << " " << carte.get_autor() << " " << carte.get_gen() << " " << carte.get_an_aparitie() << "\n";
	}
	cout << "\n\n";

}

void Console::console_undo() {
	service.undo();
	cout << "\nUndo efectuat cu succes!\n";
}

void Console::console_add_cos() {
	cout << "Introduceti:\n";

	string titlu;
	cout << "Titlu: ";
	cin >> titlu;
	if (titlu == "") {
		cout << "\nDate invalide!\n";
		return;
	}

	serviceCOS.add(titlu);
}

void Console::console_raport() const{
	auto rap = service.GenerateRaportType();
	cout << "RAPORT:\n";

	for (auto const& x : rap)
	{
		std::cout << x.first  // string (key)
			<< ':'
			<< x.second // string's value 
			<< std::endl;
	}
}

void Console::console_clear_cos() {

	serviceCOS.clear();
}

void Console::console_print_cos() const{
	auto all = serviceCOS.get_all();
	for (const auto& carte : all) {
		cout << carte.get_titlu() << " " << carte.get_autor() << " " << carte.get_gen() << " " << carte.get_an_aparitie() << "\n";
	}
}

void Console::console_generate_cos() {
	int cate;
	cout << "Cate carti sa se adauge in cos?";
	cin >> cate;


	try {
		int howManyAdded = serviceCOS.genereaza(cate);
		cout << "S-au adaugat " << howManyAdded << " carti in cos." << "\n";
	}
	catch (std::exception& ex) {
		cout << ex.what()<<"\n";
	}
}

void Console::console_export_cos() {
	cout << "\nIntroduceti fisierul in care vrei export : ";
	string fisier_path;
	cin >> fisier_path;
	if (fisier_path == "") {
		cout << "\nFisier null/invalid!\n";
		return;
	}
	serviceCOS.exportCOS(fisier_path);
	cout << "\n Cos exportat cu succes!\n";
}

int get_command() {
	int cmd;
	while (true) {
		cout << "\n->";
		cin >> cmd;
		bool fail = cin.fail();
		cin.clear();
		auto& aux = cin.ignore(1000, '\n');
		if (!fail && aux.gcount() <= 1)
			break;
		cout.width(5);
		cout << "INTEGER!!!!";
	}
	return cmd;
}




void Console::runConsole() {

	cout << "Welcome!\n\n";


	service.add("abc", "abc", "abc", "1.2.3004");
	service.add("titlu1", "autor1", "abc", "3.4.2005");
	service.add("titlu2", "autor2", "gen1", "1.2.2005");
	service.add("tittlu3", "autor2", "gen2", "1.2.2003");

	console_print_menu();
	bool running = true;
	while (running) {
		
		
		int cmd = get_command();

		try {

			switch (cmd) {

			case 1:
				console_add();
				break;

			case 2:
				console_del();
				break;

			case 3:
				console_mod();
				break;

			case 4:
				console_search();
				break;

			case 5:
				system("CLS");
				console_print_all();
				break;

			case 6:
				console_filter();
				break;

			case 7:
				console_sort();
				break;

			case 8:
				console_undo();
				break;
			case 9:
				console_raport();
				break;

			case 10:
				system("CLS");
				console_print_menu();
				break;

			case 11:
				console_clear_cos();
				console_print_cos();
				break;

			case 12:
				console_add_cos();
				console_print_cos();
				break;

			case 13:
				console_generate_cos();
				console_print_cos();
				break;

			case 14:
				console_export_cos();
				console_print_cos();
				break;

			case 100:
				running = false;
				break;

			default:
				cout << "Comanda inexistenta!\n Pentru meniu selectati optiunea ( 10 )!\n";
			}






		}
		catch(const std::exception& ex) {
			cout << ex.what() << "\n";
			
		}
		


	}



	system("CLS");
	cout << "See you soon!\n\n";
}