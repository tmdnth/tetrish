#include "libtcod.hpp"
#include "Tile.h"

class Tetris {

    int DIM_X;
    int DIM_Y;

    TCODConsole* field;

    Tetro* curTetro;

	int speed;

	public:
		Tetris(int, int);

	private:
		void drawHUD();
        void setupGame();
        void runGame();
};