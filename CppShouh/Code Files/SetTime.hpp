#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_SetTime.h"
#include <QLineEdit>
#include <QSpinBox>
#include <QSignalMapper>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
using namespace std;

class SetTime : public QDialog {
	Q_OBJECT
public:
	SetTime(QWidget *parent = Q_NULLPTR);
	~SetTime();

private slots:
	void setTime(int a);
	void setSBox();
	void save();

private:
	Ui::SetTime ui;
	void createActions();

	QSignalMapper* signalMapper;
	QAction *saveAct;

	int time = 60;
	QString t;
	vector<int> values;
};