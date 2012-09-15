#include "common/Matrix.h"
#include "common/Vector3.h"
#include <math.h>

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

const float& Matrix::operator()(size_t row, size_t col) const
{
   return _data[row*4+col];
}

float& Matrix::operator()(size_t row, size_t col)
{
   return _data[row*4+col];
}

const float& Matrix::operator[](size_t i) const
{
   return _data[i];
}

float& Matrix::operator[](size_t i)
{
   return _data[i];
}


const Matrix& Matrix::identity()
{
   return identityMatrix;
}

void Matrix::createOrthographic(
   float width,
   float height,
   float zNearPlane,
   float zFarPlane,
   Matrix& result)
{
   result._data[ 0] = 2.0f / width;
   result._data[ 1] = 0;
   result._data[ 2] = 0;
   result._data[ 3] = 0;
   result._data[ 4] = 0;
   result._data[ 5] = 2.0f / height;
   result._data[ 6] = 0;
   result._data[ 7] = 0;
   result._data[ 8] = 0;
   result._data[ 9] = 0;
   result._data[10] = 1.0f / (zNearPlane - zFarPlane);
   result._data[11] = 0;
   result._data[12] = 0;
   result._data[13] = 0;
   result._data[14] = zNearPlane / (zNearPlane - zFarPlane);
   result._data[15] = 1.0f;
}

void Matrix::createRotationX(
   float radians,
   Matrix& result)
{
   result = identity();

   float c = cosf(radians);
   float s = sinf(radians);

   result._data[ 5] = c;
   result._data[ 6] = s;
   result._data[ 9] = -s;
   result._data[10] = c;
}

void Matrix::createRotationY(
   float radians,
   Matrix& result)
{
   result = identity();

   float c = cosf(radians);
   float s = sinf(radians);

   result._data[ 0] = c;
   result._data[ 2] = -s;
   result._data[ 8] = s;
   result._data[10] = c;
}

void Matrix::createRotationZ(
   float radians,
   Matrix& result)
{
   result = identity();

   float c = cosf(radians);
   float s = sinf(radians);

   result._data[ 0] = c;
   result._data[ 1] = s;
   result._data[ 4] = -s;
   result._data[ 5] = c;
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
   result._data[ 0] = xScale;
   result._data[ 1] = 0;
   result._data[ 2] = 0;
   result._data[ 3] = 0;
   result._data[ 4] = 0;
   result._data[ 5] = yScale;
   result._data[ 6] = 0;
   result._data[ 7] = 0;
   result._data[ 8] = 0;
   result._data[ 9] = 0;
   result._data[10] = zScale;
   result._data[11] = 0;
   result._data[12] = 0;
   result._data[13] = 0;
   result._data[14] = 0;
   result._data[15] = 1;
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
   result._data[ 0] = 1;
   result._data[ 1] = 0;
   result._data[ 2] = 0;
   result._data[ 3] = 0;
   result._data[ 4] = 0;
   result._data[ 5] = 1;
   result._data[ 6] = 0;
   result._data[ 7] = 0;
   result._data[ 8] = 0;
   result._data[ 9] = 0;
   result._data[10] = 1;
   result._data[11] = 0;
   result._data[12] = xPosition;
   result._data[13] = yPosition;
   result._data[14] = zPosition;
   result._data[15] = 1;
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
   // funroll loops?
   result._data[ 0] = (((a._data[ 0] * b._data[ 0]) + (a._data[ 1] * b._data[ 4])) + (a._data[ 2] * b._data[ 8])) + (a._data[ 3] * b._data[12]);
   result._data[ 1] = (((a._data[ 0] * b._data[ 1]) + (a._data[ 1] * b._data[ 5])) + (a._data[ 2] * b._data[ 9])) + (a._data[ 3] * b._data[13]);
   result._data[ 2] = (((a._data[ 0] * b._data[ 2]) + (a._data[ 1] * b._data[ 6])) + (a._data[ 2] * b._data[10])) + (a._data[ 3] * b._data[14]);
   result._data[ 3] = (((a._data[ 0] * b._data[ 3]) + (a._data[ 1] * b._data[ 7])) + (a._data[ 2] * b._data[11])) + (a._data[ 3] * b._data[15]);
   result._data[ 4] = (((a._data[ 4] * b._data[ 0]) + (a._data[ 5] * b._data[ 4])) + (a._data[ 6] * b._data[ 8])) + (a._data[ 7] * b._data[12]);
   result._data[ 5] = (((a._data[ 4] * b._data[ 1]) + (a._data[ 5] * b._data[ 5])) + (a._data[ 6] * b._data[ 9])) + (a._data[ 7] * b._data[13]);
   result._data[ 6] = (((a._data[ 4] * b._data[ 2]) + (a._data[ 5] * b._data[ 6])) + (a._data[ 6] * b._data[10])) + (a._data[ 7] * b._data[14]);
   result._data[ 7] = (((a._data[ 4] * b._data[ 3]) + (a._data[ 5] * b._data[ 7])) + (a._data[ 6] * b._data[11])) + (a._data[ 7] * b._data[15]);
   result._data[ 8] = (((a._data[ 8] * b._data[ 0]) + (a._data[ 9] * b._data[ 4])) + (a._data[10] * b._data[ 8])) + (a._data[11] * b._data[12]);
   result._data[ 9] = (((a._data[ 8] * b._data[ 1]) + (a._data[ 9] * b._data[ 5])) + (a._data[10] * b._data[ 9])) + (a._data[11] * b._data[13]);
   result._data[10] = (((a._data[ 8] * b._data[ 2]) + (a._data[ 9] * b._data[ 6])) + (a._data[10] * b._data[10])) + (a._data[11] * b._data[14]);
   result._data[11] = (((a._data[ 8] * b._data[ 3]) + (a._data[ 9] * b._data[ 7])) + (a._data[10] * b._data[11])) + (a._data[11] * b._data[15]);
   result._data[12] = (((a._data[12] * b._data[ 0]) + (a._data[13] * b._data[ 4])) + (a._data[14] * b._data[ 8])) + (a._data[15] * b._data[12]);
   result._data[13] = (((a._data[12] * b._data[ 1]) + (a._data[13] * b._data[ 5])) + (a._data[14] * b._data[ 9])) + (a._data[15] * b._data[13]);
   result._data[14] = (((a._data[12] * b._data[ 2]) + (a._data[13] * b._data[ 6])) + (a._data[14] * b._data[10])) + (a._data[15] * b._data[14]);
   result._data[15] = (((a._data[12] * b._data[ 3]) + (a._data[13] * b._data[ 7])) + (a._data[14] * b._data[11])) + (a._data[15] * b._data[15]);
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
