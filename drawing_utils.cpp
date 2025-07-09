#include "drawing_utils.h"

void DrawCircle(SDL_Renderer *Renderer, int32_t _x, int32_t _y, int32_t radius)
{
   int32_t x = radius - 1;
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t err = tx - (radius << 1); // shifting bits left by 1 effectively
                                 // doubles the value. == tx - diameter
   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(Renderer, _x + x, _y - y);
      SDL_RenderDrawPoint(Renderer, _x + x, _y + y);
      SDL_RenderDrawPoint(Renderer, _x - x, _y - y);
      SDL_RenderDrawPoint(Renderer, _x - x, _y + y);
      SDL_RenderDrawPoint(Renderer, _x + y, _y - x);
      SDL_RenderDrawPoint(Renderer, _x + y, _y + x);
      SDL_RenderDrawPoint(Renderer, _x - y, _y - x);
      SDL_RenderDrawPoint(Renderer, _x - y, _y + x);

      if (err <= 0)
      {
         y++;
         err += ty;
         ty += 2;
      }
      if (err > 0)
      {
         x--;
         tx += 2;
         err += tx - (radius << 1);
      }
   }
}
