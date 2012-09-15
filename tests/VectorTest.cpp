#include "gtest/gtest.h"
#include "common/Vector2.h"

using namespace squidge;

TEST(VectorTest, Equals)
{
   Vector2 a(1, 2);
   Vector2 b(1, 2);
   Vector2 c(1, 3);

   EXPECT_TRUE(a == a);
   EXPECT_TRUE(a == b);
   EXPECT_TRUE(b == a);
   EXPECT_FALSE(a == c);
   EXPECT_FALSE(c == a);
   EXPECT_FALSE(b == c);
   EXPECT_FALSE(c == b);
}

TEST(VectorTest, NotEquals)
{
   Vector2 a(1, 2);
   Vector2 b(1, 2);
   Vector2 c(1, 3);

   EXPECT_FALSE(a != b);
   EXPECT_FALSE(b != a);
   EXPECT_TRUE(a != c);
   EXPECT_TRUE(c != a);
   EXPECT_TRUE(b != c);
   EXPECT_TRUE(c != b);
}

TEST(VectorTest, DefaultCtor)
{
   Vector2 a;

   EXPECT_EQ(Vector2(0, 0), a);
}

TEST(VectorTest, CopyCtor)
{
   Vector2 a(13, 37);
   Vector2 b(a);

   EXPECT_EQ(Vector2(13, 37), b);
}

TEST(VectorTest, Assignment)
{
   Vector2 a(13, 37);
   Vector2 b(99, 99);

   EXPECT_EQ(Vector2(13, 37), b = a);
   EXPECT_EQ(Vector2(13, 37), b);
}

TEST(VectorTest, SelfAssignment)
{
   Vector2 a(13, 37);
   
   a = a;

   EXPECT_EQ(Vector2(13, 37), a);
}

TEST(VectorTest, Components)
{
   Vector2 a(13, 37);

   EXPECT_EQ(13, a.x);
   EXPECT_EQ(37, a.y);
}

TEST(VectorTest, Addition)
{
   Vector2 a(7, 11);
   Vector2 b(13, 19);

   EXPECT_EQ(Vector2(7+13, 11+19), a + b);
}

TEST(VectorTest, Subtraction)
{
   Vector2 a(7, 11);
   Vector2 b(13, 19);

   EXPECT_EQ(Vector2(7-13, 11-19), a - b);
}

TEST(VectorTest, Multiplication)
{
   Vector2 a(7, 11);
   Vector2 b(13, 19);

   EXPECT_EQ(Vector2(7*13, 11*19), a * b);
}

TEST(VectorTest, Division)
{
   Vector2 a(100, 15);
   Vector2 b(20, 3);

   EXPECT_EQ(Vector2(100/20, 15/3), a / b);
}

TEST(VectorTest, ScalarMultiplication)
{
   Vector2 a(7, 11);

   EXPECT_EQ(Vector2(7*5, 11*5), a * 5);
}

TEST(VectorTest, ScalarDivision)
{
   Vector2 a(100, 25);

   EXPECT_EQ(Vector2(100/5, 25/5), a / 5);
}
