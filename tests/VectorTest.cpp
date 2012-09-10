#include "gtest/gtest.h"
#include "common/Vector2.h"

using namespace squidge;

typedef Vector2Base<int> IntVector;

TEST(VectorTest, Equals)
{
   IntVector a(1, 2);
   IntVector b(1, 2);
   IntVector c(1, 3);

   EXPECT_TRUE(a == b);
   EXPECT_TRUE(b == a);
   EXPECT_FALSE(a == c);
   EXPECT_FALSE(c == a);
   EXPECT_FALSE(b == c);
   EXPECT_FALSE(c == b);
}

TEST(VectorTest, NotEquals)
{
   IntVector a(1, 2);
   IntVector b(1, 2);
   IntVector c(1, 3);

   EXPECT_FALSE(a != b);
   EXPECT_FALSE(b != a);
   EXPECT_TRUE(a != c);
   EXPECT_TRUE(c != a);
   EXPECT_TRUE(b != c);
   EXPECT_TRUE(c != b);
}

TEST(VectorTest, DefaultCtor)
{
   IntVector a;

   EXPECT_EQ(IntVector(0, 0), a);
}

TEST(VectorTest, CopyCtor)
{
   IntVector a(13, 37);
   IntVector b(a);

   EXPECT_EQ(IntVector(13, 37), b);
}

TEST(VectorTest, Assignment)
{
   IntVector a(13, 37);
   IntVector b(99, 99);

   EXPECT_EQ(IntVector(13, 37), b = a);
   EXPECT_EQ(IntVector(13, 37), b);
}

TEST(VectorTest, Components)
{
   IntVector a(13, 37);

   EXPECT_EQ(13, a.x);
   EXPECT_EQ(37, a.y);
}

TEST(VectorTest, Addition)
{
   IntVector a(7, 11);
   IntVector b(13, 19);

   EXPECT_EQ(IntVector(7+13, 11+19), a + b);
}

TEST(VectorTest, Subtraction)
{
   IntVector a(7, 11);
   IntVector b(13, 19);

   EXPECT_EQ(IntVector(7-13, 11-19), a - b);
}

TEST(VectorTest, Multiplication)
{
   IntVector a(7, 11);
   IntVector b(13, 19);

   EXPECT_EQ(IntVector(7*13, 11*19), a * b);
}

TEST(VectorTest, Division)
{
   IntVector a(100, 15);
   IntVector b(20, 3);

   EXPECT_EQ(IntVector(100/20, 15/3), a / b);
}

TEST(VectorTest, ScalarMultiplication)
{
   IntVector a(7, 11);

   EXPECT_EQ(IntVector(7*5, 11*5), a * 5);
}

TEST(VectorTest, ScalarDivision)
{
   IntVector a(100, 25);

   EXPECT_EQ(IntVector(100/5, 25/5), a / 5);
}
