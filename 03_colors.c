/*******************************************************************************************
*
*   RAYLIB LESSON 03: Colors
*   
*   Learn how to work with colors in raylib. Understanding colors is essential
*   for creating visually appealing games!
*
*******************************************************************************************/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - colors");
    
    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        BeginDrawing();

            // ============================================================
            // BASIC COLORS
            // ============================================================
            
            // Raylib provides many predefined colors you can use directly
            // These are constants defined in raylib.h
            ClearBackground(RAYWHITE);
            
            DrawText("COLOR BASICS", 280, 20, 30, DARKGRAY);
            
            // ============================================================
            // PREDEFINED COLORS
            // ============================================================
            
            // Raylib has many predefined colors ready to use:
            // BLACK, WHITE, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, etc.
            
            int y = 60;  // Starting Y position for drawing
            int spacing = 25;  // Space between each color example
            
            DrawRectangle(50, y, 100, 20, RED);
            DrawText("RED", 160, y, 20, RED);
            y += spacing;
            
            DrawRectangle(50, y, 100, 20, GREEN);
            DrawText("GREEN", 160, y, 20, GREEN);
            y += spacing;
            
            DrawRectangle(50, y, 100, 20, BLUE);
            DrawText("BLUE", 160, y, 20, BLUE);
            y += spacing;
            
            DrawRectangle(50, y, 100, 20, YELLOW);
            DrawText("YELLOW", 160, y, 20, YELLOW);
            y += spacing;
            
            DrawRectangle(50, y, 100, 20, ORANGE);
            DrawText("ORANGE", 160, y, 20, ORANGE);
            y += spacing;
            
            DrawRectangle(50, y, 100, 20, PURPLE);
            DrawText("PURPLE", 160, y, 20, PURPLE);
            y += spacing;
            
            DrawRectangle(50, y, 100, 20, PINK);
            DrawText("PINK", 160, y, 20, PINK);
            y += spacing;
            
            DrawRectangle(50, y, 100, 20, MAROON);
            DrawText("MAROON", 160, y, 20, MAROON);
            
            // ============================================================
            // CUSTOM COLORS - RGBA
            // ============================================================
            
            // You can create custom colors using RGBA values
            // RGBA stands for: Red, Green, Blue, Alpha (transparency)
            // Each value ranges from 0 to 255
            // 
            // Color structure: { R, G, B, A }
            // R = Red component (0-255)
            // G = Green component (0-255)
            // B = Blue component (0-255)
            // A = Alpha/transparency (0=invisible, 255=fully solid)
            
            DrawText("CUSTOM COLORS (RGBA)", 320, 60, 20, DARKGRAY);
            
            y = 90;  // Reset Y position for right column
            
            // Pure red: full red, no green, no blue
            Color pureRed = { 255, 0, 0, 255 };
            DrawRectangle(320, y, 100, 20, pureRed);
            DrawText("(255, 0, 0)", 430, y, 15, DARKGRAY);
            y += spacing;
            
            // Pure green: no red, full green, no blue
            Color pureGreen = { 0, 255, 0, 255 };
            DrawRectangle(320, y, 100, 20, pureGreen);
            DrawText("(0, 255, 0)", 430, y, 15, DARKGRAY);
            y += spacing;
            
            // Pure blue: no red, no green, full blue
            Color pureBlue = { 0, 0, 255, 255 };
            DrawRectangle(320, y, 100, 20, pureBlue);
            DrawText("(0, 0, 255)", 430, y, 15, DARKGRAY);
            y += spacing;
            
            // Mixing colors: equal amounts of red and green makes yellow
            Color customYellow = { 255, 255, 0, 255 };
            DrawRectangle(320, y, 100, 20, customYellow);
            DrawText("(255, 255, 0)", 430, y, 15, DARKGRAY);
            y += spacing;
            
            // Cyan: green + blue
            Color cyan = { 0, 255, 255, 255 };
            DrawRectangle(320, y, 100, 20, cyan);
            DrawText("(0, 255, 255)", 430, y, 15, DARKGRAY);
            y += spacing;
            
            // Magenta: red + blue
            Color magenta = { 255, 0, 255, 255 };
            DrawRectangle(320, y, 100, 20, magenta);
            DrawText("(255, 0, 255)", 430, y, 15, DARKGRAY);
            y += spacing;
            
            // Gray: equal amounts of all three
            Color gray = { 128, 128, 128, 255 };
            DrawRectangle(320, y, 100, 20, gray);
            DrawText("(128, 128, 128)", 430, y, 15, DARKGRAY);
            
            // ============================================================
            // TRANSPARENCY (ALPHA CHANNEL)
            // ============================================================
            
            DrawText("TRANSPARENCY", 50, 270, 20, DARKGRAY);
            
            // Draw a solid rectangle as background reference
            DrawRectangle(50, 300, 200, 100, DARKBLUE);
            DrawText("Solid Background", 55, 305, 15, WHITE);
            
            // Now draw transparent rectangles on top
            // Alpha = 255 (fully opaque/solid)
            Color solidRed = { 255, 0, 0, 255 };
            DrawRectangle(60, 320, 60, 70, solidRed);
            DrawText("255", 70, 395, 12, WHITE);
            
            // Alpha = 200 (slightly transparent)
            Color transparent200 = { 255, 0, 0, 200 };
            DrawRectangle(130, 320, 60, 70, transparent200);
            DrawText("200", 140, 395, 12, WHITE);
            
            // Alpha = 150 (more transparent)
            Color transparent150 = { 255, 0, 0, 150 };
            DrawRectangle(200, 320, 60, 70, transparent150);
            DrawText("150", 210, 395, 12, WHITE);
            
            // Alpha = 100 (very transparent)
            Color transparent100 = { 255, 0, 0, 100 };
            DrawRectangle(270, 320, 60, 70, transparent100);
            DrawText("100", 280, 395, 12, WHITE);
            
            // Alpha = 50 (almost invisible)
            Color transparent50 = { 255, 0, 0, 50 };
            DrawRectangle(340, 320, 60, 70, transparent50);
            DrawText("50", 355, 395, 12, WHITE);
            
            // ============================================================
            // COLOR FUNCTIONS
            // ============================================================
            
            DrawText("COLOR FUNCTIONS", 420, 270, 20, DARKGRAY);
            
            // Fade() - Makes a color more transparent
            // Parameters: color, alpha (0.0 = invisible, 1.0 = solid)
            Color fadedRed = Fade(RED, 0.5f);  // 50% transparency
            DrawRectangle(420, 300, 80, 30, fadedRed);
            DrawText("Fade(RED, 0.5)", 510, 305, 12, DARKGRAY);
            
            // ColorAlpha() - Creates a new color with different alpha
            Color alphaBlue = ColorAlpha(BLUE, 0.3f);  // 30% opacity
            DrawRectangle(420, 340, 80, 30, alphaBlue);
            DrawText("ColorAlpha", 510, 345, 12, DARKGRAY);
            
            // ColorTint() - Tints a color with another color
            Color tintedGreen = ColorTint(GREEN, YELLOW);
            DrawRectangle(420, 380, 80, 30, tintedGreen);
            DrawText("ColorTint", 510, 385, 12, DARKGRAY);
            
            // ============================================================
            // HELPFUL TIPS
            // ============================================================
            
            DrawText("Tips: RGB values mix like light, not paint!", 50, 420, 15, DARKGRAY);

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}

/*******************************************************************************************
*
*   KEY CONCEPTS LEARNED:
*   
*   COLOR BASICS:
*   - Colors are made of Red, Green, and Blue components (RGB)
*   - Each component ranges from 0 (none) to 255 (full)
*   - Alpha channel controls transparency (0=invisible, 255=solid)
*   
*   PREDEFINED COLORS:
*   Raylib provides many ready-to-use colors:
*   - Basic: RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, PINK
*   - Variations: DARKBLUE, LIGHTBLUE, SKYBLUE, etc.
*   - Neutrals: BLACK, WHITE, GRAY, DARKGRAY, LIGHTGRAY
*   
*   CREATING CUSTOM COLORS:
*   Color myColor = { R, G, B, A };
*   Example: Color purple = { 128, 0, 128, 255 };
*   
*   COLOR MIXING (RGB):
*   - Red + Green = Yellow
*   - Red + Blue = Magenta
*   - Green + Blue = Cyan
*   - Red + Green + Blue = White
*   - No colors (0,0,0) = Black
*   - Equal amounts = Gray
*   
*   TRANSPARENCY:
*   - Alpha = 255: Fully opaque (solid)
*   - Alpha = 128: Half transparent
*   - Alpha = 0: Fully transparent (invisible)
*   - Transparent objects blend with what's behind them
*   
*   USEFUL COLOR FUNCTIONS:
*   - Fade(color, alpha) - Make a color transparent
*   - ColorAlpha(color, alpha) - New color with different alpha
*   - ColorTint(color1, color2) - Mix two colors
*   
*   PRO TIP:
*   RGB color mixing works like light, not paint!
*   - In light: mixing colors makes them brighter
*   - With paint: mixing colors makes them darker
*
*******************************************************************************************/

