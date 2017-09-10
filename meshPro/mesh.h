#ifndef MESH_H
#define MESH_H


#include "TriMesh.h"
#include "XForm.h"
#include "GLCamera.h"
#include "ICP.h"
#include "strutil.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <GL/glut.h>

using namespace std;
using namespace trimesh;

// Globals



class Mesh
{
public:
	void draw();
	void draw_mesh(int i);
	void draw_tstrips(const TriMesh *);
	void read_mesh(const char* filename);
	void error(const char*);
	void cls();
	void setup_lighting(int id);
private:
	vector<TriMesh *> meshes;
	vector<xform> xforms;
	vector<bool> visible;
	vector<string> filenames;

	TriMesh::BSphere global_bsph;
	xform global_xf;
	GLCamera camera;

	int current_mesh = -1;

	bool draw_edges = false;
	bool draw_points = false;
	bool draw_2side = false;
	bool draw_shiny = true;
	bool draw_lit = true;
	bool draw_falsecolor = false;
	bool draw_index = false;
	bool white_bg = false;
	bool grab_only = false;
	int point_size = 1, line_width = 1;

};

#endif