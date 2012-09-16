// Tests to make sure that I can do Stupid Pointer Tricks
// with Color/Vector/Matrix types if I need to.

#include "gtest/gtest.h"
#include "common/Color.h"
#include "common/Vector2.h"
#include "common/Vector3.h"
#include "common/Vector4.h"
#include "common/Matrix.h"

using namespace squidge;

TEST(AlignmentTest, Color)
{
   // a Color must have a byte representation that allows it
   // to be used with glColor4bv; e.g., a byte each for RGBA.

   Color a(0x11, 0x22, 0x33, 0x44);

   EXPECT_EQ(4*sizeof(uint8_t), sizeof(Color));

   EXPECT_EQ(0x11, a.r);
   EXPECT_EQ(0x22, a.g);
   EXPECT_EQ(0x33, a.b);
   EXPECT_EQ(0x44, a.a);

   uint8_t* a_as_u8 = reinterpret_cast<uint8_t*>(&a);

   EXPECT_EQ(0x11, a_as_u8[0]);
   EXPECT_EQ(0x22, a_as_u8[1]);
   EXPECT_EQ(0x33, a_as_u8[2]);
   EXPECT_EQ(0x44, a_as_u8[3]);
}

TEST(AlignmentTest, ColorArray)
{
   Color a[2] =
   {
      Color(0x11, 0x22, 0x33, 0x44),
      Color(0x55, 0x66, 0x77, 0x88)
   };

   EXPECT_EQ(8*sizeof(uint8_t), sizeof(a));

   EXPECT_EQ(0x11, a[0].r);
   EXPECT_EQ(0x22, a[0].g);
   EXPECT_EQ(0x33, a[0].b);
   EXPECT_EQ(0x44, a[0].a);
   EXPECT_EQ(0x55, a[1].r);
   EXPECT_EQ(0x66, a[1].g);
   EXPECT_EQ(0x77, a[1].b);
   EXPECT_EQ(0x88, a[1].a);

   uint8_t* a_as_u8 = reinterpret_cast<uint8_t*>(&a);

   EXPECT_EQ(0x11, a_as_u8[0]);
   EXPECT_EQ(0x22, a_as_u8[1]);
   EXPECT_EQ(0x33, a_as_u8[2]);
   EXPECT_EQ(0x44, a_as_u8[3]);
   EXPECT_EQ(0x55, a_as_u8[4]);
   EXPECT_EQ(0x66, a_as_u8[5]);
   EXPECT_EQ(0x77, a_as_u8[6]);
   EXPECT_EQ(0x88, a_as_u8[7]);
}

TEST(AlignmentTest, Vector2)
{
   // a Vector2 must have a byte representation that allows it
   // to be used with glTexCoord2fv or glVertex2fv.

   Vector2 a(31337.0, 3.14159);

   EXPECT_EQ(2*sizeof(float), sizeof(Vector2));

   EXPECT_FLOAT_EQ(31337.0, a.x);
   EXPECT_FLOAT_EQ(3.14159, a.y);

   float* a_as_float = reinterpret_cast<float*>(&a);

   EXPECT_FLOAT_EQ(31337.0, a_as_float[0]);
   EXPECT_FLOAT_EQ(3.14159, a_as_float[1]);
}

TEST(AlignmentTest, Vector2Array)
{
   Vector2 a[2] =
   {
      Vector2(31337.0, 3.14159),
      Vector2(-0.9165, -0.3999)
   };

   EXPECT_EQ(4*sizeof(float), sizeof(a));

   EXPECT_FLOAT_EQ(31337.0, a[0].x);
   EXPECT_FLOAT_EQ(3.14159, a[0].y);
   EXPECT_FLOAT_EQ(-0.9165, a[1].x);
   EXPECT_FLOAT_EQ(-0.3999, a[1].y);

   float* a_as_float = reinterpret_cast<float*>(&a);

   EXPECT_FLOAT_EQ(31337.0, a_as_float[0]);
   EXPECT_FLOAT_EQ(3.14159, a_as_float[1]);
   EXPECT_FLOAT_EQ(-0.9165, a_as_float[2]);
   EXPECT_FLOAT_EQ(-0.3999, a_as_float[3]);
}

TEST(AlignmentTest, Vector3)
{
   // a Vector3 must have a byte representation that allows it
   // to be used with glTexCoord3fv or glVertex3fv.

   Vector3 a(31337.0, 3.14159, 2.71828);

   EXPECT_EQ(3*sizeof(float), sizeof(Vector3));

   EXPECT_FLOAT_EQ(31337.0, a.x);
   EXPECT_FLOAT_EQ(3.14159, a.y);
   EXPECT_FLOAT_EQ(2.71828, a.z);

   float* a_as_float = reinterpret_cast<float*>(&a);

   EXPECT_FLOAT_EQ(31337.0, a_as_float[0]);
   EXPECT_FLOAT_EQ(3.14159, a_as_float[1]);
   EXPECT_FLOAT_EQ(2.71828, a_as_float[2]);
}

TEST(AlignmentTest, Vector3Array)
{
   Vector3 a[2] =
   {
      Vector3(31337.0, 3.14159, 2.71828),
      Vector3(-0.9165, -0.3999, 2.29139)
   };

   EXPECT_EQ(6*sizeof(float), sizeof(a));

   EXPECT_FLOAT_EQ(31337.0, a[0].x);
   EXPECT_FLOAT_EQ(3.14159, a[0].y);
   EXPECT_FLOAT_EQ(2.71828, a[0].z);
   EXPECT_FLOAT_EQ(-0.9165, a[1].x);
   EXPECT_FLOAT_EQ(-0.3999, a[1].y);
   EXPECT_FLOAT_EQ(2.29139, a[1].z);

   float* a_as_float = reinterpret_cast<float*>(&a);

   EXPECT_FLOAT_EQ(31337.0, a_as_float[0]);
   EXPECT_FLOAT_EQ(3.14159, a_as_float[1]);
   EXPECT_FLOAT_EQ(2.71828, a_as_float[2]);
   EXPECT_FLOAT_EQ(-0.9165, a_as_float[3]);
   EXPECT_FLOAT_EQ(-0.3999, a_as_float[4]);
   EXPECT_FLOAT_EQ(2.29139, a_as_float[5]);
}

TEST(AlignmentTest, Vector4)
{
   // a Vector4 must have a byte representation that allows it
   // to be used with glTexCoord4fv or glVertex4fv.

   Vector4 a(31337.0, 3.14159, 2.71828, 1.62325);

   EXPECT_EQ(4*sizeof(float), sizeof(Vector4));

   EXPECT_FLOAT_EQ(31337.0, a.x);
   EXPECT_FLOAT_EQ(3.14159, a.y);
   EXPECT_FLOAT_EQ(2.71828, a.z);
   EXPECT_FLOAT_EQ(1.62325, a.w);

   float* a_as_float = reinterpret_cast<float*>(&a);

   EXPECT_FLOAT_EQ(31337.0, a_as_float[0]);
   EXPECT_FLOAT_EQ(3.14159, a_as_float[1]);
   EXPECT_FLOAT_EQ(2.71828, a_as_float[2]);
   EXPECT_FLOAT_EQ(1.62325, a_as_float[3]);
}

TEST(AlignmentTest, Vector4Array)
{
   Vector4 a[2] =
   {
      Vector4(31337.0, 3.14159, 2.71828, 1.62325),
      Vector4(-0.9165, -0.3999, 2.29139, 3.73767)
   };

   EXPECT_EQ(8*sizeof(float), sizeof(a));

   EXPECT_FLOAT_EQ(31337.0, a[0].x);
   EXPECT_FLOAT_EQ(3.14159, a[0].y);
   EXPECT_FLOAT_EQ(2.71828, a[0].z);
   EXPECT_FLOAT_EQ(1.62325, a[0].w);
   EXPECT_FLOAT_EQ(-0.9165, a[1].x);
   EXPECT_FLOAT_EQ(-0.3999, a[1].y);
   EXPECT_FLOAT_EQ(2.29139, a[1].z);
   EXPECT_FLOAT_EQ(3.73767, a[1].w);

   float* a_as_float = reinterpret_cast<float*>(&a);

   EXPECT_FLOAT_EQ(31337.0, a_as_float[0]);
   EXPECT_FLOAT_EQ(3.14159, a_as_float[1]);
   EXPECT_FLOAT_EQ(2.71828, a_as_float[2]);
   EXPECT_FLOAT_EQ(1.62325, a_as_float[3]);
   EXPECT_FLOAT_EQ(-0.9165, a_as_float[4]);
   EXPECT_FLOAT_EQ(-0.3999, a_as_float[5]);
   EXPECT_FLOAT_EQ(2.29139, a_as_float[6]);
   EXPECT_FLOAT_EQ(3.73767, a_as_float[7]);
}

TEST(AlignmentTest, Matrix)
{
   // A Matrix must have a byte representation that allows it to be used
   // with glLoadMatrixf.

   Matrix m(0.0, 0.1, 0.2, 0.3,
            1.0, 1.1, 1.2, 1.3,
            2.0, 2.1, 2.2, 2.3,
            3.0, 3.1, 3.2, 3.3);

   EXPECT_EQ(16*sizeof(float), sizeof(m));

   EXPECT_FLOAT_EQ(0.0, m(0,0));
   EXPECT_FLOAT_EQ(0.1, m(0,1));
   EXPECT_FLOAT_EQ(0.2, m(0,2));
   EXPECT_FLOAT_EQ(0.3, m(0,3));
   EXPECT_FLOAT_EQ(1.0, m(1,0));
   EXPECT_FLOAT_EQ(1.1, m(1,1));
   EXPECT_FLOAT_EQ(1.2, m(1,2));
   EXPECT_FLOAT_EQ(1.3, m(1,3));
   EXPECT_FLOAT_EQ(2.0, m(2,0));
   EXPECT_FLOAT_EQ(2.1, m(2,1));
   EXPECT_FLOAT_EQ(2.2, m(2,2));
   EXPECT_FLOAT_EQ(2.3, m(2,3));
   EXPECT_FLOAT_EQ(3.0, m(3,0));
   EXPECT_FLOAT_EQ(3.1, m(3,1));
   EXPECT_FLOAT_EQ(3.2, m(3,2));
   EXPECT_FLOAT_EQ(3.3, m(3,3));

   float* m_as_float = reinterpret_cast<float*>(&m);

   EXPECT_FLOAT_EQ(0.0, m_as_float[0]);
   EXPECT_FLOAT_EQ(0.1, m_as_float[1]);
   EXPECT_FLOAT_EQ(0.2, m_as_float[2]);
   EXPECT_FLOAT_EQ(0.3, m_as_float[3]);
   EXPECT_FLOAT_EQ(1.0, m_as_float[4]);
   EXPECT_FLOAT_EQ(1.1, m_as_float[5]);
   EXPECT_FLOAT_EQ(1.2, m_as_float[6]);
   EXPECT_FLOAT_EQ(1.3, m_as_float[7]);
   EXPECT_FLOAT_EQ(2.0, m_as_float[8]);
   EXPECT_FLOAT_EQ(2.1, m_as_float[9]);
   EXPECT_FLOAT_EQ(2.2, m_as_float[10]);
   EXPECT_FLOAT_EQ(2.3, m_as_float[11]);
   EXPECT_FLOAT_EQ(3.0, m_as_float[12]);
   EXPECT_FLOAT_EQ(3.1, m_as_float[13]);
   EXPECT_FLOAT_EQ(3.2, m_as_float[14]);
   EXPECT_FLOAT_EQ(3.3, m_as_float[15]);
}
