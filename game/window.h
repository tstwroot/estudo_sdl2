#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL2/SDL.h>

class Window
{
public:
  Window(std::string title);
private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  std::string title;
};

#endif // WINDOW_H
