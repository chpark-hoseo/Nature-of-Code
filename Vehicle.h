#pragma once
#include "Vector2D.h"
#include "usr/include/SDL2/SDL.h"

class Vehicle
{
public:
  Vehicle(float x, float y);

  Vector2D arrive(Vector2D target);
  Vector2D seek(Vector2D target, bool arrival = false);
  void applyForce(Vector2D force);
  void update();
  void show();

private:
  Vector2D pos = Vector2D(0,0);
  Vector2D vel = Vector2D(0,0);
  Vector2D acc = Vector2D(0,0);
  float maxSpeed;
  float maxForce;
  float r;

  SDL_Texture* mTexture;
};