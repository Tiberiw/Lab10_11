#include "SortGUI.h"

void SortGUI::InitGui() {

	setLayout(BUTTONS_SORT);
	BUTTONS_SORT->addWidget(TITLE_SORT);
	BUTTONS_SORT->addWidget(AUTHOR_SROT);
	BUTTONS_SORT->addWidget(TYYEA_SORT);

	show();
}

void SortGUI::InitConnect() {

	QObject::connect(TITLE_SORT, &QPushButton::clicked, [&]() {
		bookstoreGUI.LoadData(service.Gsort(cmpByTitle));
		});

	QObject::connect(AUTHOR_SROT, &QPushButton::clicked, [&]() {
		bookstoreGUI.LoadData(service.Gsort(cmpByAuthor));
		});

	QObject::connect(TYYEA_SORT, &QPushButton::clicked, [&]() {
		bookstoreGUI.LoadData(service.Gsort(cmpByTypeANDYear));
		});

}