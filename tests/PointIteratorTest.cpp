#include "gtest/gtest.h"
#include "common/PointIterator.h"

using namespace squidge;

TEST(PointIteratorTest, RectCtor)
{
   Rectangle r(3, 6, 5, 5);
   Point p(3,6);

   PointIterator itr(r);

   EXPECT_EQ(p, *itr);
}

TEST(PointIteratorTest, RectPointCtor)
{
   Rectangle r(3, 6, 5, 5);
   Point p(4, 8);
   Point p2(4, 8);

   PointIterator itr(r, p);

   EXPECT_EQ(p2, *itr);
}

TEST(PointIteratorTest, CopyCtor)
{
   Rectangle r(3, 6, 5, 5);
   Point p(5, 6);

   PointIterator itr1(r, p);
   PointIterator itr2(itr1);

   EXPECT_EQ(*itr1, *itr2);
   EXPECT_EQ(itr1, itr2);
}

TEST(PointIteratorTest, Assignment)
{
   Rectangle r(3, 6, 5, 5);
   Point p(5, 6);

   PointIterator itr1(r, p);
   PointIterator itr2;
   itr2 = itr1;

   EXPECT_EQ(*itr1, *itr2);
   EXPECT_EQ(itr1, itr2);
}

TEST(PointIteratorTest, SelfAssignment)
{
   Rectangle r(3, 6, 5, 5);
   Point p(5, 6);

   PointIterator itr(r, p);
   itr = itr;

   EXPECT_EQ(PointIterator(r,p), itr);
}

TEST(PointIteratorTest, SimplePostfixIncrement)
{
   Rectangle r(3, 6, 5, 5);
   Point p(3, 6);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(3, 6), *itr);
   EXPECT_EQ(Point(3, 6), *(itr++));
   EXPECT_EQ(Point(4, 6), *itr);
}

TEST(PointIteratorTest, SimplePrefixIncrement)
{
   Rectangle r(3, 6, 5, 5);
   Point p(3, 6);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(3, 6), *itr);
   EXPECT_EQ(Point(4, 6), *(++itr));
   EXPECT_EQ(Point(4, 6), *itr);
}

TEST(PointIteratorTest, SimplePostfixDecrement)
{
   Rectangle r(3, 6, 5, 5);
   Point p(4, 6);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(4, 6), *itr);
   EXPECT_EQ(Point(4, 6), *(itr--));
   EXPECT_EQ(Point(3, 6), *itr);
}

TEST(PointIteratorTest, SimplePrefixDecrement)
{
   Rectangle r(3, 6, 5, 5);
   Point p(4, 6);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(4, 6), *itr);
   EXPECT_EQ(Point(3, 6), *(--itr));
   EXPECT_EQ(Point(3, 6), *itr);
}

TEST(PointIteratorTest, IncrementSequenceNoWrap)
{
   Rectangle r(3, 6, 10, 5);
   Point p(4, 6);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(4,6), *itr);
   itr++;
   EXPECT_EQ(Point(5,6), *itr);
   itr++;
   EXPECT_EQ(Point(6,6), *itr);
   itr++;
   EXPECT_EQ(Point(7,6), *itr);
   itr++;
   EXPECT_EQ(Point(8,6), *itr);
}

TEST(PointIteratorTest, IncrementSequenceWithWrap)
{
   Rectangle r(3, 6, 3, 5);
   Point p(4, 6);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(4,6), *itr);
   itr++;
   EXPECT_EQ(Point(5,6), *itr);
   itr++;
   EXPECT_EQ(Point(3,7), *itr);
   itr++;
   EXPECT_EQ(Point(4,7), *itr);
   itr++;
   EXPECT_EQ(Point(5,7), *itr);
}

TEST(PointIteratorTest, DecrementSequenceNoWrap)
{
   Rectangle r(3, 6, 10, 5);
   Point p(9, 6);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(9,6), *itr);
   itr--;
   EXPECT_EQ(Point(8,6), *itr);
   itr--;
   EXPECT_EQ(Point(7,6), *itr);
   itr--;
   EXPECT_EQ(Point(6,6), *itr);
   itr--;
   EXPECT_EQ(Point(5,6), *itr);
}

TEST(PointIteratorTest, DecrementSequenceWithWrap)
{
   Rectangle r(3, 3, 3, 5);
   Point p(4, 6);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(4,6), *itr);
   itr--;
   EXPECT_EQ(Point(3,6), *itr);
   itr--;
   EXPECT_EQ(Point(5,5), *itr);
   itr--;
   EXPECT_EQ(Point(4,5), *itr);
   itr--;
   EXPECT_EQ(Point(3,5), *itr);
}

TEST(PointIteratorTest, Reversability)
{
   Rectangle r(3, 3, 3, 3);
   Point p(4, 4);

   PointIterator itr(r, p);

   EXPECT_EQ(Point(4, 4), *itr);
   itr++;
   EXPECT_EQ(Point(5, 4), *itr);
   itr++;
   EXPECT_EQ(Point(3, 5), *itr);
   itr++;
   EXPECT_EQ(Point(4, 5), *itr);
   itr--;
   EXPECT_EQ(Point(3, 5), *itr);
   itr--;
   EXPECT_EQ(Point(5, 4), *itr);
   itr--;
   EXPECT_EQ(Point(4, 4), *itr);
}
