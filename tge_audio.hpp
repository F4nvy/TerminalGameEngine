#pragma once

#define MINIAUDIO_IMPLEMENTATION

#include <string>

#include "external/miniaudio.h"

class Audio {
	private:
    	ma_engine soundEngine;
    	ma_sound backgroundMusic;
    	bool initialized = 0;
    	bool backgroundMusicLoaded = 0;

	public:
    	Audio ();

    	~Audio ();

    	void playSound (const std::string& filename);

    	void playMusic (const std::string& filename);
};
