#ifndef PMATH_H
#define PMATH_H

#include <vector>
#include <Eigen/dense>
#include <qdebug.h>
#include <types.h>


// num: 两点间插值的个数
void cubic_spline(m_Curve *c, int num);

GLdouble cal_curvature(GLdouble dx, GLdouble dx2, GLdouble dy, GLdouble dy2);

GLdouble euclid_distance(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);


#endif