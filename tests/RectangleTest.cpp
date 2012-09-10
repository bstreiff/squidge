#include "gtest/gtest.h"
#include "common/Rectangle.h"

using namespace squidge;

TEST(RectangleTest, Equals)
{
   Rectangle a(1, 2, 3, 4);
   Rectangle b(1, 2, 3, 4);
   Rectangle c(1, 3, 5, 6);

   EXPECT_TRUE(a == b);
   EXPECT_TRUE(b == a);
   EXPECT_FALSE(a == c);
   EXPECT_FALSE(c == a);
   EXPECT_FALSE(b == c);
   EXPECT_FALSE(c == b);
}

TEST(RectangleTest, NotEquals)
{
   Rectangle a(1, 2, 3, 4);
   Rectangle b(1, 2, 3, 4);
   Rectangle c(1, 3, 5, 6);

   EXPECT_FALSE(a != b);
   EXPECT_FALSE(b != a);
   EXPECT_TRUE(a != c);
   EXPECT_TRUE(c != a);
   EXPECT_TRUE(b != c);
   EXPECT_TRUE(c != b);
}

TEST(RectangleTest, DefaultCtor)
{
   Rectangle a;

   EXPECT_EQ(Rectangle(0, 0, 0, 0), a);
}

TEST(RectangleTest, CopyCtor)
{
   Rectangle a(13, 37, 42, 9);
   Rectangle b(a);

   EXPECT_EQ(Rectangle(13, 37, 42, 9), b);
}

TEST(RectangleTest, Assignment)
{
   Rectangle a(13, 37, 42, 9);
   Rectangle b(99, 99, 99, 99);

   EXPECT_EQ(Rectangle(13, 37, 42, 9), b = a);
   EXPECT_EQ(Rectangle(13, 37, 42, 9), b);
}

TEST(RectangleTest, Components)
{
   Rectangle a(13, 37, 42, 99);

   EXPECT_EQ(13, a.x);
   EXPECT_EQ(37, a.y);
   EXPECT_EQ(42, a.width);
   EXPECT_EQ(99, a.height);
}

TEST(RectangleTest, Center)
{
   Rectangle a(2, 8, 10, 12);

   EXPECT_EQ(Point((2+10)/2, (8+12)/2), a.center());
}

TEST(RectangleTest, Bounds)
{
   Rectangle a(7, 11, 13, 17);

   EXPECT_EQ(7, a.left());
   EXPECT_EQ(11, a.top());
   EXPECT_EQ(7+13, a.right());
   EXPECT_EQ(11+17, a.bottom());
}
