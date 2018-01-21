#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_ModQuotes.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
using namespace std;

class ModQuotes : public QDialog {
	Q_OBJECT
public:
	ModQuotes(QWidget *parent = Q_NULLPTR);

private slots:
	void updateQuote();
	void modQuote();//set quote to lineEdit
	void addQuote();
	void delQuote();
	void save();

private:
	Ui::ModQuotes ui;
	void createActions();

	int currentSize;//number of quotes
	QAction *saveAct;
	vector<QString> quotes;
};