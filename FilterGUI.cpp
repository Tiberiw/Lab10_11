#include "FilterGUI.h"


void FilterGUI::InitGui() {

	setLayout(MAINLY);
	MAINLY->addWidget(LIST_FILTER);
	MAINLY->addWidget(BTNS);
	BTNS->setLayout(BUTTONS_FILTER);
	BUTTONS_FILTER->addRow(TITLE_FILTER,TITLE_LINE);
	BUTTONS_FILTER->addRow(YEAR_FILTER,YEAR_LINE);

	show();
}

void FilterGUI::InitConnect() {


	QObject::connect(TITLE_FILTER, &QPushButton::clicked, [&]() {

		string filtru;
		auto titlu = TITLE_LINE->text();
		filtru = titlu.toStdString();
		if (filtru == "") {
		QMessageBox::warning(nullptr, "Warning", "Date invalide!");
		return;
		}

		LoadData(service.get_filtered("titlu", filtru));
		});

	QObject::connect(YEAR_FILTER, &QPushButton::clicked, [&]() {


		string filtru;
		auto year = YEAR_LINE->text();
		filtru = year.toStdString();
		if (filtru == "") {
			QMessageBox::warning(nullptr, "Warning", "Date invalide!");
			return;
		}


		LoadData(service.get_filtered("an", filtru));
		});

}

void FilterGUI::LoadData(const vector<TElement>& all) {
	LIST_FILTER->clear();
	for (const auto& carte : all) {
		string crt = carte.get_titlu() + "," + carte.get_autor() + "," + carte.get_gen() + "," + carte.get_an_aparitie();
		LIST_FILTER->addItem(QString::fromStdString(crt));
	}

}