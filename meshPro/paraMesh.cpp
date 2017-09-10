#include "paraMesh.h"
#include <QTextStream>

paraMesh::paraMesh(int t, MyMesh* p){
	type = t;
	mesh = *p;
	mesh.add_property(VH_Bool, "VH_Bool");
	mesh.add_property(VH_Double, "VH_Double");
	totalVertices = mesh.n_vertices();
	qDebug() << "totalVertices" << totalVertices;
	result.resize(totalVertices);
	CoefficientMatrix.resize(totalVertices, totalVertices);
	CoefficientMatrix.setIdentity(totalVertices, totalVertices);// coefficient M
	u.resize(totalVertices, 2);
	u.setZero(totalVertices, 2);// M*u = b
	b.resize(totalVertices, 2);
	b.setZero(totalVertices, 2);
}

paraMesh::~paraMesh(){
}


bool judge(float xx, float yy){
	//cout << xx - yy << endl;   
	if ((xx - yy) > -1 * inf && (xx - yy) < inf)return true;
	return false;
}

void paraMesh::para(){
	findBorderEdges();
	calBorderPoints();
	calInnerPoints();
}

void paraMesh::findBorderEdges(){
	MyMesh::VertexHandle temp_vh_it;
	MyMesh::VertexHandle temp_mark;
	
	// find one border point
	for (auto it = mesh.vertices_begin(); it != mesh.vertices_end(); ++it)
	{
		if (mesh.is_boundary(mesh.halfedge_handle(*it))){
			temp_vh_it = it.handle();
			break;
		}	
	}
	bd_pts.push_back(temp_vh_it.idx());
	int break_ll = 0;
	temp_mark = temp_vh_it;
	// find border edges
	while (true){
		// 深度优先搜索
		for (MyMesh::VertexOHalfedgeCCWIter VOH_it = mesh.voh_ccwbegin(temp_vh_it); VOH_it != mesh.voh_ccwend(temp_vh_it); ++VOH_it){
			// 这条向外的半边是网格边界;逆时针遍历
			if (mesh.is_boundary(*VOH_it)){
				// 半边的目标点
				MyMesh::VertexHandle temp_in_v = mesh.to_vertex_handle(*VOH_it);
				// 如果目标点已经遍历，则退出循环，寻找下一条边界半边
				if (mesh.property(VH_Bool, temp_in_v))
				{ 
					qDebug() << "one step: [" << mesh.point(temp_in_v).data()[0] << "; "
					<< mesh.point(temp_in_v).data()[1] << "; "
					<< mesh.point(temp_in_v).data()[2] << "] "<<endl;
					break;
				}
				// 将半边信息压入堆栈
				h_handle.push_back(*VOH_it);
				// 将边界点的index压入堆栈
				bd_pts.push_back(temp_in_v.idx());
				// 将下一次迭代的出发点改为半边的目标点（深度优先）
				temp_vh_it = temp_in_v;
				// 设置该点已遍历
				mesh.property(VH_Bool, temp_in_v) = true;
				mesh.property(VH_Bool).set_persistent(true);
				//cout << temp_mark.idx() << " " << temp_vh_it.idx() << endl;  
			}
		}
		//回到初始点，则已找到所有边界，停止寻找
		if (temp_mark == temp_vh_it)
		{
			bd_pts.pop_back();
			break;
		}
			
	}
	qDebug() << "totalBorderVertices" << bd_pts.size();
}

void paraMesh::calBorderPoints(){
	float sum = 0.0;
	float temp_sum = 0.0;

	// calculate length
	
	for (auto it = h_handle.begin(); it != h_handle.end(); ++it){
		MyMesh::VertexHandle VH_it_to = mesh.to_vertex_handle(*it);
		MyMesh::VertexHandle VH_it_from = mesh.from_vertex_handle(*it);
		MyMesh::Point P_it_to = mesh.point(VH_it_to);
		MyMesh::Point P_it_from = mesh.point(VH_it_from);
		temp_sum = powf(P_it_from.data()[0] - P_it_to.data()[0], 2.0) + powf(P_it_from.data()[1] - P_it_to.data()[1], 2.0) + powf(P_it_from.data()[2] - P_it_to.data()[2], 2.0);
		temp_sum = sqrt(temp_sum);
		sum += temp_sum;
		mesh.property(VH_Double, VH_it_to) = sum;
	}

	//set planar border
	for (auto it = mesh.vertices_begin(); it != mesh.vertices_end(); it++){
		if (mesh.is_boundary(mesh.halfedge_handle(*it))){
			float arf = (mesh.property(VH_Double, *it) / sum);
			qDebug() << "af" << arf;
			float unitscale = 0.25;
			float bias = 0.625;
			float point_x = 0.0;
			float point_y = 0.0;
			float actual_arf = (arf + bias) > 1 ? arf + bias - 1 : arf + bias;
			if (unitscale > actual_arf)	{ point_y = actual_arf * 4.0;			point_x = 0.0; }
			else if (unitscale*2.0 > actual_arf){ point_y = 1.0;			point_x = (actual_arf - unitscale)*4.0; }
			else if (unitscale*3.0 > actual_arf){ point_y = (unitscale * 3 - actual_arf)*4.0;		point_x = 1.0; }
			else if (unitscale*4.0 > actual_arf){ point_y = 0.0;							point_x = (unitscale*4.0 - actual_arf)*4.0; }

			vector<int>::iterator iter;
			int index;
			iter = find(bd_pts.begin(), bd_pts.end(), it->idx()); // 在边界index中找vertex iter对应的index
			if (iter!=bd_pts.end())
				index = std::distance(bd_pts.begin(), iter);	// index = 该点在bd_pts中的序号
			else
				qDebug() << "参数化失败1";
			result[bd_pts[index]] = OpenMesh::Vec2f(point_x, point_y); // result[id] = (x,y);
			mesh.set_texcoord2D(*it, result[bd_pts[index]]);
			qDebug() << "tex[" << point_x << "; "
				<< point_y <<  "] " << endl;

		}
		else{
			// 将内点index压入堆栈
			in_pts.push_back((*it).idx());
			mesh.set_texcoord2D(*it, OpenMesh::Vec2f(0.0, 0.0));
		}

		//cout << (*it).idx() << endl;  
	}


	qDebug() << "totalInnerVertices" << in_pts.size();
}

void paraMesh::calInnerPoints(){
	// b
	for (int i = in_pts.size(); i < totalVertices; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			b(i, j) = result[bd_pts[i - in_pts.size()]][j];
			
		}
		
	}
	float coefficient;

	for (int i = 0; i < in_pts.size(); i++)
	{
		vector<int> ineighbors;
		auto v_handle = mesh.vertex_handle(in_pts[i]);

		vector<float> NeighborCoefficient;
		
		qDebug() << "1";
		for (auto iter = mesh.vv_begin(v_handle); iter != mesh.vv_end(v_handle); ++iter)
		{
			ineighbors.push_back(iter->idx());// 找第i个内点的邻点
		}
		if (type == 2) NeighborCoefficient = shape_preserve(in_pts[i]);
		qDebug() << i << "th inner point: neighbor" << ineighbors.size();
		for (int j = 0; j < ineighbors.size(); j++)
		{
			if (type == 1)
				coefficient = 1.0 / ineighbors.size();//均匀参数  
			else if (type == 2)//  
			{
				coefficient = NeighborCoefficient[j];
			}//保形
			int index;
			vector<int>::iterator iter;
			iter = std::find(in_pts.begin(), in_pts.end(), ineighbors[j]);
			if (iter != in_pts.end())  index = std::distance(in_pts.begin(), iter);// 在内点中找该邻点
			else{
				iter = std::find(bd_pts.begin(), bd_pts.end(), ineighbors[j]);	// 没找到则在边界点中找
				if (iter != bd_pts.end()) index = in_pts.size() + std::distance(bd_pts.begin(), iter);
				else { qDebug() << "fail 1";/*assert(0)*/;/* return;*/ }
			}
			CoefficientMatrix(i, index) = -coefficient;
		}
	}
	CoefficientMatrix = CoefficientMatrix.inverse();// M=M^-1
	//Eigen::HouseholderQR<MatrixXf> qr(CoefficientMatrix);
	//u = qr.solve(b);
	qDebug() << "2";
	u = CoefficientMatrix*b;// M*u=b  -->  u = M^(-1) *b


	for (int i = 0; i < in_pts.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result[in_pts[i]][j] = u(i, j);

		}
		auto v_handle = mesh.vertex_handle(in_pts[i]);
		mesh.set_texcoord2D(v_handle, result[in_pts[i]]);
		//qDebug() << "[" << result[in_pts[i]][0] << "," << result[in_pts[i]][1] << "]";
	}
	qDebug() << "3.5";
	for (int i = 0; i < bd_pts.size(); i++)
	if ((result[bd_pts[i]][0] != u(i + in_pts.size(), 0))
		|| (result[bd_pts[i]][1] != u(i + in_pts.size(), 1)))
	{
		qDebug() << result[bd_pts[i]][0] << ";" << u(i + in_pts.size(), 0);
		qDebug() << "fail 2";
	}
}

vector<float>  paraMesh::shape_preserve(int idx){
	vector<int> ineighbors;
	int num_Neighbors;
	//需要计算的内点handle
	OpenMesh::VertexHandle vp_handle = mesh.vertex_handle(idx);
	
	for (auto iter = mesh.vv_begin(vp_handle); iter != mesh.vv_end(vp_handle); ++iter)
	{
		ineighbors.push_back(iter->idx());
	}// 得到该点的邻点并按序存入iter容器
	num_Neighbors = ineighbors.size();
	vector<float> Angle2D(num_Neighbors, 0.0);
	Angle2D[0] = 0.0;
	float sum_angle = 0.0;

	for (int i = 1; i<num_Neighbors; i++)
	{
		auto va_handle = mesh.vertex_handle(ineighbors[i-1]);
		auto vb_handle = mesh.vertex_handle(ineighbors[i]);
		OpenMesh::Vec3f pa = mesh.point(va_handle) - mesh.point(vp_handle);
		OpenMesh::Vec3f pb = mesh.point(vb_handle) - mesh.point(vp_handle);
		float angle = (pa | pb) / (pa.norm()*pb.norm());
		sum_angle += acos(angle);
		Angle2D[i] = sum_angle;
	}
	auto va_handle = mesh.vertex_handle(ineighbors[num_Neighbors - 1]);
	auto vb_handle = mesh.vertex_handle(ineighbors[0]);
	OpenMesh::Vec3f pa = mesh.point(va_handle) - mesh.point(vp_handle);
	OpenMesh::Vec3f pb = mesh.point(vb_handle) - mesh.point(vp_handle);
	float angle = (pa | pb) / (pa.norm()*pb.norm());
	sum_angle += acos(angle);

	for (int i = 0; i<num_Neighbors; i++)
	{
		Angle2D[i] = Angle2D[i] * 2.0*PI / sum_angle;
	}

	vector<float> Radius(num_Neighbors, 0.0); // 极坐标r
	for (int i = 0; i < num_Neighbors; i++)
	{
		auto vq_handle = mesh.vertex_handle(ineighbors[i]);
		OpenMesh::Vec3f pq = mesh.point(vq_handle) - mesh.point(vp_handle);
		Radius[i] = pq.norm();
	}

	vector<OpenMesh::Vec3f> P2Dcoordinate(num_Neighbors); // 平面坐标
	
	for (int i = 0; i<num_Neighbors; i++)
	{
		P2Dcoordinate[i][0] = 10 * Radius[i] * cos(Angle2D[i]);
		P2Dcoordinate[i][1] = 10 * Radius[i] * sin(Angle2D[i]);
		P2Dcoordinate[i][2] = 0.0;
	}

	int p1, p2, p3;
	OpenMesh::Vec3f pp1, pp2, pp3;

	vector<vector<float>>Weight;
	Weight.resize(num_Neighbors);

	for (int i = 0; i<num_Neighbors; i++)
	{
		Weight[i].reserve(num_Neighbors + 2);
	}
	OpenMesh::Vec3f pSeed(0, 0, 0);


	for (int i = 0; i<num_Neighbors; i++)
	{
		p3 = i;
		pp3 = P2Dcoordinate[i] - pSeed;
		float Inaccuracy = 10000.0;
		int accuratep1, accuratep2;
		float u = 0.0;
		float v = 0.0;
		float w = 0.0;
		for (int j = 0; j<num_Neighbors; j++)
		{

			if (j<num_Neighbors - 1)
			{
				p1 = j;
				pp1 = P2Dcoordinate[j] - pSeed;
				p2 = j + 1;
				pp2 = P2Dcoordinate[j + 1] - pSeed;
			}
			else
			{
				p1 = j;
				pp1 = P2Dcoordinate[j] - pSeed;
				p2 = 0;
				pp2 = P2Dcoordinate[0] - pSeed;
			}
			if ((p1 != p3) && (p2 != p3))
			{

				//判断P点是否在三角形p1p2p3内部  
				OpenMesh::Vec3f  p1p2 = P2Dcoordinate[p2] - P2Dcoordinate[p1];
				OpenMesh::Vec3f  p1p3 = P2Dcoordinate[p3] - P2Dcoordinate[p1];
				float AreaP1PP2 = 0.5*(pp1 % pp2).norm();
				float AreaP2PP3 = 0.5*(pp2 % pp3).norm();
				float AreaP3PP1 = 0.5*(pp3 % pp1).norm();
				float AreaP1P2P3 = 0.5*(p1p2 % p1p3).norm();
				float AreaSum = AreaP1PP2 + AreaP2PP3 + AreaP3PP1;

				if (Inaccuracy>(AreaSum - AreaP1P2P3))
				{
					Inaccuracy = AreaSum - AreaP1P2P3;
					accuratep1 = p1;
					accuratep2 = p2;
					u = AreaP2PP3 / AreaSum;
					v = AreaP3PP1 / AreaSum;
					w = AreaP1PP2 / AreaSum;
				}
			}//if  
		}//for  
		Weight[accuratep1].push_back(u);
		Weight[accuratep2].push_back(v);
		Weight[p3].push_back(w);
	}
	vector<float> AverageWeight(num_Neighbors, 0.0);
	for (int i = 0; i<num_Neighbors; i++)
	{
		for (int j = 0; j<Weight[i].size(); j++)
		{
			AverageWeight[i] += Weight[i][j];
		}
		AverageWeight[i] = AverageWeight[i] / num_Neighbors;
	}
	return AverageWeight;

}

MyMesh* paraMesh::getMesh(){
	return &mesh;
}

