#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SetApTimeQ.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
using namespace std;

class SetApTimeQ : public QDialog {
	Q_OBJECT
public:
	SetApTimeQ(QWidget *parent = Q_NULLPTR);

private slots:
	void setTime();//for spinbox
	void save();

private:
	Ui::SetApTimeQ ui;
	void createActions();

	QAction *saveAct;

	int time = 60;
	QString t;
	vector<int> values;
};