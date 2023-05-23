#include "Table.h"


void TableWindow::InitGui() {


	setLayout(MAIN);
	MAIN->addWidget(tbl);
	//se pot adauga elemente
	auto all = service.get_filtered("", "");
	for (int i = 0; i < all.size(); i++) {
		auto titlu = QString::fromStdString(all[i].get_titlu());
		auto autor = QString::fromStdString(all[i].get_autor());
		auto gen = QString::fromStdString(all[i].get_gen());
		auto an = QString::fromStdString(all[i].get_an_aparitie());
			tbl->setItem(i, 0, new QTableWidgetItem(titlu));
			tbl->setItem(i, 1, new QTableWidgetItem(autor));
			tbl->setItem(i, 2, new QTableWidgetItem(gen));
			tbl->setItem(i, 3, new QTableWidgetItem(an));
	}

	show();


}