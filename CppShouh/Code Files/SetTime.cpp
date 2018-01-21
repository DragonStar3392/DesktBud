#include "SetTime.hpp"

SetTime::SetTime(QWidget *parent) :QDialog(parent) {
	ui.setupUi(this);
	createActions();
	ui.timeInput->setDisabled(true);

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
		ui.timeInput->setText(QString::number(values[0]));
	}
}

void SetTime::setTime(int tim) {
	time = tim;
	t = QString::number(time);
	ui.timeInput->setText(t);
}

SetTime::~SetTime(){

	delete saveAct;
}

void SetTime::setSBox(){

	time = ui.spinBox->value() * 100;
	t = QString::number(time);
	ui.timeInput->setText(t);
}

void SetTime::save() {
	values[0] = time; //index 0 is reserved for time interval
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

void SetTime::createActions()
{
	QSignalMapper* signalMapper = new QSignalMapper(this);
	connect(ui.sec1, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.sec3, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.sec5, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.sec10, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.sec30, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(ui.sec60, SIGNAL(clicked()), signalMapper, SLOT(map()));

	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(setSBox()));//update lineEdit value for spinbox

	signalMapper->setMapping(ui.sec1, 100);
	signalMapper->setMapping(ui.sec3, 300);
	signalMapper->setMapping(ui.sec5, 500);
	signalMapper->setMapping(ui.sec10, 1000);
	signalMapper->setMapping(ui.sec30, 3000);
	signalMapper->setMapping(ui.sec60, 6000);

	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setTime(int)));

	saveAct = new QAction(tr("&Save"), this);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(save()));
}