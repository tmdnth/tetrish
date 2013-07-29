#include "libtcod.hpp"

class Tile {
	int xPos;
	float yPos;
	TCODConsole * field;

	int tileType;

	public:
		Tile(int, int, int, TCODConsole*);
		bool framePass(int);
		void moveX(bool);
		int getXCell();
		int getYCell();
		void updateYPos(int);
};

class Tetro {
	Tile * parts [4];
	TCODConsole * field;
	int xPos;
	float yPos;

	int tetroType;	/*
				*	0 = O
				*	1 = I
				*	2 = Z
				*	3 = S
				*	4 = T
				*	5 = L
				*	6 = -L
				*/
	public:
		Tetro(int, int, int, TCODConsole*);
		bool framePass(int);
		void moveX(bool);
		bool rotate(bool);
		Tile** getTiles(); 
};