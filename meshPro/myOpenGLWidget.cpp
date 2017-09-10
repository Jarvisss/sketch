#include "myopenglwidget.h"
//#include <triangle.h>
myOpenGLWidget::myOpenGLWidget(QWidget *parent) :
QOpenGLWidget(parent),eye_distance_(5.0)
{
	ptr_arcball_ = new CArcBall(width(), height());
	eye_goal_[0] = eye_goal_[1] = eye_goal_[2] = 0.0;
	eye_direction_[0] = eye_direction_[1] = 0.0;
	eye_direction_[2] = 1.0;
	
}
myOpenGLWidget::~myOpenGLWidget()
{
	delete[] ptr_arcball_;
	/*if (myMesh)
		delete[]myMesh;*/
}

void myOpenGLWidget::resetProjection()
{
	ptr_arcball_->InitBall();
	eye_distance_ = 5.0;
	eye_goal_[0] = eye_goal_[1] = eye_goal_[2] = 0.0;
	eye_direction_[0] = eye_direction_[1] = 0.0;
	eye_direction_[2] = 1.0;
}
void myOpenGLWidget::check_edge_state(int state){
	showWire = state == Qt::Checked;
	update();
}
void myOpenGLWidget::check_face_state(int state){
	showFace = state == Qt::Checked;
	update();
}
void myOpenGLWidget::check_point_state(int state){
	showPoint = state == Qt::Checked;
	update();
}
void myOpenGLWidget::check_texture_state(int state){
	show2DTexture = state == Qt::Checked;
	update();
}
void myOpenGLWidget::check_light_state(int state){
	showLight = state == Qt::Checked;
	update();
}
void myOpenGLWidget::check_axes_state(int state){
	showAxes = state == Qt::Checked;
	update();
}


void myOpenGLWidget::setWheelSpeed(int s){
	qDebug() << "ws:" << s;
	WheelSpeed = s*1.0 / 1000;
}

void myOpenGLWidget::setLightPositionX(int x)
{
	light_position[0] = x;
	update();
}

void myOpenGLWidget::setLightPositionY(int y)
{
	light_position[1] = y;
	update();
}

void myOpenGLWidget::setLightPositionZ(int z)
{
	light_position[2] = z;
	update();
}

void myOpenGLWidget::setLight()
{
	static GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	static GLfloat mat_shininess[] = { 50.0 };
	static GLfloat white_light[] = { 0.8, 0.8, 0.8, 1.0 };
	static GLfloat lmodel_ambient[] = { 0.3, 0.3, 0.3, 1.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void myOpenGLWidget::initMesh(MyMesh* themesh){
	myMesh = themesh;
	totalVertices = myMesh->n_vertices();
	//startTimer(100);
}

void myOpenGLWidget::render(){
	if (myMesh!=NULL){
		if (showFace)
			drawFace();
		if (showWire)
			drawEdge();
		if (showPoint)
			drawPoint();
		if (show2DTexture)
			draw2DTextureLines();
			
	}
	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	drawPath();
	if (is_drawing )
		drawCurrentCurv();
	if (showAxes)
		drawAxes();
	if (is_closed)
		drawBorder();
	
	drawTransparentPlane();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
		
}

//void myOpenGLWidget::writeMesh(){
//	QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ", tr("meshFile(*.obj *.off *.ply *.3ds);;Allfile(*.*)"));
//	QTextCodec *code = QTextCodec::codecForName("gb18030");
//	std::string filename = code->fromUnicode(fileName).data();
//
//	// 请求顶点法线 vertex normals
//	myMesh->request_vertex_normals();
//	//如果不存在顶点法线，则报错 
//	if (!myMesh->has_vertex_normals())
//	{
//		qDebug() << "error: no normal read" << endl;
//		return;
//	}
//	// 如果有顶点发现则读取文件 
//	OpenMesh::IO::Options opt;
//	if (!OpenMesh::IO::write_mesh(myMesh, filename, opt))
//	{
//		//qDebug() << "error: can't read file: " << filename << endl;
//		return;
//	}
//	else
//		qDebug() << "read success: " << endl;
//	std::cout << endl; // 为了ui显示好看一些
//	//如果不存在顶点法线，则计算出
//	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
//	{
//		// 通过面法线计算顶点法线
//		myMesh->request_face_normals();
//		// mesh计算出顶点法线
//		myMesh->update_normals();
//		// 释放面法线
//		myMesh->release_face_normals();
//	}
//}
void myOpenGLWidget::drawPoint(){
	//glGenBuffers(2, uiVBO);
	glBegin(GL_POINTS);
	for (auto it = myMesh->vertices_begin(); it != myMesh->vertices_end(); ++it)
	{
		auto point = myMesh->point(it.handle()).data();
		glVertex3fv(point);
	}
	glEnd();
	glPointSize(1);
}


void myOpenGLWidget::draw2DTextureLines(){
	glBegin(GL_LINES);

	for (auto it = myMesh->halfedges_begin(); it != myMesh->halfedges_end(); ++it){
		auto frompt = myMesh->texcoord2D(myMesh->from_vertex_handle(it.handle())).data();
		auto topt = myMesh->texcoord2D(myMesh->to_vertex_handle(it.handle())).data();

		glVertex2fv(frompt);
		glVertex2fv(topt);
	}
	glEnd();
}
void myOpenGLWidget::drawEdge(){
	glBegin(GL_LINES);
	
	for (auto it = myMesh->halfedges_begin(); it != myMesh->halfedges_end(); ++it){
		auto frompt = myMesh->point(myMesh->from_vertex_handle(it.handle())).data();
		auto topt = myMesh->point(myMesh->to_vertex_handle(it.handle())).data();
		
		glVertex3fv(frompt);
		glVertex3fv(topt);
	}
	glEnd();

	
}
void myOpenGLWidget::drawFace(){
	
	glEnable(GL_TEXTURE_2D);
	//qDebug() << " tex id = " << texture_[0];
	for (auto f_it = myMesh->faces_begin(); f_it != myMesh->faces_end(); ++f_it){
		glBegin(GL_TRIANGLES);
		for (auto fv_it = myMesh->fv_iter(*f_it); fv_it.is_valid(); ++fv_it){
			glTexCoord2fv(myMesh->texcoord2D(*fv_it).data());
			glNormal3fv(myMesh->normal(*fv_it).data());
			glVertex3fv(myMesh->point(*fv_it).data());
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}
void myOpenGLWidget::drawAxes()
{
	//x axis
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.7, 0.0, 0.0);
	glEnd();
	glPushMatrix();
	glTranslatef(0.7, 0, 0);
	glRotatef(90, 0.0, 1.0, 0.0);
	//glutSolidCone(0.02, 0.06, 20, 10);
	glPopMatrix();

	//y axis
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.0, 0.7, 0.0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0, 0.7, 0);
	glRotatef(90, -1.0, 0.0, 0.0);
	//glutSolidCone(0.02, 0.06, 20, 10);
	glPopMatrix();

	//z axis
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.0, 0.0, 0.7);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0, 0, 0.7);
	//glutSolidCone(0.02, 0.06, 20, 10);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
}
void myOpenGLWidget::drawPath(){

	for (auto iter = path.begin(); iter != path.end(); ++iter){
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_STRIP);
		//qDebug() << "line" << i;
		for (auto c_iter = iter->begin(); c_iter != iter->end(); ++c_iter)
		{
			//qDebug() << c_iter->x<<"," << c_iter->y;
			glVertex2d(c_iter->x, c_iter->y);

		}
		glEnd();
	}
}

void myOpenGLWidget::drawCurrentCurv(){
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);

	for (auto c_iter = current_curve.begin(); c_iter != current_curve.end(); ++c_iter)
	{

		//qDebug() << c_iter->x << "," << c_iter->y;
		glVertex2d(c_iter->x, c_iter->y);

	}
	glEnd();
}
void myOpenGLWidget::drawTransparentPlane(){

	float x = 0.8 * 5 * tan(22.5 / 180 * PI)*width() / height();
	float y = 0.9 * 5 * tan(22.5 / 180 * PI);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.7, 0.7, 0.7, 0.3);
	glRectf(-x, -y, x, y);
	/*glColor4f(0.8, 0.8, 0.8, 0.8);
	glRectf(-x, -y, x, y);*/

	glDisable(GL_BLEND);
}

//red border
void myOpenGLWidget::drawBorder()
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for (auto iter = border_curve.begin(); iter != border_curve.end(); ++iter)
	{
		glVertex2d(iter->x, iter->y);
	}
		
	glEnd();
}
void report(
struct triangulateio *io,
int markers,
int reporttriangles,
int reportneighbors,
int reportsegments,
int reportedges,
int reportnorms)
{
	int i, j;

	for (i = 0; i < io->numberofpoints; i++) {
		qDebug() << "Point " << i <<":"<< io->pointlist[i * 2] << "," << io->pointlist[i * 2 + 1];
		//for (j = 0; j < 2; j++) {
			//qDebug() ;
		//}
		if (io->numberofpointattributes > 0) {
			printf("   attributes");
		}
		for (j = 0; j < io->numberofpointattributes; j++) {
			printf("  %.6g",
				io->pointattributelist[i * io->numberofpointattributes + j]);
		}
		if (markers) {
			printf("   marker %d\n", io->pointmarkerlist[i]);
		}
		else {
			printf("\n");
		}
	}
	printf("\n");

	if (reporttriangles || reportneighbors) {
		for (i = 0; i < io->numberoftriangles; i++) {
			if (reporttriangles) {
				printf("Triangle %4d points:", i);
				for (j = 0; j < io->numberofcorners; j++) {
					printf("  %4d", io->trianglelist[i * io->numberofcorners + j]);
				}
				if (io->numberoftriangleattributes > 0) {
					printf("   attributes");
				}
				for (j = 0; j < io->numberoftriangleattributes; j++) {
					printf("  %.6g", io->triangleattributelist[i *
						io->numberoftriangleattributes + j]);
				}
				printf("\n");
			}
			if (reportneighbors) {
				printf("Triangle %4d neighbors:", i);
				for (j = 0; j < 3; j++) {
					printf("  %4d", io->neighborlist[i * 3 + j]);
				}
				printf("\n");
			}
		}
		printf("\n");
	}

	if (reportsegments) {
		for (i = 0; i < io->numberofsegments; i++) {
			printf("Segment %4d points:", i);
			for (j = 0; j < 2; j++) {
				printf("  %4d", io->segmentlist[i * 2 + j]);
			}
			if (markers) {
				printf("   marker %d\n", io->segmentmarkerlist[i]);
			}
			else {
				printf("\n");
			}
		}
		printf("\n");
	}

	if (reportedges) {
		for (i = 0; i < io->numberofedges; i++) {
			printf("Edge %4d points:", i);
			for (j = 0; j < 2; j++) {
				printf("  %4d", io->edgelist[i * 2 + j]);
			}
			if (reportnorms && (io->edgelist[i * 2 + 1] == -1)) {
				for (j = 0; j < 2; j++) {
					printf("  %.6g", io->normlist[i * 2 + j]);
				}
			}
			if (markers) {
				printf("   marker %d\n", io->edgemarkerlist[i]);
			}
			else {
				printf("\n");
			}
		}
		printf("\n");
	}
}

void myOpenGLWidget::myTriangulate()
{
	int n = border_curve.size();
	in.numberofpoints = n;
	in.numberofpointattributes = 0;
	in.pointlist = (REAL* )malloc(in.numberofpoints * 2 * sizeof(REAL));
	int i = 0;
	for (auto iter = border_curve.begin(); iter != border_curve.end(); ++iter,i+=2)
	{
		in.pointlist[i] = iter->x;
		in.pointlist[i + 1] = iter->y;
	}

	report(&in, 0, 0, 0, 0, 0, 0);
}

void myOpenGLWidget::loadTexture(){
	
	QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ", tr("picturefile(*.jpg *.png *.bmp);;Allfile(*.*)"));

	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string name = code->fromUnicode(fileName).data();
	if (name.length()==0){
		return;
	}
	cv::Mat I = cv::imread(name.c_str());
	//imshow("opencv", I);
	p_width = I.cols;
	p_height = I.rows;
	int pixellength = p_width*p_height * 3;
	std::cout << p_width << endl;
	//GLubyte* pixels = (unsigned char*)malloc(sizeof(unsigned char)*I->imageSize);
	pixels = new GLubyte[pixellength];
	
	std::memcpy(pixels, I.data, pixellength*sizeof(GLubyte));
	
	glGenTextures(1, &texture_[0]);
	//std::cout << "222" << endl;
	glBindTexture(GL_TEXTURE_2D, texture_[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//std::cout << "33" << endl;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_width, p_height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	free(pixels);
	is_load_texture = true;
	//setBackGroundTexture();
	//this->hide();
}

void myOpenGLWidget::clearLines()
{
	path.clear();
	current_curve.clear();
	update();
}

void myOpenGLWidget::setBackGroundTexture(){
	glColor3d(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2d(-1.0, -1.0);
	glVertex2d(+1.0, -1.0);
	glVertex2d(+1.0, +1.0);
	glVertex2d(-1.0, +1.0);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(-x_ratio, -y_ratio);
	glTexCoord2d(1.0, 0.0); glVertex2d(+x_ratio, -y_ratio);
	glTexCoord2d(1.0, 1.0); glVertex2d(+x_ratio, +y_ratio);
	glTexCoord2d(0.0, 1.0); glVertex2d(-x_ratio, +y_ratio);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


bool myOpenGLWidget::isBorderClosed(){
	
	if (calcBorderPart(&current_curve))
	{
		myTriangulate();
		return true;
	}
	
	//----- not completed -----//

	return false;
	//std::vector< std::vector<m_Point> > path;
	for (auto iter = path.begin(); iter != path.end(); ++iter)
	{
		//新绘制的曲线和原曲线中的一条有2个以上交点，则有闭合区域
		int N = hasNIntersection(&(*iter), &current_curve);
		if (N >= 2)
		{
			
			int nPosition = std::distance(path.begin(), iter);
			qDebug() << "jiaodian---> "<<nPosition << N;

			return true;
		}

		else if (N == 1)
		{
			int nPosition = std::distance(path.begin(), iter);
			qDebug() << "jiaodian---> " << nPosition << N;
		}

		else if (N==0)
		{
			int nPosition = std::distance(path.begin(), iter);
			qDebug() << "jiaodian---> " << nPosition << N;
		}
		
	}
	return false;
}

bool myOpenGLWidget::calcBorderPart(Curve* c){
	if (c->size() <= 4)
	{
		return false;
	}
	m_Point p1_last = *(c->begin());
	m_Point p1;
	for (auto iter1 = c->begin() + 1; iter1 != c->end() - 2; ++iter1){

		p1 = *iter1;
		border_curve.push_back(p1);
		qDebug() << "p1" << p1.x << "," << p1.y;
		qDebug() << "p1_last" << p1_last.x << "," << p1_last.y;
		m_Point p2_last = *(iter1 + 1);
		border_curve.push_back(p2_last);
		m_Point p2;
		for (auto iter2 = iter1 + 2; iter2 != c->end(); ++iter2){
			p2 = *iter2;
			border_curve.push_back(p2);
			qDebug() << "p2" << p2.x << "," << p2.y;
			qDebug() << "p2_last" << p2_last.x << "," << p2_last.y;
			if (isCross(p1_last, p1, p2_last, p2))
			{
				if (border_curve.size() > 0)
				{
					border_curve.pop_back();
					border_curve.push_back(Cross(p1_last, p1, p2_last, p2));
				}
				
				
				return true;
			}
			p2_last = p2;
		}
		border_curve.clear();
		p1_last = p1;
	}
	return false;
}

float calculateVectorProduct(m_Point P1, m_Point P2, m_Point P3, m_Point P4) {
	return (P2.x - P1.x) * (P4.y - P3.y) - (P2.y - P1.y) * (P4.x - P3.x);
}

m_Point myOpenGLWidget::Cross(m_Point p1, m_Point p2, m_Point q1, m_Point q2)
{
	float t1 = calculateVectorProduct(q1, q2, p1, p2);
	float t2 = calculateVectorProduct(p1, p2, p1, q1);

	float x = q1.x + (q2.x - q1.x) * t2 / t1;
	float y = q1.y + (q2.y - q1.y) * t2 / t1;
	return m_Point{x,y};
}

// judge if p1p2 and q1q2 have an intersection
bool myOpenGLWidget::isCross(m_Point p1, m_Point p2, m_Point q1, m_Point q2)
{
	m_Point q1p1{ p1.x - q1.x, p1.y - q1.y };
	m_Point q1q2{ q2.x - q1.x, q2.y - q1.y };
	m_Point q1p2{ p2.x - q1.x, p2.y - q1.y };

	m_Point p1q1{ q1.x - p1.x, q1.y - p1.y };
	m_Point p1p2{ p2.x - p1.x, p2.y - p1.y };
	m_Point p1q2{ q2.x - p1.x, q2.y - p1.y };
	
	if (p1p2.x == 0 && p1p2.y == 0 && q1q2.x==0 && q1q2.y==0)
	{ 
		return false;
	}

	if ((q1q2.x*p1q2.y - q1q2.y*p1p2.x)==0)
	{
		return false;
	}
		// (q1q2 cha q1p1) * (q1q2 cha q1p2) <=0
	//qDebug() << "cross" << (q1q2.x*q1p1.y - q1q2.y*q1p1.x)*(q1q2.x*q1p2.y - q1q2.y*q1p2.x);
	if ((q1q2.x*q1p1.y - q1q2.y*q1p1.x)*(q1q2.x*q1p2.y - q1q2.y*q1p2.x) > 0)
		return false;
	// (p1p2 cha p1q1) * (p1p2 cha p1q2) <=0
	//qDebug() << "cross2" << (p1p2.x*p1q1.y - p1p2.y*p1q1.x)*(p1p2.x*p1q2.y - p1p2.y*p1q2.x);
	if ((p1p2.x*p1q1.y - p1p2.y*p1q1.x)*(p1p2.x*p1q2.y - p1p2.y*p1q2.x) > 0)
		return false;
	return true;
}
// judge if curve a and b have an intersection
int myOpenGLWidget::hasNIntersection(Curve* a, Curve* b){

	int i = 0;
	m_Point lastA = *(a->begin());
	
	for (auto a_it = a->begin()+1; a_it != a->end(); )
	{
		m_Point lastB = *(b->begin());
		//qDebug() << "b:" << lastB.x << "," << lastB.y;
		for (auto b_it = b->begin()+1; b_it != b->end(); )
		{
			/*qDebug() << "last a:" << lastA.x << "," << lastA.y;
			qDebug() << "a:" << a_it->x << "," << a_it->y;
			qDebug() << "last b:" << lastB.x << "," << lastB.y;
			qDebug() << "b:" << b_it->x << "," << b_it->y;*/

			if (isCross(lastA, *a_it, lastB, *b_it))
				i++;				
			
				
			lastB = *b_it;
			++b_it;
		}
		lastA = *a_it;
		++a_it;
	}

	return i;
}

m_Point myOpenGLWidget::to_perspect(QPoint point)
{
	/*int actualx = point.x();
	int actualy = point.y();*/
	
	/*if (point.x() > width()*x_ratio){
		actualx = width()*x_ratio;
	}
	else if (point.x() < 75){

	}
	else if ()*/

	GLdouble actual_distance_ = 5;
	GLdouble theta = 22.5 / 180 * PI;

	m_Point p;
	p.x = -actual_distance_*tan(theta)*width()/height() + point.x()*actual_distance_ * 2 * tan(theta) / height();
	p.y = actual_distance_*tan(theta) - point.y()*actual_distance_ * 2 * tan(theta) / height();
	return p;
}

void myOpenGLWidget::initializeGL()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_DOUBLEBUFFER);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1);

	light_position[0] = light_position[1] = light_position[2] = 1;
	light_position[3] = 0;
	setLight();
}
void myOpenGLWidget::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);


	if (showLight)
		setLight();
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}

	//设置背景
	glDisable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	setBackGroundTexture();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, GLdouble(width()) / GLdouble(height()), 0.001, 1000);


	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	register GLfloat eyepos[3];
	for (int i = 0; i <= 2; ++i)
		eyepos[i] = eye_distance_ * eye_direction_[i];
	
	gluLookAt(eyepos[0], eyepos[1], eyepos[2],
		eye_goal_[0], eye_goal_[1], eye_goal_[2],
		0.0, 1.0, 0.0);
	
	glPushMatrix();
	
	glMultMatrixf(ptr_arcball_->GetBallMatrix());

	render();


	
	
	glPopMatrix();



}
void myOpenGLWidget::resizeGL(int w, int h)
{
	//qDebug() <<"resize:"<< w << "," << h << endl;
	h = (h == 0) ? 1 : h;

	ptr_arcball_->reSetBound(w, h);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, GLdouble(w) / GLdouble(h), 0.001, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}
void myOpenGLWidget::timerEvent(QTimerEvent * e)
{
	qDebug() << "time";
	update();
}
void myOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
	if (inputMode == 0)
	{
		switch (event->button())
		{

		case Qt::LeftButton:
			ptr_arcball_->MouseDown(event->pos());
			break;
		case Qt::MidButton:
			current_position_ = event->pos();
			break;
		default:
			break;
		}
	}
	else if (inputMode == 1){
		m_Point p{0,0};
		switch (event->button())
		{

		case Qt::LeftButton:
			is_drawing = true;
			current_curve.clear();
			//qDebug() << "press (x,y) = ("<<event->pos().x()<<", "<<event->pos().y()<<")";
			p = to_perspect(event->pos());
			current_curve.push_back(p);
			break;
		default:
			break;
		}
	}

	update();
}
void myOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (inputMode == 0)
	{
		switch (event->buttons())
		{

			setCursor(Qt::ClosedHandCursor);
		case Qt::LeftButton:
			ptr_arcball_->MouseMove(event->pos());
			break;
		case Qt::MidButton:
			eye_goal_[0] -= 4.0*GLfloat(event->x() - current_position_.x()) / GLfloat(width());
			eye_goal_[1] += 4.0*GLfloat(event->y() - current_position_.y()) / GLfloat(height());
			current_position_ = event->pos();
			break;
		default:
			break;

		}
	}
	else if (inputMode == 1){
		m_Point p{ 0, 0 };
		switch (event->buttons())
		{

		case Qt::LeftButton:
			///qDebug() << "screen (x,y) = (" << event->pos().x() << ", " << event->pos().y() << ")";
			p = to_perspect(event->pos());
			//qDebug() << "projection (x,y) = (" << p.x << ", " << p.y << ")";
			current_curve.push_back(p);
			break;
		default:
			break;
		}
	}

	update();
}
void myOpenGLWidget::wheelEvent(QWheelEvent * event)
{
	if (inputMode == 0)
	{
		eye_distance_ += event->delta()*WheelSpeed;
		eye_distance_ = eye_distance_ < 0 ? 0 : eye_distance_;

		
	}

	update();
}
void myOpenGLWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
	switch (e->button())
	{
	case Qt::LeftButton:
		break;
	default:
		break;
	}
	update();
}
void myOpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
	if (inputMode == 0)
	{
		switch (e->button())
		{
		case Qt::LeftButton:
			ptr_arcball_->MouseUp(e->pos());
			setCursor(Qt::ArrowCursor);
			break;

		case Qt::RightButton:
			break;
		default:
			break;
		}
	}
	else if (inputMode = 1)
	{
		m_Point p{ 0, 0 };
		p = to_perspect(e->pos());

		
		current_curve.push_back(p);
		
		//intersection(current_curve, path);
		
		if (isBorderClosed())
		{
			is_closed = true;
			qDebug() << "closed" << endl;
			clearLines();
			update();
		}
		
		path.push_back(current_curve);
		

		current_curve.clear();
		is_drawing = false;
	}
	update();
}
