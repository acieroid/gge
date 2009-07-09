#include "Display.hpp"

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
	/* better than calling scm_gc_mark */
	return (scm_unused_struct *) img->surface; 
}
size_t Display::free_image(SCM image) {
  struct image *img = (struct image *) SCM_SMOB_DATA(image);
	SDL_FreeSurface(img->surface);
	/*scm_gc_free(img->surface, sizeof(SDL_Surface), "SDL surface");*/
	scm_gc_free(img, sizeof(struct image), "image");
	return 0;
}
SCM Display::scm_load_image(SCM file) {
	SCM smob;
	struct image *img;
	img->surface = IMG_Load(scm_to_locale_string(file));

	SCM_NEWSMOB(smob, get()->m_tImageTag, img);
	return smob;
}
SCM Display::scm_draw_image(SCM image, SCM pos) {
	struct image *img = (struct image *) SCM_SMOB_DATA(image);
	SDL_Rect p;
	p.x = scm_to_int(scm_car(pos));
	p.y = scm_to_int(scm_cadr(pos));
	SDL_BlitSurface(img->surface, NULL, get()->m_pScreen, &p); 
}
SCM Display::scm_update_graphics() {
		SDL_Flip(get()->m_pScreen);
}

SCM Display::scm_init_graphics(SCM size) {
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
}

SCM Display::scm_quit_graphics() {
  if (get()->m_pScreen != NULL)
    SDL_Quit();
}

