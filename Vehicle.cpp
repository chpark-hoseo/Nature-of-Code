#include "Vehicle.h"
#include "Game.h"
#include "InputHandler.h"

Vehicle::Vehicle(float x, float y) : pos(Vector2D(0,0)), vel(Vector2D(0,0)), acc(Vector2D(0,0)), maxSpeed(6), maxForce(0.4), r(16)
{
  SDL_Surface* pTempSurface = IMG_Load("Assets/arrow.png");
  mTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), pTempSurface);
  SDL_FreeSurface(pTempSurface);
}

Vector2D Vehicle::arrive(Vector2D target)
{
  return seek(target, true);
}

Vector2D Vehicle::seek(Vector2D target, bool arrival)
{
  Vector2D force = Vector2D(target.getX() - pos.getX(), target.getY() - pos.getY());
  float desiredSpeed = maxSpeed;
  if (arrival)
  {
    float slowRadius = 100;
    float distance = force.length();
    if (distance < slowRadius)
    {
      desiredSpeed = maxSpeed * distance / slowRadius;
    }
  }
  force.normalize();
  force *= desiredSpeed;
  force -= vel;

  if (force.length() > maxForce)
  {
    force.normalize();
    force *= maxForce;
  }

  return force;
}

void Vehicle::applyForce(Vector2D force)
{
  acc += force;
}

void Vehicle::update()
{
  vel += acc;
  if (vel.length() > maxSpeed)
  {
    vel.normalize();
    vel *= maxSpeed;
  }
  pos += vel;
  acc = Vector2D(0, 0);
}

void Vehicle::show()
{
  /*
  SDL_Rect srcRect;
  SDL_Rect destRect;
  srcRect.x = srcRect.y = 0;
  destRect.x = pos.getX() - 16;
  destRect.y = pos.getY() - 16;
  srcRect.w = srcRect.h = destRect.w = destRect.h = 32;
*/
  Vector2D* mousePos = TheInputHandler::Instance()->getMousePosition();
  float angle = atan2(mousePos->getY() - pos.getY(), mousePos->getX() - pos.getX()) ;//* 180 / 3.1415926535;

  Vector2D srcTriangleV1(-r, -r / 2); // 왼쪽 위
  Vector2D srcTriangleV2(-r, r / 2); // 왼쪽 아래
  Vector2D srcTriangleV3(r, 0); // 오른쪽
  
  Vector2D TriangleV1(srcTriangleV1.getX() * cos(angle) - srcTriangleV1.getY() * sin(angle), srcTriangleV1.getX() * sin(angle) +  srcTriangleV1.getY() * cos(angle));
  Vector2D TriangleV2(srcTriangleV2.getX() * cos(angle) - srcTriangleV2.getY() * sin(angle), srcTriangleV2.getX() * sin(angle) +  srcTriangleV2.getY() * cos(angle));
  Vector2D TriangleV3(srcTriangleV3.getX() * cos(angle) - srcTriangleV3.getY() * sin(angle), srcTriangleV3.getX() * sin(angle) +  srcTriangleV3.getY() * cos(angle));

  TriangleV1 += pos;
  TriangleV2 += pos;
  TriangleV3 += pos;
  
  filledTrigonRGBA(TheGame::Instance()->getRenderer(), TriangleV1.getX(), TriangleV1.getY(), TriangleV2.getX(), TriangleV2.getY(), TriangleV3.getX(), TriangleV3.getY(), 255, 255, 255, 255);

/*
  SDL_RenderCopyEx(TheGame::Instance()->getRenderer(), mTexture, &srcRect, &destRect, angle, 0, SDL_FLIP_NONE);
*/
}