#include "Tetris.h"

Tetris::Tetris(int dimX, int dimY) {
    DIM_X = dimX;
    DIM_Y = dimY;

    setupGame();
    runGame();
}

void Tetris::setupGame() {
	TCODConsole::setCustomFont("urr12.png", TCOD_FONT_LAYOUT_ASCII_INROW, 0, 0);
    TCODConsole::initRoot(DIM_X, DIM_Y, "Tetris", false);
    TCODConsole::setKeyboardRepeat(80, 30);
    field = new TCODConsole(10, 20);

    TCODSystem::setFps(333);

    TCODRandom::getInstance();

    curTetro = NULL;

    speed = 7;
}

void Tetris::runGame() {
	while ( !TCODConsole::isWindowClosed() ) {
    	TCODConsole::root->clear();

        if(curTetro == NULL) {
            curTetro = new Tetro(5, 1, TCODRandom::getInstance()->getInt(0, 6), field);
        }

    	drawHUD();
        TCODConsole::root->print(5, 2, "FPS: %f", 1.0f / TCODSystem::getLastFrameLength());
    	TCODConsole::root->print(5, 4, "Speed: %i", speed);

        for (int xf = 0; xf < 10; xf++) {
            for (int yf = 0; yf < 20; yf++) {
                if(field->getChar(xf, yf) == 'X') {
                    TCODConsole::root->putChar(6 + xf * 2, 6 + yf * 2, 'O');
                    TCODConsole::root->putChar(6 + xf * 2 + 1, 6 + yf * 2, 'O');
                    TCODConsole::root->putChar(6 + xf * 2, 6 + yf * 2 + 1, 'O');
                    TCODConsole::root->putChar(6 + xf * 2 + 1, 6 + yf * 2 + 1, 'O');
                }
            }
        }

        /* Display all Tiles of the current Tetro here */
        for(int i = 0; i < 4; i++) {
            TCODConsole::root->putChar(6 + (curTetro->getTiles()[i]->getXCell() - 1) * 2, 6 + (curTetro->getTiles()[i]->getYCell() - 1) * 2, 'X');
            TCODConsole::root->putChar(6 + (curTetro->getTiles()[i]->getXCell() - 1) * 2 + 1, 6 + (curTetro->getTiles()[i]->getYCell() - 1) * 2, 'X');
            TCODConsole::root->putChar(6 + (curTetro->getTiles()[i]->getXCell() - 1) * 2, 6 + (curTetro->getTiles()[i]->getYCell() - 1) * 2 + 1, 'X');
            TCODConsole::root->putChar(6 + (curTetro->getTiles()[i]->getXCell() - 1) * 2 + 1, 6 + (curTetro->getTiles()[i]->getYCell() - 1) * 2 + 1, 'X');
        }

        TCODConsole::root->flush();

        if(! curTetro->framePass(speed)) {
            curTetro = NULL;
            continue;
        }

    	TCOD_key_t key = TCODConsole::checkForKeypress(TCOD_KEY_PRESSED);
    	if(key.vk != TCODK_NONE) {
    		switch(key.c) {
    			case 'q' : exit(0);
                    break;
    			case 'k' : curTetro->moveX(false);
                    break;
    			case 'l' : curTetro->moveX(true);
                    break;
                case 'a' : curTetro->rotate(false);
                    break;
                case 's' : curTetro->rotate(true);
                    break;
    			case 'r' : speed++;
                    break;
    			case 'f' : speed--;
                    break;
    			default : break;
    		}
    	}
   	}
}

void Tetris::drawHUD() {
	for(int i = 5; i < 27; i++) {
        TCODConsole::root->putChar(i, 5, 196);
        TCODConsole::root->putChar(i, 46, 196);
    }
    for(int i = 5; i < 47; i++) {
        TCODConsole::root->putChar(5, i, 179);
        TCODConsole::root->putChar(26, i, 179);
    }
    TCODConsole::root->putChar(5, 5, 218);
    TCODConsole::root->putChar(26, 5, 191); 
    TCODConsole::root->putChar(5, 46, 192);
    TCODConsole::root->putChar(26, 46, 217);

    TCODConsole::root->setDefaultForeground(TCODColor::darkestGrey);

    for(int x = 0; x < 10; x++) {
        for(int y = 0; y < 20; y++) {
            TCODConsole::root->putChar(6 + x * 2, 6 + y * 2, 201);
            TCODConsole::root->putChar(6 + x * 2 + 1, 6 + y * 2, 187); 
            TCODConsole::root->putChar(6 + x * 2, 6 + y * 2 + 1, 200);
            TCODConsole::root->putChar(6 + x * 2 + 1, 6 + y * 2 + 1, 188);
        }
    }

    TCODConsole::root->setDefaultForeground(TCODColor::white);
}