#include "types.h"

m_Point::m_Point()
{
	x = y = t = 0;
	for each (GLdouble xt in coeff_xt) xt = 0.0;
	for each (GLdouble yt in coeff_yt) yt = 0.0;
}
m_Point::m_Point(GLdouble x, GLdouble y)
{
	this->x = x;
	this->y = y;
	this->t = 0;

	for each (GLdouble xt in coeff_xt) xt = 0.0;
	for each (GLdouble yt in coeff_yt) yt = 0.0;
}