#include "Game\Game.h"

class GUI {
public:
	Txtr bars;
	Txtr clock;
	Txtr oil;
	Txtr attackModes;

	Text oilTxt;
	Text attack;
	Text defense;
	Text attackTxt;
	Text defenseTxt;
	Text attackLvl;
	Text defenseLvl;
	Text day;
	Text level;
	Text cabin;
	Text dark;
	Text death;
	Text fps;

	Txtr upgrSelect;
	int select;
	Text atck;
	Text def;
	Text spd;

	Txtr attackLvls;
	Txtr selector;

	void RenderBars();
	void RenderGUI();

	void LoadGUI(SDL_Renderer* rndr)
	{
		bars.LoadTex(rndr, "Gfx/GUI/Bars.png", {{4, 3, 89, 7}, {5, 18, 87, 2}, {15, 21, 67, 2}, {107, 2, 10, 19}, {121, 3, 8, 17}});//health & xp
		clock.LoadTex(rndr, "Gfx/GUI/GUI.png", {{0, 0, 14, 13}, {16, 2, 1, 5}});
		oil.LoadTex(rndr, "Gfx/GUI/GUI.png", {{20, 0, 6, 8}});
		attackModes.LoadTex(rndr, "Gfx/GUI/GUI.png", {{0, 14, 16, 16}});
		attackLvls.LoadTex(rndr, "Gfx/GUI/GUI.png", {{18, 14, 13, 13}, {35, 15, 14, 15}});
		selector.LoadTex(rndr, "Gfx/GUI/GUI.png", {{0, 32, 16, 16}});
		upgrSelect.LoadTex(rndr, "Gfx/GUI/GUI.png", {{54, 0, 60, 34}, {55, 35, 58, 10}});

		oilTxt.Text_to_Texture(rndr, "Oil");
		attack.Text_to_Texture(rndr, "E");
		defense.Text_to_Texture(rndr, "Q");
		attackTxt.Text_to_Texture(rndr, "Attack");
		defenseTxt.Text_to_Texture(rndr, "Defense");
		attackLvl.Text_to_Texture(rndr, "I I I I");
		defenseLvl.Text_to_Texture(rndr, "I I I I");
		cabin.Text_to_Texture(rndr, "Space to enter");
		dark.Text_to_Texture(rndr, "You have been consumed by the darkness... (space to continue)");
		death.Text_to_Texture(rndr, "You have died (space to continue)");

		day.Text_to_Texture(rndr, "Day: 1");
		level.Text_to_Texture(rndr, "Level: 1       XP: 0/1000");
	}
};