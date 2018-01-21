#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSignalMapper>

#include "ui_Settings.h"
#include "SetTime.hpp"
#include "SetDistance.hpp"
#include "SetApTimeQ.hpp"
#include "SetLifespanQ.hpp"
#include "ModQuotes.hpp"
#include "QuoteED.hpp"
using namespace std;

class Settings : public QDialog {
	Q_OBJECT

public:
	Settings(QWidget *parent = Q_NULLPTR);
	~Settings();

private slots:
	void browse(int a);//which browse button did user press
	void change();//set picture(s) for change
	void setTime();//GUIs
	void setDistance();
	void setInterQ();
	void setLifespan();
	void modQuote();
	void quoteED();
	void movpic();

private:
	Ui::SettingsUI ui;
	void createActions();
	bool fit = false;//size of picture
	int pressed = 0, owoPress = 0, patPress = 0, pokePress = 0;//how many times user has pressed the buttons

	QAction *browseAct;
	QAction *changeAct;

	QAction *setTimeAct;
	QAction *setDistanceAct;
	QSignalMapper* signalMapper;//Map to assign value

	QAction *setIntQAct;
	QAction *setLifeAct;
	QAction *modQuoteAct;

	vector<QString> pictureDirectory; //loaded directories from file
	QString picDirectory; //uploaded picture directory
};