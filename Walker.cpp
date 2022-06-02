#include "Walker.h"
#include <random>

// 시드값을 얻기 위한 random_device 생성.
std::random_device rd;

// random_device 를 통해 난수 생성 엔진을 초기화 한다.
std::mt19937 gen(rd());

// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
std::uniform_int_distribution<int> dis(0, 3);

Walker::Walker(int x, int y) 
{
  _x = x;
  _y = y;
}

void Walker::update() 
{
  /*
  int choice = dis(gen);
  if (choice == 0) {
    _x++;
  } else if (choice == 1) {
    _x--;
  } else if (choice == 2) {
    _y++;
  } else {
    _y--;
  }
  */
}

void Walker::draw(SDL_Renderer* renderer)
{
 filledCircleColor(renderer, _x, _y, 1, 0xFFFFFF00); 
}
