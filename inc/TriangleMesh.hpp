#ifndef TRIANGLE_MESH_HPP
#define TRIANGLE_MESH_HPP

#include <vector>
#include <string>
#include <cmath>
#include "Edge.hpp"
#include "Bone.hpp"
#include "matrix4f.hpp"


namespace View{

    struct Node {
        int _id;
        std::vector<int> edges_to{};     
        std::vector<float> edges_cost{};   
        bool done;   
        float cost;    
    };

    /**
    Vertex_Weight class:
    Description: Load the weight data.
    Function: void as_weight_value(float w[]) ---assign the weight value to the vector.
            float weight_value(int i) ----return weight value.
            int v_size() ----return weight size.
    **/
    class Vertex_Weight{

    std::vector<float> v_weight{};
    
    public:
        Vertex_Weight(float w[]){as_weight_value(w);};
        constexpr void as_weight_value(float w[])
        {
            for(int i =0;i<21;i++)
            {
                v_weight.emplace_back(w[i]);
            }
        }
        [[nodiscard]] float weight_value(int i) const
        {
            return v_weight[i];
        }
        [[nodiscard]] int v_size() const
        {
            return v_weight.size();
        }

    };

    class Triangle {
        friend class TriangleMesh;

        int _id;
        std::array<int,3>_vertex{};
        std::array<int,3> _normal{};
        std::array<int,3> _edge{};
        float _min, _max;
        float _color; 
        float _area;
        float _ratio;

    public:

        Triangle(int v1, int v2, int v3, int n1, int n2, int n3):
        _vertex({v1,v2,v3}), _normal({n1,n2,n3})
        {
            //_vertex[0] = v1;  _vertex[1] = v2;  _vertex[2] = v3;  
            //_normal[0] = n1;  _normal[1] = n2;  _normal[2] = n3;  
        };

        constexpr void setMorseMinMax(const float min, const float max)
        {
            _min = min; _max = max;
        }

        constexpr void getMorseMinMax(float& min, float& max)
        {
            min = _min; max = _max;
        }

        constexpr void setEdge(const int e1, const int e2, const int e3)
        {
            _edge = {e1,e2,e3};
        };

        [[nodiscard]] constexpr int edge(int i) const { return _edge[i];};
        [[nodiscard]] constexpr int id() const { return _id;};
        constexpr void setColor(float f) { _color = f ;};
        [[nodiscard]] constexpr float color() const { return _color;};
    };


    class TriangleMesh 
    {
        std::vector<Vector3f> _v;
        std::vector<Vector3f> _vn;
        std::vector<Triangle> _trig;
        std::vector<Node> _node;
        std::vector<Edge> _edge;
        std::vector<Vertex_Weight> _weight; //record attachment.out

    //	map <pair < int, int > , Edge > _edge;
        float _xmax, _xmin, _ymax, _ymin, _zmin, _zmax;
    public:
        TriangleMesh() = default;
        TriangleMesh(const std::string& filename) { loadFile(filename);};
        void loadFile(const std::string&);
        void loadweight();

        [[nodiscard]] int trigNum() const { return _trig.size() ;};
            
            
        void getTriangleVertices( const int i, Vector3f& v1, Vector3f& v2, Vector3f& v3)
        { 
            v1 = _v[_trig[i]._vertex[0]]; 
            v2 = _v[_trig[i]._vertex[1]]; 
            v3 = _v[_trig[i]._vertex[2]]; 
        }
        
        void getTriangleNormals(const int i, Vector3f& v1, Vector3f& v2, Vector3f& v3)
        {
            v1 = _vn[_trig[i]._normal[0]]; 
            v2 = _vn[_trig[i]._normal[1]]; 
            v3 = _vn[_trig[i]._normal[2]]; 
        }
            

        void getMorseValue(const int i, float& v1, float& v2, float& v3)
        {
            v1 = _node[_trig[i]._vertex[0]].cost; 
            v2 = _node[_trig[i]._vertex[1]].cost; 
            v3 = _node[_trig[i]._vertex[2]].cost; 
        }

        [[nodiscard]] float color(const int i) const { return _trig[i].color();};


        void setMorseMinMax(const int i, const float min, const float max)
        {
            _trig[i].setMorseMinMax(min,max);
        }

        void getMorseMinMax(const int i, float& min, float& max)
        {
            _trig[i].getMorseMinMax(min,max);
        }


        void calcTriangleArea() 
        {
            Vector3f v1,v2,v3;

            for (int i = 0 ;i < _trig.size(); i++){
                getTriangleVertices(i, v1,v2,v3);
                v3 -= v1;
                v2 -= v1;
                _trig[i]._area = 0.5f*sqrt(v3.dot(v3)*v2.dot(v2) - (v3.dot(v2)*(v3.dot(v2))));  
    //			cout << "trig " << i << " v2 " << v2 << " v3 " << v3 << " area = " << _trig[i]._area << endl;
            }
        }

        [[nodiscard]] int findEdgeID(const Edge& e, const std::vector<Edge>& list) const
        {
            for (int i = 0; i < list.size(); i++) 
            {
                if ((list[i].v1() == e.v1() && list[i].v2() == e.v2()) ||
                    (list[i].v2() == e.v1() && list[i].v1() == e.v2())) 
                {
                    return i;
                }	
            }

            return -1;
        }

        void Weight_Calculation(const int i,Bone B,Vector3f &v1, Vector3f &v2, Vector3f &v3)
        {
            
            int number1 = _trig[i]._vertex[0];
            int number2 = _trig[i]._vertex[1];
            int number3 = _trig[i]._vertex[2];
            Vector3f ver1,ver2,ver3,vertex1,vertex2,vertex3;
            Matrix4f m{};

            for(int j =0;j<21;j++){
                ver1 = m.getMulti(B.Matrix[j+1],v1);
                
                vertex1[0] += _weight[number1].weight_value(j)*ver1[0];
                vertex1[1] += _weight[number1].weight_value(j)*ver1[1];
                vertex1[2] += _weight[number1].weight_value(j)*ver1[2]; 
                
            } 

            v1 = vertex1;

            for(int j =0;j<21;j++){
                ver2 = m.getMulti(B.Matrix[j+1],v2);

                vertex2[0] += _weight[number2].weight_value(j)*ver2[0];
                vertex2[1] += _weight[number2].weight_value(j)*ver2[1];
                vertex2[2] += _weight[number2].weight_value(j)*ver2[2];
            } 

            v2 = vertex2;
        
            for(int j =0;j<21;j++){
                ver3 = m.getMulti(B.Matrix[j+1],v3);

                vertex3[0] += _weight[number3].weight_value(j)*ver3[0]; 
                vertex3[1] += _weight[number3].weight_value(j)*ver3[1];
                vertex3[2] += _weight[number3].weight_value(j)*ver3[2];           
            }

            v3 = vertex3;
        }
    };
}
#endif