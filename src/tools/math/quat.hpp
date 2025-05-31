#ifndef QUAT_H
#define QUAT_H

#include "vec3.hpp"
#include "mat3x3.hpp"

class Quat {
public:
    float x, y, z, w;
    Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    /*
        Default quaternion templates
    */

    static const Quat identity;

    /*
        Static functions
    */

    inline static Quat fromForwardUp(const Vec3& forward, const Vec3& up) {
        const Vec3 safeForward = forward.getSafeNormal();
        const Vec3 safeRight = Vec3::cross(safeForward, up.getSafeNormal());
        const Vec3 safeUp = Vec3::cross(safeRight, safeForward);

        const float trace = safeRight.x + safeUp.y + safeForward.z;

        if (trace > 0.0f) {
            const float s = 0.5f / std::sqrt(trace + 1.0f);
            return Quat(
                (safeUp.z - safeForward.y) * s,
                (safeForward.x - safeRight.z) * s,
                (safeRight.y - safeUp.x) * s,
                0.25f / s
            );
        } else if ((safeRight.x > safeUp.y) && (safeRight.x > safeForward.z)) {
            const float s = std::sqrt(safeRight.x - safeUp.y - safeForward.z + 1.0f) * 2.0f;
            return Quat(
                s / 4.0f,
                (safeUp.x + safeRight.y) / s,
                (safeForward.x + safeRight.z) / s,
                (safeUp.z - safeForward.y) / s
            );
        } else if (safeUp.y > safeForward.z) {
            const float s = std::sqrt(safeUp.y - safeRight.x - safeForward.z + 1.0f) * 2.0f;
            return Quat(
                (safeUp.x + safeRight.y) / s,
                s / 4.0f,
                (safeForward.y + safeUp.z) / s,
                (safeForward.x - safeRight.z) / s
            );
        }
        const float s = std::sqrt(safeForward.z - safeRight.x - safeUp.y + 1.0f) * 2.0f;
        return Quat(
            (safeForward.x + safeRight.z) / s,
            (safeRight.y + safeUp.z) / s,
            s / 4.0f,
            (safeRight.y - safeUp.x) / s
        );
    }

    /*
        inline static Quat fromForwardUp(const Vec3& forward, const Vec3& up) {
        const Vec3 safeForward = forward.getSafeNormal();
        const Vec3 safeRight = Vec3::cross(up.getSafeNormal(), safeForward);
        const Vec3 safeUp = Vec3::cross(safeForward, safeRight);

        const double w = std::sqrt(1 + safeRight.x + safeUp.y + safeForward.z) / 2.0;

        return Quat(
            (safeUp.z - safeForward.y) / (4.0f * w), // X
            (safeForward.x - safeRight.z) / (4.0f * w), // Y
            (safeRight.y - safeUp.x) / (4.0f * w), // Z
            w / 4.0f // W
        );
    }
    */

    /*
        Getting vectors
    */

    inline Mat3x3 getRotationMatrix() const {
        return {
            { 1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w) },
            { 2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w) },
            { 2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y) }
        };
    }

    inline Vec3 getForwardVector() {
        return Vec3(0.0f, 0.0f, 1.0f);
    }
};

#endif // QUAT_H
