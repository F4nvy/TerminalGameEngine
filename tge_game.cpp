#include "tge.hpp"

char Game::waitForInput (){
    #ifdef _WIN32
        return _getch ();
    #else
        return std::cin.get ();
    #endif
}

Game::Game (const std::string name, const uint8_t width, const uint8_t height) : name (name), screen (this, width, height){
    if (width == 0 || height == 0) return;

    #ifdef _WIN32
        SetConsoleOutputCP (CP_UTF8);

        HANDLE hOut = GetStdHandle (STD_OUTPUT_HANDLE);

        if (hOut != INVALID_HANDLE_VALUE){
            DWORD dwMode = 0;

            if (GetConsoleMode (hOut, &dwMode)){
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode (hOut, dwMode);
            }
        }
    #else
        system ("stty -icanon -echo");
    #endif

    std::ios::sync_with_stdio (0);

    std::cout << "\033]0;" << name << "\007";
    std::cout << "\033[8;" << (int)(height/2) << ";" << (int)width << "t";

    std::cout << "\033[?1049h"; // scrollbar
    std::cout << "\033[?25l"; // cursor

    std::cout << std::flush;
}

Game::~Game (){
    std::cout << "\033[2J\033[H"; // erase

    std::cout << "\033[?1049l"; // scrollbar
    std::cout << "\033[?25h"; // cursor

    std::cout << std::flush;

    #ifndef _WIN32
        system ("stty cooked echo");
    #endif
}
