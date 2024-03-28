#include <iostream>
#include <fstream>
#include "../inc/Bone.hpp"

void View::Bone::loadFile()
{
     char buf[1024];
     float x,y,z,bone_num,next_bone_num;
     std::ifstream f("skeleton2.out");

     if (!f) {
		std::cerr << "failed reading skeleton data file " << std::endl;
		exit(1);
	}

     while (!f.eof()) {
		    f.getline(buf, sizeof(buf));
		    sscanf(buf, "%f %f %f %f %f",&bone_num,&x,&y,&z,&next_bone_num);
                    _bone.push_back(Vector3f(x,y,z));
                    _boneNum.push_back(static_cast<int>(next_bone_num));
                    
     }
     f.close();

}


void View::Bone::BodyMotion(float degree)
{
    // Vector3f v_point = new Vector3f(1.0,2.0,3.0); 
     Matrix4f t1,r1,t2,r2,t3,r3,t4;
     Vector3f v_point;
   
//bone16
    // v_point = v_point.neg(_bone[15]);//local
     
     t1 = !translation(_bone[15]);
       
     r1 = rotZ(degree);

     t2 = translation(_bone[15]);

     Matrix[16] = t2*r1*t1;

     v_point = _bone[16];

     _bone[16] = t2*r1*t1*_bone[16]; // vertex after rotation

//bone17
     //v_point = v_point.neg(old_bone[16]);//local


     t3 = !translation(v_point);//translate to local

     r2 = rotZ(degree);

     t4 = translation(_bone[16]);// translate the point
     
     Matrix[17] = t4*r2*t3;

     _bone[17] = t4*r2*t3*_bone[17];// vertex after rotation
        
}

void View::Bone::SetMatrix()
{
    Matrix4f t1,t2,m,w;
    w.setIdentity();
    Matrix.push_back(w);
    for(size_t i =1;i<_bone.size();i++)
    {
       t1 = !translation(_bone[_boneNum[i]]);
       t2 =  translation(_bone[_boneNum[i]]);       
       
       m = t2*t1; 
       Matrix.push_back(m);
    }     
   
}