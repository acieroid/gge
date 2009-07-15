#ifdef WITH_GRAPHICS
#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include "GGEElement.hpp"
#include <libguile.h>

#ifdef WITH_SDL
/* About 60 FPS */
#define DELAY_BETWEEN_FRAMES 16
#include <SDL.h>
#endif

class MainLoop : public GGEElement {
  private:
    bool m_bRunning;
    MainLoop();
    void initGuile();

    static SCM scm_main_loop();
  public:
    static MainLoop* get() {
      static MainLoop instance;
      return &instance;
    }
};

#endif
#endif
