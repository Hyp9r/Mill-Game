#pragma once
#include <SDL.h>
#include <iostream>

class AudioPlayer
{
	struct AudioData
	{
		Uint8* pos;
		Uint32 length;
	};
public:
	AudioPlayer();
	~AudioPlayer();
	void load(const char * filename);
	void play();
	void pauseSound();
private:

	/*Sound*/
	SDL_AudioSpec wavSpec;
	Uint8* wavStart;
	Uint32 wavLength;
	SDL_AudioDeviceID deviceId;
};

