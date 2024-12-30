#include "game.h" 

int main()
{
  game *_game = new game("Game");

  while(_game->get_current_game_state() != GAME_EXIT)
  {
    _game->input();
    _game->update();
    _game->draw();
  }
  _game->free();
  return 0;
}
