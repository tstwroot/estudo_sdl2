#ifndef GAME_H
#define GAME_H

#include "window.h"

#include <SDL2/SDL.h>
#include <string>

class Game
{
public:
  Game();
  void input();
  void update();
  void draw();
  void free();
private:
  Window *window = nullptr;
};

#endif // GAME_H
