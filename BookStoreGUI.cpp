#include "BookStoreGUI.h"
#include <sstream>
using std::stringstream;

/*
void BookStoreGUI::conecteaza(QPushButton* btn) {

	QObject::connect(btn, &QPushButton::clicked, [&]() {
		string de_afisat = gen + " : " + nr_string;
		QMessageBox::information(this,"Raport", QString::fromStdString(de_afisat));
		qDebug() << gen + " " + nr_string + "\n";
		});

}

void BookStoreGUI::set_window_RAP() {

	

	fereastraRAP->close();
	QVBoxLayout* lyfereastraRAP = new QVBoxLayout;
	fereastraRAP->setLayout(lyfereastraRAP);

	QLabel* options = new QLabel("Rapoarte disponibile:");
	lyfereastraRAP->addWidget(options);

	auto rap = service.GenerateRaportType();
	int size_arr = rap.size();
	buton_rap = new QPushButton[size_arr];
	int i = 0;
	for (const auto& el : rap) {
		gen = el.first;

		int nr = el.second;
		stringstream stream;
		stream << nr;
		nr_string;
		stream >> nr_string;

		buton_rap[i] = new QPushButton(QString::fromStdString(gen));
		lyfereastraRAP->addWidget(buton_rap[i]);
		conecteaza(buton_rap[i]);
		i++;
	}
	
	lyfereastraRAP->addWidget(close_btn_rap);
	

}

void BookStoreGUI::set_window_DEL() {
	QVBoxLayout* lyfereastraDEL = new QVBoxLayout;
	fereastraDEL->setLayout(lyfereastraDEL);

	QWidget* fields = new QWidget;
	QFormLayout* lybutoane = new QFormLayout;
	fields->setLayout(lybutoane);

	QLabel* titlu_lbl = new QLabel("Title:");
	lybutoane->addRow(titlu_lbl, titlu_txt_del);

	QLabel* autor_lbl = new QLabel("Author:");
	lybutoane->addRow(autor_lbl, autor_txt_del);

	lyfereastraDEL->addWidget(fields);

	QWidget* buttons = new QWidget;
	QHBoxLayout* lybuttons = new QHBoxLayout;
	buttons->setLayout(lybuttons);

	lybuttons->addWidget(delete_btn_del);
	lybuttons->addStretch();
	lybuttons->addWidget(clear_btn_del);
	lybuttons->addStretch();
	lybuttons->addWidget(close_btn_del);//closeBTN

	lyfereastraDEL->addWidget(buttons);
}

void BookStoreGUI::set_window_MOD() {

	QVBoxLayout* lyfereastraMOD = new QVBoxLayout;
	fereastraMOD->setLayout(lyfereastraMOD);

	QWidget* fields = new QWidget;
	QFormLayout* lybutoane = new QFormLayout;
	fields->setLayout(lybutoane);

	QLabel* titlu_lbl = new QLabel("Title:");
	lybutoane->addRow(titlu_lbl, titlu_txt_mod);

	QLabel* autor_lbl = new QLabel("Author:");
	lybutoane->addRow(autor_lbl, autor_txt_mod);

	QLabel* gen_lbl = new QLabel("New type:");
	lybutoane->addRow(gen_lbl, gen_txt_mod);

	QLabel* an_lbl = new QLabel("New year:");
	lybutoane->addRow(an_lbl, an_txt_mod);

	lyfereastraMOD->addWidget(fields);


	QWidget* buttons = new QWidget;
	QHBoxLayout* lybuttons = new QHBoxLayout;
	buttons->setLayout(lybuttons);


	lybuttons->addWidget(modify_btn_mod);
	lybuttons->addStretch();
	lybuttons->addWidget(clear_btn_mod);
	lybuttons->addStretch();
	lybuttons->addWidget(close_btn_mod);//closeBTN

	lyfereastraMOD->addWidget(buttons);



}

void BookStoreGUI::set_window_ADD() {

	qDebug() << "BAAA";
	QVBoxLayout* lyfereastraADD = new QVBoxLayout;
	fereastraADD->setLayout(lyfereastraADD);

	QWidget* fields = new QWidget;
	QFormLayout* lybutoane = new QFormLayout;
	fields->setLayout(lybutoane);

	QLabel* titlu_lbl = new QLabel("Title:");
	lybutoane->addRow(titlu_lbl, titlu_txt_add);

	QLabel* autor_lbl = new QLabel("Author:");
	lybutoane->addRow(autor_lbl, autor_txt_add);

	QLabel* gen_lbl = new QLabel("Type:");
	lybutoane->addRow(gen_lbl, gen_txt_add);

	QLabel* an_lbl = new QLabel("Year:");
	lybutoane->addRow(an_lbl, an_txt_add);

	lyfereastraADD->addWidget(fields);



	QWidget* buttons = new QWidget;
	QHBoxLayout* lybuttons = new QHBoxLayout;
	buttons->setLayout(lybuttons);


	lybuttons->addWidget(store_btn_add);
	lybuttons->addStretch();
	lybuttons->addWidget(clear_btn_add);
	lybuttons->addStretch();
	lybuttons->addWidget(close_btn_add);//closeBTN

	lyfereastraADD->addWidget(buttons);

}
*/
void BookStoreGUI::InitConnect() {




	QObject::connect(LIST, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = LIST->selectedItems();
	if (sel.isEmpty()) {
		MainTitleLine->setText("");
		MainAuthorLine->setText("");
		MainTypeLine->setText("");
		MainYearLine->setText("");
	}
	else {

		auto selectedItem = sel.at(0);
		auto all = selectedItem->text();

		string full_string = all.toStdString();


		//Vectorul in care avem separat an,luna,zi
		vector<string> sol;

		//Creeam obiectul de tip stringstream
		std::stringstream stringuri(full_string);

		//Cat timp mai putem face prelucrari.
		while (stringuri.good()) {

			//Declaram un string in care punem substringul
			string substring;

			//Adaugam in substring an/luna/zi
			getline(stringuri, substring, ',');

			//Adaugam in solutie substringurile
			sol.push_back(substring);
		}

		

		MainTitleLine->setText(QString::fromStdString(sol[0]));
		MainAuthorLine->setText(QString::fromStdString(sol[1]));
		MainTypeLine->setText(QString::fromStdString(sol[2]));
		MainYearLine->setText(QString::fromStdString(sol[3]));
		//txtType->setText(selItem->data(Qt::UserRole).toString());

	//	auto type = selItem->data(Qt::UserRole).toString();
	//	txtSpecies->setText(species);
	//	txtType->setText(type);
	


		//auto p = ctr.find(type.toStdString(), species.toStdString());
		//txtPrice->setText(QString::number(p.getPrice()));
	}
		});









	//BUTON EXIT PANOU PRINCIPAL
	QObject::connect(EXIT, &QPushButton::clicked, [&]() {
		qDebug() << "Buton de exit apasat!!\n";
	//QMessageBox::information(nullptr, "Exit", "Programul se va opri!");
	close();
		});


	//BUTON ADAUGARE PANOU PRINCIPAL
	QObject::connect(ADD, &QPushButton::clicked, [&]() {
		qDebug() << "Buton de adaugare apasat!!\n";

		auto titlu = MainTitleLine->text();
		auto autor = MainAuthorLine->text();
		auto gen = MainTypeLine->text();
		auto an = MainYearLine->text();

		string titlu_str = titlu.toStdString();
		string autor_str = autor.toStdString();
		string gen_str = gen.toStdString();
		string an_str = an.toStdString();
		try {
			service.add(titlu_str, autor_str, gen_str, an_str);
		}
		catch (std::exception& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.what()));
		}


		LoadData(service.get_filtered("", ""));
		});


	//BUTON MOD
	QObject::connect(MOD, &QPushButton::clicked, [&]() {
		qDebug() << "Buton de modificare apasat!!\n";
		
		auto titlu = MainTitleLine->text();
		auto autor = MainAuthorLine->text();
		auto gen = MainTypeLine->text();
		auto an = MainYearLine->text();
		string titlu_str = titlu.toStdString();
		string autor_str = autor.toStdString();
		string gen_str = gen.toStdString();
		string an_str = an.toStdString();

		try {
			service.mod(titlu_str, autor_str, gen_str, an_str);
		}
		catch (std::exception& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.what()));
		}

		LoadData(service.get_filtered("", ""));
	});

	//BUTON DEL
	QObject::connect(DEL, &QPushButton::clicked, [&]() {
		qDebug() << "Buton de modificare apasat!!\n";

		auto titlu = MainTitleLine->text();
		auto autor = MainAuthorLine->text();
		string titlu_str = titlu.toStdString();
		string autor_str = autor.toStdString();

		try {
			service.del(titlu_str, autor_str);
		}
		catch (std::exception& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.what()));
		}

		LoadData(service.get_filtered("", ""));
	});


	//BUTON CLEAR
	QObject::connect(CLEAR, &QPushButton::clicked, [&]() {
		MainTitleLine->clear();
		MainAuthorLine->clear();
		MainTypeLine->clear();
		MainYearLine->clear();
		});

	QObject::connect(COS, &QPushButton::clicked, [&]() {

		CosGUI* Cos = new CosGUI(service,serviceCOS);
		Cos->show();
		});


	QObject::connect(UNDO, &QPushButton::clicked, [&]() {

		try {
			service.undo();
		}
		catch (std::exception& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.what()));
		}
		
		LoadData(service.get_filtered("", ""));
		});


	QObject::connect(SORT, &QPushButton::clicked, [&]() {

		SortGUI* sortgui = new SortGUI(service,*this);
		sortgui->show();

		});

	QObject::connect(FILTER, &QPushButton::clicked, [&]() {

		FilterGUI* filtergui = new FilterGUI(service, *this);
		filtergui->show();

		});

	
	QObject::connect(RAPORT, &QPushButton::clicked, [&]() {
		qDebug() << "Buton de raport apasat!!\n";
		
		

	auto rap = service.GenerateRaportType();
	int size_arr = rap.size();
	vector < std::pair < QPushButton*, string > >all;
	for (const auto& el : rap) {
		string gen_str = el.first;
		auto gen = QString::fromStdString(gen_str);

		QPushButton* btn = new QPushButton(gen);
		all.push_back({ btn,gen_str });

	}

	Raport* raportgui = new Raport(service,all);
	raportgui->show();


		});

	


}


void BookStoreGUI::LoadData(const vector<TElement>& all) {
	LIST->clear();
	for(const auto& carte : all ) {
		string crt = carte.get_titlu() +","+ carte.get_autor() +","+ carte.get_gen() +","+ carte.get_an_aparitie();
	LIST->addItem(QString::fromStdString(crt));
	}
}

void BookStoreGUI::InitGui() {


	setLayout(MainLy);
	MainLy->addWidget(LEFT);
	LEFT->setLayout(LEFTLY);
	LEFTLY->addWidget(LIST);
	LEFTLY->addWidget(BTNSLEFT);
	BTNSLEFT->setLayout(BTNSLEFTLY);
	BTNSLEFTLY->addWidget(UNDO);
	BTNSLEFTLY->addWidget(COS);
	BTNSLEFTLY->addWidget(EXIT);
	//LEFTLY->addStretch();

	MainLy->addWidget(RIGHT);
	RIGHT->setLayout(RIGHTLY);

	RIGHTLY->addWidget(FORM);
	FORM->setLayout(FORMLY);
	FORMLY->addRow(MainTitleLabel, MainTitleLine);
	FORMLY->addRow(MainAuthorLabel, MainAuthorLine);
	FORMLY->addRow(MainTypeLabel, MainTypeLine);
	FORMLY->addRow(MainYearLabel, MainYearLine);

	RIGHTLY->addWidget(CLEAR);

	RIGHTLY->addWidget(ADDMODDEL);
	ADDMODDEL->setLayout(ADDMODDELLY);
	ADDMODDELLY->addWidget(ADD);
	ADDMODDELLY->addWidget(MOD);
	ADDMODDELLY->addWidget(DEL);

	RIGHTLY->addWidget(FILTERSORTRAPORT);
	FILTERSORTRAPORT->setLayout(FILTERSORTLY);
	FILTERSORTLY->addWidget(FILTER);
	FILTERSORTLY->addWidget(SORT);
	FILTERSORTLY->addWidget(RAPORT);

	LoadData(service.get_filtered("", ""));

	show();

	TableWindow* tablewindow = new TableWindow(service);
	tablewindow->show();



}