# Terminal Game Engine (TGE)

A lightweight **C++ terminal game engine** for developing games directly inside the terminal.  
TGE allows terminal graphics, input handling, and audio processing.


## Features

**Colors:** Pre-defined colors using built-in ANSI color palette.  
**Audio:** Simple sound effects and background music playback.  
**Smooth Rendering:** Prevents screen flickering during fast redraws.    
**Libraries and accessories:** All libraries, definitions, and color constants are centralized in `tge.hpp`.


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
Replace *FILE_NAME* with the name of your c++ file.

1. ELF:

```cmd
g++ FILE_NAME.cpp TerminalGameEngine/*.cpp -o FILE_NAME -lpthread -ldl -lm
```

2. .exe:

```cmd
x86_64-w64-mingw32-g++ FILE_NAME.cpp TerminalGameEngine/*.cpp -o FILE_NAME.exe -static -lpthread -lwinmm -lole32
```
