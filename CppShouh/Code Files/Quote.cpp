#include "Quote.hpp"

Quote::Quote(QWidget *parent) :QDialog(parent) {
	ui.setupUi(this);

	QDesktopWidget *desktop = QApplication::desktop();
	int screenWidth = desktop->width();

	if (values.size() != 0 && quotes.size() != 0) {
		values.clear();
		quotes.clear();
	}

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
	}

	QFile iputFile("Resources/values.txt");
	if (iputFile.open(QIODevice::ReadOnly))
	{
		QTextStream in(&iputFile);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			values.push_back(line.toInt());
		}
		iputFile.close();
	}

	QTime time = QTime::currentTime();//desktop time for random
	qsrand((uint)time.msec()); // seed

	randomValue = randInt(0, quotes.size()-1);
	sizeQ = quotes[randomValue].size();//number of characters of quote
	if (sizeQ <= 15)
		fontSize = 20;
	else if (sizeQ <= 40)
		fontSize = 15;
	else if (sizeQ <= 100)
		fontSize = 12;
	QFont quoteFont("Arial", fontSize);
	ui.text->setFont(quoteFont);
	ui.text->setText(quotes[randomValue]);

	setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_TranslucentBackground, true);
}

Quote::~Quote()
{
	//QMessageBox::information(this, tr("Message"), tr("Operation successful."));
}

int Quote::randInt(int low, int high)
{
	return qrand() % ((high + 1) - low) + low;
}
