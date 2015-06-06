#include "Game.h"

void Game::LoadObjs()
{
	objs.floor[0].tex.LoadTex(rndr, "Gfx/Woods/Tiles.png", {{0, 0, 16, 16}, {16, 0, 16, 16}, {0, 16, 16, 16}, {16, 16, 16, 16}});
	objs.floor.resize(252);
	int i = 0;
	for (int x = -64; x < 1024 + 64; x += 64) {
		for (int y = -64 * 2; y < 600 + 64 * 2; y += 64){
			objs.floor[i].coord = {x, y};
			objs.floor[i].sprite_i = random_interval(0, 3);
			++i;
		}
	}

	objs.spruce[0].tex.LoadTex(rndr, "Gfx/Woods/Environment.png", {{0, 0, 21, 39}});
	for (int i = 0; i < objs.spruce.size(); ++i) {
		objs.spruce[i].coord.x = random_interval(0, 1024);
		objs.spruce[i].coord.y = random_interval(0, 600);
	}

	objs.boulder[0].tex.LoadTex(rndr, "Gfx/Woods/Environment.png", {{32, 0, 16, 14}});
	for (int i = 0; i < objs.boulder.size(); ++i) {
		objs.boulder[i].coord.x = random_interval(0, 1024);
		objs.boulder[i].coord.y = random_interval(0, 600);
	}

	objs.fx.LoadFx(rndr);
	game.gui.LoadGUI(rndr);
	character.LoadChar(rndr);
	objs.pickups.LoadItems(rndr);

	objs.cabin.tex.LoadTex(rndr, "Gfx/Woods/Environment.png", {{52, 0, 65, 46}, {120, 0, 8, 8}, {121, 12, 8, 8}, {120, 24, 10, 10}});

	objs.birch[0].tex.LoadTex(rndr, "Gfx/Woods/Environment.png", {{0, 40, 31, 51}});
	for (int i = 0; i < objs.birch.size(); ++i) {
		objs.birch[i].coord.x = random_interval(0, 1024);
		objs.birch[i].coord.y = random_interval(0, 600);
	}

	objs.plants[0].tex.LoadTex(rndr, "Gfx/Woods/Environment.png", {{26, 21, 8, 7}, {34, 22, 4, 6}, {38, 21, 5, 7}});
	for (int i = 0; i < objs.plants.size(); ++i) {
		objs.plants[i].coord.x = random_interval(0, 1024);
		objs.plants[i].coord.y = random_interval(0, 600);
		objs.plants[i].sprite_i = random_interval(0, 2);
	}

	crtr.LoadCreatures(rndr);
	companion.LoadCompanions(rndr, random_interval(0, 3));

	companion.name.Text_to_Texture(rndr, random_scientistName());

	crtr.bunny.render = false;
	crtr.bunny.coord = {100000, 100000};
	crtr.squirrel.render = false;
	crtr.squirrel.coord = {100000, 100000};
	crtr.wolf.render = false;
	crtr.wolf.coord = {100000, 100000};
	crtr.bear.render = false;
	crtr.bear.coord = {100000, 100000};
	objs.randCabin();
}
