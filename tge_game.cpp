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

    int cols = (width > 2) ? width : 2;
    int rows = (height / 2 > 2) ? (height / 2) : 2;

    #ifdef _WIN32
        SetConsoleOutputCP (CP_UTF8);
        SetConsoleCP (CP_UTF8);

        HANDLE hOut = GetStdHandle (STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &origOutMode)){
            DWORD outMode = origOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode (hOut, outMode);
        }

        HANDLE hIn = GetStdHandle (STD_INPUT_HANDLE);
        if (hIn != INVALID_HANDLE_VALUE && GetConsoleMode (hIn, &origInMode)){
            DWORD inMode = (origInMode | ENABLE_EXTENDED_FLAGS) & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_QUICK_EDIT_MODE);
            SetConsoleMode (hIn, inMode);
        }
    #else
        if (tcgetattr (STDIN_FILENO, &origTermios) == 0){
            struct termios raw = origTermios;
            raw.c_lflag &= ~(ICANON | ECHO);
            tcsetattr (STDIN_FILENO, TCSANOW, &raw);
        }
    #endif

    std::ios::sync_with_stdio (false);
    std::cin.tie (nullptr);

    std::cout << "\033]0;" << name << "\007" << "\033[?1049h" << "\033[?25l" << std::flush;

    #ifdef _WIN32
        if (hOut != INVALID_HANDLE_VALUE){
            COORD maxSize = GetLargestConsoleWindowSize (hOut);
            SHORT targetCols = (cols < maxSize.X) ? static_cast <SHORT> (cols) : maxSize.X;
            SHORT targetRows = (rows < maxSize.Y) ? static_cast <SHORT> (rows) : maxSize.Y;

            SMALL_RECT tinyRect = {0, 0, 1, 1};
            SetConsoleWindowInfo (hOut, TRUE, &tinyRect);

            COORD bufferSize = {targetCols, targetRows};
            SetConsoleScreenBufferSize (hOut, bufferSize);

            SMALL_RECT windowRect = {0, 0, static_cast <SHORT> (targetCols - 1), static_cast <SHORT> (targetRows - 1)};
            SetConsoleWindowInfo (hOut, TRUE, &windowRect);
        }
    #else
        std::cout << "\033[8;" << rows << ";" << cols << "t" << std::flush;
    #endif
}

Game::~Game (){
    std::cout << "\033[?25h" << "\033[?1049l" << std::flush;

    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) SetConsoleMode(hOut, origOutMode);

        HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
        if (hIn != INVALID_HANDLE_VALUE) SetConsoleMode(hIn, origInMode);
    #else
        tcsetattr(STDIN_FILENO, TCSANOW, &origTermios);
    #endif
}
