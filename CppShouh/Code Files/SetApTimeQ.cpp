#include "SetApTimeQ.hpp"

SetApTimeQ::SetApTimeQ(QWidget *parent) :QDialog(parent) {
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
		ui.lineEdit->setText(QString::number(values[2]));
	}
}

void SetApTimeQ::setTime() {
	time = ui.spinBox->value();
	t = QString::number(time);
	ui.lineEdit->setText(t);
}

void SetApTimeQ::save() {
	values[2] = time; //index 2 is reserved for quote appearing interval
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

void SetApTimeQ::createActions()
{
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(setTime()));

	saveAct = new QAction(tr("&Save"), this);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(save()));
}
