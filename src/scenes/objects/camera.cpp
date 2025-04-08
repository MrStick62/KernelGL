#include "camera.hpp"

Camera::Camera(const float aspectRatio, const Vec3& position, const Quat& rotation, const float yFov, const float ncp, const float fcp) : position(position), rotation(rotation) {
    projection = Mat4x4::createFrustrum(yFov, aspectRatio, ncp, fcp);
    view.translate(position);
    view.rotate(rotation);
}
