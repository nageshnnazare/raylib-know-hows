/*******************************************************************************************
*
*   RAYLIB LESSON 07: Gamepad/Controller Input
*   
*   Learn how to use game controllers! This covers buttons, analog sticks, and triggers.
*   Essential for console-style games and providing controller support.
*
*******************************************************************************************/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - gamepad input");
    
    SetTargetFPS(60);

    // ============================================================
    // VARIABLES
    // ============================================================
    
    // Player controlled by gamepad
    Vector2 playerPosition = { 400, 225 };
    float playerRadius = 30.0f;
    float playerSpeed = 5.0f;
    
    // Gamepad ID (0-3 for up to 4 controllers)
    // 0 = first controller, 1 = second controller, etc.
    int gamepad = 0;
    
    // Visual feedback for button presses
    bool buttonA_pressed = false;
    bool buttonB_pressed = false;
    bool buttonX_pressed = false;
    bool buttonY_pressed = false;

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // ============================================================
        // CHECK IF GAMEPAD IS AVAILABLE
        // ============================================================
        
        // IsGamepadAvailable() checks if a gamepad is connected
        // Parameter is the gamepad number (0-3)
        // Returns true if that gamepad is connected and ready
        bool gamepadAvailable = IsGamepadAvailable(gamepad);
        
        // Only read gamepad input if a gamepad is connected
        if (gamepadAvailable)
        {
            // ============================================================
            // GAMEPAD BUTTONS - Digital Input
            // ============================================================
            
            // Gamepad buttons work just like keyboard keys
            // IsGamepadButtonDown() - held continuously
            // IsGamepadButtonPressed() - pressed once
            // IsGamepadButtonReleased() - released once
            
            // Face buttons (A, B, X, Y on Xbox / Cross, Circle, Square, Triangle on PlayStation)
            buttonA_pressed = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);  // A / Cross
            buttonB_pressed = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT); // B / Circle
            buttonX_pressed = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);  // X / Square
            buttonY_pressed = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP);    // Y / Triangle
            
            // D-Pad (Directional Pad) - Digital directional input
            // These are the arrow buttons on the controller
            bool dpadUp = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP);
            bool dpadDown = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
            bool dpadLeft = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
            bool dpadRight = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
            
            // Move with D-Pad
            if (dpadUp) playerPosition.y -= playerSpeed;
            if (dpadDown) playerPosition.y += playerSpeed;
            if (dpadLeft) playerPosition.x -= playerSpeed;
            if (dpadRight) playerPosition.x += playerSpeed;
            
            // Shoulder buttons
            bool leftBumper = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1);   // LB/L1
            bool rightBumper = IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_2);  // RB/R1
            
            // Speed boost with bumpers
            if (leftBumper || rightBumper)
            {
                playerSpeed = 10.0f;
            }
            else
            {
                playerSpeed = 5.0f;
            }
            
            // Start and Select/Back buttons
            bool startButton = IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT); // Start
            bool selectButton = IsGamepadButtonPressed(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT); // Select/Back
            
            // Reset position with Start button
            if (startButton)
            {
                playerPosition.x = 400;
                playerPosition.y = 225;
            }
            
            // ============================================================
            // ANALOG STICKS - Continuous Input
            // ============================================================
            
            // Analog sticks provide smooth, directional input
            // Values range from -1.0 to +1.0
            // -1.0 = fully left/up
            // 0.0 = centered
            // +1.0 = fully right/down
            
            // Left analog stick
            // GetGamepadAxisMovement() gets the position of an analog stick axis
            float leftStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
            float leftStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
            
            // Right analog stick
            float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
            float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
            
            // Move player with left analog stick
            // Multiply by speed for faster movement
            playerPosition.x += leftStickX * playerSpeed;
            playerPosition.y += leftStickY * playerSpeed;
            
            // Note: Right stick could be used for aiming, camera control, etc.
            
            // ============================================================
            // DEADZONE
            // ============================================================
            
            // Analog sticks might not return exactly 0.0 when centered
            // This is called "drift" or "noise"
            // We use a "deadzone" to ignore small movements
            
            float deadzone = 0.1f;  // Ignore movements smaller than this
            
            // Only move if stick is pushed beyond deadzone
            if (leftStickX > deadzone || leftStickX < -deadzone)
            {
                // Stick is pushed horizontally
            }
            if (leftStickY > deadzone || leftStickY < -deadzone)
            {
                // Stick is pushed vertically
            }
            
            // ============================================================
            // TRIGGERS - Analog Buttons
            // ============================================================
            
            // Triggers (LT/RT or L2/R2) are analog - they detect how hard you press
            // Values range from -1.0 (not pressed) to 1.0 (fully pressed)
            // Note: Some controllers return 0.0 to 1.0 instead
            
            float leftTrigger = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER);
            float rightTrigger = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER);
            
            // Example: Change player size based on triggers
            if (leftTrigger > 0)
            {
                playerRadius = 30.0f - (leftTrigger * 15.0f);  // Shrink
            }
            if (rightTrigger > 0)
            {
                playerRadius = 30.0f + (rightTrigger * 20.0f);  // Grow
            }
            
            // ============================================================
            // GAMEPAD NAME
            // ============================================================
            
            // GetGamepadName() returns a string with the controller's name
            // Useful for displaying "Press A" vs "Press Cross" depending on controller
            const char* gamepadName = GetGamepadName(gamepad);
        }
        
        // Keep player on screen
        if (playerPosition.x < playerRadius) playerPosition.x = playerRadius;
        if (playerPosition.x > screenWidth - playerRadius) playerPosition.x = screenWidth - playerRadius;
        if (playerPosition.y < playerRadius) playerPosition.y = playerRadius;
        if (playerPosition.y > screenHeight - playerRadius) playerPosition.y = screenHeight - playerRadius;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBLUE);
            
            DrawText("GAMEPAD INPUT", 250, 20, 30, WHITE);
            
            // Check if gamepad is available
            if (gamepadAvailable)
            {
                // Display gamepad name
                const char* gamepadName = GetGamepadName(gamepad);
                DrawText(TextFormat("Gamepad detected: %s", gamepadName), 20, 60, 15, LIME);
                
                // Instructions
                DrawText("Left Stick / D-Pad: Move", 20, 90, 14, LIGHTGRAY);
                DrawText("Bumpers (LB/RB): Speed boost", 20, 110, 14, LIGHTGRAY);
                DrawText("Triggers (LT/RT): Change size", 20, 130, 14, LIGHTGRAY);
                DrawText("Start: Reset position", 20, 150, 14, LIGHTGRAY);
                
                // Draw the player
                DrawCircleV(playerPosition, playerRadius, GREEN);
                
                // Visual feedback for face buttons
                // Draw button indicators on the right side
                int buttonX = 650;
                int buttonY = 200;
                int buttonSize = 30;
                int buttonSpacing = 45;
                
                // Y button (top)
                DrawCircle(buttonX, buttonY, buttonSize, buttonY_pressed ? YELLOW : DARKGRAY);
                DrawText("Y", buttonX - 7, buttonY - 10, 20, BLACK);
                
                // B button (right)
                DrawCircle(buttonX + buttonSpacing, buttonY + buttonSpacing, buttonSize, 
                          buttonB_pressed ? RED : DARKGRAY);
                DrawText("B", buttonX + buttonSpacing - 7, buttonY + buttonSpacing - 10, 20, BLACK);
                
                // A button (bottom)
                DrawCircle(buttonX, buttonY + buttonSpacing * 2, buttonSize, 
                          buttonA_pressed ? GREEN : DARKGRAY);
                DrawText("A", buttonX - 7, buttonY + buttonSpacing * 2 - 10, 20, BLACK);
                
                // X button (left)
                DrawCircle(buttonX - buttonSpacing, buttonY + buttonSpacing, buttonSize, 
                          buttonX_pressed ? BLUE : DARKGRAY);
                DrawText("X", buttonX - buttonSpacing - 7, buttonY + buttonSpacing - 10, 20, BLACK);
                
                // Display analog stick values
                float leftStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
                float leftStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
                float rightStickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
                float rightStickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
                
                DrawText(TextFormat("Left Stick: (%.2f, %.2f)", leftStickX, leftStickY), 
                        20, 380, 14, WHITE);
                DrawText(TextFormat("Right Stick: (%.2f, %.2f)", rightStickX, rightStickY), 
                        20, 400, 14, WHITE);
                
                // Display trigger values
                float leftTrigger = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER);
                float rightTrigger = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER);
                DrawText(TextFormat("Triggers: LT=%.2f RT=%.2f", leftTrigger, rightTrigger), 
                        20, 420, 14, WHITE);
            }
            else
            {
                // No gamepad detected
                DrawText("No gamepad detected!", 250, 200, 20, RED);
                DrawText("Please connect a gamepad/controller", 200, 230, 16, LIGHTGRAY);
                DrawText("(Xbox, PlayStation, or compatible controller)", 160, 250, 14, LIGHTGRAY);
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
*   GAMEPAD AVAILABILITY:
*   - IsGamepadAvailable(gamepadNum) - Check if controller is connected
*   - gamepadNum: 0-3 for up to 4 controllers
*   - Always check this before reading gamepad input
*   
*   GAMEPAD BUTTONS (Digital):
*   Functions work like keyboard functions:
*   - IsGamepadButtonDown(gamepad, button) - held continuously
*   - IsGamepadButtonPressed(gamepad, button) - pressed once
*   - IsGamepadButtonReleased(gamepad, button) - released
*   
*   COMMON BUTTONS:
*   Face buttons (right side):
*   - GAMEPAD_BUTTON_RIGHT_FACE_DOWN  (A / Cross)
*   - GAMEPAD_BUTTON_RIGHT_FACE_RIGHT (B / Circle)
*   - GAMEPAD_BUTTON_RIGHT_FACE_LEFT  (X / Square)
*   - GAMEPAD_BUTTON_RIGHT_FACE_UP    (Y / Triangle)
*   
*   D-Pad (left side):
*   - GAMEPAD_BUTTON_LEFT_FACE_UP
*   - GAMEPAD_BUTTON_LEFT_FACE_DOWN
*   - GAMEPAD_BUTTON_LEFT_FACE_LEFT
*   - GAMEPAD_BUTTON_LEFT_FACE_RIGHT
*   
*   Shoulder buttons:
*   - GAMEPAD_BUTTON_LEFT_TRIGGER_1  (LB / L1)
*   - GAMEPAD_BUTTON_LEFT_TRIGGER_2  (RB / R1)
*   
*   Middle buttons:
*   - GAMEPAD_BUTTON_MIDDLE_LEFT  (Select / Back / Share)
*   - GAMEPAD_BUTTON_MIDDLE_RIGHT (Start / Menu / Options)
*   
*   ANALOG STICKS:
*   - GetGamepadAxisMovement(gamepad, axis)
*   - Returns value from -1.0 to +1.0
*   - 0.0 = centered position
*   
*   Axes:
*   - GAMEPAD_AXIS_LEFT_X  (left stick horizontal)
*   - GAMEPAD_AXIS_LEFT_Y  (left stick vertical)
*   - GAMEPAD_AXIS_RIGHT_X (right stick horizontal)
*   - GAMEPAD_AXIS_RIGHT_Y (right stick vertical)
*   
*   TRIGGERS (Analog):
*   - GAMEPAD_AXIS_LEFT_TRIGGER  (LT / L2)
*   - GAMEPAD_AXIS_RIGHT_TRIGGER (RT / R2)
*   - Returns -1.0 (not pressed) to 1.0 (fully pressed)
*   - Some controllers return 0.0 to 1.0
*   
*   DEADZONE:
*   Analog sticks may not be perfectly centered at 0.0
*   Use a deadzone to ignore small movements:
*   
*   float deadzone = 0.1f;
*   if (abs(stickValue) > deadzone) {
*       // Use the stick value
*   }
*   
*   Typical deadzone: 0.1 to 0.2 (10-20%)
*   
*   GAMEPAD INFO:
*   - GetGamepadName(gamepad) - Returns controller name
*   - GetGamepadButtonPressed() - Get any button pressed
*   - GetGamepadAxisCount(gamepad) - Number of axes available
*   
*   MOVEMENT WITH ANALOG STICK:
*   
*   // Get stick values
*   float stickX = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
*   float stickY = GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
*   
*   // Apply to position
*   x += stickX * speed;
*   y += stickY * speed;
*   
*   This gives smooth, proportional movement!
*   
*   BUTTON LAYOUT DIFFERENCES:
*   Xbox:        A, B, X, Y
*   PlayStation: Cross, Circle, Square, Triangle
*   Nintendo:    B, A, Y, X (different positions!)
*   
*   Use button positions (RIGHT_FACE_DOWN) not names for consistency
*   
*   BEST PRACTICES:
*   1. Always check IsGamepadAvailable() first
*   2. Implement deadzone for analog sticks
*   3. Provide keyboard alternative (not everyone has controller)
*   4. Use left stick for movement, right stick for camera/aiming
*   5. Use triggers for analog actions (gas/brake, charge/attack)
*   6. Map face buttons to main actions (jump, attack, interact)
*   7. Test with different controller types if possible
*   
*   TYPICAL CONTROL SCHEMES:
*   
*   Platformer:
*   - Left stick: Move
*   - A/Cross: Jump
*   - B/Circle: Run
*   - X/Square: Attack
*   
*   Shooter:
*   - Left stick: Move
*   - Right stick: Aim
*   - Right trigger: Shoot
*   - Left trigger: Aim down sights
*   - A/Cross: Jump
*   - B/Circle: Crouch
*   
*   Racing:
*   - Left stick: Steer
*   - Right trigger: Accelerate
*   - Left trigger: Brake/Reverse
*   - A/Cross: Nitro
*   
*   TIPS:
*   - Analog sticks are better for movement than D-Pad (more precise)
*   - D-Pad is better for menus and discrete actions
*   - Face buttons for main actions players use frequently
*   - Shoulder buttons for secondary actions
*   - Triggers for analog actions (varying intensity)
*   - Vibration/rumble requires additional setup (not covered here)
*
*******************************************************************************************/

