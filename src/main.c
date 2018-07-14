#include "SDL/SDL.h"
#include "stdio.h"
#include "physics.h"
#include "render.h"










int main(){
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Surface* screen = SDL_SetVideoMode(512, 512, 32, 0);

  PHYSICSBUFFER* buff = randomBuffer(1000000);
  for(int i = 0; i < 600; i++){
    moveCells(buff);
    drawCells(screen, buff);

    SDL_Flip(screen);
    SDL_Delay(50);
  }

  SDL_Quit();
}
