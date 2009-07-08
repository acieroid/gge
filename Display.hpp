#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#define SDL_DEFAULT_FLAGS SDL_HWSURFACE | SDL_DOUBLEBUF

#include <libguile.h>

#include <SDL/SDL.h>

class Display {
  friend class ScriptManager;
  private:
    SDL_Surface *m_pScreen;

    Display();

    static Display* get() {
      static Display instance;
      return &instance;
    }

    static void initGuileFunctions();
  public:

    static SCM scm_init_graphics(SCM window_size);
    static SCM scm_quit_graphics();
};

#endif
