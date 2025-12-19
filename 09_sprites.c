/*******************************************************************************************
*
*   RAYLIB LESSON 09: Sprite Animation
*   
*   Learn how to animate sprites! This covers frame-based animation which is
*   essential for bringing game characters to life.
*
*******************************************************************************************/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - sprite animation");
    
    SetTargetFPS(60);

    // ============================================================
    // CREATE SPRITE SHEET
    // ============================================================
    
    // In real games, you'd load a sprite sheet image file
    // For this example, we'll create a simple animated sprite programmatically
    
    // Create an image to hold our sprite sheet
    // We'll create 4 frames of animation side by side
    const int frameWidth = 64;
    const int frameHeight = 64;
    const int frameCount = 4;
    
    Image spriteSheetImage = GenImageColor(frameWidth * frameCount, frameHeight, BLANK);
    
    // Draw 4 circles with increasing size to simulate animation
    // Frame 0 - smallest
    ImageDrawCircle(&spriteSheetImage, 32, 32, 20, RED);
    // Frame 1
    ImageDrawCircle(&spriteSheetImage, 96, 32, 25, ORANGE);
    // Frame 2
    ImageDrawCircle(&spriteSheetImage, 160, 32, 28, YELLOW);
    // Frame 3 - largest
    ImageDrawCircle(&spriteSheetImage, 224, 32, 25, ORANGE);
    
    // Convert to texture
    Texture2D spriteSheet = LoadTextureFromImage(spriteSheetImage);
    UnloadImage(spriteSheetImage);
    
    // ============================================================
    // ANIMATION VARIABLES
    // ============================================================
    
    // Current frame being displayed (0 to frameCount-1)
    int currentFrame = 0;
    
    // Frame counter - counts frames elapsed
    int frameCounter = 0;
    
    // How many game frames to wait before changing animation frame
    // 60 FPS / 8 = 7.5 animation FPS (slow animation)
    // Lower number = faster animation
    int framesSpeed = 8;
    
    // Position to draw the sprite
    Vector2 position = { 350, 200 };
    
    // ============================================================
    // MANUAL ANIMATION VARIABLES
    // ============================================================
    
    // Second sprite that we control manually with spacebar
    int manualFrame = 0;
    Vector2 manualPosition = { 150, 200 };
    
    // ============================================================
    // MOVING ANIMATED SPRITE
    // ============================================================
    
    // Third sprite that moves and animates
    Vector2 movingPosition = { 100, 350 };
    int movingFrame = 0;
    int movingFrameCounter = 0;
    float movingSpeed = 3.0f;
    bool movingRight = true;

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // ============================================================
        // AUTOMATIC ANIMATION
        // ============================================================
        
        // Increment frame counter each game frame
        frameCounter++;
        
        // When we've waited enough frames, change the animation frame
        if (frameCounter >= framesSpeed)
        {
            frameCounter = 0;  // Reset counter
            currentFrame++;    // Move to next frame
            
            // Loop back to first frame when we reach the end
            if (currentFrame >= frameCount)
            {
                currentFrame = 0;
            }
        }
        
        // Alternative simple method (using modulo):
        // currentFrame = (frameCounter / framesSpeed) % frameCount;
        
        // ============================================================
        // MANUAL ANIMATION (Controlled by player)
        // ============================================================
        
        // Press SPACE to advance to next frame manually
        if (IsKeyPressed(KEY_SPACE))
        {
            manualFrame++;
            if (manualFrame >= frameCount)
            {
                manualFrame = 0;
            }
        }
        
        // ============================================================
        // MOVING ANIMATED SPRITE
        // ============================================================
        
        // Move the sprite
        if (movingRight)
        {
            movingPosition.x += movingSpeed;
            if (movingPosition.x >= screenWidth - frameWidth)
            {
                movingRight = false;  // Hit right edge, go left
            }
        }
        else
        {
            movingPosition.x -= movingSpeed;
            if (movingPosition.x <= 0)
            {
                movingRight = true;  // Hit left edge, go right
            }
        }
        
        // Animate while moving
        movingFrameCounter++;
        if (movingFrameCounter >= 6)  // Faster animation
        {
            movingFrameCounter = 0;
            movingFrame++;
            if (movingFrame >= frameCount)
            {
                movingFrame = 0;
            }
        }
        
        // Change animation speed with keys
        if (IsKeyPressed(KEY_UP))
        {
            framesSpeed--;
            if (framesSpeed < 1) framesSpeed = 1;
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            framesSpeed++;
            if (framesSpeed > 30) framesSpeed = 30;
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKBLUE);
            
            DrawText("SPRITE ANIMATION", 250, 20, 30, WHITE);
            
            // Instructions
            DrawText("Automatic animation (center)", 250, 60, 14, LIGHTGRAY);
            DrawText("SPACE: Advance manual animation (left)", 20, 140, 12, LIGHTGRAY);
            DrawText("UP/DOWN: Change animation speed", 20, 155, 12, LIGHTGRAY);
            
            // ============================================================
            // DRAW ANIMATED SPRITES
            // ============================================================
            
            // Calculate source rectangle for current frame
            // This selects which frame from the sprite sheet to draw
            
            // Automatic animation sprite
            Rectangle sourceAuto = {
                (float)(currentFrame * frameWidth),  // X position of frame in sprite sheet
                0,                                    // Y position (top of sprite sheet)
                (float)frameWidth,                   // Width of one frame
                (float)frameHeight                   // Height of one frame
            };
            
            Rectangle destAuto = {
                position.x,
                position.y,
                (float)frameWidth * 2,  // Scale up 2x
                (float)frameHeight * 2
            };
            
            Vector2 origin = { 0, 0 };
            
            DrawTexturePro(spriteSheet, sourceAuto, destAuto, origin, 0, WHITE);
            DrawText("AUTO", (int)position.x + 40, (int)position.y + 140, 15, WHITE);
            
            // Manual animation sprite
            Rectangle sourceManual = {
                (float)(manualFrame * frameWidth),
                0,
                (float)frameWidth,
                (float)frameHeight
            };
            
            Rectangle destManual = {
                manualPosition.x,
                manualPosition.y,
                (float)frameWidth * 2,
                (float)frameHeight * 2
            };
            
            DrawTexturePro(spriteSheet, sourceManual, destManual, origin, 0, WHITE);
            DrawText("MANUAL", (int)manualPosition.x + 30, (int)manualPosition.y + 140, 15, WHITE);
            
            // Moving animated sprite
            Rectangle sourceMoving = {
                (float)(movingFrame * frameWidth),
                0,
                (float)frameWidth,
                (float)frameHeight
            };
            
            Rectangle destMoving = {
                movingPosition.x,
                movingPosition.y,
                (float)frameWidth,
                (float)frameHeight
            };
            
            DrawTexturePro(spriteSheet, sourceMoving, destMoving, origin, 0, WHITE);
            
            // ============================================================
            // DRAW SPRITE SHEET (For reference)
            // ============================================================
            
            DrawText("SPRITE SHEET:", 500, 300, 15, YELLOW);
            DrawTextureEx(spriteSheet, (Vector2){ 500, 320 }, 0, 1, WHITE);
            
            // Draw frame dividers
            for (int i = 1; i < frameCount; i++)
            {
                DrawLine(500 + (i * frameWidth), 320, 500 + (i * frameWidth), 320 + frameHeight, WHITE);
            }
            
            // Highlight current frame
            Rectangle highlight = {
                500 + (currentFrame * frameWidth),
                320,
                (float)frameWidth,
                (float)frameHeight
            };
            DrawRectangleLinesEx(highlight, 2, LIME);
            
            // ============================================================
            // DISPLAY INFORMATION
            // ============================================================
            
            DrawText(TextFormat("Current Frame: %d/%d", currentFrame, frameCount - 1), 20, 400, 15, WHITE);
            DrawText(TextFormat("Frame Counter: %d", frameCounter), 20, 420, 15, WHITE);
            DrawText(TextFormat("Animation Speed: %d frames/update", framesSpeed), 250, 400, 15, WHITE);
            DrawText(TextFormat("Animation FPS: %.1f", 60.0f / framesSpeed), 250, 420, 15, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(spriteSheet);
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}

/*******************************************************************************************
*
*   KEY CONCEPTS LEARNED:
*   
*   SPRITE ANIMATION BASICS:
*   Animation is created by showing different images in sequence
*   Like a flip book - each image is a "frame"
*   Fast frame changes create the illusion of motion
*   
*   SPRITE SHEET:
*   A single image containing multiple animation frames
*   Frames can be arranged:
*   - Horizontally (left to right)
*   - Vertically (top to bottom)
*   - Grid (rows and columns)
*   
*   Benefits:
*   - More efficient than loading many separate images
*   - Faster to load
*   - Better for performance
*   
*   FRAME-BASED ANIMATION:
*   
*   Basic pattern:
*   1. Track current frame number (0, 1, 2, 3...)
*   2. Track time/frame counter
*   3. When enough time passes, advance to next frame
*   4. Loop back to first frame at the end
*   
*   ANIMATION SPEED CONTROL:
*   
*   Method 1: Frame Counter
*   - Count game frames
*   - Change animation frame every N game frames
*   - framesSpeed = how many game frames per animation frame
*   
*   frameCounter++;
*   if (frameCounter >= framesSpeed) {
*       frameCounter = 0;
*       currentFrame++;
*       if (currentFrame >= maxFrames) currentFrame = 0;
*   }
*   
*   Method 2: Timer
*   - Use GetTime() or delta time
*   - Change frame based on elapsed seconds
*   
*   timer += deltaTime;
*   if (timer >= frameDuration) {
*       timer = 0;
*       currentFrame++;
*   }
*   
*   EXTRACTING FRAMES FROM SPRITE SHEET:
*   
*   Use DrawTexturePro() with source rectangle:
*   
*   Rectangle source = {
*       currentFrame * frameWidth,  // X position in sprite sheet
*       0,                          // Y position (or row * frameHeight)
*       frameWidth,                 // Width of one frame
*       frameHeight                 // Height of one frame
*   };
*   
*   For a 4-frame horizontal sprite sheet (64x64 frames):
*   Frame 0: x = 0,   y = 0
*   Frame 1: x = 64,  y = 0
*   Frame 2: x = 128, y = 0
*   Frame 3: x = 192, y = 0
*   
*   For grid-based sprite sheets:
*   Row = frameNumber / columns
*   Col = frameNumber % columns
*   X = col * frameWidth
*   Y = row * frameHeight
*   
*   ANIMATION TYPES:
*   
*   1. Loop (Continuous)
*      - Goes 0 -> 1 -> 2 -> 3 -> 0 -> 1...
*      - Use modulo: frame = (frame + 1) % maxFrames
*      - Good for: walking, running, idle
*   
*   2. One-Shot (Play Once)
*      - Goes 0 -> 1 -> 2 -> 3, then stops
*      - Don't loop back to 0
*      - Good for: attacks, explosions, death
*   
*   3. Ping-Pong (Back and forth)
*      - Goes 0 -> 1 -> 2 -> 3 -> 2 -> 1 -> 0...
*      - Reverse direction at ends
*      - Good for: breathing, floating
*   
*   4. Manual/Triggered
*      - Advance frame on specific events
*      - Good for: UI animations, cutscenes
*   
*   ANIMATION STATE MACHINE:
*   
*   Characters often have multiple animations:
*   - Idle
*   - Walking
*   - Running
*   - Jumping
*   - Attacking
*   
*   Use an enum and switch:
*   
*   enum AnimState { IDLE, WALK, JUMP, ATTACK };
*   AnimState currentState = IDLE;
*   
*   switch(currentState) {
*       case IDLE: frameCount = 4; startFrame = 0; break;
*       case WALK: frameCount = 8; startFrame = 4; break;
*       case JUMP: frameCount = 2; startFrame = 12; break;
*   }
*   
*   CALCULATING ANIMATION FPS:
*   
*   Game runs at 60 FPS
*   framesSpeed = 6 (change animation every 6 game frames)
*   Animation FPS = 60 / 6 = 10 FPS
*   
*   Common animation rates:
*   - 8-12 FPS: Slow, deliberate (idle, breathing)
*   - 12-15 FPS: Normal (walking)
*   - 15-24 FPS: Fast (running, attacking)
*   - 24+ FPS: Very fast (explosions, effects)
*   
*   FLIPPING SPRITES:
*   
*   To flip horizontally (face other direction):
*   Use negative width in source rectangle:
*   
*   Rectangle source = { x, y, -width, height };  // Note the minus
*   
*   Or use DrawTexturePro with negative destination width
*   
*   COMBINING ANIMATION WITH MOVEMENT:
*   
*   Common pattern:
*   1. Check input/update position
*   2. Based on movement, choose animation state
*   3. Update animation frame
*   4. Draw sprite at position with current frame
*   
*   if (isMoving) {
*       // Play walk animation
*   } else {
*       // Play idle animation
*   }
*   
*   SPRITE SHEET ORGANIZATION:
*   
*   Common layouts:
*   
*   Single row (horizontal):
*   [Frame0][Frame1][Frame2][Frame3]
*   
*   Single column (vertical):
*   [Frame0]
*   [Frame1]
*   [Frame2]
*   
*   Grid (multiple animations):
*   [Idle0][Idle1][Idle2][Idle3]
*   [Walk0][Walk1][Walk2][Walk3]
*   [Jump0][Jump1][Jump2][Jump3]
*   
*   OPTIMIZATION TIPS:
*   1. Keep frame sizes consistent
*   2. Use power-of-2 texture sizes (512x512, 1024x1024)
*   3. Pack multiple animations in one texture
*   4. Remove empty space from frames
*   5. Use texture atlases for multiple sprites
*   
*   COMMON MISTAKES:
*   1. Animation too fast (looks jittery)
*   2. Animation too slow (looks sluggish)
*   3. Forgetting to loop frame counter
*   4. Wrong frame dimensions
*   5. Not resetting animation when changing states
*   
*   BEST PRACTICES:
*   1. Separate animation logic from drawing
*   2. Use structs to organize animation data:
*      struct Animation {
*          int frameCount;
*          int currentFrame;
*          float frameTime;
*      };
*   3. Create reusable animation functions
*   4. Test different animation speeds
*   5. Make animation speed adjustable
*   
*   ADVANCED CONCEPTS (For later):
*   - Skeletal animation (bones)
*   - Blend trees (smooth transitions)
*   - Animation curves (non-linear timing)
*   - Sprite stacking (3D effect with 2D sprites)
*   - Particle animations
*
*******************************************************************************************/

