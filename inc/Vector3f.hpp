#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP
#include <vector>
#include <array>
#include <cmath>

class Vector3f {
std::array<float,3> _item{0.f};

public:
    Vector3f()=default;
    Vector3f(float x, float y, float z):_item({x,y,z}) 
    {

    };

    float& operator[](size_t index) noexcept
    {
        return _item[index];
    }

    float operator[](size_t index) const noexcept{
        return _item.at(index);
    }

    [[nodiscard]]Vector3f& operator= (const Vector3f& obj) noexcept
    {
        _item[0] = obj[0];
        _item[1] = obj[1];
        _item[2] = obj[2];

        return *this;
    };

    [[nodiscard]]Vector3f& operator+= (const Vector3f& obj) noexcept
    {
        _item[0] += obj[0];
        _item[1] += obj[1];
        _item[2] += obj[2];

        return *this;
    };

    [[nodiscard]]Vector3f& operator-= (const Vector3f& obj) noexcept
    {
        _item[0] -= obj[0];
        _item[1] -= obj[1];
        _item[2] -= obj[2];

        return *this;
    };

    
    [[nodiscard]]Vector3f& operator/= (const float& f) noexcept
    {
        _item[0] /= f;
        _item[1] /= f;
        _item[2] /= f;

        return *this;
    };

    [[nodiscard]] friend Vector3f operator %( const Vector3f& ob1, const Vector3f& ob2)
    {
        Vector3f ret{};
            
        for(size_t i = 0; i < 3; i++)
        {
            ret._item[ i ] = ob1[ ( i + 1 ) % 3 ] * ob2[ ( i + 2 ) % 3 ]
                            - ob2[ ( i + 1 ) % 3 ] * ob1[ ( i + 2 ) % 3 ];
        }

        return ret;
    }

    [[nodiscard]]friend Vector3f operator+(const Vector3f& v1, const Vector3f& v2)
    {
        Vector3f v(v1);
        for(size_t i = 0; i < 3; i++)
        {
            v[i] += v2[i];
        }

        return v;
    }

    [[nodiscard]]friend Vector3f operator-(const Vector3f& v1, const Vector3f& v2)
    {

        Vector3f v(v1);
        for(size_t i = 0; i < 3 ; i++)
        {
            v[i] -= v2[i];
        }

        return v;
    }

    [[nodiscard]]float distance(const Vector3f& v)
    {
        auto ret = (v[0]-_item[0])*(v[0]-_item[0]) 
                + (v[1]-_item[1])*(v[1]-_item[1])
                + (v[2]-_item[2])*(v[2]-_item[2]);

        return sqrt(ret);
    }

    [[nodiscard]]float distance(Vector3f & v1, Vector3f & v2) const
    {
        return sqrt((v2[0]-v1[0])*(v2[0]-v1[0]) + (v2[1]-v1[1])*(v2[1]-v1[1]) + (v2[2]-v1[2])*(v2[2]-v1[2]));
    }

    [[nodiscard]]float dot(const Vector3f& input) const
    {
        return input._item[0]*_item[0] + input._item[1]*_item[1] + input._item[2]*_item[2] ; 
    }

    [[nodiscard]]float normalize()
    {
        auto ret = sqrt(_item[0]*_item[0] + _item[1]*_item[1] + _item[2]*_item[2]); 
        for(size_t i = 0; i < 3; i++) _item[i] /= ret;

        return ret;
    }

    [[nodiscard]]float printitem(int i)
    {
        return _item[i];
    }
};
#endif