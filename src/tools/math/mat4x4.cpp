#include "mat4x4.hpp"

const Mat4x4 Mat4x4::identity = {
    { 1.0, 0.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0, 0.0 },
    { 0.0, 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 0.0, 1.0 },
}; 

Mat4x4 Mat4x4::createFrustrum(float yFov, float aspectRatio, float ncp, float fcp) {
    float tangent = std::tan((yFov * M_PI) / 360.0f);
    float top = ncp * tangent;
    float right = top * aspectRatio;

    Mat4x4 frustrum;
    frustrum[0][0] = ncp / right;
    frustrum[1][1] = ncp / top;
    frustrum[2][2] = -(fcp + ncp) / (fcp - ncp);
    frustrum[2][3] = -(2.0f * fcp * ncp) / (fcp - ncp);
    frustrum[3][2] = -1.0f; 
    frustrum[3][3] = 0.0f;
    return frustrum;
}

