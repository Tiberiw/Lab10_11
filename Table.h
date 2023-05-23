#pragma once

#include <QtWidgets/QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QBoxLayout>
#include <QStackedLayout>
#include <QFormLayout>
#include <QListWidget>
#include <vector>
#include <string>
#include <QMessageBox>
#include <QTableWidget>

#include "service.h"
#include "ServiceCos.h"
#include "BookStoreGUI.h"
using std::vector;
using std::string;

class BookStoreGUI;

class TableWindow : public QWidget {

public:

	TableWindow(Service& srv) : service{ srv } {
		InitGui();
	}

private:
	Service& service;
	int nrLinii = 4;
	int nrColoane = 4;
	QHBoxLayout* MAIN = new QHBoxLayout;
	QTableWidget* tbl = new QTableWidget{ nrLinii,nrColoane };

	void InitGui();

};