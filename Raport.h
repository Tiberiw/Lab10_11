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

#include "service.h"
#include "ServiceCos.h"
#include "BookStoreGUI.h"
using std::vector;
using std::string;

class BookStoreGUI;


class Raport : public QWidget {

public:
	Raport(Service& srv, vector < std::pair < QPushButton*, string > >& btns) : service{ srv }{
		InitGui();
	}

private:
	Service& service;
	QHBoxLayout* MAINLY = new QHBoxLayout;
	vector<QPushButton*> BTNS;

	void InitGui();
};