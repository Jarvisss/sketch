#include "meshPro.h"
#include "QDebug"
#include "QMessageBox"
#include "qlayout.h"
#include "QTextCodec"

#include "iostream"


meshPro::meshPro(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	myWidget = new myOpenGLWidget();
	myWidget->setAttribute(Qt::WA_TranslucentBackground, true);
	myWidget->resize(ui.widget->width(), ui.widget->height());
	ui.gridLayout->addWidget(myWidget, 0, 0, 1, 1);

	ui.clearLines->setToolTip("Clear strokes");



	//connect(ui.menuBar, SIGNAL(triggered(QAction*)), this, SLOT(triggerMenu(QAction*)));
	connect(ui.openImg, SIGNAL(clicked()), myWidget, SLOT(loadTexture()));
	connect(ui.clearLines, SIGNAL(clicked()), myWidget, SLOT(clearLines()));
}

meshPro::~meshPro()
{

}


void meshPro::drag_clicked(){
	unCheckModes();
	ui.drag->setChecked(true);
	myWidget->inputMode = 0;
}


void meshPro::draw_clicked(){
	unCheckModes();
	ui.draw->setChecked(true);
	myWidget->inputMode = 1;
	
	myWidget->resetProjection();
	myWidget->update();
}


void meshPro::bend_line()
{
	draw_clicked();
	unCheckLines();
	ui.Bend->setChecked(true);
	myWidget->drawMode = 0;
	myWidget->penColor = red;
}

void meshPro::contour_line()
{
	draw_clicked();
	unCheckLines();
	ui.Contour->setChecked(true);
	myWidget->drawMode = 1;
	myWidget->penColor = black;
}


void meshPro::flat_line(){
	draw_clicked();
	unCheckLines();
	ui.Flat->setChecked(true);
	myWidget->drawMode = 2;
	myWidget->penColor = green;
}

void meshPro::feature_line(){
	draw_clicked();
	unCheckLines();
	ui.Sharp->setChecked(true);
	myWidget->drawMode = 3;
	myWidget->penColor = purple;
}

void meshPro::unCheckLines()
{
	ui.Bend->setChecked(false);
	ui.Contour->setChecked(false);
	ui.Flat->setChecked(false);
	ui.Sharp->setChecked(false);
}

void meshPro::unCheckModes()
{
	ui.drag->setChecked(false);
	ui.draw->setChecked(false);
}
