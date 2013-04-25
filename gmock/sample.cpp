#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
  return !b ? a : gcd( b, a% b);
}

TEST(gcd, gcd_test)
{
  EXPECT_EQ(2, gcd(4,6));
  EXPECT_EQ(100, gcd(100, 1000));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
