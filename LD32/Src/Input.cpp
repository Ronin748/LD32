#include "Game\Game.h"

void Game::MouseInput()
{
	SDL_GetMouseState(&input.mouse.x, &input.mouse.y);

	if (screen.fullscreen) {
		input.mouse.x /= screen.scale_x;
		input.mouse.y /= screen.scale_y;
	}

	if (SDL_GetMouseState(NULL, NULL) && evnt.button.button == SDL_BUTTON_LEFT) {
		input.mouse_left = true;
	}
	else {
		input.mouse_left = false;
	}
	if (SDL_GetMouseState(NULL, NULL) && evnt.button.button == SDL_BUTTON_MIDDLE) {
		input.mouse_middle = true;
	}
	else {
		input.mouse_middle = false;
	}
	if (SDL_GetMouseState(NULL, NULL) && evnt.button.button == SDL_BUTTON_RIGHT) {
		input.mouse_right = true;
	}
	else {
		input.mouse_right = false;
	}

	if (input.mouse_left && (input.mouse_old.x != input.mouse.x || input.mouse_old.y != input.mouse.y)) {
		input.mouse_dragging = true;
	}
	else if (!input.mouse_left) {
		input.mouse_dragging = false;
	}

	input.mouse_old.x = input.mouse.x;
	input.mouse_old.y = input.mouse.y;
}

void Game::KeyboardInput()
{
	const Uint8* button = SDL_GetKeyboardState(NULL);

	if (button[SDL_SCANCODE_F11]) {
		if (input.fullscreen_toggle) {
		if (screen.fullscreen) {
		screen.Fullscreen(wndw, 0);
		}
		else {
		screen.Fullscreen(wndw, 1);
		}
		input.fullscreen_toggle = false;

		std::cout << "Fullscreen: " << screen.fullscreen << std::endl;
		}
	}
	else {
		input.fullscreen_toggle = true;
	}

	if (button[SDL_SCANCODE_ESCAPE]) {
		game.running = false;
	}

	screen.bg_coord_old = screen.bg_coord;

	if (character.health > 0) {
		if (button[SDL_SCANCODE_W]) {
			if (game.upgr) {
				if (input.select_toggle_up) {
					--gui.select;
					input.select_toggle_up = false;
					if (gui.select < 0) gui.select = 2;
				}
			}
			else {
				screen.bg_coord.y += 4 * (120 / (float)fps);
			}
		}
		else {
			input.select_toggle_up = true;
		}
		if (button[SDL_SCANCODE_A]) {
			if (!game.upgr) {
				screen.bg_coord.x += 4 * (120 / (float)fps);
				character.character.anim.anim_tex.flip = SDL_FLIP_NONE;
			}
		}
		if (button[SDL_SCANCODE_S]) {
			if (game.upgr) {
				if (input.select_toggle_down) {
					++gui.select;
					input.select_toggle_down = false;
					if (gui.select > 2) gui.select = 0;
				}
			}
			else {
				screen.bg_coord.y -= 4 * (120 / (float)fps);
			}
		}
		else {
			input.select_toggle_down = true;
		}
		if (button[SDL_SCANCODE_D]) {
			if (!game.upgr) {
				screen.bg_coord.x -= 4 * (120 / (float)fps);
				character.character.anim.anim_tex.flip = SDL_FLIP_HORIZONTAL;
			}
		}
		if (button[SDL_SCANCODE_F]) {
			if (input.lantern_toggle && character.lanternOil > 0) {
				if (character.lantern) {
					character.lantern = false;
				}
				else {
					character.lantern = true;
				}
				input.lantern_toggle = false;
			}
		}
		else {
			input.lantern_toggle = true;
		}

		if (button[SDL_SCANCODE_R]) {
			if (input.leash_toggle) {
				input.leash_toggle = false;
				if (character.leashbool) {
					character.leashbool = false;
				}
				else {
					character.leashbool = true;
				}
			}
		}
		else {
			input.leash_toggle = true;
		}

		if (button[SDL_SCANCODE_SPACE]) {
			if (input.spacedown) {
				input.spacedown = false;
				if (objs.cabinCollision) {
					game.levelcmplt = true;
				}
				if (game.upgr) {
					game.upgr = false;
					switch (gui.select) {
					case 0:
						companion.atck += 1;
						break;
					case 1:
						companion.def += 1;
						break;
					case 2:
						companion.spd += 1;
						break;
					}
					if (companion.atck > 4) companion.atck = 4;
					if (companion.def > 4) companion.def = 4;
					if (companion.spd > 4) companion.spd = 4;
				}
			}
			else {
				game.levelcmplt = false;
			}
		}
		else {
			input.spacedown = true;
			game.levelcmplt = false;
		}

		if (button[SDL_SCANCODE_E]) {
			if (input.attack_toggle) {
				input.attack_toggle = false;
				if (companion.attackmode) {
					companion.attackmode = false;
				}
				else {
					companion.attackmode = true;
					companion.defensemode = false;
				}
			}
		}
		else {
			input.attack_toggle = true;
		}
		if (button[SDL_SCANCODE_Q]) {
			if (input.defense_toggle) {
				input.defense_toggle = false;
				if (companion.defensemode) {
					companion.defensemode = false;
				}
				else {
					companion.defensemode = true;
					companion.attackmode = false;
				}
			}
		}
		else {
			input.defense_toggle = true;
		}
	}
	if (button[SDL_SCANCODE_SPACE]) {
		if (input.spacedown) {
			input.spacedown = false;

			if (objs.cabinCollision) game.levelcmplt = true;

			if (character.health <= 0) {
				game.restart();
			}
		}
	}
	else {
		input.spacedown = true;
		game.levelcmplt = false;
	}

	if (screen.bg_coord_old.x != screen.bg_coord.x || screen.bg_coord_old.y != screen.bg_coord.y) {
		character.character.moving = true;
	}
	else {
		character.character.moving = false;
	}
}

void Game::HandleInput()
{
	KeyboardInput();
	MouseInput();
}
