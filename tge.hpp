#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#include "external/lodepng.h"

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
    bool a = 1;

    bool operator == (const Color& other) const;
    bool operator != (const Color& other) const;
};

class Png {
	public:
		uint32_t width = 0;
		uint32_t height = 0;

		std::vector <uint8_t> data;

		void load (const std::string& file);

		uint8_t	ch (uint8_t x, uint8_t y, uint8_t num);
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
        void drawPng (int16_t x, int16_t y, Png& png);
        void line (int16_t x1, int16_t y1, int16_t x2, int16_t y2);

        Screen (const Game* GameAdress, const uint8_t width, const uint8_t height);
};

class Game {
	private:
		#ifdef _WIN32
	       	unsigned long origOutMode = 0;
	       	unsigned int origCodePage = 0;
	    #else
	       	termios origTermios {};
	  	#endif
    public:
        const std::string name;

        Screen screen;

        char getInput ();

		void sleepFor (uint16_t time);
		
	    Game (const std::string name, const uint8_t width, const uint8_t height);

        ~Game ();
};
