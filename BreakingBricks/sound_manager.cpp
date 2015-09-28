/*
file: sound_manager.cpp
*/

#include "sound_manager.h"

SoundManager::SoundManager(void) {
	_fmodWrapper.Init();
}

void SoundManager::Update(void) {
	_fmodWrapper.Update();
}

soundPtr_t SoundManager::GetSound(const std::string& filename, bool loop) {
	soundMapIt_t soundMapIt(_sounds.find(filename));
	if(_sounds.end() == soundMapIt) {
		soundPtr_t sound = _fmodWrapper.CreateSound(filename, loop);
		_sounds[filename] = sound;
		soundMapIt = _sounds.find(filename);
	}
	return soundMapIt->second;
}