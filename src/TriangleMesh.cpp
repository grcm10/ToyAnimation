#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "../inc/TriangleMesh.hpp"

void View::TriangleMesh::loadFile(const std::string& filename)
{

	std::ifstream f(filename);
	if (!f) {
		std::cerr << "failed reading polygon data file " << filename << std::endl;
		exit(1);
	}

	char buf[1024];
	char header[100];
	float x,y,z;
	float xmax,ymax,zmax,xmin,ymin,zmin;
	int v1, v2, v3, n1, n2, n3;

	xmax =-10000; ymax =-10000; zmax =-10000;
	xmin =10000; ymin =10000; zmin =10000;

	while (!f.eof()) {
        f.getline(buf, sizeof(buf));
        sscanf(buf, "%s", header);  

        if(std::strcmp(header, "v") == 0) {
        sscanf(buf, "%s %f %f %f", header, &x, &y, &z);  
        _v.push_back(Vector3f(x,y,z));

        _vn.push_back(Vector3f(0.f,0.f,1.f));

        Node node;

        node._id = _v.size()-1; 

        _node.push_back(node);
        

        if (x > xmax) xmax = x;
        if (y > ymax) ymax = y;
        if (z > zmax) zmax = z;

        if (x < xmin) xmin = x;
        if (y < ymin) ymin = y;
        if (z < zmin) zmin = z;
        }
        else if(std::strcmp(header, "vn") == 0) {
    //	sscanf(buf, "%s %f %f %f", header, &x, &y, &z);  
    //	_vn.push_back(Vector3f(x,y,z));
        }
        else if(std::strcmp(header, "f") == 0) 
        {
    //	sscanf(buf, "%s %d//%d %d//%d %d//%d", header, &v1, &n1,
    //		&v2, &n2, &v3, &n3);
        

        sscanf(buf, "%s %d %d %d", header, &v1, &v2, &v3);


        Triangle trig(v1-1, v2-1, v3-1, v1-1, v2-1, v3-1);
        trig._id = _trig.size(); 
        _trig.push_back(trig);

        Edge e1(v1-1, v2-1);
        Edge e2(v2-1, v3-1);
        Edge e3(v3-1, v1-1);

        /*
        pair <int, int> id10(v1-1,v2-1),id11(v2-1,v1-1),
                    id20(v2-1,v3-1),id21(v3-1,v2-1),
                id30(v3-1,v1-1),id31(v1-1,v3-1); 
        */

        int id1,id2,id3;

        if ((id1 = findEdgeID(e1, _edge)) < 0) 
        {
    //				_edge[id10] = e1; _edge[id11] = e1;

    //				_edge[id10].setId(_edge.size()/2);
    //				_edge[id11].setId(_edge.size()/2);

    //				_edge[id10].add_triangle(&trig);
    //				_edge[id11].add_triangle(&trig);

            id1 = _edge.size();
            _edge.push_back(e1);
            _edge[_edge.size()-1] = e1;

            _node[v1-1].edges_to.push_back(v2-1);
            _node[v2-1].edges_to.push_back(v1-1);


            _node[v1-1].edges_cost.push_back(_v[v1-1].distance(_v[v2-1]));
            _node[v2-1].edges_cost.push_back(_v[v1-1].distance(_v[v2-1]));
        }

        if ((id2 = findEdgeID(e2, _edge)) < 0) 
        {
            /*
            _edge[id20] = e2; _edge[id21] = e2;
            
            _edge[id20].setId(_edge.size()/2);
            _edge[id21].setId(_edge.size()/2);

            _edge[id20].add_triangle(&trig);
            _edge[id21].add_triangle(&trig);
            */

            id2 = _edge.size();
            e2.setId(id2);
            e2.add_triangle(trig._id);
            _edge.push_back(e2);
            _edge[_edge.size()-1] = e2;

            _node[v2-1].edges_to.push_back(v3-1);
            _node[v3-1].edges_to.push_back(v2-1);


            _node[v2-1].edges_cost.push_back(_v[v2-1].distance(_v[v3-1]));
            _node[v3-1].edges_cost.push_back(_v[v3-1].distance(_v[v2-1]));
        }

        if ((id3 = findEdgeID(e3, _edge)) < 0) 
        {
            /*
            _edge[id30] = e3; _edge[id31] = e3;

            _edge[id30].setId(_edge.size()/2);
            _edge[id31].setId(_edge.size()/2);

            _edge[id30].add_triangle(&trig);
            _edge[id31].add_triangle(&trig);
            */

            id3 = _edge.size();
            e3.setId(id3);
            e3.add_triangle(trig._id);
            _edge.push_back(e3);

            _node[v3-1].edges_to.push_back(v1-1);
            _node[v1-1].edges_to.push_back(v3-1);


            _node[v3-1].edges_cost.push_back(_v[v3-1].distance(_v[v1-1]));
            _node[v1-1].edges_cost.push_back(_v[v1-1].distance(_v[v3-1]));
        }

        _edge[id1].add_triangle(trig._id);
        _edge[id2].add_triangle(trig._id);
        _edge[id3].add_triangle(trig._id);


    //			_trig[_trig.size()-1].setEdge(_edge[id10].id(), _edge[id20].id(), _edge[id30].id());
        _trig[_trig.size()-1].setEdge(id1,id2,id3); 
    //			_trig[_trig.size()-1].setEdge(&_edge[id1], &_edge[id2], &_edge[id3]);

        //cout << " set Edge "<< "ids " << id1 << ' '<< id2 << ' '<<id3<<'-' << _edge[id1].id() << ' ' <<  _edge[id2].id() << ' ' <<  _edge[id3].id() << endl;
        /*
        int tmpid = _trig.size()-1 ;
        cout << " trig " << _trig.size()-1 << ' '; 
        cout << _trig[tmpid].edge(0) << ' ' << _trig[tmpid].edge(1) << ' ' 
                << _trig[tmpid].edge(2) << endl; 
        */

        }
 	}

	std::vector<std::vector<int>> facelist (_v.size());
	std::vector<Vector3f> facenorm (_trig.size());

	/*for (int i = 0; i < _edge.size(); i++) {
		cout << " edge " << i << " trig list " << _edge[i].getTrigList().size()<< endl;
	}*/

	for (int i = 0; i < _trig.size(); i++) 
	{
		/*
		cout << " trig " << i << ' '; 
			cout << _trig[i].edge(0) << ' ' << _trig[i].edge(1) << ' ' 
			     << _trig[i].edge(2) << endl; 
		*/

        //Vector3f tmpv{};
        //tmpv = tmpv.getRemainder(tmpv.getMinus(_v[_trig[i]._vertex[2]],_v[_trig[i]._vertex[0]]),tmpv.getMinus(_v[_trig[i]._vertex[1]],_v[_trig[i]._vertex[0]]));
		Vector3f tmpv = (_v[_trig[i]._vertex[2]] - _v[_trig[i]._vertex[0]]) % (_v[_trig[i]._vertex[1]] - _v[_trig[i]._vertex[0]]) ;

		tmpv.normalize();
		facenorm[i] = tmpv;

		facelist[_trig[i]._vertex[0]].push_back(i);
		facelist[_trig[i]._vertex[1]].push_back(i);
		facelist[_trig[i]._vertex[2]].push_back(i);
	}


	for (int i = 0; i < _v.size(); i++)  
	{
		Vector3f N(0.f,0.f,0.f); 

		float rate1, rate2;

		if (_v[i][1] > 0.5) 
		{
		       rate1 = 1.f ; rate2 = 0.f;	
		}
		else if (_v[i][1] < -0.5) 
		{
		       rate1 = 0.f ; rate2 = 1.f;	
		}
		else 
		{
			rate1 = _v[i][1] + 0.5f; rate2 = 1.f - rate1; 
		}

	//	cout << " v " << i << " 1:" << rate1 << " 2:" << rate2 << endl ;

		for (int j = 0; j < facelist[i].size(); j++) 
		{
			N += facenorm[facelist[i][j]]; 
	//		cout << " f " << facelist[i][j] << ' ' ;
		}
	//	cout << endl;

		N /= (float)facelist[i].size();

		_vn[i] = N;
	}


	_xmin = xmin; _ymin = ymin; _zmin = zmin;
	_xmax = xmax; _ymax = ymax; _zmax = zmax;

	f.close();

}

void View::TriangleMesh::loadweight()
{
    
     char buf[1024];
    
     float weight[21];
     int count =0;
     std::ifstream f("attachment2.out");
    
     if (!f) {
		std::cerr << "failed reading skeleton data file " << std::endl;
		exit(1);
	}

     while (!f.eof()) {
		    f.getline(buf, sizeof(buf));   
            sscanf(buf,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",&weight[0],&weight[1],&weight[2],&weight[3],&weight[4],&weight[5],&weight[6],&weight[7],&weight[8],&weight[9],&weight[10],&weight[11],&weight[12],&weight[13],&weight[14],&weight[15],&weight[16],&weight[17],&weight[18],&weight[19],&weight[20]);
            _weight.push_back(Vertex_Weight(weight));           
     }

     f.close();
}