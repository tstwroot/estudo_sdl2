#include "game.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <iostream>
#include <GL/gl.h>

game::game(std::string title)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
  {
    std::cerr << "Error: " << SDL_GetError() << "\n";
    SDL_Quit();
    ::exit(EXIT_FAILURE);
  }

  this->title = title;
  this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
  if(this->window == nullptr)
  {
    std::cerr << "window = nullptr. exiting...\n";
    SDL_Quit();
    ::exit(EXIT_FAILURE);
  }

  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(this->renderer == NULL)
  {
    std::cerr << "renderer == nullptr. exiting...\n";
    SDL_Quit();
    ::exit(EXIT_FAILURE);
  }

  std::cout << "[LOG]: Window has created with success.\n";

  SDL_GetRendererInfo(this->renderer, &renderer_info);

  std::cout << "Render: " << renderer_info.name << '\n';
  std::cout << "Hardware Accelerated: " << (renderer_info.flags & SDL_RENDERER_ACCELERATED ? "Yes" : "No") << '\n';
  this->renderer_name = (const char *)glGetString(GL_RENDERER);
  this->vendor = (const char *)glGetString(GL_VENDOR);
  std::cout << "Graphics card: " << this->renderer_name << '\n';
  std::cout << "Vendor: " << vendor << '\n';
}

void game::input()
{
   
}

void game::update()
{
  if(SDL_PollEvent(&event)) 
  {
    switch (event.type)
    {
      case SDL_QUIT:
        this->game_state = GAME_EXIT;
    }
  }
}

void game::draw()
{
  SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xff); 
  SDL_RenderClear(this->renderer);
  SDL_RenderPresent(this->renderer);
}

void game::free()
{
  SDL_DestroyWindow(this->window);
  SDL_DestroyRenderer(this->renderer);
  SDL_Quit();
}
