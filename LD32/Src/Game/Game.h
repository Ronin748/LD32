#ifndef GAME_H
#define GAME_H

#include "Object.h"
#include "..\Screen.h"
#include "..\GUI.h"
#include "Char.h"

int random_interval(int min, int max);
bool Collision(SDL_Rect rect1, SDL_Rect rect2);
bool RectCollision(SDL_Rect* rect1, SDL_Point rect1_old, SDL_Rect rect2);
Rect_float to_rectFloat(SDL_Rect rect);
std::string random_scientistName();
void Rndr(SDL_Texture* tex, Rect_float rect, SDL_Rect sprite, float angle, Rect_float angle_center, SDL_RendererFlip flip, int depth, int render_i, int* highst_i, bool bckgrnd);
void sort_depth();

class Input {
public:
	SDL_Point mouse;
	SDL_Point mouse_old;

	bool mouse_left;
	bool mouse_right;
	bool mouse_middle;
	bool mouse_dragging;

	bool fullscreen_toggle;
	bool lantern_toggle;
	bool leash_toggle;

	bool spacedown;
	bool defense_toggle;
	bool attack_toggle;

	bool select_toggle_up;
	bool select_toggle_down;
};

class Game {
public:
	bool running;

	int fps;
	int ticks;
	int old_ticks;
	float fps_delay;

	Screen screen;

	Input input;

	SDL_Window* wndw;
	SDL_Renderer* rndr;

	SDL_Event evnt;

	void Start();
	void Init();

	void HandleInput();

	void KeyboardInput();
	void MouseInput();

	void GameLoop();

	void Render();
	void Collisions();

	void LoadObjs();

	float time_night;
	int day;
	bool addDay;
	float time;

	GUI gui;

	float monster_spawn;
	int cabindist;

	bool rain;
	int rain_duration;

	bool levelcmplt;
	bool darknessDeath;

	void restart();

	bool upgr;

	Sfx sfx;

	Game()
	{
		running = true;
		fps_delay = 0;
		time_night = 0;
		day = 0;
		addDay = false;
		time = 6*2*M_PI;
		monster_spawn = 0;
		cabindist = 1000;

		levelcmplt = false;

		rain = false;
		rain_duration = false;
		upgr = false;
	}
};

extern Game game;

extern Objects objs;
extern Char character;
extern Companion companion;
extern Creature crtr;

#endif
