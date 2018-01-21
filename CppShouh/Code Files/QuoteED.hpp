#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QuoteED.h"
#include <QLineEdit>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
using namespace std;

class QuoteED : public QDialog {
	Q_OBJECT

public:
	QuoteED(QWidget *parent = Q_NULLPTR);

private slots:
	void enable();
	void disable();
	void save();

private:
	Ui::QuoteED ui;
	void createActions();

	int stat;//status if enable or disable
	vector<int> values;
};