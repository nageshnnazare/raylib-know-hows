/*******************************************************************************************
*
*   RAYLIB LESSON 04: Movement and Animation
*   
*   Learn how to create movement! This is where things start to get exciting.
*   We'll move objects around the screen and create smooth animations.
*
*******************************************************************************************/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - movement and animation");
    
    SetTargetFPS(60);

    // ============================================================
    // MOVEMENT VARIABLES
    // ============================================================
    
    // Position of our moving circle
    // We use float (decimal numbers) for smooth movement
    float ballX = 100.0f;  // Starting X position
    float ballY = 100.0f;  // Starting Y position
    float ballRadius = 20.0f;  // Size of the ball
    
    // Speed/velocity - how many pixels to move per frame
    float ballSpeedX = 3.0f;  // Move 3 pixels right per frame
    float ballSpeedY = 2.0f;  // Move 2 pixels down per frame
    
    // Rectangle that moves back and forth
    float rectX = 50.0f;
    float rectY = 250.0f;
    float rectWidth = 50.0f;
    float rectHeight = 50.0f;
    float rectSpeed = 4.0f;
    
    // Variables for pulsing circle (grows and shrinks)
    float pulseRadius = 30.0f;  // Current radius
    float pulseGrow = 0.5f;     // How much to grow per frame
    float pulseMin = 20.0f;     // Minimum size
    float pulseMax = 50.0f;     // Maximum size
    
    // Rotating line
    float rotationAngle = 0.0f;  // Current angle in degrees
    float rotationSpeed = 2.0f;  // Degrees to rotate per frame

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // ============================================================
        // BOUNCING BALL MOVEMENT
        // ============================================================
        
        // Move the ball by adding speed to position
        // This happens 60 times per second (because of SetTargetFPS(60))
        ballX += ballSpeedX;  // Same as: ballX = ballX + ballSpeedX;
        ballY += ballSpeedY;
        
        // Check if ball hits the right or left wall
        if (ballX + ballRadius >= screenWidth || ballX - ballRadius <= 0)
        {
            // Reverse horizontal direction by negating the speed
            // If speed was 3, it becomes -3 (goes left)
            // If speed was -3, it becomes 3 (goes right)
            ballSpeedX = -ballSpeedX;
        }
        
        // Check if ball hits the top or bottom wall
        if (ballY + ballRadius >= screenHeight || ballY - ballRadius <= 0)
        {
            // Reverse vertical direction
            ballSpeedY = -ballSpeedY;
        }
        
        // ============================================================
        // BACK AND FORTH RECTANGLE
        // ============================================================
        
        // Move the rectangle horizontally
        rectX += rectSpeed;
        
        // If rectangle goes too far right, reverse direction
        if (rectX + rectWidth >= screenWidth)
        {
            rectSpeed = -rectSpeed;  // Go left
        }
        
        // If rectangle goes too far left, reverse direction
        if (rectX <= 0)
        {
            rectSpeed = -rectSpeed;  // Go right
        }
        
        // ============================================================
        // PULSING CIRCLE ANIMATION
        // ============================================================
        
        // Grow the circle
        pulseRadius += pulseGrow;
        
        // If it gets too big, start shrinking
        if (pulseRadius >= pulseMax)
        {
            pulseGrow = -pulseGrow;  // Make grow negative (shrink)
        }
        
        // If it gets too small, start growing
        if (pulseRadius <= pulseMin)
        {
            pulseGrow = -pulseGrow;  // Make grow positive (grow)
        }
        
        // ============================================================
        // ROTATION ANIMATION
        // ============================================================
        
        // Increase the rotation angle
        rotationAngle += rotationSpeed;
        
        // Keep angle between 0 and 360 degrees
        // This prevents the number from getting too large
        if (rotationAngle >= 360.0f)
        {
            rotationAngle = 0.0f;  // Reset to 0
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBLUE);
            
            DrawText("MOVEMENT & ANIMATION", 220, 20, 30, WHITE);
            
            // ============================================================
            // DRAW BOUNCING BALL
            // ============================================================
            
            // Draw the ball at its current position
            // The position changes every frame, creating movement!
            DrawCircle((int)ballX, (int)ballY, ballRadius, RED);
            DrawText("Bouncing Ball", 10, 10, 15, WHITE);
            
            // ============================================================
            // DRAW MOVING RECTANGLE
            // ============================================================
            
            DrawRectangle((int)rectX, (int)rectY, (int)rectWidth, (int)rectHeight, GREEN);
            DrawText("Back & Forth", 10, 240, 15, WHITE);
            
            // ============================================================
            // DRAW PULSING CIRCLE
            // ============================================================
            
            // This circle grows and shrinks
            DrawCircle(400, 350, pulseRadius, YELLOW);
            DrawText("Pulsing Circle", 340, 410, 15, WHITE);
            
            // ============================================================
            // DRAW ROTATING LINE
            // ============================================================
            
            // DrawLineEx() draws a thick line
            // We'll rotate this line around a center point
            
            // Center point for rotation
            int centerX = 650;
            int centerY = 350;
            int lineLength = 60;
            
            // Calculate the end point of the line based on rotation angle
            // This uses trigonometry (don't worry if you don't understand yet!)
            // cos() and sin() are functions that create circular motion
            
            // Convert angle from degrees to radians (computers use radians)
            // DEG2RAD is a raylib constant that converts degrees to radians
            float angleInRadians = rotationAngle * DEG2RAD;
            
            // Calculate end point using trigonometry
            int endX = centerX + (int)(lineLength * cosf(angleInRadians));
            int endY = centerY + (int)(lineLength * sinf(angleInRadians));
            
            // Draw the rotating line
            DrawCircle(centerX, centerY, 5, WHITE);  // Draw center point
            DrawLineEx((Vector2){ centerX, centerY }, (Vector2){ endX, endY }, 4, ORANGE);
            DrawText("Rotating Line", 600, 410, 15, WHITE);
            
            // ============================================================
            // SHOW SOME VALUES FOR LEARNING
            // ============================================================
            
            DrawText(TextFormat("Ball Position: (%.0f, %.0f)", ballX, ballY), 10, 420, 12, LIGHTGRAY);
            DrawText(TextFormat("Pulse Radius: %.1f", pulseRadius), 250, 420, 12, LIGHTGRAY);
            DrawText(TextFormat("Rotation: %.0f degrees", rotationAngle), 500, 420, 12, LIGHTGRAY);

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
*   CREATING MOVEMENT:
*   1. Store position in variables (x, y)
*   2. Store speed/velocity in variables
*   3. Each frame, add speed to position: position += speed
*   4. The object appears to move because we draw it at a new position each frame
*   
*   BASIC MOVEMENT FORMULA:
*   newPosition = oldPosition + speed
*   
*   BOUNCING (COLLISION WITH WALLS):
*   - Check if object hits a boundary
*   - Reverse the speed: speed = -speed
*   - This makes the object go the opposite direction
*   
*   BACK AND FORTH MOVEMENT:
*   - Move in one direction
*   - When you hit a boundary, reverse direction
*   - Same as bouncing!
*   
*   PULSING ANIMATION:
*   - Increase a value (like size)
*   - When it reaches maximum, start decreasing
*   - When it reaches minimum, start increasing
*   - Creates a growing/shrinking effect
*   
*   ROTATION:
*   - Store current angle
*   - Increase angle each frame
*   - Use trigonometry to convert angle to position:
*     * x = centerX + radius * cos(angle)
*     * y = centerY + radius * sin(angle)
*   
*   IMPORTANT CONCEPTS:
*   
*   1. FRAME-BY-FRAME UPDATES:
*      Everything happens in the game loop, 60 times per second
*      Small changes each frame create smooth motion
*   
*   2. FLOAT vs INT:
*      Use float for positions and speeds (allows decimal values)
*      Cast to int when drawing: (int)floatValue
*      This makes movement smoother
*   
*   3. DELTA TIME (Not used here, but important to know):
*      In more complex games, you multiply speed by deltaTime
*      This makes movement consistent on different computers
*      We'll cover this in advanced lessons
*   
*   4. TRIGONOMETRY:
*      cos() and sin() create circular motion
*      Useful for rotation, circular paths, etc.
*      Angles in radians: multiply degrees by DEG2RAD
*   
*   EXPERIMENT IDEAS:
*   - Change the speed values to make things faster/slower
*   - Add more bouncing balls with different speeds
*   - Make the rectangle move vertically too
*   - Change the rotation speed
*   - Combine movements (bouncing + rotating)
*
*******************************************************************************************/

