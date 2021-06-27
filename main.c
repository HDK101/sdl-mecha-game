#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window *window = NULL;

SDL_Surface *screenSurface = NULL;

SDL_Surface *gHelloWorld = NULL;

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL Could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  else {
    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
    else {
      screenSurface = SDL_GetWindowSurface(window);
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;

  gHelloWorld = SDL_LoadBMP("tes.bmp");
  if (!gHelloWorld) {
    printf("Unable to load image %s\n", SDL_GetError());
    success = false;
  }
  
  return success;
}

void terminate() {
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();
}

int main(int argc, char* args[]) {
  if(!init()) {
    printf("Failed to initialize\n");    
  }
  else {
    if (!loadMedia()) {
      printf("Failed to load BMP\n");
    }
    else {
      bool quit = false;
      SDL_Event e;

      while (!quit) {
        SDL_BlitSurface(gHelloWorld, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(16);
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
          else if (e.type == SDL_KEYDOWN) {
            printf("KeyCode: %d\n", e.key.keysym.sym);
          }
        }
      }
    }
  }

  terminate();

  return 0;
}
