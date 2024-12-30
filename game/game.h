#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <string>

enum game_state
{
  GAME_RUNNING,
  GAME_EXIT,
};

class game
{
public:
  game(std::string title);

  // Game loop functions
  void input();
  void update();
  void draw();
  void free();
  
  // Seters
  void set_background_color(SDL_Color color) { this->background_color = color; }

  // Geters
  bool get_current_game_state() { return game_state; }
private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_RendererInfo renderer_info;
  SDL_Event event;
  std::string title;
  std::string renderer_name;
  std::string vendor;
  enum game_state game_state;
  SDL_Color background_color;
};

#endif // GAME_H
