#include "Settings.hpp"

Settings::Settings(QWidget *parent) :QDialog(parent) {
	ui.setupUi(this);
	createActions();
	ui.lineEdit->setDisabled(true);//user unable to write/type here
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
	QImage idle(pictureDirectory[0]);
	ui.Piclabel->setPixmap(QPixmap::fromImage(idle));//set picture on settings
	ui.lineEdit->setText(pictureDirectory[0]);//picture's directory

	QImage owo(pictureDirectory[1]);
	ui.owoImage->setPixmap(QPixmap::fromImage(owo));

	QImage pat(pictureDirectory[2]);
	ui.patImage->setPixmap(QPixmap::fromImage(pat));

	QImage poke(pictureDirectory[3]);
	ui.pokeImage->setPixmap(QPixmap::fromImage(poke));
}

void Settings::browse(int direct) {

	QFileDialog dialog(this);
	dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
	dialog.setViewMode(QFileDialog::Detail);
	picDirectory = QFileDialog::getOpenFileName(this,
		tr("Open Images"), QString(), tr("Image Files (*.png *.jpg *.bmp)"));

	if (!picDirectory.isEmpty())
	{
		QImage image(picDirectory);//check size
		bool width = image.size().width() <= 300 && image.size().width() >= 150;
		bool height = image.size().height() <= 300 && image.size().height() >= 150;

		if (width && height) {//if fit conditions
			QImage unscaled(picDirectory);
			if (direct == 0) {
				QImage image = unscaled.scaled(300, 300, Qt::KeepAspectRatio);
				ui.Piclabel->setPixmap(QPixmap::fromImage(image));
				ui.lineEdit->setText(picDirectory);
				pictureDirectory[0] = picDirectory;
				fit = true;
				pressed += 1;
			}
			else if (direct == 1) {
				QImage image = unscaled.scaled(200, 200, Qt::KeepAspectRatio);
				ui.owoImage->setPixmap(QPixmap::fromImage(image));
				pictureDirectory[1] = picDirectory;
				fit = true;
				owoPress += 1;
			}
			else if (direct == 2) {
				QImage image = unscaled.scaled(200, 200, Qt::KeepAspectRatio);
				ui.patImage->setPixmap(QPixmap::fromImage(image));
				pictureDirectory[2] = picDirectory;
				fit = true;
				patPress += 1;
			}
			else if (direct == 3) {
				QImage image = unscaled.scaled(200, 200, Qt::KeepAspectRatio);
				ui.pokeImage->setPixmap(QPixmap::fromImage(image));
				pictureDirectory[3] = picDirectory;
				fit = true;
				pokePress += 1;
			}
		}
		else {
			QMessageBox::warning(this, tr("Error!"), tr("Image size unfit!"));
			fit = false;
		}
	}
}

Settings::~Settings()
{
	delete browseAct;
	delete changeAct;
	delete setTimeAct;
	delete setDistanceAct;
	delete setIntQAct;
	delete setLifeAct;
}

void Settings::change()
{
	if (fit == false && (pressed > 0 || owoPress > 0 || patPress > 0 || pokePress > 0)) {
		QMessageBox::warning(this, tr("Error!"), tr("Go and recheck your image size."));
		return;
	}
	else {

		QFile outputFile("Resources/picDirectory.txt");
		if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream out(&outputFile);
			for (int i = 0; i < pictureDirectory.size(); i++) {
				out << pictureDirectory[i] << endl;
			}
			outputFile.close();
		}
		QMessageBox::information(this, tr("Message"), tr("Operation successful."));
	}
	accept();
}

void Settings::setTime()
{
	SetTime b;
	b.setModal(true);
	b.exec();
}

void Settings::setDistance()
{
	SetDistance c;
	c.setModal(true);
	c.exec();
}

void Settings::setInterQ()
{
	SetApTimeQ d;
	d.setModal(true);
	d.exec();
}

void Settings::setLifespan()
{
	SetLifespanQ e;
	e.setModal(true);
	e.exec();
}

void Settings::modQuote()
{
	ModQuotes f;
	f.setModal(true);
	f.exec();
}

void Settings::quoteED()
{
	QuoteED i;
	i.setModal(true);
	i.exec();
}

void Settings::movpic()//pls wait for next update
{
	QMessageBox::information(this, tr("Sorry"), tr("Please wait for next patch.\nSorry for your inconvenience."));
}

void Settings::createActions()
{
	QSignalMapper* signalMapper = new QSignalMapper(this);
	//same browse but for different index as each browse changes different picture's directory
	browseAct = new QAction(tr("&Browse"), this);
	browseAct->setStatusTip(tr("Browse for picture"));
	connect(ui.BrowsePic, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.owoBrowse, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.patBrowse, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.pokeBrowse, SIGNAL(clicked()), signalMapper, SLOT(map()));
	signalMapper->setMapping(ui.BrowsePic, 0);
	signalMapper->setMapping(ui.owoBrowse, 1);
	signalMapper->setMapping(ui.patBrowse, 2);
	signalMapper->setMapping(ui.pokeBrowse, 3);
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(browse(int)));

	changeAct = new QAction(tr("&Change"), this);
	changeAct->setStatusTip(tr("Change the picture"));
	connect(ui.ConfirmChanges, SIGNAL(clicked()), this, SLOT(change()));

	setTimeAct = new QAction(tr("&Set Time"), this);
	setTimeAct->setStatusTip(tr("Set the time for movement."));
	connect(ui.setIntervalB, SIGNAL(clicked()), this, SLOT(setTime()));

	setDistanceAct = new QAction(tr("&Set Distance"), this);
	setDistanceAct->setStatusTip(tr("Set the distance for movement."));
	connect(ui.setDistanceB, SIGNAL(clicked()), this, SLOT(setDistance()));

	setIntQAct = new QAction(tr("&Set Appearance Interval"), this);
	setIntQAct->setStatusTip(tr("Set quote spawn interval time."));
	connect(ui.setApTimeQ, SIGNAL(clicked()), this, SLOT(setInterQ()));

	setLifeAct = new QAction(tr("&Set lifespan"), this);
	setLifeAct->setStatusTip(tr("Set quote's lifespan."));
	connect(ui.setLifespanQ, SIGNAL(clicked()), this, SLOT(setLifespan()));

	modQuoteAct = new QAction(tr("&Modify quote"), this);
	modQuoteAct->setStatusTip(tr("Modify quote(s)."));
	connect(ui.setQuotes, SIGNAL(clicked()), this, SLOT(modQuote()));

	connect(ui.QuoteEnDis, SIGNAL(clicked()), this, SLOT(quoteED()));
	
	connect(ui.mpBrowse, SIGNAL(clicked()), this, SLOT(movpic()));
}