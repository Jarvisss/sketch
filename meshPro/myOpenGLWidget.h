#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H


#include <qopenglwidget.h>

#include <qopengltexture.h>
#include <QMouseEvent>
#include <QFileDialog>
#include <qdebug.h>
#include <QString>
#include <qtextcodec.h>
#include <QtOpenGL\qgl.h>

#include <ArcBall.h>
#include <GL\freeglut.h>
#include <iostream>
#include <OpenMesh/Core/IO/MeshIO.hh>  // 读取文件
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh> // 操作文件 
#include <opencv2\opencv.hpp>
#include <math.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <qopenglfunctions.h>

#include <triangle.h>

#define MAXSCALE 50
#define MINSCALE 0.02
#define RATIO 1.05
#define PI 3.14159265359
#define MAGIC 987654.32

//#include <QGLWidget>
namespace Ui {
class myOpenGLWidget;
}
typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;


struct m_Point{
	GLdouble x;
	GLdouble y;
};

typedef std::vector<m_Point> Curve;

//struct m_Curve{
//	Curve curve;
//	Curve* p_next;
//};

class myOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit myOpenGLWidget(QWidget *parent = 0);
    ~myOpenGLWidget();

	void setBackGroundTexture();

	void initMesh(MyMesh*);
	void resetProjection();
	void setLight();
	void render();
	void drawPoint();
	void draw2DTextureLines();
	void drawEdge();
	void drawFace();
	void drawAxes();

	void drawPath();
	void drawCurrentCurv();
	void drawBorder();
	void drawTransparentPlane();
	m_Point to_perspect(QPoint);

	/* 
	if closed, return [true] and set border_curves[] and set is_closed to true
	if not, return [false]
	*/
	bool isBorderClosed();


	/*
	return true if two segments are crossed
	*/
	bool isCross(m_Point, m_Point, m_Point, m_Point);

	/*
	return cross point;
	*/
	m_Point Cross(m_Point, m_Point, m_Point, m_Point);
	/*
	return number of intersections of two polylines
	*/
	int hasNIntersection(Curve*, Curve*);
	/*
	return true if one curve is closed
	*/
	bool calcBorderPart(Curve*);
	
	void myTriangulate();
public slots:
	// slots for xyz-rotation slider
	void check_edge_state(int state);
	void check_face_state(int state);
	void check_point_state(int state);
	void check_texture_state(int state);
	void check_light_state(int state);
	void check_axes_state(int state);

	void setWheelSpeed(int);
	void setLightPositionX(int);
	void setLightPositionY(int);
	void setLightPositionZ(int);
	void loadTexture();
	void clearLines();



signals:
	// signaling rotation from mouse movement

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void timerEvent(QTimerEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	//key func here
	void wheelEvent(QWheelEvent *event);


public:
	int xRot;
	int yRot;
	int zRot;
	struct triangulateio in, mid, out, vorout;
	float x_ratio = 0.8;
	float y_ratio = 0.9;

	int inputMode=0; // 0 for drag; 1 for draw

	bool showFace = false;
	bool showWire = false;
	bool showPoint = true;
	bool is_load_texture = false;
	bool is_drawing = false;

	// if border closed;
	bool is_closed = false;
	bool show2DTexture = false;
	bool showAxes = true;
	bool showLight = true;
	float WheelSpeed = 0.001;
	GLfloat light_position[4];
	GLfloat		eye_distance_;
	GLfloat		eye_goal_[3];
	GLfloat		eye_direction_[3];

	GLuint		uiVBO[2];
	GLuint		texture_[1];

private:
	m_Point last_p;

	//save current drawing points
	Curve current_curve;

	//save border points
	Curve border_curve;
	std::vector<Curve> path;

	CArcBall	*ptr_arcball_;
	GLubyte		*pixels;
	int			p_width;
	int			p_height;

	MyMesh		*myMesh=NULL;
	int			totalVertices;
	double		scale;
	

	QPoint		current_position_;;
};

#endif // MYOPENGLWIDGET_H
