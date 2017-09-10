#include "meshpro.h"
#include "myopenglwidget.h"
#include <qapplication.h>
#include <QtWidgets/QApplication>
#include <qmessagebox.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	meshPro w;
	w.show();

	return a.exec();
}
