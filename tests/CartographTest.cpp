#include "gtest/gtest.h"
#include "common/Cartograph.h"

using namespace squidge;

TEST(CartographTest, Ctor)
{
   Cartograph<int32_t> c;

   EXPECT_EQ(0, c.height());
   EXPECT_EQ(0, c.width());
}

TEST(CartographTest, RectCtor)
{
   Cartograph<int32_t> c(Rectangle(0, 0, 10, 10));

   EXPECT_EQ(10, c.height());
   EXPECT_EQ(10, c.width());
}

TEST(CartographTest, Resize)
{
   Cartograph<int32_t> c;
   c.resize(Rectangle(0, 0, 10, 10));

   EXPECT_EQ(10, c.height());
   EXPECT_EQ(10, c.width());
}

TEST(CartographTest, Clear)
{
   Cartograph<int32_t> c;
   c.resize(Rectangle(0, 0, 10, 10));
   c.clear();

   EXPECT_EQ(0, c.height());
   EXPECT_EQ(0, c.width());
}

TEST(CartographTest, InRange)
{
   Cartograph<int32_t> c;
   c.resize(Rectangle(0, 0, 5, 10));

   EXPECT_TRUE (c.inRange(Point(0, 0)));
   EXPECT_FALSE(c.inRange(Point(-1, 0)));
   EXPECT_FALSE(c.inRange(Point(0, -1)));

   EXPECT_TRUE (c.inRange(Point(4, 9)));
   EXPECT_FALSE(c.inRange(Point(5, 9)));
   EXPECT_FALSE(c.inRange(Point(4, 10)));
}

TEST(CartographTest, OperatorParensWithTopLeftAtOrigin)
{
   Cartograph<int32_t> c(Rectangle(0, 0, 2, 3), 99);
   c(0, 0) = 3;
   c(1, 0) = 1;
   c(0, 1) = 4;
   c(1, 1) = 1;
   c(0, 2) = 5;
   c(1, 2) = 9;

   EXPECT_EQ(3, c(0, 0));
   EXPECT_EQ(1, c(1, 0));
   EXPECT_EQ(4, c(0, 1));
   EXPECT_EQ(1, c(1, 1));
   EXPECT_EQ(5, c(0, 2));
   EXPECT_EQ(9, c(1, 2));
}

TEST(CartographTest, OperatorParensWithTopLeftNegative)
{
   Cartograph<int32_t> c(Rectangle(-1, -1, 2, 3), 99);
   c(-1, -1) = 3;
   c( 0, -1) = 1;
   c(-1,  0) = 4;
   c( 0,  0) = 1;
   c(-1,  1) = 5;
   c( 0,  1) = 9;

   EXPECT_EQ(3, c(-1, -1));
   EXPECT_EQ(1, c( 0, -1));
   EXPECT_EQ(4, c(-1,  0));
   EXPECT_EQ(1, c( 0,  0));
   EXPECT_EQ(5, c(-1,  1));
   EXPECT_EQ(9, c( 0,  1));
}

TEST(CartographTest, IteratorIncrementSequenceNoWrap)
{
   Cartograph<int32_t> c(Rectangle(3, 6, 10, 5), 99);
   c(3, 6) = 3;
   c(4, 6) = 1;
   c(5, 6) = 3;
   c(6, 6) = 3;
   c(7, 6) = 7;

   Cartograph<int32_t>::iterator itr = c.begin();

   EXPECT_EQ(Point(3, 6), itr.position());
   EXPECT_EQ(3, *itr);
   itr++;
   EXPECT_EQ(Point(4, 6), itr.position());
   EXPECT_EQ(1, *itr);
   itr++;
   EXPECT_EQ(Point(5, 6), itr.position());
   EXPECT_EQ(3, *itr);
   itr++;
   EXPECT_EQ(Point(6, 6), itr.position());
   EXPECT_EQ(3, *itr);
   itr++;
   EXPECT_EQ(Point(7, 6), itr.position());
   EXPECT_EQ(7, *itr);
}

TEST(CartographTest, IncrementSequenceWithWrap)
{
   Cartograph<int32_t> c(Rectangle(3, 6, 3, 5), 99);
   c(3, 6) = 3;
   c(4, 6) = 1;
   c(5, 6) = 3;
   c(3, 7) = 3;
   c(4, 7) = 7;

   Cartograph<int32_t>::iterator itr = c.begin();

   EXPECT_EQ(Point(3, 6), itr.position());
   EXPECT_EQ(3, *itr);
   itr++;
   EXPECT_EQ(Point(4, 6), itr.position());
   EXPECT_EQ(1, *itr);
   itr++;
   EXPECT_EQ(Point(5, 6), itr.position());
   EXPECT_EQ(3, *itr);
   itr++;
   EXPECT_EQ(Point(3, 7), itr.position());
   EXPECT_EQ(3, *itr);
   itr++;
   EXPECT_EQ(Point(4, 7), itr.position());
   EXPECT_EQ(7, *itr);
}

TEST(CartographTest, IterateFromBeginToEnd)
{
   Cartograph<int32_t> c(Rectangle(3, 6, 3, 5), 99);
   size_t expectedCount = 3*5;
   size_t count = 0;

   Cartograph<int32_t>::iterator itr = c.begin();
   for(; itr != c.end(); ++itr)
   {
      ++count;

      ASSERT_TRUE(c.inRange(itr.position()));
      ASSERT_EQ(99, *itr);
   }
   EXPECT_EQ(expectedCount, count);
}
