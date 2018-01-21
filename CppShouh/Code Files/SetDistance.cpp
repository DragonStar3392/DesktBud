#include "SetDistance.hpp"

SetDistance::SetDistance(QWidget *parent) :QDialog(parent) {
	ui.setupUi(this);
	createActions();
	ui.outputShow->setDisabled(true);

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
		ui.outputShow->setText(QString::number(values[1]));
	}
}

void SetDistance::setDistance(int dist)
{
	distance = dist;
	d = QString::number(distance);
	ui.outputShow->setText(d);
}

SetDistance::~SetDistance()
{
	delete saveAct;
}

void SetDistance::setSBox()
{
	distance = ui.spinBox->value();
	d = QString::number(distance);
	ui.outputShow->setText(d);
}

void SetDistance::save() {
	values[1] = distance; //index 1 is reserved for time interval
	QFile outputFile("Resources/values.txt");
	if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&outputFile);
		{
			QTextStream out(&outputFile);
			for (int i = 0; i < values.size(); i++) {
				out << values[i] << endl;
			}
			outputFile.close();
		}
		QMessageBox::information(this, tr("Message"), tr("Operation successful."));
	}
	accept();
}

void SetDistance::createActions()
{
	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(ui.dist0, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.dist5, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.dist10, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.dist20, SIGNAL(clicked()), signalMapper, SLOT(map()));

	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(setSBox()));

	signalMapper->setMapping(ui.dist0, 0);
	signalMapper->setMapping(ui.dist5, 5);
	signalMapper->setMapping(ui.dist10, 10);
	signalMapper->setMapping(ui.dist20, 20);

	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setDistance(int)));

	saveAct = new QAction(tr("&Save"), this);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(save()));
}