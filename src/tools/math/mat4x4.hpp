#ifndef MAT4X4_H
#define MAT4X4_H

#include <iostream>
#include <vector>

#include "vec3.hpp"
#include "vec4.hpp"
#include "quat.hpp"
#include "mat3x3.hpp"

class Mat4x4 {
private:
    std::vector<std::vector<float>> matrix = {
        { 1.0, 0.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 },
    }; 
public:
    Mat4x4() {}
    Mat4x4(std::initializer_list<std::initializer_list<float>> init) {
        if (init.size() != 4) {
            throw std::invalid_argument("Matrix must consist of strictly 4 rows!");
        }

        std::size_t rowIndex = 0;
        for (const auto& row : init) {
            if (row.size() != 4) {
                throw std::invalid_argument("Matrix must consist of strictly 5 columns!");
            }

            std::size_t colIndex = 0;
            for (const auto& num : row) {
                matrix[rowIndex][colIndex] = num;
                colIndex++;
            }
            rowIndex++;
        }
    }

    /*
        Matrix templates
    */

    static const Mat4x4 identity;

    static Mat4x4 createFrustrum(float yFov, float aspectRatio, float ncp, float fcp);

    /*
        Mathematical operations
    */

    inline std::vector<float>& operator[](size_t index) {
        if (index > 3) {
            throw std::out_of_range("Index out of bounds");
        }
        return matrix[index];
    }

    inline const std::vector<float>& operator[](size_t index) const {
        if (index > 3) {
            throw std::out_of_range("Index out of bounds");
        }
        return matrix[index];
    }

    inline Mat4x4 operator+(const Mat4x4& otherMatrix) const {
        Mat4x4 sum;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                sum[i][j] = matrix[i][j] + otherMatrix[i][j];
            }
        }
        return sum;
    }

    inline Mat4x4 operator-(const Mat4x4& otherMatrix) const {
        Mat4x4 difference;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                difference[i][j] = matrix[i][j] - otherMatrix[i][j];
            }
        }
        return difference;
    }

    inline Mat4x4 operator*(float num) const {
        Mat4x4 product;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                product[i][j] = matrix[i][j] * num;
            }
        }
        return product;
    }

    inline Mat4x4 operator*(const Mat4x4& otherMatrix) const {
        Mat4x4 product;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float result = 0;
                for (int k = 0; k < 4; k++) {
                    result += matrix[i][k] * otherMatrix[k][j];
                }
                product[i][j] = result;
            }
        }
        return product;
    }

    inline Vec4 operator*(const Vec4& vec) const {
        const std::vector<float> vector = { vec.x, vec.y, vec.z, vec.w };
        std::vector<float> product = { 0.0, 0.0, 0.0, 0.0 };
        for (int i = 0; i < 4; i++) {
            float result = 0;
            for (int j = 0; j < 4; j++) {
                result += vector[j] * matrix[i][j];
            }
            product[i] = result;
        }
        return Vec4(product[0], product[1], product[2], product[3]);
    }

    /*
        Transformations
    */

    inline void translate(const Vec3& translation) {
        matrix[0][3] += translation.x;
        matrix[1][3] += translation.y;
        matrix[2][3] += translation.z;
    }

    inline void scale(const Vec3& scalar) {
        matrix[0][0] *= scalar.x;
        matrix[1][1] *= scalar.y;
        matrix[2][2] *= scalar.z;
    }

    inline void rotate(const Quat& rot) {
        Mat3x3 rotMatrix = rot.getRotationMatrix();

        const Mat3x3 currentRot = {
            { matrix[0][0], matrix[0][1], matrix[0][2] },
            { matrix[1][0], matrix[1][1], matrix[1][2] },
            { matrix[2][0], matrix[2][1], matrix[2][2] }
        };

        rotMatrix = rotMatrix * currentRot;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrix[i][j] = rotMatrix[i][j];
            }
        }
    }

    /*
        Convert matrix into format interpretable by opengl
    */

    inline float* glFormat() const {
        float* result = new float[16];
        for (int i = 0; i < 16; i++) {
            result[i] = matrix[(int)(i / 4)][i % 4];
        }
        return result;
    }
};

#endif //MAT4X4_H