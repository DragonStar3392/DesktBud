#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SetDistance.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QSignalMapper>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
using namespace std;

class SetDistance : public QDialog {
	Q_OBJECT
public:
	SetDistance(QWidget *parent = Q_NULLPTR);
	~SetDistance();

private slots:
	void setDistance(int a);//buttons
	void setSBox();//spinbox
	void save();

private:
	Ui::SetDistance ui;
	void createActions();

	QSignalMapper* signalMapper;
	QAction *saveAct;

	int distance = 5;
	QString d;
	vector<int> values;
};