#include "Game.h"

class Companion {
public:
	Obj dog;
	Obj cat;
	Text name;

	int atck;
	int def;
	int spd;

	int limit;

	bool attacking;
	bool attackmode;
	bool defensemode;

	void AI();

	void RenderCompanion();

	void LoadCompanions(SDL_Renderer* rndr, int sprite)
	{
		if (sprite > 1) {
			dog.anim.LoadAnimation(rndr, "Gfx/Companions/Dog.png", {{0, 0, 31, 18}, {31, 0, 31, 18}, {65, 0, 31, 18}}, 140, {1, 2});
		}
		else {
			dog.anim.LoadAnimation(rndr, "Gfx/Companions/Dog.png", {{0, 19, 31, 18}, {31, 19, 31, 18}, {65, 19, 31, 18}}, 140, {1, 2});
		}
		def = 1;
		atck = 1;
		spd = 1;
		attackmode = false;
		defensemode = false;
	}
};

class Creature {
public:
	Obj bunny;//0
	Obj squirrel;//1

	int bunnyRoam_x;
	int bunnyRoam_y;
	float bunnyDormant;
	int squirrelRoam_x;
	int squirrelRoam_y;
	float squirrelDormant;

	int bearLimit;
	int wolfLimit;

	Obj bear;//2
	Obj wolf;//3

	float bear_health;
	float wolf_health;
	float bunny_health;
	float squirrel_health;

	void Creature::creatureDeath(int id, int x, int y);

	void AI();

	void LoadCreatures(SDL_Renderer* rndr)
	{
		bunny.anim.LoadAnimation(rndr, "Gfx/Woods/Animals.png", {{0, 0, 18, 15}, {20, 0, 18, 15}, {38, 0, 18, 15}}, 200, {0, 1, 2});
		squirrel.anim.LoadAnimation(rndr, "Gfx/Woods/Animals.png", {{0, 17, 14, 13}, {14, 17, 17, 13}, {31, 17, 17, 13}, {48, 17, 17, 13}}, 140, {2, 1, 3});
		wolf.anim.LoadAnimation(rndr, "Gfx/Woods/Monsters.png", {{0, 0, 39, 20}, {39, 0, 39, 20}, {78, 0, 39, 20}}, 140, {0, 1});
		bear.anim.LoadAnimation(rndr, "Gfx/Woods/Monsters.png", {{0, 23, 43, 23}, {43, 23, 43, 23}, {86, 23, 43, 23}}, 180, {1, 0, 2, 0});
		bunnyDormant = 1;
		bear_health = 20;
		wolf_health = 10;
	}

	Creature()
	{
	}
};
