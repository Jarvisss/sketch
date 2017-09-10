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
	//ui.openImg->setToolTipDuration(2);
	//menu[0] = new QMenu("File", this);

	//menu[3] = new QMenu("Open", this);
	//menu[3]->addAction("OpenImg");
	//menu[3]->addAction("OpenMesh");
	//menu[0]->addAction("New");
	//menu[0]->addMenu(menu[3]);
	//menu[0]->addAction("Save");
	//menu[0]->addAction("Exit");

	//act[0] = new QAction("Undo", this);
	//act[0]->setShortcut(Qt::CTRL | Qt::Key_Z);
	////act[0]->setStatusTip("Undo");

	//act[1] = new QAction("Copy", this);
	//act[1]->setShortcut(Qt::CTRL | Qt::Key_V);
	////act[1]->setCheckable(true);

	//menu[1] = new QMenu("Edit");
	//menu[1]->addAction(act[0]);
	//menu[1]->addAction(act[1]);

	//menu[2] = new QMenu("Tools");
	//menu[3] = new QMenu("Parameterize",this);
	//act[2] = new QAction("Uniform", this);
	//act[3] = new QAction("Shape-preserve", this);
	//menu[3]->addAction(act[2]);
	//menu[3]->addAction(act[3]);
	//menu[2]->addMenu(menu[3]);

	//ui.menuBar->addMenu(menu[0]);
	//ui.menuBar->addMenu(menu[1]);
	//ui.menuBar->addMenu(menu[2]);

	//ui.is_show_point->setChecked(true);


	//connect(ui.menuBar, SIGNAL(triggered(QAction*)), this, SLOT(triggerMenu(QAction*)));
	connect(ui.openImg, SIGNAL(clicked()), myWidget, SLOT(loadTexture()));
	connect(ui.clearLines, SIGNAL(clicked()), myWidget, SLOT(clearLines()));
}

meshPro::~meshPro()
{

}

void meshPro::triggerMenu(QAction* act)
{
//
//	if (act->text() == "Exit")
//	{
//		qDebug() << "Exit";
//		exit(0);
//	}
//
//	if (act->text() == "OpenImg")
//	{
//		ui.myWidget->loadTexture();	
//		
//		ui.myWidget->update();
//	}
//	if (act->text() == "OpenMesh")
//	{		
//		readMesh();
//		ui.myWidget->update();
//	}
//	if (act->text() == "Uniform"){
//		// for uniform parameter
//		// test...
//		if (is_loaded){
//			//newwidget = new myOpenGLWidget();
//			
//			pMesh = new paraMesh(1, &myMesh);
//			pMesh->para();
//
//			myMesh = *(pMesh->getMesh());
//			delete pMesh;
//			
//			ui.myWidget->update();
//			/*newwidget->loadTexture();
//			newwidget->initMesh(pMesh->getMesh());
//			newwidget->show2DTexture = true;
//			newwidget->showFace = true;
//			newwidget->showPoint = false;
//			
//			newwidget->show();
//			newwidget->update();*/
//		}
//		
//	}
//	if (act->text() == "Shape-preserve"){
//		if (is_loaded){
//			pMesh = new paraMesh(2, &myMesh);
//			pMesh->para();
//
//			myMesh = *(pMesh->getMesh());
//			delete pMesh;
//			
//			ui.myWidget->update();
//		}
//	}
//
}

void meshPro::drag_clicked(){
	ui.dragmode->setChecked(true);
	ui.drawmode->setChecked(false);
	myWidget->inputMode = 0;
}


void meshPro::draw_clicked(){
	ui.dragmode->setChecked(false);
	ui.drawmode->setChecked(true);
	myWidget->inputMode = 1;
	myWidget->resetProjection();
	myWidget->update();
}
