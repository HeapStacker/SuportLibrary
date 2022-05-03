#include "textAndTimeSuport.h"
#include "vectorSuport.h"

using namespace mt_text_time;

namespace mt_algorithms {
    class maze {
        int labyrinth[70][70], width, height;
    public:
        maze(int width, int height, pair<int, int> entrance);
        void alocateMaze();
        void generatePath(pair<int, int> entrance);
        bool checkAvailability(int posX, int posY);  
        void displayMaze();  
    };
}
