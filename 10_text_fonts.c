/*******************************************************************************************
*
*   RAYLIB LESSON 10: Text and Fonts
*   
*   Learn how to display text and use different fonts! Text is essential for
*   UI, dialogue, scores, and game information.
*
*******************************************************************************************/

#include "raylib.h"
#include <stdio.h>  // For sprintf

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [text] example - text and fonts");
    
    SetTargetFPS(60);

    // ============================================================
    // FONT VARIABLES
    // ============================================================
    
    // Raylib has a default font built-in, but you can also load custom fonts
    // For this example, we'll use the default font
    // To load a custom font: Font myFont = LoadFont("myfont.ttf");
    
    Font defaultFont = GetFontDefault();
    
    // ============================================================
    // TEXT VARIABLES
    // ============================================================
    
    const char* title = "Text and Fonts in Raylib";
    const char* message = "This is how you display text!";
    
    // Dynamic text (changes during program)
    int score = 0;
    float timer = 0.0f;
    
    // Text positioning
    int centerX = screenWidth / 2;

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // Update timer
        timer += GetFrameTime();  // GetFrameTime() returns seconds since last frame
        
        // Increase score with spacebar
        if (IsKeyPressed(KEY_SPACE))
        {
            score += 10;
        }
        
        // Reset with R
        if (IsKeyPressed(KEY_R))
        {
            score = 0;
            timer = 0.0f;
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // ============================================================
            // BASIC TEXT DRAWING
            // ============================================================
            
            // DrawText() is the simplest way to draw text
            // Parameters: text, x, y, fontSize, color
            DrawText("TEXT AND FONTS", 250, 20, 30, DARKBLUE);
            
            // ============================================================
            // DIFFERENT FONT SIZES
            // ============================================================
            
            DrawText("Font Size 10", 50, 70, 10, DARKGRAY);
            DrawText("Font Size 20", 50, 90, 20, DARKGRAY);
            DrawText("Font Size 30", 50, 120, 30, DARKGRAY);
            DrawText("Font Size 40", 50, 160, 40, DARKGRAY);
            
            // ============================================================
            // DIFFERENT COLORS
            // ============================================================
            
            int y = 220;
            DrawText("Red Text", 50, y, 20, RED);
            DrawText("Green Text", 200, y, 20, GREEN);
            DrawText("Blue Text", 370, y, 20, BLUE);
            DrawText("Yellow Text", 520, y, 20, YELLOW);
            
            // ============================================================
            // FORMATTED TEXT (Numbers, Variables)
            // ============================================================
            
            // TextFormat() works like sprintf/printf
            // It creates a formatted string you can draw
            // Very useful for displaying scores, health, etc.
            
            DrawText("DYNAMIC TEXT:", 50, 270, 20, MAROON);
            
            // Display the score
            DrawText(TextFormat("Score: %d", score), 50, 300, 25, DARKGREEN);
            
            // Display the timer (2 decimal places)
            DrawText(TextFormat("Timer: %.2f seconds", timer), 50, 330, 20, DARKBLUE);
            
            // Multiple values
            DrawText(TextFormat("Position: (%d, %d)", 100, 200), 50, 360, 18, PURPLE);
            
            // Formatting options:
            // %d = integer
            // %f = float (default 6 decimals)
            // %.2f = float with 2 decimals
            // %s = string
            // %c = character
            
            // ============================================================
            // TEXT ALIGNMENT AND MEASUREMENT
            // ============================================================
            
            // MeasureText() returns the width of text in pixels
            // This is essential for centering text
            
            const char* centeredText = "This text is centered!";
            int textWidth = MeasureText(centeredText, 20);
            
            // Calculate centered X position
            int centeredX = (screenWidth - textWidth) / 2;
            
            DrawText(centeredText, centeredX, 400, 20, ORANGE);
            
            // Draw a line to show the center
            DrawLine(screenWidth / 2, 390, screenWidth / 2, 430, LIGHTGRAY);
            
            // ============================================================
            // DrawTextEx() - Advanced text drawing
            // ============================================================
            
            // DrawTextEx() gives you more control:
            // - Custom fonts
            // - Precise spacing
            // - Rotation (with DrawTextPro)
            
            Vector2 position = { 400, 70 };
            float fontSize = 30.0f;
            float spacing = 2.0f;  // Space between characters
            
            DrawTextEx(defaultFont, "DrawTextEx", position, fontSize, spacing, RED);
            
            // MeasureTextEx() for advanced measurement
            Vector2 textSize = MeasureTextEx(defaultFont, "DrawTextEx", fontSize, spacing);
            DrawText(TextFormat("Size: %.0fx%.0f", textSize.x, textSize.y), 400, 110, 12, GRAY);
            
            // ============================================================
            // TEXT WITH BACKGROUND
            // ============================================================
            
            // Create text with a background box (like subtitles)
            const char* boxText = "Text with background";
            int boxTextWidth = MeasureText(boxText, 20);
            int boxX = 400;
            int boxY = 150;
            int padding = 10;
            
            // Draw background rectangle
            DrawRectangle(boxX - padding, boxY - padding, 
                         boxTextWidth + padding * 2, 20 + padding * 2, 
                         BLACK);
            
            // Draw text on top
            DrawText(boxText, boxX, boxY, 20, WHITE);
            
            // ============================================================
            // TEXT WITH SHADOW
            // ============================================================
            
            // Draw shadow (offset and darker)
            DrawText("Shadow Text", 402, 202, 25, DARKGRAY);
            // Draw actual text
            DrawText("Shadow Text", 400, 200, 25, WHITE);
            
            // ============================================================
            // COLORED TEXT EFFECT
            // ============================================================
            
            // Create rainbow effect by drawing same text in different colors
            const char* rainbowText = "Rainbow!";
            int baseX = 550;
            int baseY = 250;
            
            DrawText(rainbowText, baseX, baseY, 30, RED);
            DrawText(rainbowText, baseX + 1, baseY, 30, ORANGE);
            DrawText(rainbowText, baseX + 2, baseY, 30, YELLOW);
            DrawText(rainbowText, baseX + 3, baseY, 30, GREEN);
            DrawText(rainbowText, baseX + 4, baseY, 30, BLUE);
            
            // ============================================================
            // BLINKING TEXT
            // ============================================================
            
            // Make text blink by only drawing it sometimes
            // Use timer to control blinking
            if (((int)(timer * 2)) % 2 == 0)  // Blink twice per second
            {
                DrawText("BLINKING TEXT", 550, 350, 20, RED);
            }
            
            // ============================================================
            // INSTRUCTIONS
            // ============================================================
            
            DrawText("SPACE: Increase score | R: Reset", 180, 425, 15, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Note: No need to unload default font
    // If you loaded a custom font, use: UnloadFont(customFont);
    
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}

/*******************************************************************************************
*
*   KEY CONCEPTS LEARNED:
*   
*   DRAWING TEXT - BASIC:
*   
*   DrawText(text, x, y, fontSize, color)
*   - Simplest way to draw text
*   - x, y is the TOP-LEFT corner of the text
*   - fontSize is in pixels
*   
*   Example:
*   DrawText("Hello!", 100, 200, 20, RED);
*   
*   FORMATTED TEXT:
*   
*   TextFormat() creates formatted strings (like printf):
*   - Returns a const char* you can use with DrawText()
*   - Supports standard format specifiers
*   
*   Common formats:
*   %d or %i    - Integer (int)
*   %f          - Float (default 6 decimals)
*   %.2f        - Float with 2 decimal places
*   %s          - String (const char*)
*   %c          - Single character
*   %x          - Hexadecimal
*   
*   Examples:
*   TextFormat("Score: %d", 100)              -> "Score: 100"
*   TextFormat("Health: %.1f", 75.5f)         -> "Health: 75.5"
*   TextFormat("Name: %s", "Player")          -> "Name: Player"
*   TextFormat("Pos: (%d, %d)", x, y)         -> "Pos: (10, 20)"
*   
*   MEASURING TEXT:
*   
*   MeasureText(text, fontSize)
*   - Returns width of text in pixels
*   - Essential for alignment
*   - Does NOT measure height (use fontSize as approximate height)
*   
*   Centering text:
*   int textWidth = MeasureText("Hello", 20);
*   int centeredX = (screenWidth - textWidth) / 2;
*   DrawText("Hello", centeredX, y, 20, WHITE);
*   
*   Right-aligning text:
*   int textWidth = MeasureText("Hello", 20);
*   int rightAlignedX = screenWidth - textWidth - padding;
*   
*   ADVANCED TEXT DRAWING:
*   
*   DrawTextEx(font, text, position, fontSize, spacing, color)
*   - More control than DrawText()
*   - Can use custom fonts
*   - Adjust character spacing
*   - More precise positioning (uses float)
*   
*   DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, color)
*   - Everything DrawTextEx has
*   - Plus rotation support
*   - Custom origin/pivot point
*   
*   MeasureTextEx(font, text, fontSize, spacing)
*   - Returns Vector2 with width and height
*   - More accurate than MeasureText()
*   
*   FONTS:
*   
*   Default font:
*   Font font = GetFontDefault();
*   - Built into raylib
*   - Always available
*   - No need to unload
*   
*   Loading custom fonts:
*   Font customFont = LoadFont("myfont.ttf");
*   Font customFont = LoadFont("myfont.otf");
*   
*   Supported formats: TTF, OTF, FNT
*   
*   Loading font with size:
*   Font font = LoadFontEx("font.ttf", 32, NULL, 0);
*   
*   Always unload custom fonts:
*   UnloadFont(customFont);
*   
*   TEXT EFFECTS:
*   
*   1. Shadow:
*      DrawText(text, x+2, y+2, size, DARKGRAY);  // Shadow
*      DrawText(text, x, y, size, WHITE);         // Actual text
*   
*   2. Outline (multi-layer):
*      // Draw in 8 directions for outline
*      for (int dx = -1; dx <= 1; dx++)
*          for (int dy = -1; dy <= 1; dy++)
*              if (dx != 0 || dy != 0)
*                  DrawText(text, x+dx, y+dy, size, BLACK);
*      DrawText(text, x, y, size, WHITE);
*   
*   3. Blinking:
*      if (((int)(GetTime() * 2)) % 2 == 0)
*          DrawText("Blink", x, y, size, color);
*   
*   4. Color fade:
*      Color fadedColor = Fade(RED, alpha);
*      DrawText(text, x, y, size, fadedColor);
*   
*   5. Scrolling:
*      int offset = (GetTime() * 50) % screenWidth;
*      DrawText(text, offset, y, size, color);
*   
*   TEXT ALIGNMENT HELPERS:
*   
*   Left align (default):
*   DrawText(text, leftMargin, y, size, color);
*   
*   Center align:
*   int width = MeasureText(text, size);
*   DrawText(text, (screenWidth - width) / 2, y, size, color);
*   
*   Right align:
*   int width = MeasureText(text, size);
*   DrawText(text, screenWidth - width - rightMargin, y, size, color);
*   
*   MULTI-LINE TEXT:
*   
*   Raylib doesn't automatically wrap text
*   You need to manually handle line breaks:
*   
*   int lineHeight = 25;
*   int y = 100;
*   DrawText("Line 1", x, y, 20, WHITE);
*   y += lineHeight;
*   DrawText("Line 2", x, y, 20, WHITE);
*   y += lineHeight;
*   DrawText("Line 3", x, y, 20, WHITE);
*   
*   Or use DrawTextRec() for automatic wrapping (advanced)
*   
*   TEXT WITH BACKGROUNDS:
*   
*   Pattern for UI labels:
*   1. Measure text
*   2. Draw rectangle (background)
*   3. Draw text on top
*   
*   const char* label = "Health: 100";
*   int width = MeasureText(label, 20);
*   int padding = 10;
*   DrawRectangle(x-padding, y-padding, width+padding*2, 20+padding*2, DARKGRAY);
*   DrawText(label, x, y, 20, WHITE);
*   
*   SPECIAL CHARACTERS:
*   
*   Escape sequences in C strings:
*   \n - newline (but DrawText doesn't handle this automatically)
*   \" - double quote
*   \\ - backslash
*   \t - tab (but DrawText doesn't handle this)
*   
*   Unicode support:
*   Raylib supports UTF-8 encoding
*   You can display international characters with proper fonts
*   
*   COMMON USES:
*   
*   - Score display: TextFormat("Score: %d", score)
*   - Health bars: TextFormat("HP: %d/%d", hp, maxHp)
*   - Timer: TextFormat("Time: %.2f", timer)
*   - FPS counter: TextFormat("FPS: %d", GetFPS())
*   - Debug info: TextFormat("Pos: (%.1f, %.1f)", x, y)
*   - UI labels: "Play", "Options", "Quit"
*   - Dialogue: Character speech text
*   - Instructions: "Press SPACE to jump"
*   
*   PERFORMANCE TIPS:
*   
*   1. TextFormat() creates a static buffer - don't call excessively
*   2. Pre-compute text that doesn't change
*   3. For many text objects, consider using DrawTextEx() with custom font
*   4. Avoid MeasureText() every frame if text doesn't change
*   5. Cache text measurements
*   
*   BEST PRACTICES:
*   
*   1. Use consistent font sizes for similar elements
*   2. Ensure good contrast (text vs background)
*   3. Add shadows or backgrounds for readability
*   4. Keep font sizes readable (minimum ~12-14 for UI)
*   5. Center important text (titles, game over screen)
*   6. Right-align numbers in lists for easier reading
*   7. Use color to convey meaning (red = health, yellow = warning)
*   8. Test text on different backgrounds
*   
*   DEBUGGING TEXT:
*   
*   Draw debug info with text:
*   DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, LIME);
*   DrawText(TextFormat("Mouse: %d,%d", GetMouseX(), GetMouseY()), 10, 30, 20, LIME);
*   DrawText(TextFormat("Player: %.1f,%.1f", playerX, playerY), 10, 50, 20, LIME);
*   
*   This is incredibly useful during development!
*   
*   COMMON MISTAKES:
*   
*   1. Forgetting to unload custom fonts
*   2. Drawing text every frame without caching measurements
*   3. Not accounting for text width (text goes off screen)
*   4. Using font size 0 or negative (crashes)
*   5. Not checking for NULL text pointers
*   6. Poor color contrast making text unreadable
*   
*   TIPS:
*   - Start with default font, add custom fonts later
*   - Use MeasureText() for any alignment needs
*   - TextFormat() is your friend for dynamic text
*   - Add backgrounds to text for better readability
*   - Test text visibility on all backgrounds
*   - GetFPS() is great for performance monitoring
*
*******************************************************************************************/

