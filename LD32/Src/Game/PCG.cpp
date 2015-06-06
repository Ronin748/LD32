#include "Game.h"

int random_interval(int min, int max)
{
	std::random_device rand_device;
	int random = rand_device() % (max - min + 1) + min;

	return random;
}

std::string random_scientistName()
{
	std::string name;
	int randomint = random_interval(0, 9);

	switch (randomint) {
	case 0:
		name = "Schrödinger";
		break;
	case 1:
		name = "Curie";
		break;
	case 2:
		name = "Feynman";
		break;
	case 3:
		name = "Oppenheimer";
		break;
	case 4:
		name = "Hawking";
		break;
	case 5:
		name = "Poliakoff";
		break;
	case 6:
		name = "Turing";
		break;
	case 7:
		name = "Tesla";
		break;
	case 8:
		name = "Fermi";
		break;
	case 9:
		name = "Planck";
		break;
	}

	return name;
}

void Objects::randCabin()
{
	int cabin_x = random_interval(-game.cabindist, game.cabindist);
	int cabin_y = random_interval(-game.cabindist, game.cabindist);

	cabin.coord = {cabin_x, cabin_y};
}

void Creature::creatureDeath(int id, int x, int y)
{
	switch (id) {
	case 0:
		objs.pickups.xp.resize(objs.pickups.xp.size() + 1);
		objs.pickups.xp[objs.pickups.xp.size() - 1].coord.x = x + 20;
		objs.pickups.xp[objs.pickups.xp.size() - 1].coord.x = y + 20;
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void Objects::RandomFloors()
{
	bool randomize = false;
	int randomint = 0;
	for (int i = 0; i < floor.size(); ++i) {
		if (floor[i].coord.x + game.screen.bg_coord.x > 1024) {
			floor[i].coord.x -= (int)((1024 + 64) / (float)64) * 64;
			randomize = true;
		}
		else if (floor[i].coord.x + game.screen.bg_coord.x < -64) {
			floor[i].coord.x += (int)((1024 + 64) / (float)64) * 64;
			randomize = true;
		}
		if (floor[i].coord.y + game.screen.bg_coord.y > 600) {
			floor[i].coord.y -= (int)((600 + 64 * 2) / (float)64) * 64;
			randomize = true;
		}
		else if (floor[i].coord.y + game.screen.bg_coord.y < -64) {
			floor[i].coord.y += (int)((600 + 64 * 2) / (float)64) * 64;
			randomize = true;
		}
		if (randomize) {
			randomint = random_interval(0, 3);
			if (randomint == 3) {
				if (random_interval(0, 200) != 32) {
					randomint = random_interval(0, 2);
				}
			}

			if (i + 18 < floor.size() && i - 18 > 0) {
				if (floor[i + 18].sprite_i == 3 || floor[i + 1].sprite_i == 3 || floor[i - 1].sprite_i == 3) {
					randomint = random_interval(2, 3);
				}
			}
			floor[i].sprite_i = randomint;
		}
		randomize = false;
	}
}

void outOfScreen(Obj* obj, int w, int h, bool sprite, int min, int max)
{
	if (obj->coord.x + game.screen.bg_coord.x > 1024) {
		obj->coord.x = -game.screen.bg_coord.x - w - random_interval(0, 512);
		obj->coord.y = random_interval(-80, 600) - game.screen.bg_coord.y;
		if (sprite) obj->sprite_i = random_interval(min, max);
	}
	if (obj->coord.x + game.screen.bg_coord.x < -w) {
		obj->coord.x = -game.screen.bg_coord.x + 1024 + random_interval(0, 512);
		obj->coord.y = random_interval(-80, 600) - game.screen.bg_coord.y;
		if (sprite) obj->sprite_i = random_interval(min, max);
	}
	if (obj->coord.y + game.screen.bg_coord.y < -h) {
		obj->coord.x = random_interval(0, 1024) - game.screen.bg_coord.x;
		obj->coord.y = -game.screen.bg_coord.y + 600 + random_interval(0, 300);
		if (sprite) obj->sprite_i = random_interval(min, max);
	}
	if (obj->coord.y + game.screen.bg_coord.y > 600) {
		obj->coord.x = random_interval(0, 1024) - game.screen.bg_coord.x;
		obj->coord.y = -game.screen.bg_coord.y - random_interval(0, 300) - h;
		if (sprite) obj->sprite_i = random_interval(min, max);
	}
}

void Objects::RandomEnvinronments()
{
	for (int i = 0; i < spruce.size(); ++i) {
			outOfScreen(&spruce[i], 21 * 4, 39 * 4, 0, 0, 0);
			
			if (Collision({objs.cabin.coord.x, objs.cabin.coord.y, objs.cabin.tex.sprite[0].w * 4, objs.cabin.tex.sprite[0].h * 4}, {objs.spruce[i].coord.x, objs.spruce[i].coord.y, objs.spruce[0].tex.sprite[0].w * 4, objs.spruce[0].tex.sprite[0].h * 4})) {
				spruce[i].coord = {10000, 10000};
			}
	}

	for (int i = 0; i < boulder.size(); ++i) {
		outOfScreen(&boulder[i], 16 * 4, 14 * 4, 0, 0, 0);
	}
	for (int i = 0; i < birch.size(); ++i) {
		outOfScreen(&birch[i], 31 * 4, 51 * 4, 0, 0, 0);
		if (Collision({objs.cabin.coord.x, objs.cabin.coord.y, objs.cabin.tex.sprite[0].w * 4, objs.cabin.tex.sprite[0].h * 4}, {objs.birch[i].coord.x, objs.birch[i].coord.y, objs.birch[0].tex.sprite[0].w * 4, objs.birch[0].tex.sprite[0].h * 4})) {
			birch[i].coord = {10000, 10000};
		}
	}

	for (int i = 0; i < birch.size(); ++i) {
		outOfScreen(&plants[i], plants[0].tex.sprite[plants[i].sprite_i].w * 4, plants[0].tex.sprite[plants[i].sprite_i].h * 4, true, 0, 2);
	}

	if (random_interval(0, 30)) {
		if (crtr.bunny.coord.x + game.screen.bg_coord.x > 1424 || crtr.bunny.coord.x + game.screen.bg_coord.x < -400 || crtr.bunny.coord.y + game.screen.bg_coord.y > 1000 || crtr.bunny.coord.y + game.screen.bg_coord.y < -400) {
			if (random_interval(0, 30) == 5) {
				int x = random_interval(-300, 1324);
				int y = random_interval(-300, 900);
				if ((x < 0 || x > 1024) || (y < 0 || y > 600)) crtr.bunny.coord = {x - game.screen.bg_coord.x, y - game.screen.bg_coord.y};	crtr.bunny.render = true;
				crtr.bunny_health = 5;
			}
			else {
				crtr.bunny.coord = {100000, 100000};
				crtr.bunny.render = false;
			}
		}
	}

	if (random_interval(0, 25)) {
		if (crtr.squirrel.coord.x + game.screen.bg_coord.x > 1424 || crtr.squirrel.coord.x + game.screen.bg_coord.x < -400 || crtr.squirrel.coord.y + game.screen.bg_coord.y > 1000 || crtr.squirrel.coord.y + game.screen.bg_coord.y < -400) {
			if (random_interval(0, 25) == 5) {
				int x = random_interval(-300, 1324);
				int y = random_interval(-300, 900);
				if ((x < 0 || x > 1024) || (y < 0 || y > 600)) crtr.squirrel.coord = {x - game.screen.bg_coord.x, y - game.screen.bg_coord.y};	crtr.squirrel.render = true;
				crtr.squirrel_health = 3;
			}
			else {
				crtr.squirrel.coord = {100000, 100000};
				crtr.squirrel.render = false;
			}
		}
	}

	if (SDL_GetTicks() > 20000) {
		if (random_interval(0, 43 * (float)game.monster_spawn) == 16) {
			if (crtr.wolf.coord.x + game.screen.bg_coord.x > 1424 || crtr.wolf.coord.x + game.screen.bg_coord.x < -400 || crtr.wolf.coord.y + game.screen.bg_coord.y > 1000 || crtr.wolf.coord.y + game.screen.bg_coord.y < -400) {
				if (random_interval(0, 43 * (float)game.monster_spawn) == 12) {
					int x = random_interval(-300, 1324);
					int y = random_interval(-300, 900);
					if ((x < 0 || x > 1024) || (y < 0 || y > 600)) crtr.wolf.coord = {x - game.screen.bg_coord.x, y - game.screen.bg_coord.y};	crtr.wolf.render = true;
					crtr.wolf_health = 10;
				}
				else {
					crtr.wolf.coord = {100000, 100000};
					crtr.wolf.render = false;
				}
			}
		}

		if (random_interval(0, 50 * (float)game.monster_spawn) == 32) {
			if (crtr.bear.coord.x + game.screen.bg_coord.x > 1424 || crtr.bear.coord.x + game.screen.bg_coord.x < -400 || crtr.bear.coord.y + game.screen.bg_coord.y > 1000 || crtr.bear.coord.y + game.screen.bg_coord.y < -400) {
				if (random_interval(0, 50 * (float)game.monster_spawn) == 13) {
					int x = random_interval(-300, 1324);
					int y = random_interval(-300, 900);
					if ((x < 0 || x > 1024) || (y < 0 || y > 600)) crtr.bear.coord = {x - game.screen.bg_coord.x, y - game.screen.bg_coord.y};	crtr.bear.render = true;
					crtr.bear_health = 20;
				}
				else {
					crtr.bear.coord = {100000, 100000};
					crtr.bear.render = false;
				}
			}
		}
	}

	if (random_interval(0, 100000) == 646) {
		game.rain = true;
		game.rain_duration = SDL_GetTicks();
	}
	if (SDL_GetTicks() - game.rain_duration >= 20000 && game.rain) {
		game.rain = false;
	}

	if (game.rain && !Mix_Playing(3)) {
		Mix_FadeInChannel(3, game.sfx.rain, 0, 500);
	}
	else if (Mix_Playing(3) && !game.rain) {
		Mix_FadeOutChannel(3, 500);
	}
}