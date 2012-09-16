#include "common/Matrix.h"
#include "common/Vector3.h"
#include <math.h>
#include <algorithm>

namespace squidge {

namespace {

Matrix identityMatrix(
   1, 0, 0, 0,
   0, 1, 0, 0,
   0, 0, 1, 0,
   0, 0, 0, 1);

}

Matrix::Matrix()
{
   for (size_t i; i < 4*4; ++i)
   {
      _data[i] = 0;
   }
}

Matrix::Matrix(
   float m00, float m01, float m02, float m03,
   float m10, float m11, float m12, float m13,
   float m20, float m21, float m22, float m23,
   float m30, float m31, float m32, float m33)
{
   _data[ 0] = m00;
   _data[ 1] = m01;
   _data[ 2] = m02;
   _data[ 3] = m03;
   _data[ 4] = m10;
   _data[ 5] = m11;
   _data[ 6] = m12;
   _data[ 7] = m13;
   _data[ 8] = m20;
   _data[ 9] = m21;
   _data[10] = m22;
   _data[11] = m23;
   _data[12] = m30;
   _data[13] = m31;
   _data[14] = m32;
   _data[15] = m33;
}

Matrix::Matrix(const float data[4*4])
{
   for (size_t i; i < 4*4; ++i)
   {
      _data[i] = data[i];
   }
}

Matrix::Matrix(const boost::array<float, 16>& data) :
   _data(data)
{ }

const float& Matrix::operator()(size_t col, size_t row) const
{
   return _data[col*4+row];
}

float& Matrix::operator()(size_t col, size_t row)
{
   return _data[col*4+row];
}

const float& Matrix::operator[](size_t i) const
{
   return _data[i];
}

float& Matrix::operator[](size_t i)
{
   return _data[i];
}

const float* Matrix::data() const
{
   return &_data[0];
}

const Matrix& Matrix::identity()
{
   return identityMatrix;
}

void Matrix::createOrthographic(
   float left,
   float right,
   float bottom,
   float top,
   float nearVal,
   float farVal,
   Matrix& result)
{
   result(0,0) = 2.0f / (right - left);
   result(0,1) = 0;
   result(0,2) = 0;
   result(0,3) = 0;
   result(1,0) = 0;
   result(1,1) = 2.0f / (top - bottom);
   result(1,2) = 0;
   result(1,3) = 0;
   result(2,0) = 0;
   result(2,1) = 0;
   result(2,2) = -2.0f / (nearVal - farVal);
   result(2,3) = 0;
   result(3,0) = - (right + left) / (right - left);
   result(3,1) = - (top + bottom) / (top - bottom);
   result(3,2) = - (farVal + nearVal) / (farVal - nearVal);
   result(3,3) = 1.0f;
}

void Matrix::createRotationX(
   float radians,
   Matrix& result)
{
   result = identity();

   float c = cosf(radians);
   float s = sinf(radians);

   result(1,1) = c;
   result(1,2) = s;
   result(2,1) = -s;
   result(2,2) = c;
}

void Matrix::createRotationY(
   float radians,
   Matrix& result)
{
   result = identity();

   float c = cosf(radians);
   float s = sinf(radians);

   result(0,0) = c;
   result(0,2) = -s;
   result(2,0) = s;
   result(2,2) = c;
}

void Matrix::createRotationZ(
   float radians,
   Matrix& result)
{
   result = identity();

   float c = cosf(radians);
   float s = sinf(radians);

   result(0,0) = c;
   result(0,1) = s;
   result(1,0) = -s;
   result(1,1) = c;
}

void Matrix::createScale(
   float scale,
   Matrix& result)
{
   createScale(scale, scale, scale, result);
}

void Matrix::createScale(
   const Vector3& scales,
   Matrix& result)
{
   createScale(scales.x, scales.y, scales.z, result);
}

void Matrix::createScale(
   float xScale,
   float yScale,
   float zScale,
   Matrix& result)
{
   result(0,0) = xScale;
   result(0,1) = 0;
   result(0,2) = 0;
   result(0,3) = 0;
   result(1,0) = 0;
   result(1,1) = yScale;
   result(1,2) = 0;
   result(1,3) = 0;
   result(2,0) = 0;
   result(2,1) = 0;
   result(2,2) = zScale;
   result(2,3) = 0;
   result(3,0) = 0;
   result(3,1) = 0;
   result(3,2) = 0;
   result(3,3) = 1;
}

void Matrix::createTranslation(
   const Vector3& positions,
   Matrix& result)
{
   createTranslation(positions.x, positions.y, positions.z, result);
}

void Matrix::createTranslation(
   float xPosition,
   float yPosition,
   float zPosition,
   Matrix& result)
{
   result(0,0) = 1;
   result(0,1) = 0;
   result(0,2) = 0;
   result(0,3) = 0;
   result(1,0) = 0;
   result(1,1) = 1;
   result(1,2) = 0;
   result(1,3) = 0;
   result(2,0) = 0;
   result(2,1) = 0;
   result(2,2) = 1;
   result(2,3) = 0;
   result(3,0) = xPosition;
   result(3,1) = yPosition;
   result(3,2) = zPosition;
   result(3,3) = 1;
}

void Matrix::add(const Matrix& a, const Matrix& b, Matrix& result)
{
   for (size_t i = 0; i < 4*4; ++i)
      result._data[i] = a._data[i] + b._data[i];
}

void Matrix::divide(const Matrix& a, float b, Matrix& result)
{
   for (size_t i = 0; i < 4*4; ++i)
      result._data[i] = a._data[i] / b;
}

void Matrix::divide(const Matrix& a, const Matrix& b, Matrix& result)
{
   for (size_t i = 0; i < 4*4; ++i)
      result._data[i] = a._data[i] / b._data[i];
}

void Matrix::multiply(const Matrix& a, float b, Matrix& result)
{
   for (size_t i = 0; i < 4*4; ++i)
      result._data[i] = a._data[i] * b;
}

void Matrix::multiply(const Matrix& a, const Matrix& b, Matrix& result)
{
   // We have to use a temporary because a or b could be result.
   Matrix tmp;
   tmp(0,0) = (((a(0,0) * b(0,0)) + (a(0,1) * b(1,0))) + (a(0,2) * b(2,0))) + (a(0,3) * b(3,0));
   tmp(0,1) = (((a(0,0) * b(0,1)) + (a(0,1) * b(1,1))) + (a(0,2) * b(2,1))) + (a(0,3) * b(3,1));
   tmp(0,2) = (((a(0,0) * b(0,2)) + (a(0,1) * b(1,2))) + (a(0,2) * b(2,2))) + (a(0,3) * b(3,2));
   tmp(0,3) = (((a(0,0) * b(0,3)) + (a(0,1) * b(1,3))) + (a(0,2) * b(2,3))) + (a(0,3) * b(3,3));
   tmp(1,0) = (((a(1,0) * b(0,0)) + (a(1,1) * b(1,0))) + (a(1,2) * b(2,0))) + (a(1,3) * b(3,0));
   tmp(1,1) = (((a(1,0) * b(0,1)) + (a(1,1) * b(1,1))) + (a(1,2) * b(2,1))) + (a(1,3) * b(3,1));
   tmp(1,2) = (((a(1,0) * b(0,2)) + (a(1,1) * b(1,2))) + (a(1,2) * b(2,2))) + (a(1,3) * b(3,2));
   tmp(1,3) = (((a(1,0) * b(0,3)) + (a(1,1) * b(1,3))) + (a(1,2) * b(2,3))) + (a(1,3) * b(3,3));
   tmp(2,0) = (((a(2,0) * b(0,0)) + (a(2,1) * b(1,0))) + (a(2,2) * b(2,0))) + (a(2,3) * b(3,0));
   tmp(2,1) = (((a(2,0) * b(0,1)) + (a(2,1) * b(1,1))) + (a(2,2) * b(2,1))) + (a(2,3) * b(3,1));
   tmp(2,2) = (((a(2,0) * b(0,2)) + (a(2,1) * b(1,2))) + (a(2,2) * b(2,2))) + (a(2,3) * b(3,2));
   tmp(2,3) = (((a(2,0) * b(0,3)) + (a(2,1) * b(1,3))) + (a(2,2) * b(2,3))) + (a(2,3) * b(3,3));
   tmp(3,0) = (((a(3,0) * b(0,0)) + (a(3,1) * b(1,0))) + (a(3,2) * b(2,0))) + (a(3,3) * b(3,0));
   tmp(3,1) = (((a(3,0) * b(0,1)) + (a(3,1) * b(1,1))) + (a(3,2) * b(2,1))) + (a(3,3) * b(3,1));
   tmp(3,2) = (((a(3,0) * b(0,2)) + (a(3,1) * b(1,2))) + (a(3,2) * b(2,2))) + (a(3,3) * b(3,2));
   tmp(3,3) = (((a(3,0) * b(0,3)) + (a(3,1) * b(1,3))) + (a(3,2) * b(2,3))) + (a(3,3) * b(3,3));

   std::swap(result, tmp);
}

void Matrix::negate(Matrix& a)
{
   for (size_t i = 0; i < 4*4; ++i)
      a._data[i] = -a._data[i];
}

void Matrix::subtract(const Matrix& a, const Matrix& b, Matrix& result)
{
   for (size_t i = 0; i < 4*4; ++i)
      result._data[i] = a._data[i] - b._data[i];
}

bool operator==(const Matrix& a, const Matrix& b)
{
   for (size_t i = 0; i < 4*4; ++i)
   {
      if (a[i] != b[i]) return false;
   }
   return true;
}

bool operator!=(const Matrix& a, const Matrix& b)
{
   return !(a == b);
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
   Matrix mat;
   Matrix::add(a, b, mat);
   return mat;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
   Matrix mat;
   Matrix::subtract(a, b, mat);
   return mat;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
   Matrix mat;
   Matrix::multiply(a, b, mat);
   return mat;
}


} // namespace squidge
