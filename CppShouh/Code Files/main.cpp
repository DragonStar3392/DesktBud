#include "BaseFrame.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	BaseFrame w;
	w.show();
	return app.exec();
}
