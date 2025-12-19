/*******************************************************************************************
*
*   RAYLIB LESSON 01: Hello Window
*   
*   Welcome to your first raylib program! This example creates a simple window.
*   We'll explain every single line so you understand what's happening.
*
*******************************************************************************************/

// This is a preprocessor directive that includes the raylib library
// Think of it as importing all the tools we need to create games
#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    // These constants define our window size
    // const means these values won't change during the program
    // The window will be 800 pixels wide and 450 pixels tall
    const int screenWidth = 800;
    const int screenHeight = 450;

    // InitWindow() is a raylib function that creates and opens a window
    // Parameters:
    //   1. screenWidth - how wide the window should be (800 pixels)
    //   2. screenHeight - how tall the window should be (450 pixels)
    //   3. title - the text that appears in the window's title bar
    // This MUST be called before any other raylib drawing functions
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // SetTargetFPS() tells raylib how many frames per second we want
    // FPS = Frames Per Second = how many times per second the screen updates
    // 60 FPS means the screen redraws 60 times every second
    // This makes animations smooth and consistent across different computers
    SetTargetFPS(60);

    // Main game loop
    //--------------------------------------------------------------------------------------
    
    // WindowShouldClose() returns false while the window is open
    // It returns true when the user clicks the X button or presses ESC
    // The ! means "not", so !WindowShouldClose() means "while window should NOT close"
    // This creates an infinite loop that keeps running until the user wants to quit
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        // In this simple example, we don't have anything to update
        // In games, this is where you would:
        //   - Update player position
        //   - Check for collisions
        //   - Update enemy AI
        //   - Handle game logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        
        // BeginDrawing() tells raylib we're about to draw things on screen
        // Everything between BeginDrawing() and EndDrawing() will appear on screen
        // Think of it as opening a canvas to paint on
        BeginDrawing();

            // ClearBackground() fills the entire screen with one color
            // RAYWHITE is a predefined color (light gray/white)
            // This is like painting the entire canvas with a base color
            // We do this every frame to "erase" what was drawn in the previous frame
            ClearBackground(RAYWHITE);

            // DrawText() puts text on the screen
            // Parameters:
            //   1. "Congrats! ..." - the text to display
            //   2. 190 - X position (pixels from the left edge)
            //   3. 200 - Y position (pixels from the top edge)
            //   4. 20 - font size (in pixels)
            //   5. LIGHTGRAY - the color of the text
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        // EndDrawing() tells raylib we're done drawing for this frame
        // It "closes" the canvas and displays everything we drew
        // After this, raylib will handle showing it on the monitor
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // CloseWindow() closes the window and cleans up raylib resources
    // This frees memory and properly shuts down the graphics system
    // ALWAYS call this when your program ends
    // Think of it as cleaning up your workspace when you're done
    CloseWindow();
    //--------------------------------------------------------------------------------------

    // Return 0 to tell the operating system the program ended successfully
    // In C, returning 0 from main() means "everything went well"
    // Returning other numbers usually indicates an error occurred
    return 0;
}

/*******************************************************************************************
*
*   KEY CONCEPTS LEARNED:
*   
*   1. InitWindow() - Creates a window (always call this first)
*   2. SetTargetFPS() - Sets how fast your game runs
*   3. Game Loop - The while loop that runs continuously
*   4. WindowShouldClose() - Checks if user wants to quit
*   5. BeginDrawing()/EndDrawing() - Frame boundaries for drawing
*   6. ClearBackground() - Fills screen with a color
*   7. DrawText() - Displays text on screen
*   8. CloseWindow() - Cleans up when done (always call this last)
*
*   THE GAME LOOP PATTERN:
*   
*   while (game is running) {
*       1. Handle Input (keyboard, mouse, etc.)
*       2. Update (game logic, physics, AI)
*       3. Draw (render everything to screen)
*   }
*
*   This pattern is fundamental to all games!
*
*******************************************************************************************/

