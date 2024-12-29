#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <unistd.h>

enum state
{
  NONE,
  RUNNING,
  REQUEST_CLOSE_WINDOW
};

struct global
{
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;
  int w_width;
  int w_height;
  double gravity;
  enum state state;
}
global = {
  .w_width = 500,
  .w_height = 500,
  .gravity = 1.08
};

struct object
{
  SDL_Rect rect;
  SDL_Color color;
  double h_velocity;
  double v_velocity;
  bool is_dragging;
  bool in_ground;
  SDL_Point displacement;
}
object = {
  .rect = {50, 50, 50, 50},
  .color = {0x00, 0xff, 0x00, 0xff},
  .h_velocity = 0,
  .v_velocity = 0,
  .is_dragging = false,
  .displacement = {0, 0},
  .in_ground = false
};

int main(int argc, char **argv)
{
  printf("%d\n", getpid());
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return -1;
  }

  global.window = SDL_CreateWindow(
    "Rect",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    global.w_width,
    global.w_height, 
    SDL_WINDOW_RESIZABLE
    | SDL_WINDOW_ALLOW_HIGHDPI
  );

  if(global.window == NULL)
  {
    fprintf(stderr, "Error: global.window can not be created.\n");
    SDL_Quit();
    return -1;
  }

  global.renderer = SDL_CreateRenderer(
    global.window,
    -1,
    SDL_RENDERER_ACCELERATED
    | SDL_RENDERER_PRESENTVSYNC
  );

  if(global.renderer == NULL)
  {
    fprintf(stderr, "Error: global.renderer can not be created.\n");
    SDL_Quit();
    return -1;
  }

  SDL_RendererInfo renderer_info;
  SDL_GetRendererInfo(global.renderer, &renderer_info);

  printf("Render: %s\n", renderer_info.name);
  printf("Hardware Accelerated: %s\n", (renderer_info.flags & SDL_RENDERER_ACCELERATED) ? "Sim" : "Não");
  const char *renderer = (const char *)glGetString(GL_RENDERER);
  const char *vendor = (const char *)glGetString(GL_VENDOR);
  printf("Graphics card: %s\n", renderer);
  printf("Vendor: %s\n", vendor);

  while(global.state != REQUEST_CLOSE_WINDOW)
  {
    while(SDL_PollEvent(&global.event))
    {
      if(object.rect.y + object.rect.h < global.w_height)
        object.in_ground = false;

      switch(global.event.type)
      {
        case SDL_QUIT:
          puts("Requested close.");
          global.state = REQUEST_CLOSE_WINDOW;
          break;
        case SDL_WINDOWEVENT:
          if(global.event.window.event == SDL_WINDOWEVENT_RESIZED
            || global.event.window.event == SDL_WINDOWEVENT_RESTORED)
          {
            if(object.rect.y + object.rect.h > global.w_height)
              object.rect.y = global.w_height - object.rect.y;

            SDL_GetWindowSize(global.window, &global.w_width, &global.w_height);
            printf("[LOG]: resize window. (w:%d h:%d)\n", global.w_width, global.w_height); 
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          if(SDL_PointInRect(&(const SDL_Point){global.event.button.x, global.event.button.y}, &object.rect))
          {
            object.displacement.x = global.event.button.x - object.rect.x;
            object.displacement.y = global.event.button.y - object.rect.y;
            object.is_dragging = true;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          object.is_dragging = false;
          object.displacement.x = 0;
          object.displacement.y = 0;
          break;
        case SDL_MOUSEMOTION:
          if(object.is_dragging == true)
          {
            if(object.rect.y + object.rect.h < global.w_height)
              object.in_ground = false;         

            if(global.event.button.x - object.displacement.x > 0 
              && global.event.button.x - object.displacement.x < global.w_width - object.rect.w 
              && global.event.button.y - object.displacement.y > 0 
              && global.event.button.y - object.displacement.y < global.w_height - object.rect.h) 
            {
              object.rect.x = global.event.button.x - object.displacement.x;
              object.rect.y = global.event.button.y - object.displacement.y;
            }
          }
        default:
          break;
      } 
    }

    if(object.in_ground == false && object.is_dragging == false)
    {
      object.h_velocity += 0.1;
      object.h_velocity *= global.gravity;
      if(object.rect.y + object.h_velocity > global.w_height - object.rect.h)
        object.rect.y = global.w_height - object.rect.h;
      else
        object.rect.y += object.h_velocity;

      if(object.rect.y + object.rect.h >= global.w_height)
      { 
        object.in_ground = true;
        object.h_velocity = 0;
      }
    }

    SDL_SetRenderDrawColor(global.renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(global.renderer);
    SDL_SetRenderDrawColor(global.renderer, object.color.r, object.color.g, object.color.b, object.color.a);
    SDL_RenderFillRect(global.renderer, &object.rect);
    SDL_RenderPresent(global.renderer);
  }
  
  SDL_DestroyWindow(global.window);
  SDL_DestroyRenderer(global.renderer);
  SDL_Quit();
  return 0;
}
