#ifndef MAT3X3_H
#define MAT3X3_H

#include <iostream>
#include <vector>

class Mat3x3 {
private:
    std::vector<std::vector<double>> matrix = {
        { 1.0, 0.0, 0.0 },
        { 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 1.0 },
    }; 
public:
    Mat3x3() {}
    Mat3x3(std::initializer_list<std::initializer_list<double>> init) {
        if (init.size() != 3) {
            throw std::invalid_argument("Matrix must consist of strictly 4 rows!");
        }

        std::size_t rowIndex = 0;
        for (const auto& row : init) {
            if (row.size() != 3) {
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

    static const Mat3x3 identity;

    /*
        Mathematical operations
    */

    inline std::vector<double>& operator[](size_t index) {
        if (index > 2) {
            throw std::out_of_range("Index out of bounds");
        }
        return matrix[index];
    }

    inline const std::vector<double>& operator[](size_t index) const {
        if (index > 2) {
            throw std::out_of_range("Index out of bounds");
        }
        return matrix[index];
    }

    inline Mat3x3 operator+(const Mat3x3& otherMatrix) const {
        Mat3x3 sum;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                sum[i][j] = matrix[i][j] + otherMatrix[i][j];
            }
        }
        return sum;
    }

    inline Mat3x3 operator-(const Mat3x3& otherMatrix) const {
        Mat3x3 difference;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                difference[i][j] = matrix[i][j] - otherMatrix[i][j];
            }
        }
        return difference;
    }

    inline Mat3x3 operator*(double num) const {
        Mat3x3 product;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                product[i][j] = matrix[i][j] * num;
            }
        }
        return product;
    }

    inline Mat3x3 operator*(const Mat3x3& otherMatrix) const {
        Mat3x3 product;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                double result = 0;
                for (int k = 0; k < 3; k++) {
                    result += matrix[i][k] * otherMatrix[k][j];
                }
                product[i][j] = result;
            }
        }
        return product;
    }
};

#endif //MAT3X3_H