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

class SortGUI : public QWidget{
	friend class BookStoreGUI;
public:
	SortGUI(Service& srv, BookStoreGUI& bkstr) : service{ srv }, bookstoreGUI{bkstr} {
		InitGui();
		InitConnect();
	}

private:
	Service& service;
	BookStoreGUI& bookstoreGUI;
	QHBoxLayout* BUTTONS_SORT = new QHBoxLayout;
	QPushButton* TITLE_SORT = new QPushButton("TITLE");
	QPushButton* AUTHOR_SROT = new QPushButton("AUTHOR");
	QPushButton* TYYEA_SORT = new QPushButton("TYPE + YEAR");

	void InitGui();
	void InitConnect();

};