#include "Display.hpp"

Display::Display() {
  m_pScreen = NULL;
}

void Display::initGuile() {
  scm_c_define_gsubr("init-graphics", 1, 0, 0, (SCM (*)()) scm_init_graphics);
  scm_c_define_gsubr("quit-graphics", 0, 0, 0, (SCM (*)()) scm_quit_graphics);
}

SCM Display::scm_init_graphics(SCM size) {
  SDL_Surface *screen = get()->m_pScreen;
  screen = SDL_SetVideoMode(scm_to_uint(scm_car(size)),
                            scm_to_uint(scm_cadr(size)), 32,
                            SDL_DEFAULT_FLAGS);
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
}

SCM Display::scm_quit_graphics() {
  if (get()->m_pScreen != NULL)
    SDL_Quit();
}

