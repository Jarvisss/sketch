#include "pMath.h"
#include <QTextStream>

pMath::pMath(int n){
	totalVertices = n;
	
	qDebug() << "totalVertices" << totalVertices;
	CoefficientMatrix.resize(totalVertices, totalVertices);
	CoefficientMatrix.setIdentity(totalVertices, totalVertices);// coefficient M
	m.resize(totalVertices, 1);
	m.setZero(totalVertices, 1);// M*u = b
	b.resize(totalVertices, 1);
	b.setZero(totalVertices, 1);
}

pMath::~pMath(){
}


bool judge(float xx, float yy){
	//cout << xx - yy << endl;   
	if ((xx - yy) > -1 * inf && (xx - yy) < inf)return true;
	return false;
}

void pMath::cubic_spline(){
	
}



