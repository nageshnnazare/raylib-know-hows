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

# Counters
total=0
success=0
failed=0

# Check if raylib is installed
echo "Checking for raylib installation..."
if ! command -v pkg-config &> /dev/null || ! pkg-config --exists raylib; then
    echo -e "${YELLOW}Warning: raylib may not be properly installed${NC}"
    echo "Attempting compilation anyway..."
fi
echo ""

# Function to compile a single file
compile_file() {
    local file=$1
    local output="${file%.c}"
    
    echo -n "Compiling $file... "
    
    # Try to compile
    if gcc "$file" -o "$output" -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall 2>/dev/null; then
        echo -e "${GREEN}✓ SUCCESS${NC}"
        rm -f "$output"  # Clean up the binary
        return 0
    else
        echo -e "${RED}✗ FAILED${NC}"
        # Show error details
        echo -e "${RED}Error details:${NC}"
        gcc "$file" -o "$output" -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall 2>&1 | head -5
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
    echo ""
    echo "To run an example:"
    echo "  1. Compile it: ./compile.sh filename.c"
    echo "  2. Run it: ./filename"
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

