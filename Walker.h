#pragma once

#include "usr/include/SDL2/SDL.h"
#include "usr/include/SDL2/SDL2_gfxPrimitives.h"


class Walker {
  int _x, _y;
public:
  Walker(int x, int y) {
    _x = x;
    _y = y;
  }

  void draw(SDL_Renderer* renderer)
  {
    static Sint16 vx[] = { 100, 300, 200 };
	  static Sint16 vy[] = { 100, 100, 300 };

    vx[0]+= _x;
    vx[1]+= _x;
    vx[2]+= _x;

    vy[0]+= _y;
    vy[1]+= _y;
    vy[2]+= _y;

    filledCircleColor(renderer, _x, _y, 5, 0xFFFF0000); 
   // filledPolygonColor(renderer, vx, vy, 3, 0xFFFF0000);

  }

  void step() {
    _x++;
    _y++;
  }
};