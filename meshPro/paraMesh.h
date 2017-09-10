#ifndef PARAMESH_H
#define PARAMESH_H

#include <OpenMesh/Core/IO/MeshIO.hh>  // 读取文件
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh> // 操作文件 
#include <OpenMesh\Core\Mesh\Handles.hh>
//#include <OpenMesh\Core\Mesh\PolyConnectivity.hh>
#include <vector>
#include <Eigen/dense>
#include <qdebug.h>

#ifndef PI
#define PI 3.14159265359
#endif // !PI


const double inf = 0.0000001;
using namespace Eigen;
using std::vector;

typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;

class paraMesh{
	MyMesh				mesh;
	int					totalVertices;
	//MyMesh				*ptrMesh;
	int					type;

	OpenMesh::VPropHandleT<bool>VH_Bool;
	OpenMesh::VPropHandleT<double>VH_Double;
	
	vector<MyMesh::HalfedgeHandle> h_handle;
	MatrixXd CoefficientMatrix;
	MatrixXd u;
	MatrixXd b;


	vector<int>	bd_pts;
	vector<int>	in_pts;
	vector<OpenMesh::Vec2f>	result;

public:
	/*
	type:
	1 uniform;
	2 minimum square;
	3 shape preserve;
	*/
	paraMesh(int, MyMesh*);
	~paraMesh();

	/* calculate parameterized surface according to different types of parameterization */
	void para();


	/*
	* calculate the border points' plannar position
	*/
	void calBorderPoints();

	/*
	* find border edges and save into 'h_handle'
	*/
	void findBorderEdges();

	/*
	* calculate the inner points' plannar position
	*/
	void calInnerPoints();

	vector<float> shape_preserve(int);
	MyMesh* getMesh();

};

#endif PARAMESH_H