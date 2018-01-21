#include "ModQuotes.hpp"

ModQuotes::ModQuotes(QWidget *parent) :QDialog(parent) {
	ui.setupUi(this);
	createActions();

	QFile inputFile("Resources/quotes.txt");
	if (inputFile.open(QIODevice::ReadOnly))
	{
		QTextStream in(&inputFile);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			quotes.push_back(line);
		}
		inputFile.close();
		ui.lineEdit->setText(quotes[0]);
	}
	ui.spinBox->setMaximum(quotes.size());
	currentSize = quotes.size();
}

void ModQuotes::updateQuote() {
	ui.lineEdit->setText(quotes[ui.spinBox->value()-1]);
}

void ModQuotes::modQuote()
{
	quotes[ui.spinBox->value()-1] = ui.lineEdit->text();
}

void ModQuotes::addQuote()
{
	ui.spinBox->setMaximum(currentSize+1);
	quotes.push_back("");
	currentSize += 1;
	QMessageBox::information(this, tr("Sucessful"), tr("Added a new space for a quote.\nIt is located at the last number."));
}

void ModQuotes::delQuote()
{
	if (currentSize > 1) {
		quotes.erase(quotes.begin() + (ui.spinBox->value() - 1));
		ui.spinBox->setMaximum(currentSize - 1);
		currentSize -= 1;
		ui.lineEdit->setText(quotes[ui.spinBox->value() - 1]);
		QMessageBox::information(this, tr("Sucessful"), tr("Deleted the current quote. \n It is possible to recover by clicking cancel button."));
	}
	else {
		QMessageBox::warning(this, tr("Error!"), tr("There must be at least one quote!"));
	}
}

void ModQuotes::save()
{
	QFile outputFile("Resources/quotes.txt");
	if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&outputFile);
		{
			QTextStream out(&outputFile);
			for (int i = 0; i < quotes.size(); i++) {
				out << quotes[i] << endl;
			}
			outputFile.close();
		}
		QMessageBox::information(this, tr("Message"), tr("Operation successful."));
	}
	accept();
}

void ModQuotes::createActions()
{
	connect(ui.spinBox, SIGNAL(valueChanged(int)), this, SLOT(updateQuote()));
	connect(ui.lineEdit, SIGNAL(textEdited(const QString&)), this, SLOT(modQuote()));

	connect(ui.addQte, SIGNAL(clicked()), this, SLOT(addQuote()));
	connect(ui.delQte, SIGNAL(clicked()), this, SLOT(delQuote()));

	saveAct = new QAction(tr("&Save"), this);
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(save()));
}
