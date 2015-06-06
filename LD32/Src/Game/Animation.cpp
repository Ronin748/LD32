#include "Game.h"

void Anim::RenderAnimation(int x, int y, float size, bool bg)
{
	Rndr(anim_tex.tex, {x, y, floor(anim_tex.sprite[animation_cycle[animation]].w * 4 * (float)size + 0.9), floor(anim_tex.sprite[animation_cycle[animation]].h * 4 * (float)size + 0.9)}, anim_tex.sprite[animation_cycle[animation]], 0, {0, 0}, anim_tex.flip, 0, 0, 0, bg);
}

int Anim::AnimationTick()
{
	if (SDL_GetTicks() - animation_time >= ms) {
		++animation;
		animation_time = SDL_GetTicks();
	}

	if (animation >= animation_length) {
		animation = 0;
	}
	return animation;
}