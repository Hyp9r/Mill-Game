#include "AudioPlayer.h"



AudioPlayer::AudioPlayer()
{
}


AudioPlayer::~AudioPlayer()
{
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavStart);
}

void AudioPlayer::load(const char * filename) {
	SDL_LoadWAV(filename, &wavSpec, &wavStart, &wavLength);
	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void AudioPlayer::play() {
	SDL_QueueAudio(deviceId, wavStart, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
}

void AudioPlayer::pauseSound() {
	SDL_PauseAudioDevice(deviceId, 1);
}


