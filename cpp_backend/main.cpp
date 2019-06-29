#include "gol/gol.h"

int main() {
  using namespace std;

  GameOfLife::bool_matrix matr = {
      {0, 0, 0, 1, 0, 1, 1, 1, 0, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 1, 0, 1, 0, 0, 0, 0, 0, 1}, {0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0, 1, 0, 1, 0},
      {1, 1, 0, 1, 0, 0, 0, 1, 1, 1}, {1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
      {1, 0, 1, 1, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 1, 1, 1, 1, 1}};

  GameOfLife g(matr);
  g.PrinState();
  cout << "\n";
  g.OneStep();
  g.PrinState();
  cout << "\n";
  g.OneStep();
  g.PrinState();
  cout << "\n";
  g.OneStep();
  g.PrinState();
  cout << "\n";

  return 0;
}