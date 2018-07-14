#include "SDL/SDL.h"










int main(){
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Surface* screen = SDL_SetVideoMode(512, 512, 32, 0);

  SDL_Flip(screen);
  SDL_Delay(500);
  SDL_Quit();
}
