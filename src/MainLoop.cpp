#include "MainLoop.hpp"

MainLoop::MainLoop() {}

MainLoop::initGuile() {
  scm_c_define_gsubr("main-loop", 0, 0, 0, (SCM (*)()) scm_main_loop);
}

SCM scm_main_loop() {
#ifdef WITH_SDL
  SDL_Event e;
  int curTime = 0;
  int lastTime = 0;
  while (m_bRunning) {
    SDL_PollEvent(&e);
    /* Handle events */
    if (event.type == SDL_QUIT) {
      m_bRunning = false;
      break;
    }
    get()->handleEvents(e);
    /* Wait a bit */
    curTime = SDL_GetTicks();
    if (curTime - lastTime > DELAY_BETWEEN_FRAMES) {
      get()->callDrawHooks();
      lastTime = curTime;
    }
    else 
      SDL_Delay(DELAY_BETWEEN + lastTime - curTime);
  }
#endif
}
