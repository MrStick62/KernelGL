#ifndef CAMERA_H
#define CAMERA_H

#include "../../tools/math/vec3.hpp"
#include "../../tools/math/quat.hpp"
#include "../../tools/math/mat4x4.hpp"

class Camera {
public:
    Camera(const float aspectRatio = 1.0f, const Vec3& position = Vec3::zeroVector, const Quat& rotation = Quat::identity, const float yFov = 45.0f, const float ncp = 0.1f, const float fcp = 100.0f);

    Mat4x4 projection;
    Mat4x4 view;

    Vec3 position;
    Quat rotation;

    inline void updateTransform(const Vec3& position, const Quat& rotation) {
        this->position = position;
        this->rotation = rotation;

        view = Mat4x4::identity;
        view.translate(position);
        view.rotate(rotation);
    }
};

#endif //CAMERA_H
