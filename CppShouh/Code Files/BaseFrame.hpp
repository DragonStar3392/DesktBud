#pragma once

#include <QtWidgets/QMainWindow>
#include <vector>
#include <QTimer>

#include <QFile>
#include <QApplication>
#include <QDesktopWidget>

#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QTextStream>
#include <QIcon>

#include "ui_BaseFrame.h"
#include "Settings.hpp"
#include "Quote.hpp"

#include <QDebug>
using namespace std;

class BaseFrame : public QMainWindow
{
	Q_OBJECT

public:
	BaseFrame(QWidget *parent = Q_NULLPTR);
	~BaseFrame();
	void setPicture(int currentPic);//set main picture

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	
private slots :
	void owo();
	void patMode();
	void pokeMode();
	void dragdropmode();
	void hidePic();
	void showPic();
	void setting();
	void what();
	void selfmove();
	void selftalk();
	void delQuote();
	void discon();

private:
	Ui::BaseFrameClass ui;
	void createActions();//create actions
	void updatedPic(int index); //update main picture after changing from settings
	void updateValue();// update values from settings
	//Actions can contain mouse hover event, any action from user,however, sometimes not needed
	QActionGroup *cursorGroup;//group of cursors
	QAction *OwOAct;
	QAction *PatAct;
	QAction *PokeAct;
	QAction *DragDropAct;
	QAction *HideAct;
	QAction *ShowAct;
	QAction *setAct;
	QAction *exitAct;
	QAction *aboutAct;

	QTimer *walkAct;//normal timers, count from start time to 0
	QTimer *talkAct;
	int timeCounterS = 0;//used as substitue for timer as when program uses, the timing is wrong
	bool quoteStat = 1; //Enable/disable quote
	bool appear = false;//shows quote or not

	QVBoxLayout *layout = new QVBoxLayout();//layout or a container for objects
	QLabel *image = new QLabel(this);
	QRect shape;//shape of image

	QPoint dragPos;//current dragged position
	QPoint displacementLeft = QPoint(5, 0); //character movement distance towards right
	QPoint displacementRight = QPoint(-5, 0);
	QPoint topLeft, topRight, bottomLeft, bottomRight; //4 corners of the app
	QPoint centre; //center of picture
	QPoint screenCenter;

	int screenWidth;
	int screenHeight;

	int width, height; bool direction = 1;//width and height of the picture, direction where the picture is moving
	int second = 10, minute, walkTime;//second = 10 miliseconds

	Quote *a;
	int talkTime, lifespan;//for quote

	vector<QString> pictureDirectory;
	vector<int> values;
	QPixmap pix;//another kind of image
};
