#include "Game.h"
#include "InputHandler.h"

  Game* Game::s_pInstance = 0;

bool Game::init(const char *title, int xpos, int ypos, int width, int height, int flags) 
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL);
    if (m_pWindow != 0) {
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

      if (m_pRenderer != 0) {
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255); 
      } else {
        return false; // 랜더러 생성 실패
      }
    } else {
      return false; // 윈도우 생설 실패 l
    }
  } else {
    return false; // SDL 초기화 실패
  }

  m_bRunning = true;

  _walker = new Walker(10,10);

  return true;
}

void Game::update()
{
  _walker->step();
}

void Game::render()
{

  SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
  SDL_RenderClear(m_pRenderer);  

  _walker->draw(m_pRenderer);


  SDL_RenderPresent(m_pRenderer); 
}

bool Game::running()
{ 
   return m_bRunning; 
}

void Game::handleEvents() 
{
 TheInputHandler::Instance()->update();
}

void Game::clean() 
{
  delete _walker;
  
  TheInputHandler::Instance()->clean();
  
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}