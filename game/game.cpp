#include "game.h"
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>

Game::Game()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) 
  {
    std::cerr << "Error: " << SDL_GetError() << "\n";
    ::exit(EXIT_FAILURE);
  }

  window = new Window();
}

void Game::input()
{

}

void Game::update()
{

}

void Game::draw()
{

}

void Game::free()
{

}
