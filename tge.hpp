#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include "external/miniaudio.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

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

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
    bool transparent = false;

    bool operator == (const Color& other) const;
    bool operator != (const Color& other) const;
};

class Game;

class Screen {
    private:
        const Game* GameAdress;

        std::vector <Color> board;
        std::vector <Color> prevBoard;

        const Color emptyColor = {100, 100, 100};

        Color currentFillColor = {0, 0, 0};
        Color currentStrokeColor = {0, 0, 0};

    public:
        const uint8_t width;
        const uint8_t height;

        void draw ();
        void clear (const Color color);
        void add (int16_t x, int16_t y, const Color color);

        void fillColor (const Color color);
        void strokeColor (const Color color);
        
        void fillRect (int16_t x, int16_t y, uint8_t width, uint8_t height);
        void strokeRect (int16_t x, int16_t y, uint8_t width, uint8_t height);
        void drawSprite (int16_t x, int16_t y, uint8_t width, uint8_t height, const std::vector <std::vector <Color>>& sprite);
        void line (int16_t x1, int16_t y1, int16_t x2, int16_t y2);

        Screen (const Game* GameAdress, const uint8_t width, const uint8_t height);
};

class Game {
	private:
		#ifdef _WIN32
	       	unsigned long origOutMode = 0;
	       	unsigned int origCOdePage = 0;
	    #else
	       	termios origTermios {};
	  	#endif
    public:
        const std::string name;

        Screen screen;

        Audio audio;

        char getInput ();

		void sleepFor (uint16_t time);
		
	    Game (const std::string name, const uint8_t width, const uint8_t height);

        ~Game ();
};
