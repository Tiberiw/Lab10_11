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

using std::vector;
using std::string;


class CosGUI : public QWidget {

public:
	CosGUI(Service& srv, ServiceCos& servCOS) : service{ srv }, serviceCOS{ servCOS } {
		InitGui();
		InitConnect();
	}

private:
	Service& service;
	ServiceCos& serviceCOS;

	QHBoxLayout* MainLy_COS = new QHBoxLayout;

	QWidget* LEFT_COS = new QWidget;
	QVBoxLayout* LEFTLY_COS = new QVBoxLayout;
	QListWidget* LIST_COS = new QListWidget;
	QPushButton* CLEAR_COS = new QPushButton("CLEAR_COS");

	QWidget* RIGHT_COS = new QWidget;
	QVBoxLayout* RIGHTLY_COS = new QVBoxLayout;

	QWidget* FORM_COS = new QWidget;
	QFormLayout* FORMLY_COS = new QFormLayout;
	QLineEdit* MainTitleLine_COS = new QLineEdit;
	QLineEdit* MainRandomNrLine_COS = new QLineEdit;
	QLineEdit* MainExportFileLine_COS = new QLineEdit;

	QPushButton* MainTitleButton_COS = new QPushButton("ADD");
	QPushButton* MainRandomNrButton_COS = new QPushButton("ADD_RANDOM");
	QPushButton* MainExportFileButton_COS = new QPushButton("EXPORT");


	void InitGui();
	void InitConnect();
	void LoadData(const vector<TElement>& all);
};