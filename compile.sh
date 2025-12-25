#!/bin/bash
# Raylib Compilation Script
# Usage: ./compile.sh filename.c

if [ $# -eq 0 ]; then
    echo "Usage: ./compile.sh filename.c"
    exit 1
fi

SOURCE_FILE="$1"
OUTPUT_FILE="${SOURCE_FILE%.c}"

echo "Compiling $SOURCE_FILE..."

# Check OS
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    RAYLIB_FLAGS="-lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -I/opt/homebrew/include -L/opt/homebrew/lib"
else
    # Linux (assuming default names)
    RAYLIB_FLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
fi

# Compile with raylib
gcc -g "$SOURCE_FILE" -o "$OUTPUT_FILE" $RAYLIB_FLAGS

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo "Run with: ./$OUTPUT_FILE"
else
    echo "✗ Compilation failed!"
    exit 1
fi

