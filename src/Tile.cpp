#include "Tile.h"

Tile::Tile(int x, int y, int t, TCODConsole* f) {
	xPos = x;
	yPos = (float) y;
	tileType = t;
	field = f;
}

/*
*	Returns true on a successul downwards movement
*/
bool Tile::framePass(int speed) {
	float newYPos = yPos + TCODSystem::getLastFrameLength() * speed;
	if((int) newYPos >= 21 || field->getChar(xPos - 1, (int) newYPos - 1) == 'X') {
		return false;
	} else {
		return true;
	}
}

void Tile::updateYPos(int speed) {
	yPos += TCODSystem::getLastFrameLength() * (float) speed;
}

void Tile::moveX(bool toRight) {
	if(toRight) {
		xPos++;
	} else {
		xPos--;
	}
}

int Tile::getXCell() {
	return (int) xPos;
}

int Tile::getYCell() {
	return (int) yPos;
}

Tetro::Tetro(int x, int y, int t, TCODConsole* f) {
	xPos = x;
	yPos = (float) y;
	tetroType = t;
	field = f;
	switch(tetroType) {
		case 0 : parts[0] = new Tile(xPos, yPos, 0, field);
				 parts[1] = new Tile(xPos + 1, yPos, 0, field);
				 parts[2] = new Tile(xPos, yPos + 1, 0, field);
				 parts[3] = new Tile(xPos + 1, yPos + 1, 0, field);
			break;
		case 1 : parts[0] = new Tile(xPos - 1, yPos, 0, field);
				 parts[1] = new Tile(xPos, yPos, 0, field);
				 parts[2] = new Tile(xPos + 1, yPos, 0, field);
				 parts[3] = new Tile(xPos + 2, yPos, 0, field);
			break;
		case 2 : parts[0] = new Tile(xPos, yPos, 0, field);
				 parts[1] = new Tile(xPos + 1, yPos, 0, field);
				 parts[2] = new Tile(xPos + 1, yPos + 1, 0, field);
				 parts[3] = new Tile(xPos + 2, yPos + 1, 0, field);
			break;
		case 3 : parts[0] = new Tile(xPos - 1, yPos + 1, 0, field);
				 parts[1] = new Tile(xPos, yPos + 1, 0, field);
				 parts[2] = new Tile(xPos, yPos, 0, field);
				 parts[3] = new Tile(xPos + 1, yPos, 0, field);
			break;
		case 4 : parts[0] = new Tile(xPos - 1, yPos, 0, field);
				 parts[1] = new Tile(xPos, yPos, 0, field);
				 parts[2] = new Tile(xPos + 1, yPos, 0, field);
				 parts[3] = new Tile(xPos, yPos + 1, 0, field);
			break;
		case 5 : parts[0] = new Tile(xPos - 1, yPos, 0, field);
				 parts[1] = new Tile(xPos, yPos, 0, field);
				 parts[2] = new Tile(xPos + 1, yPos, 0, field);
				 parts[3] = new Tile(xPos - 1, yPos + 1, 0, field);
			break;
		case 6 : parts[0] = new Tile(xPos - 1, yPos, 0, field);
				 parts[1] = new Tile(xPos, yPos, 0, field);
				 parts[2] = new Tile(xPos + 1, yPos, 0, field);
				 parts[3] = new Tile(xPos + 1, yPos + 1, 0, field);
			break;
		default : parts[0] = new Tile(0, 0, 0, field);
				  parts[1] = new Tile(0, 0, 0, field);
				  parts[2] = new Tile(0, 0, 0, field);
				  parts[3] = new Tile(0, 0, 0, field);
			break;
	}
}

bool Tetro::framePass(int speed) {
	bool allSuccessful = true;
	for(int i = 0; i < 4; i++) {
		if(! parts[i]->framePass(speed)) {
			allSuccessful = false;
		}
	}
	if(allSuccessful) {
		for(int i = 0; i < 4; i++) {
			parts[i]->updateYPos(speed);
		}
		return true;
	} else {
		for(int i = 0; i < 4; i++) {
			field->putChar(parts[i]->getXCell() - 1, parts[i]->getYCell() - 1, 'X');
		}
		return false;
	}
}

/*
				*	0 = O
				*	1 = I
				*	2 = Z
				*	3 = S
				*	4 = T
				*	5 = L
				*	6 = -L
				*/
bool Tetro::rotate(bool clockwise) {
	switch(tetroType) {
		case 0 : return true;
			break;
		case 1 :
			break;
		case 2 : 
			break;
		case 3 : 
			break;
		case 4 : 
			break;
		case 5 : 
			break;
		case 6 : 
			break;
		default : 
			break;
	}
	return false;
}

void Tetro::moveX(bool toRight) {
	int n = 0;
	for(int i = 0; i < 4; i++) {
		if(toRight && parts[i]->getXCell() < 10 && field->getChar(parts[i]->getXCell(), parts[i]->getYCell() - 1) != 'X') {
			n++;
		}
		if(!toRight && parts[i]->getXCell() > 1 && field->getChar(parts[i]->getXCell() - 2, parts[i]->getYCell() - 1) != 'X') {
			n++;
		}
	}

	if(n == 4) {
		for(int i = 0; i < 4; i++) {
			parts[i]->moveX(toRight);
		}
	}
}

Tile** Tetro::getTiles() {
	return parts;
}