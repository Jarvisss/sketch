#include "pMath.h"


void cubic_spline(m_Curve* c, int num){
	
	int size = c->curve.size();

	if (size < 3) return;
	GLdouble* length = new GLdouble[size];

	for (int i = 0; i < size; i++) length[i] = 0.0;

	GLdouble x,y,last_x,last_y;
	GLdouble t = 0;


	// calculate length of polyline
	last_x = c->curve.at(0).x;
	last_y = c->curve.at(0).y;

	int i = 1;
	for (auto iter = c->curve.begin()+1; iter != c->curve.end(); ++iter,++i)
	{
		x = iter->x;
		y = iter->y;
		length[i] = length[i-1] +euclid_distance(last_x, last_y, x, y);
		last_x = x;
		last_y = y;
	}

	// normalize to (0,1)
	i = 0;
	//qDebug("total :%lf\n", length[size - 1]);
	for (auto iter = c->curve.begin(); iter != c->curve.end(); ++iter, ++i)
	{
		length[i] /= length[size - 1];
		iter->t = length[i];
		qDebug("%d :%lf\n",i, length[i]);
	}

	// Ax=b
	Eigen::MatrixXd A(size,size);
	Eigen::VectorXd x_to_solve(size), y_to_solve(size), b1(size), b2(size);
	A.setIdentity(size, size);
	x_to_solve.setZero(size);
	b1.setZero(size);
	b2.setZero(size);

	// set A and b
	i = 1;
	for (auto iter = c->curve.begin()+1; iter != c->curve.end()-1; ++iter, ++i)
	{
		A(i, i - 1) = iter->t - (iter - 1)->t;  // h0 = t1-t0
		A(i, i) = 2 * ((iter + 1)->t - (iter - 1)->t); // 2(h0+h1) = 2*(t2-t0)
		A(i, i + 1) = (iter + 1)->t - iter->t;	// h1 = t2-t1


		b1(i) = ((iter + 1)->x - iter->x) / ((iter + 1)->t - iter->t) 
			- (iter->x - (iter - 1)->x) / (iter->t - (iter - 1)->t);
		b1(i) *= 6;


		b2(i) = ((iter + 1)->y - iter->y) / ((iter + 1)->t - iter->t)
			- (iter->y - (iter - 1)->y) / (iter->t - (iter - 1)->t);
		b2(i) *= 6;
	}

	// solve x,y
	x_to_solve = A.colPivHouseholderQr().solve(b1);
	y_to_solve = A.colPivHouseholderQr().solve(b2);
	//for (int i = 0; i < size; i++)
	//{
	//	qDebug("xto_solve[%d] = %lf\n", i, x_to_solve[i]);
	//	qDebug("yto_solve[%d] = %lf\n", i, y_to_solve[i]);
	//}



	// calculate a,b,c,d
	i = 0;
	for (auto iter = c->curve.begin(); iter != c->curve.end() - 1; ++iter, ++i)
	{
		// step length
		GLdouble hi = (iter + 1)->t - iter->t;
		// xai = xi  || yai = yi
		iter->coeff_xt[0] = iter->x; 
		iter->coeff_yt[0] = iter->y; 

		// xbi = (xi+1 - xi)/hi - hi* mi / 2 - hi*( mi+1 - mi )/6
		iter->coeff_xt[1] = ((iter + 1)->x - iter->x) / hi - hi / 2 * x_to_solve(i) - hi / 6 * (x_to_solve(i + 1) - x_to_solve(i));
		iter->coeff_yt[1] = ((iter + 1)->y - iter->y) / hi - hi / 2 * y_to_solve(i) - hi / 6 * (y_to_solve(i + 1) - y_to_solve(i));


		iter->coeff_xt[2] = x_to_solve(i) / 2;
		iter->coeff_yt[2] = y_to_solve(i) / 2;


		iter->coeff_xt[3] = (x_to_solve(i + 1) - x_to_solve(i)) / (6 * hi);
		iter->coeff_yt[3] = (y_to_solve(i + 1) - y_to_solve(i)) / (6 * hi);

		//qDebug("xa[%d] = %lf\n", i, iter->coeff_xt[0]);
		//qDebug("xb[%d] = %lf\n", i, iter->coeff_xt[1]);
		//qDebug("xc[%d] = %lf\n", i, iter->coeff_xt[2]);
		//qDebug("xd[%d] = %lf\n", i, iter->coeff_xt[3]);

		//qDebug("ya[%d] = %lf\n", i, iter->coeff_yt[0]);
		//qDebug("yb[%d] = %lf\n", i, iter->coeff_yt[1]);
		//qDebug("yc[%d] = %lf\n", i, iter->coeff_yt[2]);
		//qDebug("yd[%d] = %lf\n", i, iter->coeff_yt[3]);

	}

	//cal_curvature(c);

	// interpolation
	i = 0;
	Curve temp;
	GLdouble dx, dy, dx2, dy2;
	for (auto iter = c->curve.begin(); iter != c->curve.end()-1; ++iter, ++i)
	{
		GLdouble step = ((iter + 1)->t - iter->t)/(num+1);
		dx = iter->coeff_xt[1];  // x' = b
		dx2 = 2 * iter->coeff_xt[2]; // x'' = 2c
		dy = iter->coeff_yt[1];
		dy2 = 2 * iter->coeff_yt[2];
		iter->curvature = cal_curvature(dx, dx2, dy, dy2);
		qDebug("curvature[%d] = %lf\n", i, iter->curvature);
		temp.push_back(*iter);
		for (int j = 1; j <= num; j++)
		{
			GLdouble distance = step*j;
			GLdouble x_new = iter->coeff_xt[0] + iter->coeff_xt[1] * distance + iter->coeff_xt[2] * distance*distance + iter->coeff_xt[3] * distance*distance*distance;
			GLdouble y_new = iter->coeff_yt[0] + iter->coeff_yt[1] * distance + iter->coeff_yt[2] * distance*distance + iter->coeff_yt[3] * distance*distance*distance;
			
			dx = iter->coeff_xt[1] + 2 * iter->coeff_xt[2] * distance + 3 * iter->coeff_xt[3] * distance * distance;
			dx2 = 2 * iter->coeff_xt[2] + 6 * iter->coeff_xt[3] * distance;
			dy = iter->coeff_yt[1] + 2 * iter->coeff_yt[2] * distance + 3 * iter->coeff_yt[3] * distance * distance;
			dy2 = 2 * iter->coeff_yt[2] + 6 * iter->coeff_yt[3] * distance;
			m_Point np = *iter;
			np.t = iter->t + distance;
			np.x = x_new;
			np.y = y_new;
			np.curvature = cal_curvature(dx, dx2, dy, dy2);
			qDebug("curvature[%d][%d] = %lf\n", i, j, np.curvature);
			temp.push_back(np);
			
			//newpoint[i*num + j-1] = np;
		}
		
	}
	(c->curve.end() - 1)->curvature = 0;
	temp.push_back(*(c->curve.end() - 1));
	c->curve = temp;

}


GLdouble cal_curvature(GLdouble dx, GLdouble dx2, GLdouble dy, GLdouble dy2 )
{
	return (dx*dy2 - dx2*dy) / sqrt((pow((dx*dx + dy*dy), 3)));	
}


GLdouble euclid_distance(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}



