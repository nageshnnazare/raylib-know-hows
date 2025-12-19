/*******************************************************************************************
*
*   RAYLIB LESSON 11: 2D Camera
*   
*   Learn how to use the 2D camera! Cameras let you create worlds larger than the screen,
*   implement smooth following, zooming, and more. Essential for most 2D games!
*
*******************************************************************************************/

#include "raylib.h"

#define MAX_BUILDINGS 20

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");
    
    SetTargetFPS(60);

    // ============================================================
    // PLAYER
    // ============================================================
    
    Rectangle player = { 400, 200, 40, 40 };
    float playerSpeed = 5.0f;
    
    // ============================================================
    // WORLD (larger than screen)
    // ============================================================
    
    // Create a world that's much larger than the screen
    Rectangle buildings[MAX_BUILDINGS];
    Color buildingColors[MAX_BUILDINGS];
    
    int spacing = 0;
    for (int i = 0; i < MAX_BUILDINGS; i++)
    {
        // Random building dimensions
        buildings[i].width = (float)GetRandomValue(50, 200);
        buildings[i].height = (float)GetRandomValue(100, 800);
        buildings[i].x = -6000.0f + spacing;
        buildings[i].y = screenHeight - 130.0f - buildings[i].height;
        
        spacing += (int)buildings[i].width;
        
        buildingColors[i] = (Color){ GetRandomValue(100, 250), 
                                     GetRandomValue(100, 250), 
                                     GetRandomValue(100, 250), 255 };
    }
    
    // ============================================================
    // CAMERA SETUP
    // ============================================================
    
    // Camera2D is a structure that defines a 2D camera view
    Camera2D camera = { 0 };
    
    // camera.offset - The offset from the screen (where camera draws on screen)
    // Usually center of screen for character following
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    
    // camera.target - What point in the world the camera is looking at
    // This is the world position that will appear at the camera.offset point on screen
    camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    
    // camera.rotation - Rotation of the camera in degrees
    camera.rotation = 0.0f;
    
    // camera.zoom - Camera zoom (1.0 = normal, 2.0 = 2x zoom in, 0.5 = 2x zoom out)
    camera.zoom = 1.0f;

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // ============================================================
        // PLAYER MOVEMENT
        // ============================================================
        
        if (IsKeyDown(KEY_RIGHT)) player.x += playerSpeed;
        if (IsKeyDown(KEY_LEFT)) player.x -= playerSpeed;
        if (IsKeyDown(KEY_UP)) player.y -= playerSpeed;
        if (IsKeyDown(KEY_DOWN)) player.y += playerSpeed;
        
        // ============================================================
        // CAMERA CONTROLS
        // ============================================================
        
        // Make camera follow the player
        // The camera target is set to the player's center position
        camera.target = (Vector2){ player.x + 20, player.y + 20 };
        
        // Zoom in/out with mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Zoom increment
            const float zoomIncrement = 0.125f;
            
            camera.zoom += wheel * zoomIncrement;
            
            // Limit zoom levels
            if (camera.zoom > 3.0f) camera.zoom = 3.0f;
            if (camera.zoom < 0.25f) camera.zoom = 0.25f;
        }
        
        // Reset zoom with R key
        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }
        
        // Rotate camera with Q and E
        if (IsKeyDown(KEY_Q)) camera.rotation -= 1.0f;
        if (IsKeyDown(KEY_E)) camera.rotation += 1.0f;
        
        // Keep rotation in 0-360 range
        if (camera.rotation >= 360.0f) camera.rotation = 0.0f;
        if (camera.rotation < 0.0f) camera.rotation = 360.0f;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // ============================================================
            // DRAWING WITH CAMERA
            // ============================================================
            
            // BeginMode2D() starts camera mode
            // Everything drawn between BeginMode2D() and EndMode2D() 
            // will be affected by the camera transformation
            // 
            // Camera does three things:
            // 1. Translates (moves) the view to follow camera.target
            // 2. Rotates around camera.target by camera.rotation degrees
            // 3. Scales (zooms) by camera.zoom
            BeginMode2D(camera);
            
                // All drawing here is in WORLD SPACE
                // Coordinates are world positions, not screen positions
                
                // Draw the ground
                DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
                
                // Draw the buildings
                for (int i = 0; i < MAX_BUILDINGS; i++)
                {
                    DrawRectangleRec(buildings[i], buildingColors[i]);
                }
                
                // Draw the player
                DrawRectangleRec(player, RED);
                
                // Draw world grid for reference
                // This helps visualize the camera movement
                for (int i = -60; i < 60; i++)
                {
                    DrawLine(i * 100, -5000, i * 100, 5000, LIGHTGRAY);
                    DrawLine(-6000, i * 100, 6000, i * 100, LIGHTGRAY);
                }
                
                // Draw world origin marker
                DrawCircle(0, 0, 10, BLUE);
                DrawText("(0, 0)", 15, -5, 20, BLUE);
                
                // Draw player position in world
                DrawText(TextFormat("World: (%.0f, %.0f)", player.x, player.y), 
                        player.x - 50, player.y - 30, 10, BLACK);
            
            // EndMode2D() stops camera mode
            // Everything after this is drawn in SCREEN SPACE (not affected by camera)
            EndMode2D();
            
            // ============================================================
            // DRAWING WITHOUT CAMERA (UI)
            // ============================================================
            
            // UI elements should be drawn AFTER EndMode2D()
            // This keeps them fixed on screen regardless of camera movement
            
            // Draw UI background
            DrawRectangle(0, 0, screenWidth, 50, Fade(SKYBLUE, 0.5f));
            DrawRectangle(0, screenHeight - 50, screenWidth, 50, Fade(SKYBLUE, 0.5f));
            
            // Title
            DrawText("2D CAMERA", 10, 10, 20, DARKBLUE);
            
            // Instructions
            DrawText("Arrow Keys: Move player", 10, screenHeight - 40, 15, DARKBLUE);
            DrawText("Q/E: Rotate | Mouse Wheel: Zoom | R: Reset", 300, screenHeight - 40, 15, DARKBLUE);
            
            // Camera info
            DrawText(TextFormat("Zoom: %.2fx", camera.zoom), 640, 10, 15, DARKBLUE);
            DrawText(TextFormat("Rotation: %.0f", camera.rotation), 640, 30, 15, DARKBLUE);
            
            // Show camera target
            DrawText(TextFormat("Camera Target: (%.0f, %.0f)", camera.target.x, camera.target.y), 
                    300, 10, 15, DARKBLUE);

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
*   WHAT IS A CAMERA?
*   A camera defines how the game world is viewed on screen
*   Think of it as a virtual camera filming your game world
*   
*   WHY USE A CAMERA?
*   - Create worlds larger than the screen
*   - Follow the player smoothly
*   - Zoom in/out
*   - Screen shake effects
*   - Split-screen multiplayer
*   - Minimap views
*   
*   CAMERA2D STRUCTURE:
*   
*   Camera2D camera = { 0 };
*   
*   camera.offset (Vector2):
*   - Position on SCREEN where camera center appears
*   - Usually center of screen: { screenWidth/2, screenHeight/2 }
*   - For UI at top: { screenWidth/2, screenHeight - 100 }
*   
*   camera.target (Vector2):
*   - Position in WORLD that camera is looking at
*   - This world point appears at camera.offset on screen
*   - Change this to move camera around world
*   
*   camera.rotation (float):
*   - Rotation in degrees
*   - 0 = no rotation
*   - Rotates around the target point
*   
*   camera.zoom (float):
*   - Zoom level
*   - 1.0 = normal (1:1 pixels)
*   - 2.0 = zoomed in 2x (things appear bigger)
*   - 0.5 = zoomed out 2x (things appear smaller)
*   
*   USING THE CAMERA:
*   
*   BeginMode2D(camera);
*       // All drawing here is affected by camera
*       DrawPlayer();
*       DrawWorld();
*   EndMode2D();
*   
*   // UI drawn here is NOT affected by camera
*   DrawUI();
*   
*   WORLD SPACE vs SCREEN SPACE:
*   
*   World Space (inside BeginMode2D/EndMode2D):
*   - Coordinates are positions in the game world
*   - player.x = 1000 means 1000 units in world
*   - Affected by camera position, zoom, rotation
*   
*   Screen Space (outside camera mode):
*   - Coordinates are pixels on screen
*   - x = 100 means 100 pixels from left edge
*   - NOT affected by camera
*   - Use for UI, HUD, menus
*   
*   CAMERA FOLLOWING PATTERNS:
*   
*   1. Direct Following (what we used):
*      camera.target = playerPosition;
*      - Camera instantly follows player
*      - Can feel jerky
*   
*   2. Smooth Following (lerp):
*      camera.target.x += (player.x - camera.target.x) * smoothness * deltaTime;
*      camera.target.y += (player.y - camera.target.y) * smoothness * deltaTime;
*      - Camera smoothly catches up to player
*      - smoothness = 0.1 to 0.3 usually
*   
*   3. Leading (look ahead):
*      Vector2 leadTarget = player.position + player.velocity * leadAmount;
*      camera.target = leadTarget;
*      - Camera looks ahead in direction of movement
*      - Good for fast-moving games
*   
*   4. Boundary Box:
*      Only move camera when player reaches edge of a box
*      Common in platformers
*   
*   ZOOM CONTROLS:
*   
*   Mouse wheel zoom (what we used):
*   float wheel = GetMouseWheelMove();
*   camera.zoom += wheel * 0.1f;
*   
*   Zoom with keys:
*   if (IsKeyDown(KEY_EQUAL)) camera.zoom += 0.01f;  // + key
*   if (IsKeyDown(KEY_MINUS)) camera.zoom -= 0.01f;  // - key
*   
*   Always limit zoom:
*   if (camera.zoom < 0.1f) camera.zoom = 0.1f;
*   if (camera.zoom > 3.0f) camera.zoom = 3.0f;
*   
*   ZOOM TOWARD MOUSE:
*   For more intuitive zoom (zoom toward cursor):
*   
*   Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
*   camera.offset = GetMousePosition();
*   camera.target = mouseWorld;
*   camera.zoom += GetMouseWheelMove() * 0.1f;
*   
*   COORDINATE CONVERSION:
*   
*   Screen to World:
*   Vector2 worldPos = GetScreenToWorld2D(screenPos, camera);
*   - Converts screen coordinates to world coordinates
*   - Use for: mouse click positions, UI to world interaction
*   
*   World to Screen:
*   Vector2 screenPos = GetWorldToScreen2D(worldPos, camera);
*   - Converts world coordinates to screen coordinates
*   - Use for: drawing UI at world object position
*   
*   Example (draw health bar above player):
*   Vector2 screenPos = GetWorldToScreen2D(playerWorldPos, camera);
*   DrawRectangle(screenPos.x, screenPos.y - 20, 50, 5, RED);
*   
*   CAMERA BOUNDS:
*   Limit camera to world boundaries:
*   
*   // Define world bounds
*   float minX = 0, maxX = 5000;
*   float minY = 0, maxY = 3000;
*   
*   // Clamp camera target
*   if (camera.target.x < minX) camera.target.x = minX;
*   if (camera.target.x > maxX) camera.target.x = maxX;
*   if (camera.target.y < minY) camera.target.y = minY;
*   if (camera.target.y > maxY) camera.target.y = maxY;
*   
*   CAMERA SHAKE:
*   Add screen shake for impacts, explosions:
*   
*   if (shaking) {
*       camera.offset.x += GetRandomValue(-shakeAmount, shakeAmount);
*       camera.offset.y += GetRandomValue(-shakeAmount, shakeAmount);
*       shakeAmount *= 0.9f;  // Decay
*       if (shakeAmount < 1) shaking = false;
*   }
*   
*   ROTATION TIPS:
*   - Rotation is fun but can be disorienting
*   - Usually use rotation = 0 for most games
*   - Good for special effects or specific game types
*   - Rotation happens around camera.target
*   
*   ZOOM TIPS:
*   - zoom = 1.0 is usually best for pixel-art games
*   - Higher zoom (2.0-3.0) for tactical/detail viewing
*   - Lower zoom (0.3-0.8) for strategy/overview
*   - Smooth zoom changes: zoom += (targetZoom - zoom) * 0.1f
*   
*   PERFORMANCE:
*   - Only draw what's visible (frustum culling)
*   - Check if objects are on screen before drawing
*   - Use Rectangle CheckCollisionRecs() with camera viewport
*   
*   GetCameraViewport():
*   Rectangle viewport = {
*       camera.target.x - screenWidth / (2 * camera.zoom),
*       camera.target.y - screenHeight / (2 * camera.zoom),
*       screenWidth / camera.zoom,
*       screenHeight / camera.zoom
*   };
*   
*   COMMON PATTERNS:
*   
*   Minimap:
*   - Use a second camera with different zoom/position
*   - Draw world twice: once with main camera, once with minimap camera
*   
*   Split-screen:
*   - Create two cameras
*   - Use ScissorMode to restrict drawing area
*   - Draw each player's view with their camera
*   
*   UI with World Elements:
*   - Draw world objects with camera
*   - Convert their positions to screen space
*   - Draw UI elements at converted positions
*   
*   BEST PRACTICES:
*   
*   1. Always set camera.offset to center of screen initially
*   2. Update camera.target to follow player/focus point
*   3. Draw game world inside BeginMode2D/EndMode2D
*   4. Draw UI outside camera mode (after EndMode2D)
*   5. Limit zoom levels to reasonable range
*   6. Consider smooth following for better feel
*   7. Use coordinate conversion for mouse interaction with world
*   8. Test camera at different zoom levels
*   9. Add camera bounds to prevent showing empty space
*   10. Profile performance with large worlds
*   
*   TROUBLESHOOTING:
*   
*   Camera not moving:
*   - Make sure you're updating camera.target
*   - Check that BeginMode2D() is called
*   
*   UI moving with world:
*   - UI must be drawn AFTER EndMode2D()
*   
*   Mouse clicks in wrong place:
*   - Convert mouse position to world space first
*   - Vector2 worldMouse = GetScreenToWorld2D(GetMousePosition(), camera);
*   
*   Everything too small/large:
*   - Check camera.zoom value
*   - Reset to 1.0 if unsure
*   
*   TIPS:
*   - Start simple: just follow player at zoom 1.0
*   - Add smooth following for polish
*   - Zoom is powerful but test thoroughly
*   - Always provide camera reset option for players
*   - Consider accessibility: some players sensitive to camera effects
*
*******************************************************************************************/

