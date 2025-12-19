/*******************************************************************************************
*
*   RAYLIB LESSON 13: Collision Detection
*   
*   Learn how to detect collisions between objects! This is essential for game physics,
*   hit detection, and interactive gameplay.
*
*******************************************************************************************/

#include "raylib.h"
#include <stdbool.h>

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - collision detection");
    
    SetTargetFPS(60);

    // ============================================================
    // GAME OBJECTS
    // ============================================================
    
    // Player (controlled by WASD)
    Rectangle player = { 100, 100, 40, 40 };
    float playerSpeed = 5.0f;
    
    // Static obstacles
    Rectangle wall1 = { 200, 50, 30, 350 };
    Rectangle wall2 = { 400, 50, 30, 350 };
    Rectangle wall3 = { 300, 200, 80, 30 };
    
    // Moving obstacle
    Rectangle movingBox = { 500, 300, 60, 60 };
    float boxSpeedX = 2.0f;
    
    // Collectible circles
    Vector2 coin1 = { 300, 100 };
    Vector2 coin2 = { 500, 100 };
    Vector2 coin3 = { 650, 350 };
    float coinRadius = 15.0f;
    bool coin1Collected = false;
    bool coin2Collected = false;
    bool coin3Collected = false;
    
    // Trigger zone (invisible area that triggers an event)
    Rectangle triggerZone = { 600, 150, 150, 100 };
    bool inTriggerZone = false;
    
    // Collision flags
    bool collidingWithWall = false;
    bool collidingWithMovingBox = false;
    
    int score = 0;

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // ============================================================
        // PLAYER MOVEMENT (Before collision)
        // ============================================================
        
        // Store previous position for collision resolution
        Rectangle previousPlayer = player;
        
        // Move player
        if (IsKeyDown(KEY_W)) player.y -= playerSpeed;
        if (IsKeyDown(KEY_S)) player.y += playerSpeed;
        if (IsKeyDown(KEY_A)) player.x -= playerSpeed;
        if (IsKeyDown(KEY_D)) player.x += playerSpeed;
        
        // ============================================================
        // RECTANGLE vs RECTANGLE COLLISION
        // ============================================================
        
        // CheckCollisionRecs() checks if two rectangles overlap
        // Returns true if they collide, false otherwise
        
        collidingWithWall = false;
        
        // Check collision with wall 1
        if (CheckCollisionRecs(player, wall1))
        {
            // Collision detected! Push player back to previous position
            player = previousPlayer;
            collidingWithWall = true;
        }
        
        // Check collision with wall 2
        if (CheckCollisionRecs(player, wall2))
        {
            player = previousPlayer;
            collidingWithWall = true;
        }
        
        // Check collision with wall 3
        if (CheckCollisionRecs(player, wall3))
        {
            player = previousPlayer;
            collidingWithWall = true;
        }
        
        // ============================================================
        // MOVING OBSTACLE
        // ============================================================
        
        // Move the box back and forth
        movingBox.x += boxSpeedX;
        if (movingBox.x >= 700 || movingBox.x <= 450)
        {
            boxSpeedX = -boxSpeedX;  // Reverse direction
        }
        
        // Check collision with moving box
        collidingWithMovingBox = CheckCollisionRecs(player, movingBox);
        if (collidingWithMovingBox)
        {
            // Push player back
            player = previousPlayer;
        }
        
        // ============================================================
        // CIRCLE vs CIRCLE COLLISION
        // ============================================================
        
        // CheckCollisionCircles() checks if two circles overlap
        // Parameters: center1, radius1, center2, radius2
        
        Vector2 playerCenter = { player.x + 20, player.y + 20 };
        float playerRadius = 20.0f;
        
        // Check collision with coins (collect them)
        if (!coin1Collected && CheckCollisionCircles(playerCenter, playerRadius, coin1, coinRadius))
        {
            coin1Collected = true;
            score += 10;
        }
        
        if (!coin2Collected && CheckCollisionCircles(playerCenter, playerRadius, coin2, coinRadius))
        {
            coin2Collected = true;
            score += 10;
        }
        
        if (!coin3Collected && CheckCollisionCircles(playerCenter, playerRadius, coin3, coinRadius))
        {
            coin3Collected = true;
            score += 10;
        }
        
        // ============================================================
        // POINT vs RECTANGLE COLLISION
        // ============================================================
        
        // CheckCollisionPointRec() checks if a point is inside a rectangle
        // Useful for: mouse clicks, trigger zones, pickups
        
        inTriggerZone = CheckCollisionPointRec(playerCenter, triggerZone);
        
        // ============================================================
        // CIRCLE vs RECTANGLE COLLISION
        // ============================================================
        
        // CheckCollisionCircleRec() checks if a circle overlaps a rectangle
        // Useful for: circular player vs rectangular obstacles
        
        bool circleHitsWall = CheckCollisionCircleRec(playerCenter, playerRadius, wall1);
        
        // ============================================================
        // GET COLLISION RECTANGLE
        // ============================================================
        
        // GetCollisionRec() returns the overlapping area between two rectangles
        // Returns a Rectangle representing the intersection
        
        Rectangle collision = GetCollisionRec(player, wall1);
        // collision.width and collision.height tell you how much they overlap
        
        // ============================================================
        // BOUNDARY CHECKING
        // ============================================================
        
        // Keep player on screen
        if (player.x < 0) player.x = 0;
        if (player.x + player.width > screenWidth) player.x = screenWidth - player.width;
        if (player.y < 0) player.y = 0;
        if (player.y + player.height > screenHeight) player.y = screenHeight - player.height;
        
        // Reset with R
        if (IsKeyPressed(KEY_R))
        {
            player.x = 100;
            player.y = 100;
            coin1Collected = false;
            coin2Collected = false;
            coin3Collected = false;
            score = 0;
        }
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);
            
            DrawText("COLLISION DETECTION", 230, 10, 30, WHITE);
            
            // ============================================================
            // DRAW GAME OBJECTS
            // ============================================================
            
            // Draw walls
            DrawRectangleRec(wall1, GRAY);
            DrawRectangleRec(wall2, GRAY);
            DrawRectangleRec(wall3, GRAY);
            
            // Draw moving box
            Color boxColor = collidingWithMovingBox ? RED : ORANGE;
            DrawRectangleRec(movingBox, boxColor);
            DrawText("MOVE", (int)movingBox.x + 5, (int)movingBox.y + 23, 15, WHITE);
            
            // Draw trigger zone (semi-transparent)
            Color zoneColor = inTriggerZone ? Fade(YELLOW, 0.5f) : Fade(BLUE, 0.3f);
            DrawRectangleRec(triggerZone, zoneColor);
            DrawRectangleLinesEx(triggerZone, 2, inTriggerZone ? YELLOW : BLUE);
            DrawText("TRIGGER", (int)triggerZone.x + 30, (int)triggerZone.y + 40, 15, WHITE);
            
            // Draw coins
            if (!coin1Collected) DrawCircleV(coin1, coinRadius, GOLD);
            if (!coin2Collected) DrawCircleV(coin2, coinRadius, GOLD);
            if (!coin3Collected) DrawCircleV(coin3, coinRadius, GOLD);
            
            // Draw player
            Color playerColor = WHITE;
            if (collidingWithWall || collidingWithMovingBox)
                playerColor = RED;  // Show red when colliding
            else if (inTriggerZone)
                playerColor = YELLOW;  // Show yellow in trigger zone
            
            DrawRectangleRec(player, playerColor);
            
            // Draw player collision circle (for visualization)
            Vector2 playerCenter = { player.x + 20, player.y + 20 };
            DrawCircleLines((int)playerCenter.x, (int)playerCenter.y, 20, Fade(GREEN, 0.5f));
            
            // ============================================================
            // UI AND INFORMATION
            // ============================================================
            
            // Instructions
            DrawRectangle(0, screenHeight - 80, screenWidth, 80, Fade(BLACK, 0.7f));
            DrawText("WASD: Move player", 20, screenHeight - 70, 14, WHITE);
            DrawText("R: Reset", 20, screenHeight - 50, 14, WHITE);
            DrawText("Collect coins and avoid walls!", 20, screenHeight - 30, 14, YELLOW);
            
            // Score
            DrawText(TextFormat("Score: %d", score), 650, screenHeight - 60, 20, GOLD);
            
            // Status indicators
            int infoX = 250;
            DrawText("Collision Status:", infoX, screenHeight - 70, 14, LIGHTGRAY);
            
            if (collidingWithWall)
                DrawText("[Wall Hit!]", infoX, screenHeight - 50, 14, RED);
            if (collidingWithMovingBox)
                DrawText("[Box Hit!]", infoX, screenHeight - 30, 14, RED);
            if (inTriggerZone)
                DrawText("[In Trigger Zone!]", infoX + 120, screenHeight - 50, 14, YELLOW);
            
            // Show collision rectangle overlay when colliding
            if (CheckCollisionRecs(player, wall1))
            {
                Rectangle overlap = GetCollisionRec(player, wall1);
                DrawRectangleRec(overlap, Fade(RED, 0.5f));
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
*   WHAT IS COLLISION DETECTION?
*   Checking if two or more game objects overlap or touch
*   Essential for: physics, hit detection, pickups, boundaries
*   
*   COLLISION TYPES IN RAYLIB:
*   
*   1. Rectangle vs Rectangle
*      CheckCollisionRecs(rect1, rect2)
*      - Returns true if rectangles overlap
*      - Most common collision type
*      - Use for: walls, boxes, most game objects
*   
*   2. Circle vs Circle
*      CheckCollisionCircles(center1, radius1, center2, radius2)
*      - Returns true if circles overlap
*      - Fast and efficient
*      - Use for: circular objects, bullets, explosions
*   
*   3. Circle vs Rectangle
*      CheckCollisionCircleRec(center, radius, rect)
*      - Returns true if circle overlaps rectangle
*      - Useful for mixed shapes
*   
*   4. Point vs Rectangle
*      CheckCollisionPointRec(point, rect)
*      - Returns true if point is inside rectangle
*      - Use for: mouse clicks, trigger checks
*   
*   5. Point vs Circle
*      CheckCollisionPointCircle(point, center, radius)
*      - Returns true if point is inside circle
*   
*   6. Point vs Line
*      CheckCollisionPointLine(point, p1, p2, threshold)
*      - Returns true if point is near a line
*   
*   COLLISION RESPONSE PATTERNS:
*   
*   1. Solid Collision (blocking):
*      Store previous position
*      Move object
*      If collision, restore previous position
*   
*      Rectangle previous = player;
*      player.x += speed;
*      if (CheckCollisionRecs(player, wall)) {
*          player = previous;  // Block movement
*      }
*   
*   2. Trigger (non-blocking):
*      Just check and respond, don't block movement
*   
*      if (CheckCollisionRecs(player, triggerZone)) {
*          // Do something (open door, show message)
*      }
*   
*   3. Collectible:
*      Check collision and remove/disable object
*   
*      if (!collected && CheckCollision(player, coin)) {
*          collected = true;
*          score++;
*      }
*   
*   4. Damage/Hurt:
*      Check collision and apply effect
*   
*      if (CheckCollision(player, enemy)) {
*          playerHealth -= 10;
*      }
*   
*   GETTING COLLISION INFORMATION:
*   
*   GetCollisionRec(rect1, rect2)
*   - Returns Rectangle of overlap area
*   - If no collision, returns empty rectangle
*   - Use overlap size to determine collision depth
*   
*   Rectangle overlap = GetCollisionRec(player, wall);
*   if (overlap.width > 0 && overlap.height > 0) {
*       // Collision occurred
*       // overlap.width = how much they overlap horizontally
*       // overlap.height = how much they overlap vertically
*   }
*   
*   COLLISION RESOLUTION:
*   
*   Simple method (what we used):
*   - Restore previous position
*   - Easy to implement
*   - Can feel "sticky"
*   
*   Sliding collision:
*   - Allow movement in non-colliding axis
*   - Try moving X, if collision, try Y
*   - Feels smoother
*   
*   // Try horizontal movement
*   player.x += velocityX;
*   if (CheckCollisionRecs(player, wall)) {
*       player.x -= velocityX;  // Undo X movement
*   }
*   // Try vertical movement
*   player.y += velocityY;
*   if (CheckCollisionRecs(player, wall)) {
*       player.y -= velocityY;  // Undo Y movement
*   }
*   
*   Push-out collision:
*   - Calculate overlap
*   - Push object out by overlap amount
*   - More complex but smoother
*   
*   TRIGGER ZONES:
*   Areas that detect presence but don't block movement
*   
*   Uses:
*   - Door opening triggers
*   - Level transition zones
*   - Camera zones
*   - Audio zones (start music)
*   - Tutorial pop-ups
*   
*   if (CheckCollisionPointRec(player.position, triggerZone)) {
*       // Player entered zone
*       OpenDoor();
*       ShowMessage("Press E to enter");
*   }
*   
*   BOUNDARY CHECKING:
*   Keep objects within screen or world bounds
*   
*   if (x < 0) x = 0;
*   if (x > maxX) x = maxX;
*   if (y < 0) y = 0;
*   if (y > maxY) y = maxY;
*   
*   Or bounce:
*   if (x < 0 || x > maxX) velocityX = -velocityX;
*   if (y < 0 || y > maxY) velocityY = -velocityY;
*   
*   OPTIMIZATION:
*   
*   1. Spatial partitioning:
*      Only check collisions between nearby objects
*      Use grids or quad-trees for many objects
*   
*   2. Broad phase -> Narrow phase:
*      First: cheap approximate check (distance)
*      Then: expensive precise check (rectangle)
*   
*   3. Early exit:
*      if (abs(obj1.x - obj2.x) > maxDistance) continue;
*   
*   4. Object layers:
*      Only check collisions between relevant layers
*      Don't check player bullets vs player
*   
*   COMMON PATTERNS:
*   
*   Platformer collision:
*   - Check ground collision for landing
*   - Check ceiling collision for bonking head
*   - Check wall collision for blocking
*   - Separate horizontal and vertical collision
*   
*   Top-down collision:
*   - Check collision before moving
*   - Allow diagonal movement if one direction is free
*   - Use sliding collision
*   
*   Bullet collision:
*   - Check circle collision (fast)
*   - Remove bullet and damage target on hit
*   - Consider raycast for fast bullets
*   
*   DISTANCE-BASED COLLISION:
*   Sometimes approximate collision first:
*   
*   float dx = obj1.x - obj2.x;
*   float dy = obj1.y - obj2.y;
*   float distance = sqrtf(dx*dx + dy*dy);
*   
*   if (distance < maxDistance) {
*       // Objects are close, do precise collision check
*       if (CheckCollisionRecs(obj1, obj2)) {
*           // Actual collision
*       }
*   }
*   
*   COLLISION MASKS:
*   For complex shapes, use multiple simple shapes
*   
*   // Character has multiple hitboxes
*   Rectangle head = { x, y, 20, 20 };
*   Rectangle body = { x, y+20, 20, 40 };
*   Rectangle legs = { x, y+60, 20, 30 };
*   
*   bool hit = CheckCollisionRecs(bullet, head) ||
*              CheckCollisionRecs(bullet, body) ||
*              CheckCollisionRecs(bullet, legs);
*   
*   ONE-WAY PLATFORMS:
*   Platforms you can jump through from below:
*   
*   if (playerVelocityY > 0 && player.bottom > platform.top) {
*       if (CheckCollisionRecs(player, platform)) {
*           // Landing on platform from above
*           player.y = platform.y - player.height;
*           playerVelocityY = 0;
*           onGround = true;
*       }
*   }
*   
*   BEST PRACTICES:
*   
*   1. Separate collision detection from response
*   2. Use appropriate shape (circle vs rectangle)
*   3. Check collisions AFTER movement
*   4. Store previous position for solid collisions
*   5. Use layers to filter collision checks
*   6. Optimize for many objects (spatial partitioning)
*   7. Make hitboxes slightly smaller than visuals (feels better)
*   8. Test collision from all angles
*   9. Visualize hitboxes during development
*   10. Consider gameplay feel over perfect accuracy
*   
*   DEBUGGING COLLISIONS:
*   
*   Draw collision shapes:
*   DrawRectangleLinesEx(hitbox, 2, RED);
*   DrawCircleLines(centerX, centerY, radius, GREEN);
*   
*   Show collision state:
*   DrawText(CheckCollisionRecs(a,b) ? "HIT" : "CLEAR", 10, 10, 20, WHITE);
*   
*   COMMON MISTAKES:
*   
*   1. Checking collision BEFORE movement
*   2. Forgetting to store previous position
*   3. Infinite collision loops (stuck in wall)
*   4. Not handling diagonal collisions properly
*   5. Hitbox size doesn't match visual
*   6. Checking too many collisions per frame
*   7. Not limiting collision checks to active objects
*   
*   ADVANCED TOPICS (Not covered here):
*   - Raycasting (for line-of-sight, bullets)
*   - SAT (Separated Axis Theorem) for rotated rectangles
*   - Physics engines integration
*   - Collision islands (sleeping objects)
*   - Continuous collision detection (for fast objects)
*   - Polygon collision
*
*******************************************************************************************/

