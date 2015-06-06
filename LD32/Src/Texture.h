#ifndef TEX_H
#define TEX_H

#include "Lib.h"

class Rect_float {
public:
	float x;
	float y;
	float w;
	float h;

};

class Point_float {
public:
	float x;
	float y;
};

class Txtr {
public:
	SDL_Texture* tex;
	Rect_float coords;
	std::vector <SDL_Rect> sprite;
	SDL_RendererFlip flip;
	int depth;

	void NewSprite(std::vector <SDL_Rect> new_sprite)
	{
		for (int i = 0; i < new_sprite.size(); ++i) {
			sprite.resize(sprite.size() + 1);
			sprite[sprite.size() - 1] = new_sprite[i];
		}
	}

	SDL_Texture* LoadTex(SDL_Renderer* rndr, std::string path, std::vector <SDL_Rect> tex_sprite)
	{
		//if (tex != NULL) SDL_DestroyTexture(tex);
		tex = IMG_LoadTexture(rndr, path.c_str());

		for (int i = 0; i < tex_sprite.size(); ++i) {
			sprite.resize(sprite.size() + 1);
			sprite[sprite.size() - 1] = tex_sprite[i];
		}

		return tex;
	}

	void Txtr::RenderTex(int x, int y, int sprite_i);

	Txtr()
	{
		coords = {0, 0, 0, 0};
	}
};

class Fx {
public:
	Txtr dark;
	Txtr lanternGlow;
	Txtr rain;

	void LoadFx(SDL_Renderer* rndr)
	{
		lanternGlow.LoadTex(rndr, "Gfx/Fx/LanternGlow.png", {{0, 0, 362, 213}});
		lanternGlow.coords = {0, 0, 1024, 600};
		dark.LoadTex(rndr, "Gfx/Fx/LanternGlow.png", {{0, 0, 32, 32}});
		dark.coords = {0, 0, 1024, 600};
		rain.LoadTex(rndr, "Gfx/Fx/Rain.png", {{0, 0, 68, 63}});
		rain.coords = {0, 0, 1024, 378};

		SDL_SetTextureBlendMode(lanternGlow.tex, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(dark.tex, SDL_BLENDMODE_BLEND);
	}
};

class Text {
public:
	TTF_Font* font;
	std::string str;
	SDL_Texture* text;

	SDL_Color col;

	int w;
	int h;

	SDL_Texture* Text_to_Texture(SDL_Renderer* rndr, std::string string)
	{
		if (text != NULL) SDL_DestroyTexture(text);
		if (font == NULL) font = TTF_OpenFont("Gfx/Misc/font.ttf", 20);
		SDL_Surface* txt_srfc = TTF_RenderText_Solid(font, string.c_str(), col);
		text = SDL_CreateTextureFromSurface(rndr, txt_srfc);

		SDL_QueryTexture(text, NULL, NULL, &w, &h);
		SDL_FreeSurface(txt_srfc);

		return text;
	}

	void RenderText(int x, int y, float size);

	Text()
	{
		font = TTF_OpenFont("Gfx/Misc/font.ttf", 20);
		col = {255, 255, 255, 255};
	}
};

#endif