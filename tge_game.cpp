#include "tge.hpp"

void Png::load (const std::string& file){
	data.clear ();

	lodepng::decode (data, width, height, file);
}

uint8_t Png::ch (uint8_t x, uint8_t y, uint8_t num){
	uint32_t index = 4 * (y * width + x) + num;

	return data [index];
}

char Game::getInput (){
	char lastKey = 0;
    
    #ifdef _WIN32
        while (_kbhit ()){
            lastKey = _getch ();
        }
    #else
        char ch = 0;
        
        while (read (STDIN_FILENO, &ch, 1) > 0){
            lastKey = static_cast <char> (ch);
        }
    #endif
    
    return lastKey;
}

void Game::sleepFor (uint16_t time){
	std::this_thread::sleep_for (std::chrono::milliseconds (time));
}

Game::Game (const std::string name, const uint8_t width, const uint8_t height) : name (name), screen (this, width, height){
    if (width == 0 || height == 0) return;

	#ifdef _WIN32
		HANDLE hOut = GetStdHandle (STD_OUTPUT_HANDLE);
		GetConsoleMode (hOut, &origOutMode);
		SetConsoleMode (hOut, origOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		origCodePage = GetConsoleOutputCP ();
		SetConsoleOutputCP (CP_UTF8);
	#else
		tcgetattr (STDIN_FILENO, &origTermios);
		termios raw = origTermios;
		
		raw.c_lflag &= ~(ICANON | ECHO); // turn off waiting for Enter
		raw.c_cc [VMIN] = 0; // read () is not waiting for any byte
		raw.c_cc [VTIME] = 0; // zero timeout
		tcsetattr (STDIN_FILENO, TCSANOW, &raw);
	#endif

	std::string initializationSeq;

	initializationSeq += "\033[?1049h"; // alternate buffer
	initializationSeq += "\033[8;" + std::to_string (height / 2) + ";" + std::to_string (width) + "t";
	initializationSeq += "\033[?7l"; // turn off line ending
	initializationSeq += "\033[?25l"; // hide cursor
    initializationSeq += "\033]0;" + name + "\007";
    initializationSeq += "\033[2J\033[H"; // clear terminal and set cursor to [1, 1]

    std::cout << initializationSeq << std::flush;
}

Game::~Game (){
    std::cout << "\033[0m\033[?7h\033[?25h\033[2J\033[H\033[?1049l" << std::flush;

    #ifdef _WIN32
        HANDLE hOut = GetStdHandle (STD_OUTPUT_HANDLE);
        SetConsoleMode (hOut, origOutMode);
		SetConsoleOutputCP (origCodePage);
    #else
        tcsetattr (STDIN_FILENO, TCSANOW, &origTermios);
    #endif
}
