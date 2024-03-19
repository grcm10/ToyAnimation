#ifndef BONE_HPP
#define BONE_HPP

#include <vector>
#include "matrix4f.hpp"
#include "Edge.hpp"
#include "Vector3f.hpp"

namespace View{

  //
  // Sample code for physics simulation
  //

  // Implements cloth simulation

  /**
  Bone class:
  Description: Load the bone data ,rotate or translate the bone.
  Function: void BodyMotion(float degree) ---calculate the body movement.
            void loadFile() ----load bone data.
            void SetMatrix() ----set the initial transformation matrix for each bone.
  **/
  class Bone
  {
  public:  
    std::vector<Vector3f> _bone{};//store bone data
    std::vector<int> _boneNum{}; //record the connect bone.
    std::vector<Matrix4f> Matrix{}; // store the transformation matrix.
    
    Bone(){
      loadFile();
      SetMatrix();
    };
    
    void loadFile();
    
    void BodyMotion(const float degree);//v = M*v M is the matrix represented the body movement(rotation,translation).

    void SetMatrix();
  };
}
#endif //BONE_HPP
