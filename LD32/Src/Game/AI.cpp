#include "Game.h"

void Companion::AI()
{
	if (companion.attackmode || companion.defensemode) {
		companion.attacking = true;
	}
	else {
		companion.attacking = false;
	}
	if (random_interval(0, 14000) == 1 && (attacking) && !Mix_Playing(1)) Mix_PlayChannel(1, game.sfx.dog, 0);
	if (dog.coord.x != dog.coord_old.x || dog.coord.y != dog.coord_old.y) {
		dog.moving = true;
	}
	else {
		dog.moving = false;
	}
	if (dog.moving) {
		if (dog.coord.x - dog.coord_old.x != 0) {
			if (dog.coord.x - dog.coord_old.x > 0) {
				dog.direction = true;
			}
			else {
				dog.direction = false;
			}
			if (limit > 40) {
				if (!dog.direction) {
					dog.anim.anim_tex.flip = SDL_FLIP_HORIZONTAL;
				}
				else {
					dog.anim.anim_tex.flip = SDL_FLIP_NONE;
				}
				limit = 0;
			}
			else {
				limit += 1;
			}
		}
	}
	companion.dog.coord_old = companion.dog.coord;

	if (((sqrt(pow(companion.dog.coord.x + 100 - 20 + 4 * 2 + (game.screen.bg_coord.x - 512), 2) + pow(companion.dog.coord.y + 50 - 20 + 2 + (game.screen.bg_coord.y - 300), 2)) > 250) && (character.leashbool)) || (companion.defensemode && (sqrt(pow(companion.dog.coord.x + 100 - 20 + 4 * 2 + (game.screen.bg_coord.x - 512), 2) + pow(companion.dog.coord.y + 50 - 20 + 2 + (game.screen.bg_coord.y - 300), 2)) > 400))) {
		if (companion.dog.coord.x + 14 < -game.screen.bg_coord.x + 512) {
			companion.dog.coord.x += 4 * (120 / (float)game.fps) + (companion.spd / (float)3)* (120 / (float)game.fps);
		}
		else {
			companion.dog.coord.x -= 4 * (120 / (float)game.fps) + (companion.spd / (float)3)* (120 / (float)game.fps);
		}
		if (companion.dog.coord.y + 14 < -game.screen.bg_coord.y + 300) {
			companion.dog.coord.y += 4 * (120 / (float)game.fps) + (companion.spd / (float)3)* (120 / (float)game.fps);
		}
		else {
			companion.dog.coord.y -= 4 * (120 / (float)game.fps) + (companion.spd / (float)3)* (120 / (float)game.fps);
		}
	}
	else if (companion.defensemode) {
		if (sqrt(pow(character.character.coord.x - crtr.wolf.coord.x, 2) + pow(character.character.coord.y - crtr.wolf.coord.y, 2)) <= sqrt(pow(character.character.coord.x - crtr.bear.coord.x, 2) + pow(character.character.coord.y - crtr.bear.coord.y, 2))) {
			if (crtr.wolf.render) {
				if (companion.dog.coord.x + 14 < crtr.wolf.coord.x + 20) {
					companion.dog.coord.x += 4 * (120 / (float)game.fps);
				}
				else {
					companion.dog.coord.x -= 4 * (120 / (float)game.fps);
				}
				if (companion.dog.coord.y + 14 < crtr.wolf.coord.y + 20) {
					companion.dog.coord.y += 4 * (120 / (float)game.fps);
				}
				else {
					companion.dog.coord.y -= 4 * (120 / (float)game.fps);
				}
			}
		}
		else {
			if (crtr.bear.render) {
				if (companion.dog.coord.x + 14 < crtr.bear.coord.x + 20) {
					companion.dog.coord.x += 4 * (120 / (float)game.fps);
				}
				else {
					companion.dog.coord.x -= 4 * (120 / (float)game.fps);
				}
				if (companion.dog.coord.y + 14 < crtr.bear.coord.y + 20) {
					companion.dog.coord.y += 4 * (120 / (float)game.fps);
				}
				else {
					companion.dog.coord.y -= 4 * (120 / (float)game.fps);
				}
			}
		}
	}
	else if (companion.attackmode) {
		if (crtr.wolf.render || crtr.bear.render) {
			if (sqrt(pow(character.character.coord.x - crtr.wolf.coord.x, 2) + pow(character.character.coord.y - crtr.wolf.coord.y, 2)) <= sqrt(pow(character.character.coord.x - crtr.bear.coord.x, 2) + pow(character.character.coord.y - crtr.bear.coord.y, 2))) {
				if (crtr.wolf.render) {
					if (companion.dog.coord.x + 14 < crtr.wolf.coord.x + 20) {
						companion.dog.coord.x += 4 * (120 / (float)game.fps);
					}
					else {
						companion.dog.coord.x -= 4 * (120 / (float)game.fps);
					}
					if (companion.dog.coord.y + 14 < crtr.wolf.coord.y + 20) {
						companion.dog.coord.y += 4 * (120 / (float)game.fps);
					}
					else {
						companion.dog.coord.y -= 4 * (120 / (float)game.fps);
					}
				}
			}
			else {
				if (crtr.bear.render) {
					if (companion.dog.coord.x + 14 < crtr.bear.coord.x + 20) {
						companion.dog.coord.x += 4 * (120 / (float)game.fps);
					}
					else {
						companion.dog.coord.x -= 4 * (120 / (float)game.fps);
					}
					if (companion.dog.coord.y + 14 < crtr.bear.coord.y + 20) {
						companion.dog.coord.y += 4 * (120 / (float)game.fps);
					}
					else {
						companion.dog.coord.y -= 4 * (120 / (float)game.fps);
					}
				}
			}
		}
		else if (!crtr.wolf.render && !crtr.bear.render) {
			if (sqrt(pow(character.character.coord.x - crtr.squirrel.coord.x, 2) + pow(character.character.coord.y - crtr.squirrel.coord.y, 2)) <= sqrt(pow(character.character.coord.x - crtr.bunny.coord.x, 2) + pow(character.character.coord.y - crtr.bunny.coord.y, 2))) {
				if (crtr.squirrel.render) {
					if (companion.dog.coord.x + 14 < crtr.squirrel.coord.x + 20) {
						companion.dog.coord.x += 4 * (120 / (float)game.fps);
					}
					else {
						companion.dog.coord.x -= 4 * (120 / (float)game.fps);
					}
					if (companion.dog.coord.y + 14 < crtr.squirrel.coord.y + 20) {
						companion.dog.coord.y += 4 * (120 / (float)game.fps);
					}
					else {
						companion.dog.coord.y -= 4 * (120 / (float)game.fps);
					}
				}
			}
			else {
				if (crtr.bunny.render) {
					if (companion.dog.coord.x + 14 < crtr.bunny.coord.x + 20) {
						companion.dog.coord.x += 4 * (120 / (float)game.fps);
					}
					else {
						companion.dog.coord.x -= 4 * (120 / (float)game.fps);
					}
					if (companion.dog.coord.y + 14 < crtr.bunny.coord.y + 20) {
						companion.dog.coord.y += 4 * (120 / (float)game.fps);
					}
					else {
						companion.dog.coord.y -= 4 * (120 / (float)game.fps);
					}
				}
			}
		}
	}
}

void Creature::AI()
{
	if (random_interval(0, 15000) == 1 && (bear.render) && !Mix_Playing(2)) {
		if (random_interval(0, 1)) {
			Mix_PlayChannel(2, game.sfx.bear1, 0);
		}
		else {
			Mix_PlayChannel(2, game.sfx.bear2, 0);
		}
	}
	if (random_interval(0, 20000) == 546 && (wolf.render) && !Mix_Playing(2)) {
		Mix_PlayChannel(2, game.sfx.wolf, 0);
	}

	squirrel.coord_old = squirrel.coord;

	if (cos(squirrelDormant) > 0 && sin(squirrelDormant) > 0) {

		squirrel.coord.x += squirrelRoam_x * 1 * 2 * (120 / (float)game.fps);
		squirrel.coord.y += squirrelRoam_y * 1 * 2 * (120 / (float)game.fps);
	}
	else {
		squirrelRoam_x = random_interval(-1, 1);
		squirrelRoam_y = random_interval(-1, 1);
	}
	squirrelDormant += 0.01 * (120 / (float)game.fps);

	if (squirrel.coord.x != squirrel.coord_old.x || squirrel.coord.y != squirrel.coord_old.y) {
		squirrel.moving = true;
	}
	else {
		squirrel.moving = false;
	}
	if (squirrel.coord.x - squirrel.coord_old.x != 0) {
		if (squirrel.coord.x - squirrel.coord_old.x < 0) {
			squirrel.anim.anim_tex.flip = SDL_FLIP_HORIZONTAL;
		}
		else {

			squirrel.anim.anim_tex.flip = SDL_FLIP_NONE;
		}
	}

	bunny.coord_old = bunny.coord;

	if (cos(bunnyDormant) > 0 && sin(bunnyDormant) > 0) {

		bunny.coord.x += bunnyRoam_x * 1 * 2 * (120 / (float)game.fps);
		bunny.coord.y += bunnyRoam_y * 1 * 2 * (120 / (float)game.fps);
	}
	else {
		bunnyRoam_x = random_interval(-1, 1);
		bunnyRoam_y = random_interval(-1, 1);
	}
	bunnyDormant += 0.01* (120 / (float)game.fps);

	if (bunny.coord.x != bunny.coord_old.x || bunny.coord.y != bunny.coord_old.y) {
		bunny.moving = true;
	}
	else {
		bunny.moving = false;
	}
	if (bunny.coord.x - bunny.coord_old.x != 0) {
		if (bunny.coord.x - bunny.coord_old.x < 0) {
			bunny.anim.anim_tex.flip = SDL_FLIP_HORIZONTAL;
		}
		else {

			bunny.anim.anim_tex.flip = SDL_FLIP_NONE;
		}
	}
	bear.coord_old = bear.coord;

	float beardist = sqrt(pow(bear.coord.x + 100 - 20 + 4 * 2 + (game.screen.bg_coord.x - 512), 2) + pow(bear.coord.y + 50 - 20 + 2 + (game.screen.bg_coord.y - 300), 2));
	if (beardist > 80 && bear.coord.x + game.screen.bg_coord.x < 1124 && bear.coord.x + game.screen.bg_coord.x > -100 && bear.coord.y + game.screen.bg_coord.y < 700 && bear.coord.y + game.screen.bg_coord.y > -100) {
		if (bear.coord.x + 14 < -game.screen.bg_coord.x + 512 - 50) {
			bear.coord.x += 3 * (120 / (float)game.fps);
		}
		else {
			bear.coord.x -= 3 * (120 / (float)game.fps);
		}
		if (bear.coord.y + 14 < -game.screen.bg_coord.y + 300) {
			bear.coord.y += 3 * (120 / (float)game.fps);
		}
		else {
			bear.coord.y -= 3 * (120 / (float)game.fps);
		}
	}
	if (bear.coord.x != bear.coord_old.x || bear.coord.y != bear.coord_old.y) {
		bear.moving = true;
	}
	else {
		bear.moving = false;
	}

	if (bearLimit > 40) {
		if (bear.coord.x - bear.coord_old.x != 0) {
			if (bear.coord.x - bear.coord_old.x < 0) {
				bear.anim.anim_tex.flip = SDL_FLIP_HORIZONTAL;
			}
			else {

				bear.anim.anim_tex.flip = SDL_FLIP_NONE;
			}
		}
		bearLimit = 0;
	}
	else {
		++bearLimit;
	}
	wolf.coord_old = wolf.coord;

	float wolfdist = sqrt(pow(wolf.coord.x + 100 - 20 + 4 * 2 + (game.screen.bg_coord.x - 512), 2) + pow(wolf.coord.y + 50 - 20 + 2 + (game.screen.bg_coord.y - 300), 2));
	if (wolfdist > 80 && wolf.coord.x + game.screen.bg_coord.x < 1124 && wolf.coord.x + game.screen.bg_coord.x > -100 && wolf.coord.y + game.screen.bg_coord.y < 700 && wolf.coord.y + game.screen.bg_coord.y > -100) {
		if (wolf.coord.x + 14 < -game.screen.bg_coord.x + 512 - 50) {
			wolf.coord.x += 3.6 * (120 / (float)game.fps);
		}
		else {
			wolf.coord.x -= 3.6 * (120 / (float)game.fps);
		}
		if (wolf.coord.y + 14 < -game.screen.bg_coord.y + 300) {
			wolf.coord.y += 3.6 * (120 / (float)game.fps);
		}
		else {
			wolf.coord.y -= 3.6 * (120 / (float)game.fps);
		}
	}
	if (wolf.coord.x != wolf.coord_old.x || wolf.coord.y != wolf.coord_old.y) {
		wolf.moving = true;
	}
	else {
		wolf.moving = false;
	}

	if (wolfLimit > 40) {
		if (wolf.coord.x - wolf.coord_old.x != 0) {
			if (wolf.coord.x - wolf.coord_old.x < 0) {
				wolf.anim.anim_tex.flip = SDL_FLIP_HORIZONTAL;
			}
			else {

				wolf.anim.anim_tex.flip = SDL_FLIP_NONE;
			}
		}
		wolfLimit = 0;
	}
	else {
		++wolfLimit;
	}
}