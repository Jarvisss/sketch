#ifndef _TYPES_H
#define _TYPES_H

#include <OpenMesh/Core/IO/MeshIO.hh>  // 读取文件
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh> // 操作文件 
#include <GL\freeglut.h>


#ifndef PI
#define PI 3.14159265359
#endif // !PI


class m_Point{

public:
	GLdouble x;
	GLdouble y;
	GLdouble t;
	GLdouble coeff_xt[4],coeff_yt[4];
	GLdouble curvature;

	m_Point(GLdouble,GLdouble);
	m_Point();
};

typedef std::vector<m_Point> Curve;
typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;


struct m_Curve{
	Curve curve;
	
	/*
	0	bend_line
	1	contour_line
	2	flat_line
	3	feature_line
	*/
	int mode;

	const GLfloat* penColor;
};

#endif