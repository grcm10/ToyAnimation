#ifndef _matrix_H
#define _matrix_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "Vector3f.hpp"

class Matrix4f {
	float _item[4][4];

	public:
	[[nodiscard]] float& operator() (const int i, const int j) noexcept{
		return _item[i][j];
    }

	[[nodiscard]]float operator() (const int i, const int j) const noexcept{
		return _item[i][j];
    }

	Matrix4f() 
	{ 
		for (int i = 0; i< 4; i++) 
			for (int j = 0; j< 4; j++) _item[i][j] = 0; 
	}


  	Matrix4f(const float & a00, const float & a01, const float & a02, const float & a03, 
		 const float & a10, const float & a11, const float & a12, const float & a13, 
		 const float & a20, const float & a21, const float & a22, const float & a23, 
		 const float & a30, const float & a31, const float & a32, const float & a33)
	{
		_item[0][0]=a00;_item[0][1]=a01;_item[0][2]=a02;_item[0][3]=a03;
		_item[1][0]=a10;_item[1][1]=a11;_item[1][2]=a12;_item[1][3]=a13;
		_item[2][0]=a20;_item[2][1]=a21;_item[2][2]=a22;_item[2][3]=a23;
		_item[3][0]=a30;_item[3][1]=a31;_item[3][2]=a32;_item[3][3]=a33;
	}

	void setIdentity() 
	{
		for (int i = 0; i < 4; i++) 
			for (int j = 0; j < 4; j++) 
				_item[i][j] = 0;
		_item[0][0] = _item[1][1] = _item[2][2] = _item[3][3] = 1.;
	}

	[[nodiscard]] float lu(Matrix4f & a, int ip[]);

	[[nodiscard]] float inv(Matrix4f & a, Matrix4f & a_inv);

	[[nodiscard]] Matrix4f operator !() noexcept;

	void setTranslation(const Vector3f& vec) ;

	[[nodiscard]] Matrix4f& operator*= (const Matrix4f& m2) noexcept;

	[[nodiscard]] Matrix4f trans();

	[[nodiscard]] Matrix4f& operator= ( const Matrix4f & obj )noexcept;

	[[nodiscard]]Vector3f getMulti(const Matrix4f& mat,const Vector3f& vec) 
	{
		Vector3f ret{};

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
			{
				ret[i] += mat(i,j)* vec[j];
			}
			ret[i] += mat(i,3);
		}
		
		return ret;
	}

	friend Matrix4f operator*(const Matrix4f & obj1, const Matrix4f & obj2) noexcept;
};



Matrix4f rotX(const float & rad );
Matrix4f rotY(const float & rad);
Matrix4f rotZ(const float & rad);
Matrix4f translation(const Vector3f& vec);

#endif // _matrix_H
