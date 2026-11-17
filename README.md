# Terminal Game Engine (TGE)

A lightweight **C++ terminal game engine** for developing games directly inside the terminal.  
TGE allows terminal graphics, input handling, and audio processing.


## Features

**Colors:** RGB color system using 24-bit TrueColor RGB.  
**Audio:** Simple sound effects and background music playback.
**PNGs:** NEW functions for reading and drawing PNG images.
**Smooth Rendering:** Prevents screen flickering during fast redraws.    
**Libraries and accessories:** All libraries and definitions are centralized in `tge.hpp`.


## How to download TGE

### Method 1: git clone

1. Open your project directory (with your C++ file) and open it inside the terminal.
2. Write this to copy TGE into your project directory:

```cmd
git clone https://github.com/F4nvy/TerminalGameEngine.git
```

### Method 2: ZIP

1. Download all the TGE files and internal directories (like `external/`) as ZIP and extract it.
2. Put the whole TerminalGameEngine folder into your project directory.


## How to include TGE in your project

TGE is made to be easily integrated into any C++ project.

```C++
#include "TerminalGameEngine/tge.hpp"
```

## How to compile the entire project

TGE is compilable on Linux as ELF (for Linux) and .exe (for Windows), so you have to use different commands.  
The working compiler TGE was tested with is `g++`. 

`Os` and `-s` are optimizing the compiled program. You can omit this during testing for faster compiling.
 
Replace *FILE_NAME* with the name of your C++ file.

1. ELF:

```cmd
g++ -Os -s FILE_NAME.cpp TerminalGameEngine/*.cpp -o FILE_NAME -pthread -ldl -lm
```

2. .exe:

```cmd
x86_64-w64-mingw32-g++ -Os -s FILE_NAME.cpp TerminalGameEngine/*.cpp -o FILE_NAME.exe -static -lwinmm -lole32
```
If you don't use any audio, you can delete `-pthread -ldl -lm` (for Linux) and `-static -lwinmm -lole32` (for Windows).


## Example

```C++
#include "TerminalGameEngine/tge.hpp"
#include "TerminalGameEngine/tge_audio.hpp"

int main (){
    Game game ("My Terminal Game :-)", 120, 70);
	Audio audio;

	Png sprite (); // initialization

	// image.png has to be in the same folder
	sprite.load ("image.png");
    
    // music.mp3 has to be in the same folder
    // plays in loop
    audio.playMusic ("music.mp3");

    int16_t x = 30;
    int16_t y = 20;
    uint8_t size = 12;
    
    while (1){

        game.screen.clear ({100, 100, 100}); // RGB

        game.screen.strokeColor ({255, 255, 255});
        game.screen.line (0, 0, game.screen.width, game.screen.height);

        game.screen.fillColor ({220, 20, 20});
        game.screen.fillRect (x, y, size, size);

        game.screen.strokeColor ({20, 255, 100});
        game.screen.strokeRect (x, y, size, size);

        game.screen.drawSprite (50, 30, sprite);
        
        game.screen.draw ();

        char input = game.getInput ();

        if (input == 'w' || input == 'W') y--;
        if (input == 's' || input == 'S') y++;
        if (input == 'a' || input == 'A') x--;
        if (input == 'd' || input == 'D') x++;
        
        // sound.mp3 has to be in the same folder
        audio.playSound ("sound.mp3");
        
        if (input == 'q' || input == 'Q') break;

        game.sleepFor (20); // sleeps for 20 ms
        
    }

    return 0;
}
```
