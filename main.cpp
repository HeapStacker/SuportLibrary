#include "algorithms.h"
using namespace mt_algorithms;

int main(void) {
  int width = 40, height = 35;
  maze lab(width, height, {0,1});
  lab.displayMaze();
  return 0;
}