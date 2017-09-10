#ifndef OPMESH_H
#define OPMESH_H


#include <iostream>
#include <OpenMesh/Core/IO/MeshIO.hh>  // 读取文件
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh> // 操作文件 
#include "GL\glut.h"
#include "QtOpenGL\qgl.h"
#include <math.h>
#include <Windows.h>
#include <string>
#include <qdebug.h>


typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;

using namespace std;

class opMesh{
	

public:
	GLuint	showFaceList, showWireList;
	MyMesh	mymesh;
	


	void	readfile(string str);
	void	loadTexture(string str);
	MyMesh*	getMymesh();
};

#endif