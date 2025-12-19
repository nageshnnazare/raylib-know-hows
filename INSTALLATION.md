# Raylib Installation Guide

## Linux (Ubuntu/Debian)

### Method 1: Install from Package Manager (Easiest)
```bash
sudo apt update
sudo apt install libraylib-dev
```

### Method 2: Build from Source (Latest Version)
```bash
# Install dependencies
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev

# Clone raylib repository
git clone https://github.com/raysan5/raylib.git
cd raylib/src

# Build and install
make PLATFORM=PLATFORM_DESKTOP
sudo make install

# Update library cache
sudo ldconfig
```

### Verify Installation
```bash
pkg-config --modversion raylib
```

## Linux (Fedora/RHEL/CentOS)
```bash
# Install dependencies
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel

# Then follow build from source steps above
```

## Linux (Arch)
```bash
sudo pacman -S raylib
```

## macOS

### Using Homebrew
```bash
brew install raylib
```

### Build from Source
```bash
# Install Xcode Command Line Tools first
xcode-select --install

# Clone and build
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install
```

## Windows

### Using MSYS2/MinGW
```bash
# In MSYS2 terminal
pacman -S mingw-w64-x86_64-raylib
```

### Using vcpkg
```bash
vcpkg install raylib
```

### Manual Installation
1. Download raylib from: https://github.com/raysan5/raylib/releases
2. Extract to C:\raylib
3. Add to your compiler's include and library paths

## Compilation Commands

### Linux/macOS
```bash
# Basic compilation
gcc game.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# With all warnings
gcc game.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra

# Debug build
gcc game.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g

# Optimized build
gcc game.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -O2
```

### macOS (sometimes needs fewer flags)
```bash
gcc game.c -o game -lraylib -framework OpenGL -framework Cocoa -framework IOKit
```

### Windows (MinGW)
```bash
gcc game.c -o game.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

## Using CMake

Create `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.11)
project(MyGame C)

find_package(raylib 4.0 REQUIRED)

add_executable(game game.c)
target_link_libraries(game raylib)

# Copy assets to build directory if needed
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
```

Build:
```bash
mkdir build
cd build
cmake ..
make
```

## Using the Provided Scripts

This guide includes helper scripts:

### compile.sh - Compile a single file
```bash
./compile.sh 01_hello_window.c
./01_hello_window
```

### compile_all.sh - Test all examples
```bash
./compile_all.sh
```

## Troubleshooting

### "raylib.h: No such file or directory"
**Solution:** Raylib is not installed or not in include path
- Install raylib using one of the methods above
- Or specify include path: `gcc -I/path/to/raylib/src game.c ...`

### "undefined reference to InitWindow"
**Solution:** Not linking raylib library
- Add `-lraylib` to your compile command
- Check library is in linker path

### "cannot find -lraylib"
**Solution:** Raylib library not in system library path
- Run `sudo ldconfig` after installing (Linux)
- Or specify library path: `gcc -L/path/to/raylib game.c -lraylib ...`

### Window doesn't open / Black screen
**Solution:** Graphics drivers issue
- Update graphics drivers
- Try software rendering: `export LIBGL_ALWAYS_SOFTWARE=1`

### "Display not found" error
**Solution:** No X11 display (Linux)
- Make sure you're running in a graphical environment
- Not SSH session without X forwarding

### Audio doesn't work
**Solution:** Audio device not initialized
- Call `InitAudioDevice()` before audio functions
- Check audio drivers/permissions

### Compilation works but program crashes
**Solution:** Various possibilities
- Check you're calling `InitWindow()` first
- Verify all resources are loaded successfully
- Check for null pointers
- Use debugger: `gdb ./game`

## IDE Setup

### Visual Studio Code
1. Install C/C++ extension
2. Create `.vscode/c_cpp_properties.json`:
```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/local/include"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c11"
        }
    ]
}
```

3. Create `.vscode/tasks.json` for building:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "gcc",
            "args": [
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}",
                "-lraylib",
                "-lGL",
                "-lm",
                "-lpthread",
                "-ldl",
                "-lrt",
                "-lX11",
                "-Wall"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

### CLion
- File → Settings → Build, Execution, Deployment → CMake
- Use the CMakeLists.txt example above

### Code::Blocks
- Settings → Compiler → Linker settings
- Add: raylib, GL, m, pthread, dl, rt, X11

## Minimal Test Program

Save as `test.c` to verify installation:
```c
#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "Raylib Test");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Raylib is working!", 290, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
```

Compile and run:
```bash
gcc test.c -o test -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./test
```

If a window opens with the text, raylib is correctly installed!

## Next Steps

Once raylib is installed:
1. Start with `01_hello_window.c`
2. Work through examples in order
3. Read the explanatory comments in each file
4. Modify examples to experiment
5. Build your own projects!

## Additional Resources

- **Official Documentation:** https://www.raylib.com/
- **API Reference:** https://www.raylib.com/cheatsheet/cheatsheet.html
- **Examples:** https://www.raylib.com/examples.html
- **Wiki:** https://github.com/raysan5/raylib/wiki
- **Discord Community:** https://discord.gg/raylib
- **GitHub:** https://github.com/raysan5/raylib

## Getting Help

If you have issues:
1. Check this troubleshooting section
2. Search raylib GitHub issues
3. Ask on Discord
4. Post on raylib forums

Happy coding! 🎮

