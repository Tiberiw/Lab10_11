#include "Raport.h"
#include <sstream>
void Raport::InitGui() {

	setLayout(MAINLY);
	BTNS.clear();
	for (auto el : service.GenerateRaportType()) {
		auto btn = new QPushButton(QString::fromStdString(el.first));
		BTNS.push_back(btn);
		MAINLY->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [btn, el]() {
			QMessageBox::information(nullptr, "Raport", QString::fromStdString(el.first) + " : " + QString::number(el.second));
			});
	}


	show();

}

/*
void Raport::InitConnect() {

	for (const auto& btn : buttons) {
		QObject::connect(btn.first, &QPushButton::clicked, [&]() {
			auto rap = service.GenerateRaportType();
			int nr = rap[btn.second];
			auto gen = QString::fromStdString(btn.second);

			std::stringstream s;
			s << nr;
			string nr_str;
			s >> nr_str;
			auto nr_Q = QString::fromStdString(nr_str);

			QMessageBox::information(nullptr, "Rapott", gen + " : " + nr_Q);
			});
	}
	


}

*/