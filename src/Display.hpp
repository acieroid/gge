#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "GGEElement.hpp"
#include <libguile.h>
#include <iostream>

#define SDL_DEFAULT_FLAGS SDL_HWSURFACE | SDL_DOUBLEBUF
#include <SDL.h>
#include <SDL_image.h>

class Display : public GGEElement{
  private:
    SDL_Surface *m_pScreen;

    Display();
    void initGuile();

		/* Image smob */
		struct image {
		  SDL_Surface *surface;
		};

		scm_t_bits m_tImageTag;
		static SCM mark_image(SCM image);
		static size_t free_image(SCM image);
		static SCM scm_load_image(SCM file);
		static SCM scm_draw_image(SCM image, SCM pos);
		
  public:
    static Display* get() {
      static Display instance;
      return &instance;
    }

    static SCM scm_init_graphics(SCM window_size);
    static SCM scm_quit_graphics();
    static SCM scm_update_graphics();
};

#endif
