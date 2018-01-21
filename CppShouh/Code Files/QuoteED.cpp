#include "QuoteED.hpp"

QuoteED::QuoteED(QWidget *parent) :QDialog(parent) {
	ui.setupUi(this);
	createActions();
	ui.lineEdit->setDisabled(true);

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
	stat = values[4];

	if (values[4] == 1)
		ui.lineEdit->setText("Enabled");
	else
		ui.lineEdit->setText("Disabled");
}

void QuoteED::enable()
{
	stat = 1;
	ui.lineEdit->setText("Enabled");
}

void QuoteED::disable()
{
	stat = 0;
	ui.lineEdit->setText("Disabled");
}

void QuoteED::save()
{
	values[4] = stat; //index 4 is reserved for quote enable/disable
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

void QuoteED::createActions()
{
	connect(ui.enable, SIGNAL(clicked()), this, SLOT(enable()));
	connect(ui.disable, SIGNAL(clicked()), this, SLOT(disable()));

	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(save()));
}