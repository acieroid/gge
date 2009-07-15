#include "MainLoop.hpp"
#include <iostream>

MainLoop::MainLoop() {}

void MainLoop::initGuile() {
  scm_c_define_gsubr("main-loop", 0, 0, 0, (SCM (*)()) scm_main_loop);
}

SCM MainLoop::scm_main_loop() {
#ifdef WITH_SDL
  SDL_Event e;
  int curTime = 0;
  int lastTime = 0;
  get()->m_bRunning = true;
  while (get()->m_bRunning) {
    SDL_PollEvent(&e);
    /* Handle events */
    if (e.type == SDL_QUIT) {
      get()->m_bRunning = false;
      break;
    }
    //get()->handleEvents(e);
    /* Wait a bit */
    curTime = SDL_GetTicks();
    if (curTime - lastTime > DELAY_BETWEEN_FRAMES) {
      //get()->callDrawHooks();
      lastTime = curTime;
    }
    else 
      SDL_Delay(DELAY_BETWEEN_FRAMES + lastTime - curTime);
  }
#endif
}
