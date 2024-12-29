#include "game.h" 

int main()
{
  Game *game = new Game();

  while(true)
  {
    game->input();
    game->update();
    game->draw();
  }
  game->free();
  return 0;
}
