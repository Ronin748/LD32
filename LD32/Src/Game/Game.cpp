#include "..\Lib.h"
#include "Game.h"

Objects objs;
Char character;
Companion companion;
Creature crtr;

void Game::Start()
{
	std::cout << "Ludum Dare 32 Ronin748_ 2015" << std::endl;

	Init();

	LoadObjs();
	sfx.LoadSound();

	Mix_PlayChannel(7, sfx.background, -1);

	GameLoop();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

	screen.InitScreen();

	if (screen.fullscreen) {
		wndw = SDL_CreateWindow("Daunting Disorientation LD32", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 600, SDL_WINDOW_FULLSCREEN_DESKTOP);

		screen.scale_x = (float)screen.screen_w / (float)screen.wndw_w;
		screen.scale_y = (float)screen.screen_h / (float)screen.wndw_h;
	}
	else {
		wndw = SDL_CreateWindow("Daunting Disorientation LD32", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 600, 0);
	}

	screen.icon = IMG_Load("Gfx/Misc/LD32.png");
	SDL_SetWindowIcon(wndw, screen.icon);

	rndr = SDL_CreateRenderer(wndw, -1, SDL_RENDERER_ACCELERATED);
}

void Game::restart()
{
	character.health = 100;
	character.lanternOil = 7;
	character.xp = 0;
	character.xp_max = 1000;
	character.level = 0;
	time_night = 0;
	day = 0;
	time = 24 * 2 * M_PI*day + 12 * 2 * M_PI;
	screen.bg_coord = {0, 0};
	objs.randCabin();
	crtr.bunny.render = false;
	crtr.bunny.coord = {100000, 100000};
	crtr.squirrel.render = false;
	crtr.squirrel.coord = {100000, 100000};
	crtr.wolf.render = false;
	crtr.wolf.coord = {100000, 100000};
	crtr.bear.render = false;
	crtr.bear.coord = {100000, 100000};
	character.leashbool = true;
	companion.dog.coord = {0, 0};
	character.lantern = false;
	darknessDeath = false;
	game.levelcmplt = false;
	companion.name.Text_to_Texture(rndr, random_scientistName());

	if (random_interval(0, 1)) {
		companion.dog.anim.anim_tex.sprite = {{0, 0, 31, 18}, {31, 0, 31, 18}, {65, 0, 31, 18}};
	}
	else {
		companion.dog.anim.anim_tex.sprite = {{0, 19, 31, 18}, {31, 19, 31, 18}, {65, 19, 31, 18}};
	}
	game.rain = false;

	for (int i = 0; i < objs.pickups.health.size(); ++i) {
		objs.pickups.health[i].render = false;
	}
	objs.pickups.health.resize(1);
	for (int i = 0; i < objs.pickups.xp.size(); ++i) {
		objs.pickups.xp[i].render = false;
	}
	objs.pickups.xp.resize(1);
	for (int i = 0; i < objs.pickups.oil.size(); ++i) {
		objs.pickups.oil[i].render = false;
	}
	objs.pickups.oil.resize(1);

	monster_spawn = 0;
	cabindist = 1000;

	companion.atck = 1;
	companion.def = 1;
	companion.spd = 1;
}

void Game::GameLoop()
{
	while (running) {
		++ticks;
		//character.health = 100;
		if (SDL_GetTicks() - old_ticks >= 100) {
			fps = 10 * ticks;

			old_ticks = SDL_GetTicks();
			ticks = 0;
			std::cout << "FPS: " << fps << ", " << fps_delay << " ms" << std::endl;
			gui.fps.Text_to_Texture(rndr, "FPS: " + std::to_string(fps));
			SDL_SetTextureAlphaMod(gui.fps.text, 50);
			/*
			if (fps > 200) {
			fps_delay += 0.1;
			}
			if (fps < 150) {
			fps_delay -= 0.1;
			}*/
			if (fps_delay < 0) {
				fps_delay = 0;
			}

			if (time_night < 1 && time > 24 * 2 * M_PI*(day - 1) + 18 * 2 * M_PI) {
				time_night += 0.01; addDay = false;
			}
			else if (time_night > 0 && time > 24 * 2 * M_PI*(day - 1) + 6 * 2 * M_PI  && time < 24 * 2 * M_PI*(day - 1) + 12 * 2 * M_PI) time_night -= 0.01;

			if (time_night > 1) time_night = 1;

			if (time_night < 0) time_night = 0;

			if (time > 24 * 2 * M_PI*(day) && !addDay) {
				++day;
				addDay = true;
			}
			if (character.lantern && character.lanternOil > 0) {
				character.lanternOil -= 0.02;
			}
			if (character.lanternOil <= 0) {
				character.lantern = false;
			}
			if (time_night > 0.9 && !character.lantern && character.health > 0) {
				character.health -= 2;
				if (character.health <= 0) {
					darknessDeath = true;
				}
			}
			monster_spawn = day*0.1;
			cabindist = day * 300 + 1000;

			gui.day.Text_to_Texture(rndr, "Day: " + std::to_string(game.day));
			gui.level.Text_to_Texture(rndr, "Level: " + std::to_string(character.level) + "     " + "XP: " + std::to_string(character.xp) + "/" + std::to_string(character.xp_max));

			switch (companion.atck) {
			case 1:
				gui.attackLvl.Text_to_Texture(rndr, "I");
				break;
			case 2:
				gui.attackLvl.Text_to_Texture(rndr, "I I");
				break;
			case 3:
				gui.attackLvl.Text_to_Texture(rndr, "I I I");
				break;
			case 4:
				gui.attackLvl.Text_to_Texture(rndr, "I I I I");
				break;
			}
			switch (companion.def) {
			case 1:
				gui.defenseLvl.Text_to_Texture(rndr, "I");
				break;
			case 2:
				gui.defenseLvl.Text_to_Texture(rndr, "I I");
				break;
			case 3:
				gui.defenseLvl.Text_to_Texture(rndr, "I I I");
				break;
			case 4:
				gui.defenseLvl.Text_to_Texture(rndr, "I I I I");
				break;
			}

			//time_night = 0;//disable time

			for (int i = 0; i < objs.pickups.xp.size(); ++i) {
				if (SDL_GetTicks() - objs.pickups.xp[i].time > 20000 && i != 0) {
					objs.pickups.xp[i].render = false;
				}
			}
			for (int i = 0; i < objs.pickups.health.size(); ++i) {
				if (SDL_GetTicks() - objs.pickups.health[i].time > 20000) {
					objs.pickups.health[i].render = false;
				}
			}
			for (int i = 0; i < objs.pickups.oil.size(); ++i) {
				if (SDL_GetTicks() - objs.pickups.oil[i].time > 20000) {
					objs.pickups.oil[i].render = false;
				}
			}
			bool clear = true;
			while (clear) {
				clear = false;
				if ((!objs.pickups.xp[objs.pickups.xp.size() - 1].render || objs.pickups.xp[objs.pickups.xp.size() - 1].coord.x >= 90000) && objs.pickups.xp.size() > 1) {
					objs.pickups.xp.resize(objs.pickups.xp.size() - 1);
					clear = true;
				}
				if ((!objs.pickups.health[objs.pickups.health.size() - 1].render || objs.pickups.health[objs.pickups.health.size() - 1].coord.x >= 90000) && objs.pickups.health.size() > 1) {
					objs.pickups.health.resize(objs.pickups.health.size() - 1);
					clear = true;
				}
				if ((!objs.pickups.oil[objs.pickups.oil.size() - 1].render || objs.pickups.oil[objs.pickups.oil.size() - 1].coord.x >= 90000) && objs.pickups.oil.size() > 1) {
					objs.pickups.oil.resize(objs.pickups.oil.size() - 1);
					clear = true;
				}
				if (objs.pickups.xp.size() > 2) {
					if ((!objs.pickups.xp[1].render || objs.pickups.xp[1].coord.x >= 90000)) {
						for (int i = 1; i < objs.pickups.xp.size(); ++i) {
							if (i + 1 < objs.pickups.xp.size()) {
								objs.pickups.xp[i].coord = objs.pickups.xp[i + 1].coord;
								objs.pickups.xp[i].render = objs.pickups.xp[i + 1].render;
								objs.pickups.xp[i].time = objs.pickups.xp[i + 1].time;
							}
						}
						objs.pickups.xp.resize(objs.pickups.xp.size() - 1);
						clear = true;
					}
				}
			}
			/*
			std::cout << "xp size: " << objs.pickups.xp.size() << std::endl;
			std::cout << "health size: " << objs.pickups.health.size() << std::endl;
			std::cout << "oil size: " << objs.pickups.oil.size() << std::endl;*/
		}

		if (character.health > 0) time += 0.02* (120 / (float)fps);

		if (SDL_GetTicks() >= 30000 && !Mix_PlayingMusic()) {
			Mix_FadeInMusic(sfx.music, 0, 4000);
		}

		while (SDL_PollEvent(&evnt)) {
			if (evnt.type == SDL_QUIT) {
				running = false;
			}
		}

		HandleInput();
		Collisions();

		companion.AI();
		crtr.AI();

		if (character.health <= 0) {
			character.health = 0;
			game.upgr = false;
		}

		if (game.levelcmplt) {
			if (!Mix_Playing(4)) Mix_PlayChannel(4, game.sfx.door, 0);
			character.xp += 400;
			character.lanternOil += 3;
			character.health += 30;
			time_night = 0;
			time = 24 * 2 * M_PI*day + 12 * 2 * M_PI;
			screen.bg_coord = {0, 0};
			companion.dog.coord = {0, 0};
			objs.randCabin();
			game.levelcmplt = false;
			game.rain = false;
		}

		if (character.lanternOil > 10)character.lanternOil = 10;
		if (character.xp > character.xp_max)character.xp = character.xp_max;
		if (character.health > 100)character.health = 100;

		if (character.xp >= character.xp_max) {
			character.level += 1;
			character.xp = 0;
			character.xp_max *= 1.2;
			upgr = true;
		}

		if (SDL_GetTicks() - old_ticks >= 20) {
			objs.RandomFloors();
			objs.RandomEnvinronments();
		}

		Render();

		//SDL_Delay(fps_delay);
	}
}
