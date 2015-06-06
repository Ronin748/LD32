#ifndef OBJ_H
#define OBJ_H

#include "Animation.h"
#include "..\Audio.h"

class Obj {
public:
	Txtr tex;
	Point_float coord;
	Point_float coord_old;
	int sprite_i;
	bool render;
	Anim anim;

	bool moving;
	bool direction;

	int time;

	Obj()
	{
		coord = {0, 0};
		coord_old = {0, 0};
		sprite_i = 0;
		render = true;
		time = 0;
	}
};

class Items {
public:
	std::vector <Obj> health;
	std::vector <Obj> xp;
	std::vector <Obj> oil;

	void LoadItems(SDL_Renderer* rndr)
	{
		health[0].tex.LoadTex(rndr, "Gfx/Woods/Items.png", {{9, 0, 9, 9}});
		xp[0].tex.LoadTex(rndr, "Gfx/Woods/Items.png", {{1, 2, 6, 6}});
		oil[0].tex.LoadTex(rndr, "Gfx/Woods/Items.png", {{22, 0, 7, 8}});
	}

	void RenderItems();

	void DropItem(int id, int x, int y) {
		switch (id) {
		case 0:
			if (health[health.size() - 1].render) health.resize(health.size() + 1);
			health[health.size() - 1].time = SDL_GetTicks();
			health[health.size() - 1].coord.x = x;
			health[health.size() - 1].coord.y = y;
			health[health.size() - 1].render = true;
			break;
		case 1:
			if (xp[xp.size() - 1].render)xp.resize(xp.size() + 1);
			xp[xp.size() - 1].time = SDL_GetTicks();
			xp[xp.size() - 1].coord.x = x;
			xp[xp.size() - 1].coord.y = y;
			xp[xp.size() - 1].render = true;
			break;
		case 2:
			if (oil[oil.size() - 1].render) oil.resize(oil.size() + 1);
			oil[oil.size() - 1].time = SDL_GetTicks();
			oil[oil.size() - 1].coord.x = x;
			oil[oil.size() - 1].coord.y = y;
			oil[oil.size() - 1].render = true;
			break;
		}
	}

	Items()
	{
		health.resize(1);
		xp.resize(1);
		oil.resize(1);
		health[0].render = false;
		oil[0].render = false;
		xp[0].render = false;
	}
};

class Objects {
public:
	std::vector <Obj> floor;
	std::vector <Obj> spruce;
	std::vector <Obj> birch;
	std::vector <Obj> boulder;
	Obj cabin;
	std::vector <Obj> plants;

	Fx fx;

	Items pickups;

	bool cabinCollision;

	void randCabin();

	void renderCabin();

	void NewFloor(SDL_Rect coord, int sprite)
	{
		floor.resize(floor.size() + 1);
		floor[floor.size() - 1].tex.coords = {coord.x, coord.y, coord.w, coord.h};
		floor[floor.size() - 1].coord = {coord.x, coord.y};
		floor[floor.size() - 1].sprite_i = sprite;
	}

	void RandomFloors();
	void RandomEnvinronments();

	Objects()
	{
		floor.resize(1);
		spruce.resize(20);
		boulder.resize(5);
		birch.resize(3);
		plants.resize(4);
		cabinCollision = false;
	}
};

#endif
