#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#define SDL_DEFAULT_FLAGS SDL_HWSURFACE | SDL_DOUBLEBUF

#include "GGEElement.hpp"
#include <libguile.h>
#include <SDL/SDL.h>

class Display : public GGEElement{
  private:
    SDL_Surface *m_pScreen;

    Display();
    void initGuile();

  public:
    static Display* get() {
      static Display instance;
      return &instance;
    }

    static SCM scm_init_graphics(SCM window_size);
    static SCM scm_quit_graphics();
};

#endif
