#include "algorithms.h"

namespace mt_algorithms {
  maze::maze(int width, int height, pair<int, int> entrance) {
    this->width = width;
    this->height = height;
    alocateMaze();
    labyrinth[entrance.second][entrance.first] = 3;
    generatePath(entrance);
    bool endFound = false;
    int randFlag = (int)getRandomNumber() % height;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (labyrinth[i][j] == 2) labyrinth[i][j] = 4;
        if (j == width - 1 && !endFound && labyrinth[i][j - 1] == 3 && i >= randFlag) {
          endFound = true;
          labyrinth[i][j] = 3;
        }
      }
    }
  }
  void maze::alocateMaze() {
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          labyrinth[i][j] = 2;
        }
      }
      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
            labyrinth[i][j] = 4;
          }
        }
      }
  }
  void maze::generatePath(pair<int, int> entrance) {
    stack<pair<int, int>> path;
    path.push(entrance);
    while(!path.empty()) {
      int flag = (int)getRandomNumber() % 4;
      pair<int, int> positions[] = {
        {path.top().first - 1, path.top().second},
        {path.top().first + 1, path.top().second},
        {path.top().first, path.top().second - 1},
        {path.top().first, path.top().second + 1}
      };
      int counter = 0;
      for (int i = flag; i < 4; i++) {
        if (checkAvailability(positions[i].first, positions[i].second)) {
          labyrinth[positions[i].second][positions[i].first] = 3;
          path.push(positions[i]);
          break;
        }
        if (i >= 3) i = 0;
        if (counter > 3) {
          path.pop();
          break;
        }
        counter++;
      }
    }
  } 
  bool maze::checkAvailability(int posX, int posY) {
    if (posX >= 0 && posX < 70 && posY >= 0 && posY < 70) {
      if (labyrinth[posY][posX] == 2) {
        int counter = 0;
        if (labyrinth[posY][posX - 1] == 3) counter++;
        if (labyrinth[posY][posX + 1] == 3) counter++;
        if (labyrinth[posY - 1][posX] == 3) counter++;
        if (labyrinth[posY + 1][posX] == 3) counter++;
        if (counter <= 1) {
          return true;
        }
      }
    }
    return false;
  }  
  void maze::displayMaze() {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (labyrinth[i][j] == 4)
          cout << "██";
        if (labyrinth[i][j] == 3) cout << "  ";
      }
      cout << endl;
    }
  } 
}
