#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SetLifespanQ.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
using namespace std;

class SetLifespanQ : public QDialog {
	Q_OBJECT
public:
	SetLifespanQ(QWidget *parent = Q_NULLPTR);

private slots:
	void setTime();
	void save();

private:
	Ui::SetLifespanQ ui;
	void createActions();

	QAction *saveAct;

	int time = 10;
	QString lp;
	vector<int> values;
};