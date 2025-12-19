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

# Compile with raylib
gcc "$SOURCE_FILE" -o "$OUTPUT_FILE" -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo "Run with: ./$OUTPUT_FILE"
else
    echo "✗ Compilation failed!"
    exit 1
fi

