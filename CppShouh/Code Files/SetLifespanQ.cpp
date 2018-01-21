#include "SetLifespanQ.hpp"

SetLifespanQ::SetLifespanQ(QWidget *parent) :QDialog(parent) {
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
		ui.lineEdit->setText(QString::number(values[3]));
	}

	if (values[2] < 60) {
		ui.spinBox->setMaximum(values[2]-5);/*set limit so that lifespan of quote 
										does not go over the appearance interval*/ //<------ values[2]-5
	}
}

void SetLifespanQ::setTime() {
	time = ui.spinBox->value();
	lp = QString::number(time);
	ui.lineEdit->setText(lp);
}

void SetLifespanQ::save() {
	values[3] = time; //index 3 is reserved for quote's lifespan
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
	ui.spinBox->setMaximum(60);/*Set limit back to 60*/
	accept();
}

void SetLifespanQ::createActions()
{
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(setTime()));

	saveAct = new QAction(tr("&Save"), this);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(save()));
}
