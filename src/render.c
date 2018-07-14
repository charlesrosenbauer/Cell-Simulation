#include "render.h"
#include "physics.h"
#include "SDL/SDL.h"










// Assumes screen is 512x512, fix this later
void drawCells(SDL_Surface* screen, PHYSICSBUFFER* cells){

  uint32_t* pix = screen->pixels;
  for(int i = 0; i < 262144; i++)
    pix[i] = 0;

  for(int i = 0; i < cells->size; i++){
    CELLOBJ* c = &cells->oldcellsobjs[i];
    int x = (c->x / 128) + 256;
    int y = (c->y / 128) + 256;
    pix[(512*y)+x] += (pix[(512*y)+x] >= 0xFF00)? 0 : 0x001000;
  }
}
