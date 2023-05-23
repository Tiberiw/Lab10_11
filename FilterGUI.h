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

class FilterGUI : public QWidget {

	friend class BookStoreGUI;
public:
	FilterGUI(Service& srv, BookStoreGUI& bkstr) : service{ srv }, bookstoreGUI{bkstr} {
		InitGui();
		InitConnect();
	}

private:

	Service& service;
	BookStoreGUI& bookstoreGUI;
	QHBoxLayout* MAINLY = new QHBoxLayout;
	QListWidget* LIST_FILTER = new QListWidget;

	QWidget* BTNS = new QWidget;
	QFormLayout* BUTTONS_FILTER = new QFormLayout;
	QPushButton* TITLE_FILTER = new QPushButton("TITLE");
	QLineEdit* TITLE_LINE = new QLineEdit;
	QPushButton* YEAR_FILTER = new QPushButton("YEAR");
	QLineEdit* YEAR_LINE = new QLineEdit;

	void InitGui();
	void InitConnect();
	void LoadData(const vector<TElement>& all);
};