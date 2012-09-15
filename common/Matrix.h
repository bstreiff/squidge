#pragma once

#include <boost/array.hpp>

namespace squidge {

class Vector3;

class Matrix
{
public:
   Matrix();
   Matrix(
      float m00, float m01, float m02, float m03,
      float m10, float m11, float m12, float m13,
      float m20, float m21, float m22, float m23,
      float m30, float m31, float m32, float m33);
   Matrix(const float data[4*4]);
   Matrix(const boost::array<float, 16>& data);

   const float& operator()(size_t row, size_t col) const;
   float& operator()(size_t row, size_t col);
   const float& operator[](size_t index) const;
   float& operator[](size_t index);

   static const Matrix& identity();

   static void createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Matrix& result);

   static void createRotationX(float radians, Matrix& result);
   static void createRotationY(float radians, Matrix& result);
   static void createRotationZ(float radians, Matrix& result);

   static void createScale(float scale, Matrix& result);
   static void createScale(const Vector3& scales, Matrix& result);
   static void createScale(float xScale, float yScale, float zScale, Matrix& result);

   static void createTranslation(const Vector3& positions, Matrix& result);
   static void createTranslation(float xPosition, float yPosition, float zPosition, Matrix& result);

   static void add(const Matrix& a, const Matrix& b, Matrix& result);
   static void divide(const Matrix& a, float b, Matrix& result);
   static void divide(const Matrix& a, const Matrix& b, Matrix& result);
   static void multiply(const Matrix& a, float b, Matrix& result);
   static void multiply(const Matrix& a, const Matrix& b, Matrix& result);
   static void negate(Matrix& a);
   static void subtract(const Matrix& a, const Matrix& b, Matrix& result);

private:
   boost::array<float, 16> _data;
};

bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);
Matrix operator+(const Matrix& a, const Matrix& b);
Matrix operator-(const Matrix& a, const Matrix& b);
Matrix operator*(const Matrix& a, const Matrix& b);


} // namespace squidge
