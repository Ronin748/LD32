#include "Lib.h"

class Screen {
public:
	void InitScreen();

	bool fullscreen;

	int screen_w;
	int screen_h;

	int wndw_w;
	int wndw_h;

	float scale_x;
	float scale_y;

	SDL_Surface* icon;

	Point_float bg_coord;
	Point_float bg_coord_old;

	void Fullscreen(SDL_Window* window, bool fulscr);

	Screen() {
		fullscreen = true;
		scale_x = 1;
		scale_y = 1;
	}
};
