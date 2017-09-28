#ifndef PMATH_H
#define PMATH_H

#include <vector>
#include <Eigen/dense>
#include <qdebug.h>

#ifndef PI
#define PI 3.14159265359
#endif // !PI


const double inf = 0.0000001;
using namespace Eigen;
using std::vector;


class pMath{

	int					totalVertices;
	//MyMesh				*ptrMesh;
	int					type;


	MatrixXd CoefficientMatrix;
	MatrixXd m;
	MatrixXd b;


	vector<int>	bd_pts;
	vector<int>	in_pts;

public:
	
	pMath(int );
	~pMath();
	void cubic_spline();
};

#endif 