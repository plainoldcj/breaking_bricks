/*
file: sound_manager.h
*/

#pragma once

#include <string>
#include <map>
#include "fmod_wrapper.h"
#include "util_singleton.h"

typedef boost::shared_ptr<FmodSound> soundPtr_t;

class SoundManager : public UTIL::Singleton<SoundManager> {
private:
	typedef std::map<std::string, soundPtr_t> soundMap_t;
	typedef soundMap_t::iterator soundMapIt_t;

	FmodWrapper _fmodWrapper;
	soundMap_t _sounds;
public:
	SoundManager(void);

	void Update(void);

	soundPtr_t GetSound(const std::string& filename, bool loop);
};