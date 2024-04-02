#include "csts.hpp"

const int FPS = 60;
const int FRAMEDELAY = 1000 / FPS;
const int SCREEN_HEIGHT = 448;
const int SCREEN_WIDTH = 608;
const int MAX_LINE_SIZE = 1024;
const int POSINIT = (SCREEN_WIDTH / 2) - 16;
const int MAX = 17;
const int NUMTOMATCH = 3;

SDL_Texture *Globalcolors[4][4];
SDL_Texture *destruction;
