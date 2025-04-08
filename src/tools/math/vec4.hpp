#ifndef VEC4_H
#define VEC4_H

class Vec4 {
public:
    float x, y, z, w = 0.0;

    Vec4() {};
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    static const Vec4 zeroVector;
};

#endif //VEC4_H