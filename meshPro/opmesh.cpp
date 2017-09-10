#include "opmesh.h"
#include "QDebug"

void opMesh::readfile(string file) {
	QString str = QString::fromStdString(file);
	qDebug() << "here" <<str << endl;
	// ���󶥵㷨�� vertex normals
	mymesh.request_vertex_normals();
	//��������ڶ��㷨�ߣ��򱨴� 
	if (!mymesh.has_vertex_normals())
	{
		qDebug() << "error: no normal read" << endl;
		return;
	}
	// ����ж��㷢�����ȡ�ļ� 
	OpenMesh::IO::Options opt;
	if (!OpenMesh::IO::read_mesh(mymesh, file, opt))
	{
		qDebug() << "error: can't read file: " << str << endl;
		return;
	}
	else qDebug() << "read success: " << str << endl;
	cout << endl; // Ϊ��ui��ʾ�ÿ�һЩ
	//��������ڶ��㷨�ߣ�������
	if (!opt.check(OpenMesh::IO::Options::VertexNormal))
	{
		// ͨ���淨�߼��㶥�㷨��
		mymesh.request_face_normals();
		// mesh��������㷨��
		mymesh.update_normals();
		// �ͷ��淨��
		mymesh.release_face_normals();
	}
}

void opMesh::loadTexture(string filename){
	QString str = QString::fromStdString(filename);
	qDebug() << str;
	//glGenTextures(1, &texture_[0]);
	QImage tex1, buf;
	if (!buf.load(str))
	{
		qDebug() << "Cancel";
	}

	tex1 = QGLWidget::convertToGLFormat(buf);
	qDebug() << tex1.width();
	qDebug() << tex1.height();
	qDebug() << tex1.depth();
	qDebug()<<tex1.byteCount();
	//glBindTexture(GL_TEXTURE_2D, texture_[0]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	//glTexImage2D(GL_TEXTURE_2D, GL_RGBA, 0, tex1.width(), tex1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex1.bits());
	/*gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB, tex1.width(), tex1.height(),
		GL_RGBA, GL_UNSIGNED_BYTE, tex1.bits());*/

	qDebug() << "load success";

	//is_load_texture_ = true;
}

MyMesh* opMesh::getMymesh(){
	return &mymesh;
}
