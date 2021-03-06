#ifdef WITH_GRAPHICS
#include "Display.hpp"
#include <cstdio>

Display::Display() {
  m_pScreen = NULL;
}

void Display::initGuile() {
	/* Functions */
  scm_c_define_gsubr("init-graphics", 1, 0, 0, (SCM (*)()) scm_init_graphics);
  scm_c_define_gsubr("quit-graphics", 0, 0, 0, (SCM (*)()) scm_quit_graphics);
	scm_c_define_gsubr("update-graphics", 0, 0, 0, (SCM (*)()) scm_update_graphics);

	/* Smobs */
	m_tImageTag = scm_make_smob_type ("image", sizeof(struct image));
	scm_set_smob_mark(m_tImageTag, mark_image);
	scm_set_smob_free(m_tImageTag, free_image);
	scm_c_define_gsubr("load-image", 1, 0, 0, (SCM (*)()) scm_load_image);
	scm_c_define_gsubr("draw-image", 2, 0, 0, (SCM (*)()) scm_draw_image);
}

SCM Display::mark_image(SCM image) {
	struct image *img = (struct image *) SCM_SMOB_DATA(image);
#ifdef WITH_SDL
	/* better than calling scm_gc_mark */
	std::cout << "Mark !\n";
	return (SCM) img->surface; 
#endif
}

size_t Display::free_image(SCM image) {
  struct image *img = (struct image *) SCM_SMOB_DATA(image);
#ifdef WITH_SDL
	std::cout << "Free !\n";
	SDL_FreeSurface(img->surface);
	/*scm_gc_free(img->surface, sizeof(SDL_Surface), "SDL surface");*/
	scm_gc_free(img, sizeof(struct image), "image");
#endif
	return 0;
}

SCM Display::scm_load_image(SCM file) {
	SCM smob;
#ifdef WITH_SDL
	struct image *img = (struct image *) scm_gc_malloc(sizeof(struct image), "image");

	img->surface = IMG_Load(scm_to_locale_string(file));
	if (!img->surface) {
		std::cout << "Error loading image : "
							<< IMG_GetError() << std::endl;
	}
#endif
	SCM_NEWSMOB(smob, get()->m_tImageTag, img);
	return smob;
}

SCM Display::scm_draw_image(SCM image, SCM pos) {
#ifdef WITH_SDL
	struct image *img = (struct image *) SCM_SMOB_DATA(image);
	SDL_Rect p;
	p.x = scm_to_int(scm_car(pos));
	p.y = scm_to_int(scm_cadr(pos));
	printf("%d, %d", img->surface, NULL);
	SDL_BlitSurface(img->surface, NULL, get()->m_pScreen, &p); 
#endif
}

SCM Display::scm_update_graphics() {
#ifdef WITH_SDL
  SDL_Flip(get()->m_pScreen);
	/* Clean the screen for the next update */
  SDL_FillRect(get()->m_pScreen, NULL, SDL_MapRGB(get()->m_pScreen->format, 0, 0, 0));
#endif
}

SCM Display::scm_init_graphics(SCM size) {
#ifdef WITH_SDL
	SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = NULL;
  screen = SDL_SetVideoMode(scm_to_uint(scm_car(size)),
                            scm_to_uint(scm_cadr(size)), 32,
                            SDL_DEFAULT_FLAGS);
	if (screen == NULL) {
		/* TODO: handle errors like this */
		std::cout << "Can't init SDL\n";
		exit(0);
	}
	get()->m_pScreen = screen;
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
#endif
}

SCM Display::scm_quit_graphics() {
#ifdef WITH_SDL
  if (get()->m_pScreen != NULL)
    SDL_Quit();
#endif
}

#endif
