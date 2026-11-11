#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdint>
#include <vector>
#include <string>
#include <cmath>

#include "miniaudio.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <sys/ioctl.h>
#endif

#define DRED        "5;52"
#define RED         "5;124"
#define LRED        "5;196"
#define ORANGE      "5;166"
#define LORANGE     "5;208"
#define PINK        "5;198"
#define LPINK       "5;212"

#define GOLD        "5;178"
#define YELLOW      "5;220"
#define LYELLOW     "5;226"

#define DGREEN      "5;22"
#define GREEN       "5;28"
#define LGREEN      "5;46"
#define LIME        "5;118"
#define OLIVE       "5;58"

#define NAVY        "5;17"
#define DBLUE       "5;19"
#define BLUE        "5;27"
#define LBLUE       "5;39"
#define SKYBLUE     "5;117"
#define TEAL        "5;30"
#define LTEAL       "5;51"

#define DPURPLE     "5;54"
#define PURPLE      "5;90"
#define LPURPLE     "5;129"
#define VIOLET      "5;141"

#define DBROWN      "5;94"
#define BROWN       "5;130"
#define LBROWN      "5;172"
#define TAN         "5;180"
#define BEIGE       "5;223"

#define BLACK       "5;16"
#define VDGRAY      "5;234"
#define DGRAY       "5;238"
#define GRAY        "5;242"
#define LGRAY       "5;247"
#define VLGRAY      "5;251"
#define WHITE       "5;255"

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

class Game;

class Screen {
    private:
        const Game* GameAdress;

        std::vector <std::string> board;

        const std::string emptyColor = DGRAY;

        std::string currentFillColor = BLACK;
        std::string currentStrokeColor = BLACK;

    public:
        const uint8_t width;
        const uint8_t height;

        void draw ();
        void clear (const std::string& color);
        void add (int16_t x, int16_t y, const std::string& color);
        void fillColor (const std::string& color);
        void strokeColor (const std::string& color);
        void fillRect (int16_t x, int16_t y, uint8_t width, uint8_t height);
        void strokeRect (int16_t x, int16_t y, uint8_t width, uint8_t height);
        void drawSprite (int16_t x, int16_t y, uint8_t width, uint8_t height, const std::vector <std::vector <std::string>>& sprite);
        void line (int16_t x1, int16_t y1, int16_t x2, int16_t y2);

        Screen (const Game* GameAdress, const uint8_t width, const uint8_t height);
};

class Game {
    public:
        const std::string name;

        Screen screen;

        Audio audio;

        char waitForInput ();

	Game (const std::string name, const uint8_t width, const uint8_t height);

        ~Game ();
};
