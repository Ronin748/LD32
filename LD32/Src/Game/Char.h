#include "Companion.h"

class Char {
public:
	Obj character;
	Obj characterLantern;

	Txtr leash;
	bool leashbool;

	bool lantern;
	float lanternOil;

	int xp;
	int xp_max;
	float health;
	int level;

	int damageticks;

	void LoadChar(SDL_Renderer* rndr)
	{
		leash.LoadTex(rndr, "Gfx/GUI/Bars.png", {{11, 35, 73, 6}});
		character.tex.LoadTex(rndr, "Gfx/Char/Char.png", {{0, 0, 19, 34}});
		character.anim.LoadAnimation(rndr, "Gfx/Char/Char.png", {{0, 0, 19, 34}, {19, 0, 19, 34}, {38, 0, 19, 34}}, 200, {1, 0, 2, 0});
		characterLantern.tex.LoadTex(rndr, "Gfx/Char/Char.png", {{0, 34, 19, 34}});
		characterLantern.anim.LoadAnimation(rndr, "Gfx/Char/Char.png", {{0, 34, 19, 34}, {19, 34, 19, 34}, {38, 34, 19, 34}}, 200, {1, 0, 2, 0});
	}

	void RenderChar();
		
	Char()
	{
		xp = 0;
		xp_max = 1000;
		health = 100;
		lantern = false;
		lanternOil = 7;
		damageticks = 0;
		leashbool = true;
	}
};