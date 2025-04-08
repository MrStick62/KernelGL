#ifndef VEC3_H
#define VEC3_H

#include <math.h>

class Vec3 {
public:
    float x, y, z = 0;

    Vec3() {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    /*
        Default vector templates
    */

    static const Vec3 zeroVector;
    static const Vec3 upVector;
    static const Vec3 forwardVector;

    /*
        Static functions
    */

    inline static float dot(const Vec3& v1, const Vec3& v2) { 
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
    }

    inline static Vec3 cross(const Vec3& v1, const Vec3& v2) {
        const float x = v1.y * v2.z - v1.z * v2.y;
        const float y = v1.x * v2.z - v1.z * v2.x;
        const float z = v1.x * v2.y - v1.y * v2.z;
        return Vec3(x, y, z);
    }
    
    /*
        Other functions
    */

    inline float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    inline Vec3 getSafeNormal() const {
        float length = this->length();
        return (length) ? Vec3(x / length, y / length, z / length) : Vec3(0.0f, 0.0f, 1.0f);
    }   

    inline void normalize() {
        float length = this->length();
        if (length) {
            x /= length;
            y /= length;
            z /= length;
        }
    }

    /*
        Vector math
    */

    inline Vec3 operator*(const int num) const {
        return Vec3(x * num, y * num, z * num);
    }

    inline Vec3 operator+(const Vec3& otherVec) const {
        return Vec3(x + otherVec.x, y + otherVec.y, z + otherVec.z);
    }

    inline Vec3 operator-(const Vec3& otherVec) const {
        return Vec3(x - otherVec.x, y - otherVec.y, z - otherVec.z);
    }
};

#endif //VEC3_H