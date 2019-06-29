//
// Created by vlad on 28.06.19.
//
#include "../gol/gol.h"
#include <gtest/gtest.h>


static const GameOfLife::bool_matrix first_generation = {
        {0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, {0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 0, 1, 0, 0, 0, 0, 0, 1}};

TEST(GOL, test_next) {
  GameOfLife::bool_matrix matr = {
      {0, 0, 0, 1, 0, 1, 1, 1, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
      {1, 1, 0, 1, 0, 0, 0, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
      {1, 0, 1, 1, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 1, 1, 1, 1, 1}};



  GameOfLife g(matr);
  g.OneStep();
  ASSERT_EQ(g.get__state(), first_generation);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}