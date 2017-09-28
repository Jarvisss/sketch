#ifndef MESHPRO_H
#define MESHPRO_H

#include <QtWidgets/QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QImage>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "ui_sketch.h"
#include "myOpenGLWidget.h"
//#include "paraMesh.h"


namespace Ui {
	class MainWindow;
}

using namespace std;

class meshPro : public QMainWindow
{
	Q_OBJECT

public:
	meshPro(QWidget *parent = 0);
	~meshPro();

	//void readMesh();
	//void writeMesh(MyMesh*);

private:
	Ui::meshProClass ui;

	myOpenGLWidget *myWidget=NULL;
	QMenu		*menu[10];
	QAction		*act[10];
	//paraMesh	*pMesh;
	MyMesh		myMesh;
	bool		is_loaded=false;

	void unCheckModes();
	void unCheckLines();
private slots:
	void drag_clicked();
	void draw_clicked();
	void bend_line();
	void contour_line();
	void flat_line();
	void feature_line();
};

#endif // MESHPRO_H
