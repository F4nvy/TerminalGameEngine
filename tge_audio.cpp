#include "tge.hpp"
#include "external/miniaudio.h"

Audio::Audio (){
    if (ma_engine_init (0, &soundEngine) == 0) initialized = 1;
}

Audio::~Audio (){
    if (initialized){
        if (backgroundMusicLoaded) ma_sound_uninit (&backgroundMusic);
        ma_engine_uninit (&soundEngine);
    }
}

void Audio::playSound (const std::string& filename){
    if (!initialized) return;
    ma_engine_play_sound (&soundEngine, filename.c_str (), 0);
}

void Audio::playMusic (const std::string& filename){
    if (!initialized) return;

    if (backgroundMusicLoaded){
        ma_sound_uninit (&backgroundMusic);
        backgroundMusicLoaded = 0;
    }

    if (ma_sound_init_from_file (&soundEngine, filename.c_str (), 0, 0, 0, &backgroundMusic) == 0){
        ma_sound_set_looping (&backgroundMusic, 1);
        ma_sound_start (&backgroundMusic);
        backgroundMusicLoaded = 1;
    }
}
