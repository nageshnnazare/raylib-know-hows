/*******************************************************************************************
*
*   RAYLIB LESSON 05: Keyboard Input
*   
*   Learn how to handle keyboard input! This is essential for player control.
*   We'll cover different ways to detect key presses.
*
*******************************************************************************************/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");
    
    SetTargetFPS(60);

    // ============================================================
    // PLAYER VARIABLES
    // ============================================================
    
    // Player position (controlled by arrow keys)
    float playerX = 400.0f;
    float playerY = 225.0f;
    float playerSize = 30.0f;
    float playerSpeed = 5.0f;  // Pixels per frame
    
    // Variables to track different key states
    bool spacePressed = false;
    bool enterJustPressed = false;
    int spacebarPressCount = 0;
    
    // Color that changes with keys
    Color playerColor = BLUE;

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // ============================================================
        // IsKeyDown() - Continuous key press
        // ============================================================
        
        // IsKeyDown() returns true WHILE a key is being held down
        // Use this for continuous actions like movement
        // The player keeps moving as long as you hold the key
        
        // Move UP when UP arrow is held
        if (IsKeyDown(KEY_UP))
        {
            playerY -= playerSpeed;  // Subtract to move up (Y decreases upward)
        }
        
        // Move DOWN when DOWN arrow is held
        if (IsKeyDown(KEY_DOWN))
        {
            playerY += playerSpeed;  // Add to move down (Y increases downward)
        }
        
        // Move LEFT when LEFT arrow is held
        if (IsKeyDown(KEY_LEFT))
        {
            playerX -= playerSpeed;  // Subtract to move left (X decreases leftward)
        }
        
        // Move RIGHT when RIGHT arrow is held
        if (IsKeyDown(KEY_RIGHT))
        {
            playerX += playerSpeed;  // Add to move right (X increases rightward)
        }
        
        // Alternative: WASD keys for movement (common in PC games)
        if (IsKeyDown(KEY_W)) playerY -= playerSpeed;  // W = up
        if (IsKeyDown(KEY_S)) playerY += playerSpeed;  // S = down
        if (IsKeyDown(KEY_A)) playerX -= playerSpeed;  // A = left
        if (IsKeyDown(KEY_D)) playerX += playerSpeed;  // D = right
        
        // Keep player on screen (boundary checking)
        if (playerX < playerSize) playerX = playerSize;
        if (playerX > screenWidth - playerSize) playerX = screenWidth - playerSize;
        if (playerY < playerSize) playerY = playerSize;
        if (playerY > screenHeight - playerSize) playerY = screenHeight - playerSize;
        
        // ============================================================
        // IsKeyPressed() - Single key press (not continuous)
        // ============================================================
        
        // IsKeyPressed() returns true ONCE when a key is first pressed
        // Even if you hold the key down, it only triggers once
        // Use this for actions that should only happen once per press
        // Like jumping, shooting, or toggling something
        
        if (IsKeyPressed(KEY_SPACE))
        {
            // This will only trigger once per press
            // Even if you hold space, it won't keep triggering
            spacebarPressCount++;
            spacePressed = true;
        }
        else
        {
            spacePressed = false;
        }
        
        // Change color when ENTER is pressed
        if (IsKeyPressed(KEY_ENTER))
        {
            enterJustPressed = true;
            
            // Cycle through colors
            if (playerColor.r == 0 && playerColor.g == 0 && playerColor.b == 255)
                playerColor = RED;      // Blue -> Red
            else if (playerColor.r == 255 && playerColor.g == 0)
                playerColor = GREEN;    // Red -> Green
            else if (playerColor.g == 255 && playerColor.b == 0)
                playerColor = YELLOW;   // Green -> Yellow
            else if (playerColor.r == 255 && playerColor.g == 255)
                playerColor = PURPLE;   // Yellow -> Purple
            else
                playerColor = BLUE;     // Purple -> Blue
        }
        else
        {
            enterJustPressed = false;
        }
        
        // ============================================================
        // IsKeyReleased() - Detects when key is released
        // ============================================================
        
        // IsKeyReleased() returns true when you let go of a key
        // Useful for "hold and release" mechanics
        
        if (IsKeyReleased(KEY_R))
        {
            // Reset player position when R is released
            playerX = 400.0f;
            playerY = 225.0f;
        }
        
        // ============================================================
        // IsKeyUp() - Key is NOT being pressed
        // ============================================================
        
        // IsKeyUp() returns true when a key is NOT pressed
        // It's the opposite of IsKeyDown()
        // Less commonly used, but good to know
        
        // Example: player color fades when not pressing SHIFT
        if (IsKeyUp(KEY_LEFT_SHIFT) && IsKeyUp(KEY_RIGHT_SHIFT))
        {
            // Not holding shift - could do something here
        }
        
        // ============================================================
        // GetKeyPressed() - Get the actual key code pressed
        // ============================================================
        
        // GetKeyPressed() returns the key code of any key pressed
        // Returns 0 if no key is pressed
        // Useful for text input or detecting any key
        
        int keyPressed = GetKeyPressed();
        
        // Speed boost when holding SHIFT
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        {
            playerSpeed = 10.0f;  // Move faster
        }
        else
        {
            playerSpeed = 5.0f;   // Normal speed
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);
            
            // Title
            DrawText("KEYBOARD INPUT", 250, 20, 30, WHITE);
            
            // Instructions
            DrawText("Arrow Keys or WASD: Move", 20, 50, 15, LIGHTGRAY);
            DrawText("SHIFT: Speed boost", 20, 70, 15, LIGHTGRAY);
            DrawText("SPACE: Count presses", 20, 90, 15, LIGHTGRAY);
            DrawText("ENTER: Change color", 20, 110, 15, LIGHTGRAY);
            DrawText("R (release): Reset position", 20, 130, 15, LIGHTGRAY);
            DrawText("ESC: Exit", 20, 150, 15, LIGHTGRAY);
            
            // Draw the player
            DrawCircle((int)playerX, (int)playerY, playerSize, playerColor);
            
            // Visual feedback when space is pressed
            if (spacePressed)
            {
                DrawRing((Vector2){ playerX, playerY }, playerSize + 5, playerSize + 10, 0, 360, 32, GOLD);
            }
            
            // Display information
            DrawText(TextFormat("Position: (%.0f, %.0f)", playerX, playerY), 20, 380, 15, WHITE);
            DrawText(TextFormat("Speed: %.0f px/frame", playerSpeed), 20, 400, 15, WHITE);
            DrawText(TextFormat("Space presses: %d", spacebarPressCount), 20, 420, 15, WHITE);
            
            if (enterJustPressed)
            {
                DrawText("Color Changed!", 600, 50, 20, YELLOW);
            }
            
            // Show if any key is being pressed
            if (keyPressed > 0)
            {
                DrawText(TextFormat("Key Pressed: %d", keyPressed), 600, 400, 15, LIGHTGRAY);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
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
*   KEYBOARD INPUT FUNCTIONS:
*   
*   1. IsKeyDown(KEY)
*      - Returns true WHILE key is held down
*      - Checks every frame
*      - Use for: continuous actions (movement, holding a button)
*      - Example: holding right arrow keeps moving player right
*   
*   2. IsKeyPressed(KEY)
*      - Returns true ONCE when key is first pressed
*      - Only triggers on the initial press, not while held
*      - Use for: single actions (jump, shoot, toggle)
*      - Example: press space once to jump, must release and press again
*   
*   3. IsKeyReleased(KEY)
*      - Returns true when key is let go
*      - Triggers when you stop pressing
*      - Use for: "charge and release" mechanics
*      - Example: release space to fire a charged shot
*   
*   4. IsKeyUp(KEY)
*      - Returns true when key is NOT pressed
*      - Opposite of IsKeyDown()
*      - Use for: checking if player is NOT doing something
*   
*   5. GetKeyPressed()
*      - Returns the key code of any pressed key
*      - Returns 0 if no key pressed
*      - Use for: text input, detecting "any" key
*   
*   COMMON KEY CONSTANTS:
*   - Arrow keys: KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
*   - Letters: KEY_A through KEY_Z
*   - Numbers: KEY_ZERO through KEY_NINE
*   - Special: KEY_SPACE, KEY_ENTER, KEY_ESCAPE
*   - Modifiers: KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT, KEY_LEFT_CONTROL, etc.
*   
*   MOVEMENT PATTERN:
*   The standard movement pattern is:
*   
*   if (IsKeyDown(KEY_RIGHT)) x += speed;  // Move right
*   if (IsKeyDown(KEY_LEFT))  x -= speed;  // Move left
*   if (IsKeyDown(KEY_DOWN))  y += speed;  // Move down
*   if (IsKeyDown(KEY_UP))    y -= speed;  // Move up
*   
*   BOUNDARY CHECKING:
*   Always check if player stays on screen:
*   
*   if (x < 0) x = 0;                    // Left boundary
*   if (x > screenWidth) x = screenWidth; // Right boundary
*   if (y < 0) y = 0;                    // Top boundary
*   if (y > screenHeight) y = screenHeight; // Bottom boundary
*   
*   IsKeyDown vs IsKeyPressed:
*   
*   IsKeyDown():
*   - Triggers every frame while held
*   - Frame 1: TRUE, Frame 2: TRUE, Frame 3: TRUE...
*   - Use for movement
*   
*   IsKeyPressed():
*   - Triggers only on first press
*   - Frame 1: TRUE, Frame 2: FALSE, Frame 3: FALSE...
*   - Use for single actions
*   
*   TIPS:
*   - Use IsKeyDown() for smooth continuous movement
*   - Use IsKeyPressed() for discrete actions (jump, shoot)
*   - Always provide multiple control schemes (arrows AND WASD)
*   - Add boundary checking to keep objects on screen
*   - Consider adding acceleration/deceleration for better feel
*
*******************************************************************************************/

