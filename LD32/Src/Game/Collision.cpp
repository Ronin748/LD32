#include "Game.h"

bool Collision(SDL_Rect rect1, SDL_Rect rect2)
{
	if ((rect1.x <= rect2.x + rect2.w) && (rect1.x + rect1.w >= rect2.x) && ((rect1.y <= rect2.y + rect2.h) && (rect1.y + rect1.h >= rect2.y))) {
		return true;
	}
	else {
		return false;
	}
}

bool RectCollision(SDL_Rect* rect1, SDL_Point rect1_old, SDL_Rect rect2)
{
	bool collide = false;

	if (Collision(*rect1, rect2)) {
		if (Collision(*rect1, rect2) && !Collision({rect1->x, rect1_old.y, rect1->w, rect1->h}, rect2) && Collision({rect1_old.x, rect1->y, rect1->w, rect1->h}, rect2)) {
			rect1->y = rect1_old.y;
			collide = true;
		}
		if (Collision(*rect1, rect2) && Collision({rect1->x, rect1_old.y, rect1->w, rect1->h}, rect2) && !Collision({rect1_old.x, rect1->y, rect1->w, rect1->h}, rect2)) {
			rect1->x = rect1_old.x;
			collide = true;
		}
		if (!collide) {
			rect1->x = rect1_old.x;
			rect1->y = rect1_old.y;
			collide = true;
		}
	}

	return collide;
}

void Game::Collisions()
{
	if (Collision({512 - character.character.tex.sprite[0].w * 1.25 * 2.5 / 2 - screen.bg_coord.x, 300 - character.character.tex.sprite[0].h * 1.25 * 2.5 / 2 - screen.bg_coord.y, character.character.tex.sprite[0].w * 2.5*1.25, character.character.tex.sprite[0].h * 2.5*1.25}, {crtr.bear.coord.x, crtr.bear.coord.y, crtr.bear.anim.anim_tex.sprite[0].w * 4, crtr.bear.anim.anim_tex.sprite[0].h * 4})) {
		character.health -= 0.1 * (120 / (float)fps);
		if (!Mix_Playing(5) && SDL_GetTicks() - sfx.damageTicks >= 1000) {
			sfx.damageTicks = SDL_GetTicks();
			Mix_PlayChannel(5, sfx.damage, 0);
		}
	}
	if (Collision({512 - character.character.tex.sprite[0].w * 1.25* 2.5 / 2 - screen.bg_coord.x, 300 - character.character.tex.sprite[0].h * 1.25 * 2.5 / 2 - screen.bg_coord.y, character.character.tex.sprite[0].w * 1.25 * 2.5, character.character.tex.sprite[0].h * 1.25 * 2.5}, {crtr.wolf.coord.x, crtr.wolf.coord.y, crtr.wolf.anim.anim_tex.sprite[2].w * 4, crtr.wolf.anim.anim_tex.sprite[2].h * 4})) {
		character.health -= 0.05 * (120 / (float)fps);
		if (!Mix_Playing(5) && SDL_GetTicks() - sfx.damageTicks >= 1000) {
			sfx.damageTicks = SDL_GetTicks();
			Mix_PlayChannel(5, sfx.damage, 0);
		}
	}

	if (Collision({companion.dog.coord.x, companion.dog.coord.y, 31 * 4, 18 * 4}, {crtr.wolf.coord.x, crtr.wolf.coord.y, 39 * 4, 20 * 4}) && (companion.defensemode || companion.attackmode)) {
		crtr.wolf_health -= 0.03* (120 / (float)game.fps) + companion.attackmode*0.03*(companion.atck / (float)3)* (120 / (float)game.fps) + companion.defensemode*0.03*(companion.def / (float)3)* (120 / (float)game.fps);

		if (SDL_GetTicks() - sfx.hitTicks >= 700) {
			sfx.hitTicks = SDL_GetTicks();
			Mix_PlayChannel(-1, sfx.hit, 0);
		}
	}
	if (Collision({companion.dog.coord.x, companion.dog.coord.y, 31 * 4, 18 * 4}, {crtr.bear.coord.x, crtr.bear.coord.y, 43 * 4, 23 * 4}) && (companion.defensemode || companion.attackmode)) {
		crtr.bear_health -= 0.03* (120 / (float)game.fps) + companion.attackmode*0.03*(companion.atck / (float)3)* (120 / (float)game.fps) + companion.defensemode*0.03*(companion.def / (float)3)* (120 / (float)game.fps);

		if (SDL_GetTicks() - sfx.hitTicks >= 700) {
			sfx.hitTicks = SDL_GetTicks();
			Mix_PlayChannel(-1, sfx.hit, 0);
		}
	}
	if (Collision({companion.dog.coord.x, companion.dog.coord.y, 31 * 4, 18 * 4}, {crtr.bunny.coord.x, crtr.bunny.coord.y, 18 * 4, 15 * 4}) && companion.attackmode) {
		crtr.bunny_health -= 0.03* (120 / (float)game.fps) + companion.attackmode*0.03*(companion.atck / (float)3)* (120 / (float)game.fps) + companion.defensemode*0.03*(companion.def / (float)3)* (120 / (float)game.fps);

		if (SDL_GetTicks() - sfx.hitTicks >= 700) {
			sfx.hitTicks = SDL_GetTicks();
			Mix_PlayChannel(-1, sfx.hit, 0);
		}
	}
	if (Collision({companion.dog.coord.x, companion.dog.coord.y, 31 * 4, 18 * 4}, {crtr.squirrel.coord.x, crtr.squirrel.coord.y, 17 * 4, 13 * 4}) && companion.attackmode) {
		crtr.squirrel_health -= 0.03* (120 / (float)game.fps) + companion.attackmode*0.03*(companion.atck / (float)3)* (120 / (float)game.fps) + companion.defensemode*0.03*(companion.def / (float)3)* (120 / (float)game.fps);

		if (SDL_GetTicks() - sfx.hitTicks >= 700) {
			sfx.hitTicks = SDL_GetTicks();
			Mix_PlayChannel(-1, sfx.hit, 0);
		}
	}
	if (crtr.squirrel_health <= 0) {
		crtr.squirrel_health = 3;
		crtr.squirrel.render = false;
		objs.pickups.DropItem(1, crtr.squirrel.coord.x + 20, crtr.squirrel.coord.y + 20);
		crtr.squirrel.coord = {100000, 100000};
	}
	if (crtr.wolf_health <= 0) {
		crtr.wolf_health = 10;
		crtr.wolf.render = false;
		objs.pickups.DropItem(1, crtr.wolf.coord.x + 20, crtr.wolf.coord.y + 20);
		objs.pickups.DropItem(1, crtr.wolf.coord.x + 20 + 20, crtr.wolf.coord.y + 20 + 10);
		if (random_interval(0, 7) == 2) objs.pickups.DropItem(0, crtr.wolf.coord.x + 30 - 20, crtr.wolf.coord.y + 20 + 18);
		if (random_interval(0, 4) == 2) objs.pickups.DropItem(2, crtr.wolf.coord.x + 10 - 20, crtr.wolf.coord.y + 20 + 18);
		crtr.wolf.coord = {100000, 100000};
	}
	if (crtr.bear_health <= 0) {
		crtr.bear_health = 20;
		crtr.bear.render = false;
		objs.pickups.DropItem(1, crtr.bear.coord.x, crtr.bear.coord.y);
		objs.pickups.DropItem(1, crtr.bear.coord.x + 20 + 20, crtr.bear.coord.y + 20 + 10);
		objs.pickups.DropItem(1, crtr.bear.coord.x + 20 - 20, crtr.bear.coord.y + 20 + 18);
		if (random_interval(0, 5) == 2) objs.pickups.DropItem(0, crtr.bear.coord.x + 30 - 20, crtr.bear.coord.y + 20 + 18);
		if (random_interval(0, 3) == 2) objs.pickups.DropItem(2, crtr.bear.coord.x + 10 - 20, crtr.bear.coord.y + 20 + 18);
		crtr.bear.coord = {100000, 100000};
	}
	if (crtr.bunny_health <= 0) {
		crtr.bunny_health = 5;
		crtr.bunny.render = false;
		objs.pickups.DropItem(1, crtr.bunny.coord.x + 20 + 20, crtr.bunny.coord.y + 20 + 10);
		crtr.bunny.coord = {100000, 100000};
	}

	for (int i = 0; i < objs.pickups.health.size(); ++i) {
		if (Collision({512 - character.character.tex.sprite[0].w * 1.25 * 2.5 / 2 - screen.bg_coord.x, 300 - character.character.tex.sprite[0].h * 1.25 * 2.5 / 2 - screen.bg_coord.y, character.character.tex.sprite[0].w * 2.5*1.25, character.character.tex.sprite[0].h * 2.5*1.25}, {objs.pickups.health[i].coord.x, objs.pickups.health[i].coord.y, 9 * 4, 9 * 4}) && objs.pickups.health[i].render) {
			character.health += 20;
			Mix_PlayChannel(6, sfx.pickup, 0);
			objs.pickups.health[i].render = false;
		}
	}
	for (int i = 0; i < objs.pickups.xp.size(); ++i) {
		if (Collision({512 - character.character.tex.sprite[0].w * 1.25 * 2.5 / 2 - screen.bg_coord.x, 300 - character.character.tex.sprite[0].h * 1.25 * 2.5 / 2 - screen.bg_coord.y, character.character.tex.sprite[0].w * 2.5*1.25, character.character.tex.sprite[0].h * 2.5*1.25}, {objs.pickups.xp[i].coord.x, objs.pickups.xp[i].coord.y, 9 * 4, 9 * 4}) && objs.pickups.xp[i].render) {
			character.xp += 100;
			Mix_PlayChannel(6, sfx.pickup, 0);
			objs.pickups.xp[i].render = false;
		}
	}
	for (int i = 0; i < objs.pickups.oil.size(); ++i) {

		if (Collision({512 - character.character.tex.sprite[0].w * 1.25 * 2.5 / 2 - screen.bg_coord.x, 300 - character.character.tex.sprite[0].h * 1.25 * 2.5 / 2 - screen.bg_coord.y, character.character.tex.sprite[0].w * 2.5*1.25, character.character.tex.sprite[0].h * 2.5*1.25}, {objs.pickups.oil[i].coord.x, objs.pickups.oil[i].coord.y, 9 * 4, 9 * 4}) && objs.pickups.oil[i].render) {
			character.lanternOil += 3;
			Mix_PlayChannel(6, sfx.pickup, 0);
			objs.pickups.oil[i].render = false;
		}
	}

	objs.cabinCollision = Collision({objs.cabin.coord.x, objs.cabin.coord.y, objs.cabin.tex.sprite[0].w * 4, objs.cabin.tex.sprite[0].h * 4}, {512 - character.character.tex.sprite[0].w * 2.5 - screen.bg_coord.x, 300 - character.character.tex.sprite[0].h * 2.5 - screen.bg_coord.y, character.character.tex.sprite[0].w * 2.5, character.character.tex.sprite[0].h * 2.5});
}