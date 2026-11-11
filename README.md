# Terminal Game Engine (TGE)

A lightweight, cross-platform **C++ terminal game engine** for developing games directly inside terminal.  
TGE allows terminal graphics, input handling, and audio processing.


## Features

**Colors:** Pre-defined colors using built-in ANSI color palette.  
**Audio:** Simple sound effects and background music playback.  
**Smooth Rendering:** Prevents screen flickering during fast redraws.  
**Cross-Platform:** Compilable for both Linux and Windows.  
**Libraries and accessories:** All libraries, definitions, and color constants are centralized in `tge.hpp`.


## How to include TGE in your project

TGE is made to be easily integrated into any C++ project.

1. Copy all the files and internal directories (like `external/`) into your project directory.
2. Include it at the top of your C++ file:

```c++
    #include "tge.hpp"
```

## How to compile the entire project

TGE is compilable for both Linux and Windows, so you have to use different commands.  
The working compiler TGE was tested with is `g++`.  
Overwrite *FILE_NAME* with the name of your c++ file.

1. Linux:

```cmd
g++ FILE_NAME.cpp TGE/*.cpp -o FILE_NAME -lpthread -ldl -lm
```

2. Windows:

```cmd
x86_64-w64-mingw32-g++ FILE_NAME.cpp TGE/*.cpp -o FILE_NAME.exe -static -lpthread -lwinmm -lole32
```