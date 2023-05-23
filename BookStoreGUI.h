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

#include "CosGUI.h"
#include "service.h"
#include "ServiceCos.h"
#include "SortGUI.h"
#include "FilterGUI.h"
#include "Table.h"
#include "Raport.h"

using std::vector;
using std::string;

class SortGUI;

class BookStoreGUI : public QWidget {

	friend class SortGUI;

public:

	BookStoreGUI(Service& srv, ServiceCos& srvCOS) : service{ srv }, serviceCOS{srvCOS} {

		service.add("abc", "abc", "abc", "1.2.3004");
		service.add("titlu1", "autor1", "abc", "3.4.2005");
		service.add("titlu2", "autor2", "gen1", "1.2.2005");
		service.add("tittlu3", "autor2", "gen2", "1.2.2003");

		InitGui();
		InitConnect();
	}

private:
	Service& service;
	ServiceCos& serviceCOS;
	QHBoxLayout* MainLy = new QHBoxLayout;

	QWidget* LEFT = new QWidget;
	QVBoxLayout* LEFTLY = new QVBoxLayout;
	QListWidget* LIST = new QListWidget;
	QWidget* BTNSLEFT = new QWidget;
	QHBoxLayout* BTNSLEFTLY = new QHBoxLayout;
	QPushButton* UNDO = new QPushButton("&UNDO");
	QPushButton* COS = new QPushButton("&CART");
	QPushButton* EXIT = new QPushButton("&EXIT");

	QWidget* RIGHT = new QWidget;
	QVBoxLayout* RIGHTLY = new QVBoxLayout;

	QPushButton* CLEAR = new QPushButton("CLEAR");

	QWidget* FORM = new QWidget;
	QFormLayout* FORMLY = new QFormLayout;
	QLineEdit* MainTitleLine = new QLineEdit;
	QLineEdit* MainAuthorLine = new QLineEdit;
	QLineEdit* MainTypeLine = new QLineEdit;
	QLineEdit* MainYearLine = new QLineEdit;
	QLabel* MainTitleLabel = new QLabel("Title:");
	QLabel* MainAuthorLabel = new QLabel("Author:");
	QLabel* MainTypeLabel = new QLabel("Type:");
	QLabel* MainYearLabel = new QLabel("Year:");

	QWidget* ADDMODDEL = new QWidget;
	QHBoxLayout* ADDMODDELLY = new QHBoxLayout;
	QPushButton* ADD = new QPushButton("&ADD");
	QPushButton* MOD = new QPushButton("&MODIFY");
	QPushButton* DEL = new QPushButton("&DELETE");

	QWidget* FILTERSORTRAPORT = new QWidget;
	QHBoxLayout* FILTERSORTLY = new QHBoxLayout;
	QPushButton* FILTER = new QPushButton("&FILTER");
	QPushButton* SORT = new QPushButton("&SORT");
	QPushButton* RAPORT = new QPushButton("&RAPORT");
	void InitGui();
	void InitConnect();

	void LoadData(const vector<TElement>& all);
};
