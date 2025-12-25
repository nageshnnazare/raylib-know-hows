#!/bin/bash
# Comprehensive compilation and verification script for all raylib examples
# This script compiles all C files and reports any errors

echo "============================================"
echo "  Raylib Examples Compilation Test"
echo "============================================"
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

RAYLIB_PATH=/opt/homebrew/include
RAYLIB_LIB_PATH=/opt/homebrew/lib

# Counters
total=0
success=0
failed=0

# Parse arguments
SAVE_BIN=false
BIN_DIR="./bin"

for arg in "$@"; do
    case $arg in
        --bin|-b)
            SAVE_BIN=true
            ;;
    esac
done

if [ "$SAVE_BIN" = true ]; then
    mkdir -p "$BIN_DIR"
fi

# Check if raylib is installed
echo "Checking for raylib installation..."
if ! command -v pkg-config &> /dev/null || ! pkg-config --exists raylib; then
    echo -e "${YELLOW}Warning: raylib may not be properly installed${NC}"
    echo "Attempting compilation anyway..."
fi
echo ""

# Check OS
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    PLATFORM_FLAGS="-lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -I/opt/homebrew/include -L/opt/homebrew/lib"
else
    # Linux
    PLATFORM_FLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -I${RAYLIB_PATH} -L${RAYLIB_LIB_PATH}"
fi

# Function to compile a single file
compile_file() {
    local file=$1
    local filename="${file%.c}"
    local output="$filename"
    
    if [ "$SAVE_BIN" = true ]; then
        output="$BIN_DIR/$filename"
    fi

    echo -n "Compiling $file... "

    # Try to compile
    if gcc "$file" -o "$output" $PLATFORM_FLAGS -Wall 2>/dev/null; then
        echo -e "${GREEN}✓ SUCCESS${NC}"
        if [ "$SAVE_BIN" = false ]; then
            rm -f "$output"  # Clean up the binary if not saving
        fi
        return 0
    else
        echo -e "${RED}✗ FAILED${NC}"
        # Show error details
        echo -e "${RED}Error details:${NC}"
        gcc "$file" -o "$output" $PLATFORM_FLAGS -Wall 2>&1 | head -10
        echo ""
        return 1
    fi
}

echo "============================================"
echo "  Compiling all examples..."
echo "============================================"
echo ""

# Find all .c files and compile them
for file in *.c; do
    if [ -f "$file" ]; then
        ((total++))
        if compile_file "$file"; then
            ((success++))
        else
            ((failed++))
        fi
    fi
done

echo ""
echo "============================================"
echo "  Compilation Summary"
echo "============================================"
echo -e "Total files:    $total"
echo -e "${GREEN}Successful:     $success${NC}"
echo -e "${RED}Failed:         $failed${NC}"
echo ""

if [ $failed -eq 0 ]; then
    echo -e "${GREEN}✓ All examples compiled successfully!${NC}"
    if [ "$SAVE_BIN" = true ]; then
        echo -e "Executables are located in: ${YELLOW}$BIN_DIR${NC}"
        echo ""
        echo "To run an example:"
        echo "  ./bin/filename"
    else
        echo ""
        echo "To run an example:"
        echo "  1. Compile it: ./compile.sh filename.c"
        echo "  2. Run it: ./filename"
    fi
    exit 0
else
    echo -e "${YELLOW}⚠ Some examples failed to compile${NC}"
    echo ""
    echo "Common issues:"
    echo "  - Raylib not installed: Install with instructions in README.md"
    echo "  - Missing dependencies: Install required libraries"
    echo "  - Compiler not found: Install gcc"
    exit 1
fi

