#include "Lib.h"

class Sfx {
public:
	Mix_Chunk* dog;
	Mix_Chunk* bear1;
	Mix_Chunk* bear2;
	Mix_Chunk* wolf;
	Mix_Chunk* rain;
	Mix_Chunk* door;
	Mix_Chunk* hit;
	Mix_Chunk* background;

	Mix_Chunk* pickup;
	Mix_Chunk* damage;

	int damageTicks;
	int hitTicks;

	Mix_Music* music;

	void LoadSound()
	{
		dog = Mix_LoadWAV("Sfx/DogGrowl.wav");
		bear1 = Mix_LoadWAV("Sfx/BearGrowl.wav");
		bear2 = Mix_LoadWAV("Sfx/BearGrowl2.wav");
		wolf = Mix_LoadWAV("Sfx/WolfGrowl.wav");
		rain = Mix_LoadWAV("Sfx/Rain.wav");
		door = Mix_LoadWAV("Sfx/Door.wav");
		pickup = Mix_LoadWAV("Sfx/Pickup.wav");
		damage = Mix_LoadWAV("Sfx/Damage.wav");
		hit = Mix_LoadWAV("Sfx/Hit.wav");
		background = Mix_LoadWAV("Sfx/Background.wav");
		music = Mix_LoadMUS("Sfx/Music.ogg");
		
		Mix_VolumeChunk(bear1, 85);
		Mix_VolumeChunk(bear2, 85);
		Mix_VolumeChunk(wolf, 85);
		Mix_VolumeChunk(hit, 55);

		Mix_VolumeChunk(door, 70);
		Mix_VolumeChunk(damage, 70);
		Mix_VolumeChunk(rain, 120);
		Mix_VolumeChunk(dog, 60);
		Mix_VolumeChunk(background, 25);

		Mix_VolumeMusic(18);
	}

	void PlaySound()
	{
	}

	Sfx()
	{
		hitTicks = 0;
		damageTicks = 0;
	}
};
