
#include "CosGUI.h"
#include <sstream>

void CosGUI::InitGui() {

	setLayout(MainLy_COS);

	MainLy_COS->addWidget(LEFT_COS);
	LEFT_COS->setLayout(LEFTLY_COS);
	LEFTLY_COS->addWidget(LIST_COS);
	LEFTLY_COS->addWidget(CLEAR_COS);


	MainLy_COS->addWidget(RIGHT_COS);
	RIGHT_COS->setLayout(RIGHTLY_COS);

	RIGHTLY_COS->addWidget(FORM_COS);
	FORM_COS->setLayout(FORMLY_COS);
	FORMLY_COS->addRow(MainTitleButton_COS, MainTitleLine_COS);
	FORMLY_COS->addRow(MainRandomNrButton_COS, MainRandomNrLine_COS);
	FORMLY_COS->addRow(MainExportFileButton_COS, MainExportFileLine_COS);

	LoadData(serviceCOS.get_all());
	show();
}


void CosGUI::InitConnect() {

	QObject::connect(CLEAR_COS, &QPushButton::clicked, [&]() {
		LIST_COS->clear();
		});

	QObject::connect(MainTitleButton_COS, &QPushButton::clicked, [&]() {
		

		string titlu_str;
		auto titlu = MainTitleLine_COS->text();
		titlu_str = titlu.toStdString();
		if (titlu == "") {
			QMessageBox::warning(nullptr, "Warning", "Date invalide!");

			return;
		}

		serviceCOS.add(titlu_str);
		LoadData(serviceCOS.get_all());
		});

	QObject::connect(MainRandomNrButton_COS, &QPushButton::clicked, [&]() {
		

		int cate;
		auto nr = MainRandomNrLine_COS->text();
		string nr_str = nr.toStdString();

		std::stringstream s;
		s << nr_str;
		s >> cate;


		try {
			int howManyAdded = serviceCOS.genereaza(cate);
			s << howManyAdded;
			s >> nr_str;
			nr = QString::fromStdString(nr_str);
			QMessageBox::information(nullptr, "Generate", "S-au adaugat " + nr + " carti in cos.");
		}
		catch (std::exception& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.what()));
		}
		LoadData(serviceCOS.get_all());
		});

	QObject::connect(MainExportFileButton_COS, &QPushButton::clicked, [&]() {
		
	auto path = MainExportFileLine_COS->text();
	string fisier_path = path.toStdString();
	
	if (fisier_path == "") {
		QMessageBox::warning(nullptr, "Warning", "Fisier null / invalid!");
		return;
	}
	serviceCOS.exportCOS(fisier_path);
	QMessageBox::information(nullptr, "Export", "Cos exportat cu succes!");
		});

}

void CosGUI::LoadData(const vector<TElement>& all) {
	LIST_COS->clear();
	for (const auto& carte : all) {
		string crt = carte.get_titlu() + "," + carte.get_autor() + "," + carte.get_gen() + "," + carte.get_an_aparitie();
		LIST_COS->addItem(QString::fromStdString(crt));
	}
}