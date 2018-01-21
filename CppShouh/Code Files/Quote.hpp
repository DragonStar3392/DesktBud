#pragma once
#include <QtWidgets/QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDesktopWidget>
#include <QTime>
#include <QFont>
#include <QMessageBox>
#include "ui_Quote.h"
using namespace std;

class Quote : public QDialog {
	Q_OBJECT

public:
	Quote(QWidget *parent = Q_NULLPTR);
	~Quote();

private:
	Ui::QuoteLog ui;

	int fontSize;
	int sizeQ;
	int randomValue;
	int randInt(int l, int h);
	vector<QString> quotes;
	vector<int> values;
};