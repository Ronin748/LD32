#include "..\Texture.h"

class Anim {
public:
	Txtr anim_tex;
	int animation;
	int animation_length;

	int animation_time;
	int ms;

	std::vector <int> animation_cycle;

	void LoadAnimation(SDL_Renderer* rndr, std::string path, std::vector <SDL_Rect> tex_sprite, int speed, std::vector <int> cycle)
	{
		animation_cycle = cycle;
		ms = speed;
		animation_length = cycle.size();

		anim_tex.tex = IMG_LoadTexture(rndr, path.c_str());
		SDL_SetTextureBlendMode(anim_tex.tex, SDL_BLENDMODE_BLEND);

		for (int i = 0; i < tex_sprite.size(); ++i) {
			anim_tex.sprite.resize(anim_tex.sprite.size() + 1);
			anim_tex.sprite[anim_tex.sprite.size() - 1] = tex_sprite[i];
		}
	}

	Anim()
	{
		animation = 0;
	}

	void Anim::RenderAnimation(int x, int y, float size, bool bg);
	int AnimationTick();
};