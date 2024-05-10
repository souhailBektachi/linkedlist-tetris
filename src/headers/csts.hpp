#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderWindow.hpp"
#ifndef CSTS_H
#define CSTS_H
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
extern const int MAX_LINE_SIZE;
extern const char WALLS_TYPES[8];
extern const int FPS;
extern const int FRAMEDELAY;
extern const int POSINIT;
extern const int MAX;
extern const int NUMTOMATCH;
extern SDL_Texture *Globalcolors[4][4];
extern SDL_Texture *destruction;
extern SDL_Texture *gradientTexture;
extern const char *FONTS[2];
extern SDL_Texture *GlobalIcons[10][2];
extern int BlocksUsed;
extern int HighScore;
#define HASH_SIZE 1000

#endif
