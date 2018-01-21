#include "BaseFrame.hpp"

BaseFrame::BaseFrame(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);

	updatedPic(0);//init main picture
	updateValue();//store value
	createActions();

	QDesktopWidget *desktop = QApplication::desktop();//get data for desktop sizes
	screenWidth = desktop->width();
	screenHeight = desktop->height();
	screenCenter = QPoint((screenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2));//picture center to desktop center
	
	setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);// no frame
	setParent(0); // Create TopLevel-Widget
	setAttribute(Qt::WA_NoSystemBackground, true);//do not draw background
	setAttribute(Qt::WA_TranslucentBackground, true);//invisible background
}

BaseFrame::~BaseFrame()
{
	//Auto delete by Qt
	delete cursorGroup;
	delete OwOAct;
	delete PatAct;
	delete PokeAct;
	delete DragDropAct;
	delete HideAct;
	delete ShowAct;
	delete setAct;
	delete exitAct;
	delete aboutAct;
	delete walkAct;
	delete layout;
	delete image;
}

void BaseFrame::setPicture(int cPic)
{
	QImage image(pictureDirectory[cPic]);//get picture from index of directories
	pix = QPixmap::fromImage(image);
}


#include <QMouseEvent>
void BaseFrame::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::RightButton) {

		QMenu menu(this);//due to invisible frame, no menu will be seen and context menu will contain the following:
		menu.addAction(OwOAct);
		menu.addAction(PatAct);
		menu.addAction(PokeAct);
		menu.addAction(DragDropAct);
		menu.addSeparator();
		menu.addAction(HideAct);
		menu.addAction(ShowAct);
		menu.addSeparator();
		menu.addAction(setAct);
		menu.addAction(aboutAct);
		menu.addSeparator();
		menu.addAction(exitAct);
		menu.exec(event->globalPos());//on the postion where user clicked
	}
	if (event->button() == Qt::LeftButton && cursor().shape() == Qt::WhatsThisCursor) {
		updatedPic(1);
	}
	else if (event->button() == Qt::LeftButton && cursor().shape() == Qt::OpenHandCursor) {
		updatedPic(2);
	}
	else if (event->button() == Qt::LeftButton && cursor().shape() == Qt::PointingHandCursor) {
		updatedPic(3);
	}
	else  if (event->button() == Qt::LeftButton && cursor().shape() == Qt::ArrowCursor) {
		dragPos = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void BaseFrame::mouseMoveEvent(QMouseEvent * event)
{
	if (event->buttons() & Qt::LeftButton && cursor().shape() == Qt::ArrowCursor) {
		topLeft = this->mapToGlobal(QPoint(0, 0));
		topRight = this->mapToGlobal(QPoint(width, 0));
		bottomLeft = this->mapToGlobal(QPoint(0, height));
		if (topLeft.x() >= 0 && topRight.x() <= screenWidth && topLeft.y() >= 0 && bottomLeft.y() <= screenHeight) {
			move(event->globalPos() - dragPos);//if within the screen, move the picture
			event->accept();
		}
		else
			event->ignore();
	}
}

void BaseFrame::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton && cursor().shape() == Qt::WhatsThisCursor) {
		updatedPic(0);
	}
	else if (event->button() == Qt::LeftButton && cursor().shape() == Qt::OpenHandCursor) {
		updatedPic(0);
	}
	else if (event->button() == Qt::LeftButton && cursor().shape() == Qt::PointingHandCursor) {
		updatedPic(0);
	}

	else if (event->button() == Qt::LeftButton && cursor().shape() == Qt::ArrowCursor) {
		topLeft = this->mapToGlobal(QPoint(0, 0));//current position of the app's window
		topRight = this->mapToGlobal(QPoint(width, 0));
		bottomLeft = this->mapToGlobal(QPoint(0, height));
		//QPoint a = dragPos;
		if(topLeft.x() < 0 ){//left
			if (topLeft.y() < 0) {//top corner
				move(QPoint(0, 0));
				event->accept();
			}
			else if (bottomLeft.y() > screenHeight) {//down corner
				move(QPoint(0, screenHeight - height));
				event->accept();
			}
			else {//middle
				move(QPoint(0, event->globalPos().y() - dragPos.y()));
				event->accept();
			}
		}
		else if (topRight.x() > screenWidth) {//right
			if (topLeft.y() < 0) {//top corner
				move(QPoint(screenWidth-width, 0));
				event->accept();
			}
			else if (bottomLeft.y() > screenHeight) {//down corner
				move(QPoint(screenWidth-width, screenHeight - height));
				event->accept();
			}
			else {//middle
				move(QPoint(screenWidth - width, event->globalPos().y() - dragPos.y()));
				event->accept();
			}
		}
		else if (topLeft.y() < 0) {//top center
			move(QPoint(event->globalPos().x() - dragPos.x(),0));
			event->accept();
		}
		else if (bottomLeft.y() > screenHeight) {//down center
			move(QPoint(event->globalPos().x() - dragPos.x(), screenHeight-height));
			event->accept();
		}
	}
}

void BaseFrame::owo() {
	OwOAct->setChecked(true);
	setCursor(Qt::WhatsThisCursor);//set cursor to the shape
}

void BaseFrame::patMode()
{
	PatAct->setChecked(true);
	setCursor(Qt::OpenHandCursor);
}

void BaseFrame::pokeMode()
{
	PokeAct->setChecked(true);
	setCursor(Qt::PointingHandCursor);
}

void BaseFrame::dragdropmode()
{
	DragDropAct->setChecked(true);
	setCursor(Qt::ArrowCursor);
}

void BaseFrame::hidePic()
{
	this->setWindowOpacity(0.05);//opacity or how clear it is
}

void BaseFrame::showPic()
{
	this->setWindowOpacity(1);// 100 not translucent
}

void BaseFrame::setting()
{
	Settings a;
	a.setModal(true);//cannot touch the main frame/character while the settings window is open
	a.exec();//execute
	updatedPic(0);//update everything even if user didn't change any thing
	updateValue();
}

void BaseFrame::what()
{
	QMessageBox::about(this, tr("About this app"),
		tr("The app is about you wasting time with the character.\n Have fun."));
}

void BaseFrame::createActions()
{
	QFont font("Arial", 8);//init font
	OwOAct = new QAction(tr("&OwO??"), this);
	OwOAct->setFont(font);
	OwOAct->setStatusTip(tr("OwO???"));// tip/help is at the bottom of the character towards the left
	connect(OwOAct, &QAction::triggered, this, &BaseFrame::owo);//connect the action, when clicked/activated, it will call f(x) owo

	PatAct = new QAction(tr("&Pat Mode"), this);
	PatAct->setFont(font);
	PatAct->setStatusTip(tr("It's time to pat!"));
	connect(PatAct, &QAction::triggered, this, &BaseFrame::patMode);

	PokeAct = new QAction(tr("&Poke Mode"), this);
	PokeAct->setFont(font);
	PokeAct->setStatusTip(tr("Poke death"));
	connect(PokeAct, &QAction::triggered, this, &BaseFrame::pokeMode);

	DragDropAct = new QAction(tr("&User move mode"));
	DragDropAct->setFont(font);
	connect(DragDropAct, &QAction::triggered, this, &BaseFrame::dragdropmode);

	HideAct = new QAction(tr("&Hide"));
	HideAct->setFont(font);
	connect(HideAct, &QAction::triggered, this, &BaseFrame::hidePic);

	ShowAct = new QAction(tr("&Show"));
	ShowAct->setFont(font);
	connect(ShowAct, &QAction::triggered, this, &BaseFrame::showPic);

	cursorGroup = new QActionGroup(this);//one of the modes can be on, not all
	cursorGroup->addAction(OwOAct);
	cursorGroup->addAction(PatAct);
	cursorGroup->addAction(PokeAct);
	cursorGroup->addAction(DragDropAct);
	OwOAct->setChecked(true);
	
	walkAct = new QTimer(this);
	connect(walkAct, SIGNAL(timeout()), this, SLOT(selfmove()));
	walkAct->start(walkTime);//start timer

	talkAct = new QTimer(this);
	connect(talkAct, SIGNAL(timeout()), this, SLOT(selftalk()));
	talkAct->start(talkTime); //quote init

	setAct = new QAction(tr("&Settings"), this);
	setAct->setFont(font);
	setAct->setStatusTip(tr("It's the settings."));
	connect(setAct, &QAction::triggered, this, &BaseFrame::setting);//open settings panel

	exitAct = new QAction(tr("&Exit"), this);
	exitAct->setFont(font);
	exitAct->setShortcuts(QKeySequence::Quit);
	exitAct->setStatusTip(tr("Exit the application"));
	connect(exitAct, &QAction::triggered, this, &BaseFrame::discon);//close other functions than character
	connect(exitAct, &QAction::triggered, this, &QWidget::close);//close app
	
	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setFont(font);
	aboutAct->setStatusTip(tr("What is this app about?"));
	connect(aboutAct, &QAction::triggered, this, &BaseFrame::what);
}


void BaseFrame::selfmove()
{
	topLeft = this->mapToGlobal(QPoint(0, 0));
	topRight = this->mapToGlobal(QPoint(width, 0));
	bottomLeft = this->mapToGlobal(QPoint(0, height));
	bottomRight = this->mapToGlobal(QPoint(width, height));
	centre = this->mapToGlobal(QPoint(width/2, height/2));

	if (topLeft.x() >= 0 && topRight.x() <= screenWidth && topLeft.y() >= 0 && bottomLeft.y() <= screenHeight) {

			if (direction == 1) {//towards right
				if (topRight.x() + displacementLeft.x() < screenWidth) {//within screen width
					move(topLeft + displacementLeft);
					topLeft = this->mapToGlobal(QPoint(0, 0));//update current position of the app from top left
					topRight = this->mapToGlobal(QPoint(width, 0));
				}
				else if (topRight.x() + displacementLeft.x() >= screenWidth) {//more than screenwidth
					direction = 0;//change direction to left
					move(topLeft + displacementRight);
					topLeft = this->mapToGlobal(QPoint(0, 0));//update current position of the app from top left
					topRight = this->mapToGlobal(QPoint(width, 0));
				}
				else {
					move(screenCenter);//if at center of the screen
					topLeft = this->mapToGlobal(QPoint(0, 0));//update current position of the app from top left
					topRight = this->mapToGlobal(QPoint(width, 0));
				}
			}

			if(direction == 0) {//towards left
				if (topLeft.x() + displacementRight.x() > 0) {
					move(topLeft + displacementRight);
					topLeft = this->mapToGlobal(QPoint(0, 0));//update current position of the app from top left
					topRight = this->mapToGlobal(QPoint(width, 0));
				}
				else if(topLeft.x() + displacementRight.x() <= 0){
					direction = 1; //change direction to right
					move(topLeft + displacementLeft);
					topLeft = this->mapToGlobal(QPoint(0, 0));//update current position of the app from top left
					topRight = this->mapToGlobal(QPoint(width, 0));
				}
				else {
					move(screenCenter);//if at center
					topLeft = this->mapToGlobal(QPoint(0, 0));//update current position of the app from top left
					topRight = this->mapToGlobal(QPoint(width, 0));;
				}
			}
	}
	else {//when user successfully dragged out of screen
		move(screenCenter);
		topLeft = this->mapToGlobal(QPoint(0, 0));//update current position of the app from top left
		topRight = this->mapToGlobal(QPoint(width, 0));
		QMessageBox::information(this, tr("Out of screen"), tr("Please be a bit more considerate."));
	}
	update();

	if (quoteStat == 1) {//quote is enabled
		if (appear == true) {
			if (centre.x() < screenWidth / 2 && centre.y() < screenHeight / 2) {
				a->move(topRight);
			}
			else if (centre.x() > screenWidth / 2 && centre.y() < screenHeight / 2) {
				a->move(topLeft - QPoint(a->width(), 0));
			}
			else if (centre.x() < screenWidth / 2 && centre.y() > screenHeight / 2) {
				a->move(topRight);
			}
			else if (centre.x() > screenWidth / 2 && centre.y() > screenHeight / 2) {
				a->move(topLeft - QPoint(a->width(), 0));
			}
			else if (centre == screenCenter) {
				a->move(topRight);
			}
			else {//when out of screen
				if (centre.x() < screenWidth / 2) {
					a->move(topRight);
				}
				else if (centre.x() > screenWidth / 2 ) {
					a->move(topLeft - QPoint(a->width(), 0));
				}
			}
		}
	}
	
	else {//quote is disabled
		if (appear == true) {//if disabled while running as before was enabled
			delete a;
			appear = false;
		}
	}

	update();
}
void BaseFrame::selftalk()
{
	if (quoteStat == 1) {
		if (appear == false) {
			a = new Quote;//init quote
			if (centre.x() < screenWidth / 2 && centre.y() < screenHeight / 2) {
				a->move(topRight);
			}
			else if (centre.x() > screenWidth / 2 && centre.y() < screenHeight / 2) {
				a->move(topLeft - QPoint(a->width(), 0));
			}
			else if (centre.x() < screenWidth / 2 && centre.y() > screenHeight / 2) {
				a->move(topRight);
			}
			else if (centre.x() > screenWidth / 2 && centre.y() > screenHeight / 2) {
				a->move(topLeft - QPoint(a->width(), 0));
			}
			else {
				a->move(QPoint(screenWidth / 2, 0));
			}
			a->show();
			appear = true;
			QTimer::singleShot(lifespan, this, SLOT(delQuote()));//to be called once per quote init then call F(x) in slot
		}
	}
	update();
}

void BaseFrame::delQuote()
{
	if (quoteStat == 1) {
		if (appear == true) {
			delete a;
			appear = false;
		}
	}
	update();
}

void BaseFrame::discon()
{
	QCoreApplication::exit();
}


void BaseFrame::updatedPic(int i)
{
	if (pictureDirectory.size() == 0) {
		QFile inputFile("Resources/picDirectory.txt");
		if (inputFile.open(QIODevice::ReadOnly))//if able to open, readonly = delete previous content
		{
			QTextStream in(&inputFile);
			while (!in.atEnd())
			{
				QString line = in.readLine();
				pictureDirectory.push_back(line);
			}
			inputFile.close();
		}

		setPicture(i);
		image->setPixmap(pix);
		layout->addWidget(image);

		shape.setSize(pix.size());
		layout->setGeometry(shape);
		layout->setAlignment(this, Qt::AlignBottom);
		this->setMaximumSize(pix.size());
		this->setMinimumSize(pix.size());
		setLayout(layout);
		width = pix.size().width();
		height = pix.size().height();
		update();
	}
	else if((pictureDirectory.size() != 0)) {
		pictureDirectory.clear();
		QFile inputFile("Resources/picDirectory.txt");
		if (inputFile.open(QIODevice::ReadOnly))
		{
			QTextStream in(&inputFile);
			
			while (!in.atEnd())
			{
				QString line = in.readLine();
				pictureDirectory.push_back(line);
				
			}
			inputFile.close();
		}
		setPicture(i);
		image->setPixmap(pix);
		shape.setSize(pix.size());
		layout->setGeometry(shape);
		layout->setAlignment(this, Qt::AlignBottom);
		this->setMaximumSize(pix.size());
		this->setMinimumSize(pix.size());
		setLayout(layout);
		width = pix.size().width();
		height = pix.size().height();
		layout->update(); //instead of deleting and adding, just replace by updating as variable is the same (image)
		screenCenter = QPoint((screenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2)); //when picture changes, center changes
		update();
	}
}

void BaseFrame::updateValue()
{
	if (values.size() == 0) {
		QFile inputFile("Resources/values.txt");
		if (inputFile.open(QIODevice::ReadOnly))
		{
			QTextStream in(&inputFile);
			while (!in.atEnd())
			{
				QString line = in.readLine();
				values.push_back(line.toInt());
			}
			inputFile.close();
		}
		minute = values[0];
		displacementLeft = QPoint(values[1], 0);
		displacementRight = QPoint(-values[1], 0);
		walkTime = minute * second;
		talkTime = values[2] * 1000;
		lifespan = values[3] * 1000;
		quoteStat = values[4];
	}
	else {
		values.clear();
		QFile inputFile("Resources/values.txt");
		if (inputFile.open(QIODevice::ReadOnly))
		{
			QTextStream in(&inputFile);
			while (!in.atEnd())
			{
				QString line = in.readLine();
				values.push_back(line.toInt());
			}
			inputFile.close();
		}
		minute = values[0];
		displacementLeft = QPoint(values[1],0);
		displacementRight = QPoint(-values[1], 0);
		walkTime = minute * second;
		talkTime = values[2] * 1000;
		lifespan = values[3] * 1000;
		quoteStat = values[4];
		walkAct->start(walkTime);//reset the time and start a new one
		update();
	}
}