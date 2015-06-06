#include "Game\Game.h"

void Rndr(SDL_Texture* tex, Rect_float rect, SDL_Rect sprite, float angle, Rect_float angle_center, SDL_RendererFlip flip, int depth, int render_i, int* highst_i, bool bckgrnd)
{
	if (bckgrnd) {
		rect.x += game.screen.bg_coord.x;
		rect.y += game.screen.bg_coord.y;
	}

	float r = sqrt(pow(rect.w, 2) + pow(rect.h, 2)) / 2.0;
	Point_float middle = {rect.x + rect.w / 2.0, rect.y + rect.h / 2.0};
	bool bounds = (((middle.x + r) >= 0 && middle.x - r <= 1024) && (middle.y + r >= 0 && middle.y - r <= 600));

	if (depth == render_i && bounds) {
		SDL_Rect dstrect = {floor(rect.x*game.screen.scale_x + 0.9), floor(rect.y*game.screen.scale_y + 0.9), floor(rect.w*game.screen.scale_x + 0.9), floor(rect.h*game.screen.scale_y + 0.9)};
		SDL_Point cntr = {floor(angle_center.x*game.screen.scale_x + 0.5), floor(angle_center.y*game.screen.scale_y + 0.5)};

		SDL_RenderCopyEx(game.rndr, tex, &sprite, &dstrect, angle, &cntr, flip);
	}
	if (highst_i != NULL) {
		if (depth >= *highst_i) {
			*highst_i = depth;
		}
	}
}

void Txtr::RenderTex(int x, int y, int sprite_i)
{
	Rndr(tex, {x, y, sprite[sprite_i].w * 4, sprite[sprite_i].h * 4}, sprite[sprite_i], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 1);
}

void RenderObjs(std::vector <Obj> renderObjs)
{
	for (int i = 0; i < renderObjs.size(); ++i) {
		if (objs.spruce[i].render) {
			Rndr(renderObjs[0].tex.tex, {renderObjs[i].coord.x, renderObjs[i].coord.y, renderObjs[0].tex.sprite[renderObjs[i].sprite_i].w * 4, renderObjs[0].tex.sprite[renderObjs[i].sprite_i].h * 4}, renderObjs[0].tex.sprite[renderObjs[i].sprite_i], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 1);
		}
	}
}

void Text::RenderText(int x, int y, float size)
{
	Rndr(text, {x, y, w*size, h*size}, {0, 0, w, h}, 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
}

float sine = 0;

void GUI::RenderGUI()
{
	RenderBars();

	Rndr(clock.tex, {30, 20, 14 * 6, 13 * 6}, clock.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
	Rndr(clock.tex, {30 + 6 * 6, 20 + 6 * 2, 1 * 6, 5 * 6}, clock.sprite[1], game.time / (M_PI / 180), {3, 27}, SDL_FLIP_NONE, 0, 0, 0, 0);
	Rndr(clock.tex, {30 + 6 * 6, 20 + 6 * 4, 1 * 6, 3 * 6}, clock.sprite[1], (game.time / (M_PI / 180)) / 12, {3, 2 * 6 + 3}, SDL_FLIP_NONE, 0, 0, 0, 0);

	Rndr(attackModes.tex, {1024 - 16 * 8, 600 - 16 * 8, 16 * 8, 16 * 8}, attackModes.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
	Rndr(attackModes.tex, {0, 600 - 16 * 8, 16 * 8, 16 * 8}, attackModes.sprite[0], 0, {0, 0}, SDL_FLIP_HORIZONTAL, 0, 0, 0, 0);
	defenseTxt.RenderText(25, 500 - 55, 1);
	attackTxt.RenderText(1024 - 50 - 46, 500 - 55, 1);

	if (companion.attackmode) {
		Rndr(selector.tex, {1024 - 16 * 8, 600 - 16 * 8, 16 * 8, 16 * 8}, selector.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
	}
	if (companion.defensemode) {
		Rndr(selector.tex, {0, 600 - 16 * 8, 16 * 8, 16 * 8}, selector.sprite[0], 0, {0, 0}, SDL_FLIP_HORIZONTAL, 0, 0, 0, 0);
	}

	Rndr(attackLvls.tex, {1024 - 15 * 4 - 30, 600 - 16 * 8 + 27, 13 * 5, 13 * 5}, attackLvls.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
	Rndr(attackLvls.tex, {15 * 4 - 28, 600 - 16 * 8 + 24, 14 * 5, 15 * 5}, attackLvls.sprite[1], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);

	defense.RenderText(140, 480, 2);
	attack.RenderText(1024 - 160, 480, 2);

	attackLvl.RenderText(1024 - 15 - 90 - 7, 600 - 30, 1.2);
	defenseLvl.RenderText(15, 600 - 30, 1.2);

	day.RenderText(25, 110, 1.3);
	level.RenderText(340, 57, 1.3);

	if (game.upgr) {
		Rndr(upgrSelect.tex, {512 - upgrSelect.sprite[0].w * 4, 200, upgrSelect.sprite[0].w * 8, upgrSelect.sprite[0].h * 8}, upgrSelect.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
		switch (game.gui.select) {
		case 0:
			Rndr(upgrSelect.tex, {512 - upgrSelect.sprite[1].w * 4, 200 + 8, upgrSelect.sprite[1].w * 8, upgrSelect.sprite[1].h * 8}, upgrSelect.sprite[1], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
			break;
		case 1:
			Rndr(upgrSelect.tex, {512 - upgrSelect.sprite[1].w * 4, 200 + 12 * 8, upgrSelect.sprite[1].w * 8, upgrSelect.sprite[1].h * 8}, upgrSelect.sprite[1], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
			break;
		case 2:
			Rndr(upgrSelect.tex, {512 - upgrSelect.sprite[1].w * 4, 200 + 23 * 8, upgrSelect.sprite[1].w * 8, upgrSelect.sprite[1].h * 8}, upgrSelect.sprite[1], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
			break;
		}

		std::string atckstring;
		std::string defstring;
		std::string spdstring;

		switch (companion.atck) {
		case 1:
			atckstring = "I";
			break;
		case 2:
			atckstring = "I  I";
			break;
		case 3:
			atckstring = "I  I  I";
			break;
		case 4:
			atckstring = "I  I  I  I";
			break;
		}
		switch (companion.def) {
		case 1:
			defstring = "I";
			break;
		case 2:
			defstring = "I  I";
			break;
		case 3:
			defstring = "I  I  I";
			break;
		case 4:
			defstring = "I  I  I  I";
			break;
		}

		switch (companion.spd) {
		case 1:
			spdstring = "I";
			break;
		case 2:
			spdstring = "I  I";
			break;
		case 3:
			spdstring = "I  I  I";
			break;
		case 4:
			spdstring = "I  I  I  I";
			break;
		}
		atck.Text_to_Texture(game.rndr, "Attack:       " + atckstring);
		def.Text_to_Texture(game.rndr, "Defense:      " + defstring);
		spd.Text_to_Texture(game.rndr, "Speed:        " + spdstring);

		atck.RenderText(512 - upgrSelect.sprite[0].w * 4 + 30, 200 + 30, 1.3);
		def.RenderText(512 - upgrSelect.sprite[0].w * 4 + 30, 200 + 30 + 12 * 8, 1.3);
		spd.RenderText(512 - upgrSelect.sprite[0].w * 4 + 30, 200 + 30 + 23*8, 1.3);
	}
}

void GUI::RenderBars()
{
	Rndr(game.gui.bars.tex, {245 + 6, 16, 87 * 6 * ((float)character.health / (float)100), 2 * 6}, game.gui.bars.sprite[1], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);//health
	Rndr(game.gui.bars.tex, {245 + 66, 10 + 4 * 6, 67 * 6 * ((float)character.xp / (float)character.xp_max), 2 * 6}, game.gui.bars.sprite[2], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);//xp

	Rndr(game.gui.bars.tex, {954 + 6, 200 + 6 + 17 * 6, 8 * 6, -17 * 6 * (character.lanternOil / 10)/* abs(sin(sine))*/}, game.gui.bars.sprite[4], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);//oil
	Rndr(game.gui.bars.tex, {954, 200, 10 * 6, 19 * 6}, game.gui.bars.sprite[3], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
	Rndr(game.gui.oil.tex, {954 + 2 * 6 - 3, 180 - 7 * 6, 6 * 6, 8 * 6}, game.gui.oil.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
	oilTxt.RenderText(954 + 2 * 6 - 3, 180 - 7 * 6 + 190, 1.3);

	Rndr(game.gui.bars.tex, {245, 10, 89 * 6, 7 * 6}, game.gui.bars.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
}

void Char::RenderChar()
{
	character.anim.AnimationTick();
	characterLantern.anim.AnimationTick();
	if (character.moving) {
		characterLantern.anim.anim_tex.flip = character.anim.anim_tex.flip;
		if (lantern) {
			characterLantern.anim.RenderAnimation(512 - character.tex.sprite[0].w * 2.5, 300 - character.tex.sprite[0].h * 2.5, 1.25, 0);
		}
		else {
			character.anim.RenderAnimation(512 - character.tex.sprite[0].w * 2.5, 300 - character.tex.sprite[0].h * 2.5, 1.25, 0);
		}
	}
	else {
		if (lantern) {
			Rndr(characterLantern.tex.tex, {512 - characterLantern.tex.sprite[0].w * 2.5, 300 - characterLantern.tex.sprite[0].h * 2.5, characterLantern.tex.sprite[0].w * 5, characterLantern.tex.sprite[0].h * 5}, characterLantern.tex.sprite[0], 0, {0, 0}, character.anim.anim_tex.flip, 0, 0, 0, 0);
		}
		else {
			Rndr(character.tex.tex, {512 - character.tex.sprite[0].w * 2.5, 300 - character.tex.sprite[0].h * 2.5, character.tex.sprite[0].w * 5, character.tex.sprite[0].h * 5}, character.tex.sprite[0], 0, {0, 0}, character.anim.anim_tex.flip, 0, 0, 0, 0);
		}
	}
	if (leashbool) {
		int xOffs = 100 - 20 + 4 * 2 - 57 * companion.dog.anim.anim_tex.flip - 24;
		int yOffs = 50 - 20 + 2 - 16;
		int handX = 0;
		int angle_flip = 0;
		if (character.anim.anim_tex.flip != 0) {
			if (character.anim.animation_cycle[character.anim.animation] == 1) {
				handX = -1 * character.moving - 5;
			}
			else {
				handX = -5;
			}
		}
		else {
			if (character.anim.animation_cycle[character.anim.animation] == 1) {
				handX = 1 * character.moving;
			}
			else {
				handX = 0;
			}
		}
		xOffs -= handX * 8;
		if (companion.dog.coord.x + xOffs + (game.screen.bg_coord.x - 512) < 0) {
			angle_flip = 180;
		}
		if (cos(angle_flip*(M_PI / 180) + atan((companion.dog.coord.y + yOffs + (game.screen.bg_coord.y - 300)) / (companion.dog.coord.x + xOffs + (game.screen.bg_coord.x - 512)))) < 0) {
			leash.flip = SDL_FLIP_VERTICAL;
		}
		else {
			leash.flip = SDL_FLIP_NONE;
		}
		Rndr(leash.tex, {512 + 20 + handX * 8, 300 - 4 * leash.flip + 18, sqrt(pow(companion.dog.coord.x + xOffs + (game.screen.bg_coord.x - 512), 2) + pow(companion.dog.coord.y + yOffs + (game.screen.bg_coord.y - 300), 2)), leash.sprite[0].h * 2}, leash.sprite[0], angle_flip + atan((companion.dog.coord.y + yOffs + (game.screen.bg_coord.y - 300)) / (companion.dog.coord.x + xOffs + (game.screen.bg_coord.x - 512))) / (M_PI / 180), {2, 2 + 4 * leash.flip}, leash.flip, 0, 0, 0, 0);
	}
}

void Items::RenderItems()
{
	for (int i = 0; i < xp.size(); ++i) {
		if (xp[i].render) {

			Rndr(xp[0].tex.tex, {xp[i].coord.x, xp[i].coord.y + 10 * sin(25 * sine), xp[0].tex.sprite[0].w * 4, xp[0].tex.sprite[0].h * 4}, xp[0].tex.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 1);
		}
	}
	for (int i = 0; i < health.size(); ++i) {
		if (health[i].render) {

			Rndr(health[0].tex.tex, {health[i].coord.x, health[i].coord.y + 10 * sin(25 * sine + 2), health[0].tex.sprite[0].w * 4, health[0].tex.sprite[0].h * 4}, health[0].tex.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 1);
		}
	}
	for (int i = 0; i < oil.size(); ++i) {
		if (oil[i].render) {

			Rndr(oil[0].tex.tex, {oil[i].coord.x, oil[i].coord.y, oil[0].tex.sprite[0].w * 4, oil[0].tex.sprite[0].h * 4}, oil[0].tex.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 1);
		}
	}
}

void Companion::RenderCompanion()
{
	if (companion.dog.moving) {
		companion.dog.anim.AnimationTick();
		companion.dog.anim.RenderAnimation(companion.dog.coord.x, companion.dog.coord.y, 1, 1);
	}
	else {
		Rndr(companion.dog.anim.anim_tex.tex, {companion.dog.coord.x, companion.dog.coord.y, companion.dog.anim.anim_tex.sprite[0].w * 4, companion.dog.anim.anim_tex.sprite[0].h * 4}, companion.dog.anim.anim_tex.sprite[0], 0, {0, 0}, dog.anim.anim_tex.flip, 0, 0, 0, 1);
	}
	name.RenderText(companion.dog.coord.x + game.screen.bg_coord.x + (dog.anim.anim_tex.sprite[0].w * 4 - name.w) / 2, companion.dog.coord.y + game.screen.bg_coord.y - 15, 1);
}

void Objects::renderCabin()
{
	objs.cabin.tex.RenderTex(objs.cabin.coord.x, objs.cabin.coord.y, 0);
}

void sort_depth()
{
	objs.cabin.tex.depth = 1;
	character.character.tex.depth = 2;
}

void Game::Render()//TODO: depth
{
	SDL_RenderClear(rndr);

	sine += 0.001* (120 / (float)fps);

	for (int i = 0; i < objs.floor.size(); ++i) {
		if (objs.floor[i].render) {
			Rndr(objs.floor[0].tex.tex, {objs.floor[i].coord.x, objs.floor[i].coord.y, 4 * 16, 4 * 16}, objs.floor[0].tex.sprite[objs.floor[i].sprite_i], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 1);
		}
	}

	for (int i = 0; i < objs.plants.size(); ++i) {
		Rndr(objs.plants[0].tex.tex, {objs.plants[i].coord.x, objs.plants[i].coord.y, objs.plants[0].tex.sprite[objs.plants[i].sprite_i].w * 4, objs.plants[0].tex.sprite[objs.plants[i].sprite_i].h * 4}, objs.plants[0].tex.sprite[objs.plants[i].sprite_i], 25 * sin(10 * sine), {8 + 4, 6 * 4}, SDL_FLIP_NONE, 0, 0, 0, 1);
	}

	RenderObjs(objs.boulder);
	objs.pickups.RenderItems();
	RenderObjs(objs.spruce);
	RenderObjs(objs.birch);

	objs.renderCabin();

	if (crtr.bunny.render) {
		if (crtr.bunny.moving) {
			crtr.bunny.anim.AnimationTick();
			crtr.bunny.anim.RenderAnimation(crtr.bunny.coord.x, crtr.bunny.coord.y, 0.8, 1);
		}
		else {
			crtr.bunny.anim.animation = 0;
			crtr.bunny.anim.RenderAnimation(crtr.bunny.coord.x, crtr.bunny.coord.y, 0.8, 1);
		}
	}

	if (crtr.squirrel.render) {
		if (crtr.squirrel.moving) {
			crtr.squirrel.anim.AnimationTick();
			crtr.squirrel.anim.RenderAnimation(crtr.squirrel.coord.x, crtr.squirrel.coord.y, 1, 1);
		}
		else {
			Rndr(crtr.squirrel.anim.anim_tex.tex, {crtr.squirrel.coord.x, crtr.squirrel.coord.y, crtr.squirrel.anim.anim_tex.sprite[0].w * 4, crtr.squirrel.anim.anim_tex.sprite[0].h * 4}, crtr.squirrel.anim.anim_tex.sprite[0], 0, {0, 0}, crtr.squirrel.anim.anim_tex.flip, 0, 0, 0, 1);
		}
	}
	if (crtr.wolf.render) {
		if (crtr.wolf.moving) {
			crtr.wolf.anim.AnimationTick();
			crtr.wolf.anim.RenderAnimation(crtr.wolf.coord.x, crtr.wolf.coord.y, 1, 1);
		}
		else {
			Rndr(crtr.wolf.anim.anim_tex.tex, {crtr.wolf.coord.x, crtr.wolf.coord.y, crtr.wolf.anim.anim_tex.sprite[2].w * 4, crtr.wolf.anim.anim_tex.sprite[2].h * 4}, crtr.wolf.anim.anim_tex.sprite[2], 0, {0, 0}, crtr.wolf.anim.anim_tex.flip, 0, 0, 0, 1);
		}
	}
	if (crtr.bear.render) {
		if (crtr.bear.moving) {
			crtr.bear.anim.AnimationTick();
			crtr.bear.anim.RenderAnimation(crtr.bear.coord.x, crtr.bear.coord.y, 1, 1);
		}
		else {
			Rndr(crtr.bear.anim.anim_tex.tex, {crtr.bear.coord.x, crtr.bear.coord.y, crtr.bear.anim.anim_tex.sprite[0].w * 4, crtr.bear.anim.anim_tex.sprite[0].h * 4}, crtr.bear.anim.anim_tex.sprite[0], 0, {0, 0}, crtr.bear.anim.anim_tex.flip, 0, 0, 0, 1);
		}
	}
	companion.RenderCompanion();
	character.RenderChar();

	if (game.rain) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 2; ++j) {
				Rndr(objs.fx.rain.tex, {408 * i + (screen.bg_coord.x - floor(screen.bg_coord.x / 408) * 408) - 408, 600 * j + (screen.bg_coord.y + sine * 4600 - floor((screen.bg_coord.y + sine * 4600) / 600) * 600) - 600, 408, 600}, objs.fx.rain.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
			}
		}
	}
	if (time_night > 0) {
		SDL_SetTextureAlphaMod(objs.fx.dark.tex, 255 * time_night);
		SDL_SetTextureAlphaMod(objs.fx.lanternGlow.tex, 255 * time_night);

		if (character.lantern) {
			Rndr(objs.fx.lanternGlow.tex, {0, 0, 1024, 600}, objs.fx.lanternGlow.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
		}
		else {
			Rndr(objs.fx.dark.tex, {0, 0, 1024, 600}, objs.fx.dark.sprite[0], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 0);
		}
	}

	if (time_night > 0.7) {
		if (sqrt(pow(crtr.wolf.coord.x + 2 + 31 * 4 - 24 * 4 * crtr.wolf.anim.anim_tex.flip - (512 - screen.bg_coord.x/* - character.character.tex.sprite[0].w * 2.5 / 2.0 */), 2) + pow(crtr.wolf.coord.y + 24 + 2 - (300/* - character.character.tex.sprite[0].h * 2.5 / 2.0*/ - screen.bg_coord.y), 2)) > 227) {
			Rndr(crtr.wolf.anim.anim_tex.tex, {crtr.wolf.coord.x + 31 * 4 - 24 * 4 * crtr.wolf.anim.anim_tex.flip, crtr.wolf.coord.y + 24, 4, 4}, {31, 6, 1, 1}, 0, {0, 0}, crtr.wolf.anim.anim_tex.flip, 0, 0, 0, 1);
		}
		if (sqrt(pow(crtr.bear.coord.x + 2 + 34 * 4 - 26 * 4 * crtr.bear.anim.anim_tex.flip - (512 - screen.bg_coord.x/* - character.character.tex.sprite[0].w * 2.5 / 2.0 */), 2) + pow(crtr.bear.coord.y + 24 + 2 - (300/* - character.character.tex.sprite[0].h * 2.5 / 2.0*/ - screen.bg_coord.y), 2)) > 227) {
			Rndr(crtr.bear.anim.anim_tex.tex, {crtr.bear.coord.x + 34 * 4 - 26 * 4 * crtr.bear.anim.anim_tex.flip, crtr.bear.coord.y + 24, 4, 4}, {34, 29, 1, 1}, 0, {0, 0}, crtr.bear.anim.anim_tex.flip, 0, 0, 0, 1);
		}
		if (sqrt(pow(companion.dog.coord.x + 2 + 24 * 4 - 18 * 4 * companion.dog.anim.anim_tex.flip - (512 - screen.bg_coord.x/* - character.character.tex.sprite[0].w * 2.5 / 2.0 */), 2) + pow(companion.dog.coord.y + 16 + 2 - (300/* - character.character.tex.sprite[0].h * 2.5 / 2.0*/ - screen.bg_coord.y), 2)) > 227) {
			Rndr(companion.dog.anim.anim_tex.tex, {companion.dog.coord.x + 24 * 4 - 18 * 4 * companion.dog.anim.anim_tex.flip, companion.dog.coord.y + 16, 4, 4}, {24, 4, 1, 1}, 0, {0, 0}, companion.dog.anim.anim_tex.flip, 0, 0, 0, 1);
		}
		if (!Collision({512 - character.character.tex.sprite[0].w * 1.25 * 2.5 / 2 - screen.bg_coord.x, 300 - character.character.tex.sprite[0].h * 1.25 * 2.5 / 2 - screen.bg_coord.y, character.character.tex.sprite[0].w * 2.5*1.25, character.character.tex.sprite[0].h * 2.5*1.25}, {objs.cabin.coord.x + 11 * 4, objs.cabin.coord.y + 10 * 4, 32, 32})) {
			Rndr(objs.cabin.tex.tex, {objs.cabin.coord.x + 11 * 4, objs.cabin.coord.y + 10 * 4, 32, 32}, objs.cabin.tex.sprite[2], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 1);
		}
		if (!Collision({512 - character.character.tex.sprite[0].w * 1.25 * 2.5 / 2 - screen.bg_coord.x, 300 - character.character.tex.sprite[0].h * 1.25 * 2.5 / 2 - screen.bg_coord.y, character.character.tex.sprite[0].w * 2.5*1.25, character.character.tex.sprite[0].h * 2.5*1.25}, {objs.cabin.coord.x + 38 * 4, objs.cabin.coord.y + 19 * 4, 40, 40})) {
			Rndr(objs.cabin.tex.tex, {objs.cabin.coord.x + 38 * 4, objs.cabin.coord.y + 19 * 4, 40, 40}, objs.cabin.tex.sprite[3], 0, {0, 0}, SDL_FLIP_NONE, 0, 0, 0, 1);
		}
	}

	gui.RenderGUI();
	gui.fps.RenderText(920, 10, 0.7);

	if (objs.cabinCollision) gui.cabin.RenderText(512 - 80, 200, 1);
	if (darknessDeath) {
		gui.dark.RenderText(512 - 330, 300, 1);
	}
	else if (character.health <= 0) {
		gui.death.RenderText(512 - 170, 300, 1);
	}

	SDL_RenderPresent(rndr);
}