/*******************************************************************************************
*
*   RAYLIB LESSON 08: Textures and Images
*   
*   Learn how to load and display images! This is essential for game graphics.
*   We'll cover loading textures, drawing them, and basic image manipulation.
*
*   NOTE: This example creates a procedural texture (no external file needed).
*   In real games, you'd load PNG/JPG files with LoadTexture("filename.png")
*
*******************************************************************************************/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - textures and images");
    
    SetTargetFPS(60);

    // ============================================================
    // CREATING A PROCEDURAL IMAGE
    // ============================================================
    
    // For this example, we'll create an image programmatically
    // This way the example works without needing external files
    
    // Create a blank 64x64 image with RGBA format
    // RGBA means: Red, Green, Blue, Alpha channels
    Image checkedImage = GenImageChecked(64, 64, 8, 8, RED, BLUE);
    
    // Convert the Image to a Texture so we can draw it
    // Image = data in RAM (can be modified)
    // Texture = data in GPU (optimized for drawing)
    Texture2D texture = LoadTextureFromImage(checkedImage);
    
    // Once we've created the texture, we can free the image from RAM
    UnloadImage(checkedImage);
    
    // ============================================================
    // CREATE MORE TEXTURES
    // ============================================================
    
    // Gradient texture
    Image gradientImg = GenImageGradientLinear(128, 128, 0, WHITE, BLACK);
    Texture2D gradientTexture = LoadTextureFromImage(gradientImg);
    UnloadImage(gradientImg);
    
    // Circle texture
    Image circleImg = GenImageColor(64, 64, BLANK);  // Start with transparent image
    // Draw a circle on the image
    ImageDrawCircle(&circleImg, 32, 32, 28, YELLOW);
    Texture2D circleTexture = LoadTextureFromImage(circleImg);
    UnloadImage(circleImg);
    
    // ============================================================
    // TEXTURE PROPERTIES
    // ============================================================
    
    // Position and rotation for our main texture
    Vector2 position = { 100, 100 };
    float rotation = 0.0f;
    float scale = 2.0f;
    
    // Tint color (used to color textures)
    Color tint = WHITE;  // WHITE means no tinting (original colors)

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // Rotate the texture
        rotation += 1.0f;
        if (rotation >= 360.0f) rotation = 0.0f;
        
        // Move texture with arrow keys
        if (IsKeyDown(KEY_RIGHT)) position.x += 3.0f;
        if (IsKeyDown(KEY_LEFT)) position.x -= 3.0f;
        if (IsKeyDown(KEY_DOWN)) position.y += 3.0f;
        if (IsKeyDown(KEY_UP)) position.y -= 3.0f;
        
        // Change scale with +/-
        if (IsKeyPressed(KEY_EQUAL)) scale += 0.5f;  // + key
        if (IsKeyPressed(KEY_MINUS)) scale -= 0.5f;  // - key
        if (scale < 0.5f) scale = 0.5f;
        if (scale > 5.0f) scale = 5.0f;
        
        // Change tint with number keys
        if (IsKeyPressed(KEY_ONE)) tint = WHITE;
        if (IsKeyPressed(KEY_TWO)) tint = RED;
        if (IsKeyPressed(KEY_THREE)) tint = GREEN;
        if (IsKeyPressed(KEY_FOUR)) tint = BLUE;
        if (IsKeyPressed(KEY_FIVE)) tint = YELLOW;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);
            
            DrawText("TEXTURES & IMAGES", 250, 10, 30, WHITE);
            
            // Instructions
            DrawText("Arrow Keys: Move", 20, 50, 14, LIGHTGRAY);
            DrawText("+/- : Scale", 20, 70, 14, LIGHTGRAY);
            DrawText("1-5: Change tint", 20, 90, 14, LIGHTGRAY);
            
            // ============================================================
            // DRAWING TEXTURES - Different Methods
            // ============================================================
            
            // Method 1: DrawTexture() - Simple draw at position
            // Parameters: texture, x, y, tint
            // Draws at original size, no rotation
            DrawTexture(texture, 20, 150, WHITE);
            DrawText("DrawTexture", 20, 220, 12, WHITE);
            
            // Method 2: DrawTextureV() - Draw with Vector2 position
            // Same as DrawTexture but uses Vector2 for position
            Vector2 pos2 = { 120, 150 };
            DrawTextureV(texture, pos2, tint);
            DrawText("With tint", 120, 220, 12, WHITE);
            
            // Method 3: DrawTextureEx() - Draw with rotation and scale
            // Parameters: texture, position, rotation, scale, tint
            // This is the most flexible drawing method
            DrawTextureEx(texture, position, rotation, scale, tint);
            DrawText("Rotated/Scaled", (int)position.x, (int)position.y + 80, 12, WHITE);
            
            // Method 4: DrawTexturePro() - Draw with source/dest rectangles
            // This is the most powerful method - allows:
            // - Drawing part of a texture (sprite sheets!)
            // - Stretching/squishing
            // - Custom origin point for rotation
            
            // Source rectangle (what part of the texture to draw)
            // { x, y, width, height } in texture coordinates
            Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
            
            // Destination rectangle (where and how big on screen)
            Rectangle dest = { 500, 200, 100, 100 };
            
            // Origin point (pivot point for rotation)
            // { 0, 0 } = top-left corner
            // { width/2, height/2 } = center
            Vector2 origin = { 50, 50 };  // Center of the destination rect
            
            DrawTexturePro(texture, source, dest, origin, rotation * 0.5f, WHITE);
            DrawText("DrawTexturePro", 460, 280, 12, WHITE);
            
            // ============================================================
            // DRAWING OTHER TEXTURES
            // ============================================================
            
            // Gradient texture
            DrawTexture(gradientTexture, 600, 50, WHITE);
            DrawText("Gradient", 620, 185, 12, WHITE);
            
            // Circle texture
            DrawTexture(circleTexture, 650, 300, WHITE);
            DrawText("Circle", 655, 370, 12, WHITE);
            
            // ============================================================
            // TEXTURE PROPERTIES AND INFO
            // ============================================================
            
            DrawText("TEXTURE INFO:", 20, 320, 16, YELLOW);
            DrawText(TextFormat("Size: %d x %d", texture.width, texture.height), 20, 345, 14, WHITE);
            DrawText(TextFormat("Position: (%.0f, %.0f)", position.x, position.y), 20, 365, 14, WHITE);
            DrawText(TextFormat("Rotation: %.0f degrees", rotation), 20, 385, 14, WHITE);
            DrawText(TextFormat("Scale: %.1f", scale), 20, 405, 14, WHITE);
            DrawText(TextFormat("Tint: %d,%d,%d", tint.r, tint.g, tint.b), 20, 425, 14, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // IMPORTANT: Always unload textures when done!
    // This frees GPU memory
    UnloadTexture(texture);
    UnloadTexture(gradientTexture);
    UnloadTexture(circleTexture);
    
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}

/*******************************************************************************************
*
*   KEY CONCEPTS LEARNED:
*   
*   IMAGE vs TEXTURE:
*   
*   Image:
*   - Data stored in RAM (system memory)
*   - Can be modified (change pixels, apply filters)
*   - Cannot be drawn directly
*   - Use for processing, manipulation
*   
*   Texture:
*   - Data stored in GPU memory (graphics card)
*   - Optimized for fast drawing
*   - Cannot be easily modified
*   - Use for rendering to screen
*   
*   Workflow: Create/Load Image -> Process it -> Convert to Texture -> Draw it
*   
*   LOADING TEXTURES:
*   
*   From file (most common):
*   Texture2D texture = LoadTexture("image.png");
*   
*   Supported formats: PNG, BMP, TGA, JPG, GIF, PSD, HDR, PIC
*   
*   From Image:
*   Image img = LoadImage("file.png");
*   Texture2D texture = LoadTextureFromImage(img);
*   UnloadImage(img);  // Free RAM after converting
*   
*   GENERATING IMAGES (No file needed):
*   - GenImageColor() - solid color
*   - GenImageGradientLinear() - linear gradient
*   - GenImageGradientRadial() - radial gradient
*   - GenImageChecked() - checkerboard pattern
*   - GenImageWhiteNoise() - random noise
*   
*   DRAWING TEXTURES:
*   
*   1. DrawTexture(texture, x, y, tint)
*      - Simplest method
*      - Original size, no rotation
*   
*   2. DrawTextureV(texture, position, tint)
*      - Same as DrawTexture but with Vector2
*   
*   3. DrawTextureEx(texture, position, rotation, scale, tint)
*      - Adds rotation and scaling
*      - Rotation in degrees
*      - Scale: 1.0 = original size, 2.0 = double, 0.5 = half
*   
*   4. DrawTexturePro(texture, source, dest, origin, rotation, tint)
*      - Most powerful method
*      - source: Rectangle defining which part of texture to use
*      - dest: Rectangle defining where and how big to draw
*      - origin: Pivot point for rotation
*      - Allows sprite sheet extraction and advanced effects
*   
*   TEXTURE TINTING:
*   - Multiplies texture colors by tint color
*   - WHITE = no change (shows original colors)
*   - RED = only red channel (red tint)
*   - Fade(WHITE, 0.5) = 50% transparent
*   
*   TEXTURE PROPERTIES:
*   - texture.width - width in pixels
*   - texture.height - height in pixels
*   - texture.id - OpenGL texture ID (advanced)
*   - texture.format - pixel format (advanced)
*   
*   RECTANGLES:
*   Used extensively with textures:
*   
*   Rectangle rect = { x, y, width, height };
*   
*   For DrawTexturePro():
*   - source rect: which part of texture (in texture coordinates)
*   - dest rect: where to draw on screen (in screen coordinates)
*   
*   ORIGIN POINT:
*   The pivot point for rotation:
*   
*   { 0, 0 } - Top-left corner (default)
*   { width/2, height/2 } - Center (most common for rotation)
*   { width, height } - Bottom-right corner
*   
*   IMAGE MANIPULATION:
*   Images can be modified before converting to texture:
*   
*   Image img = GenImageColor(100, 100, WHITE);
*   ImageDrawRectangle(&img, 10, 10, 50, 50, RED);
*   ImageDrawCircle(&img, 50, 50, 20, BLUE);
*   ImageFlipVertical(&img);
*   ImageResize(&img, 200, 200);
*   Texture2D tex = LoadTextureFromImage(img);
*   
*   MEMORY MANAGEMENT:
*   CRITICAL: Always unload textures when done!
*   
*   UnloadTexture(texture);  // Free GPU memory
*   UnloadImage(image);      // Free RAM
*   
*   Forgetting this causes memory leaks!
*   
*   COMMON TEXTURE USES:
*   - Sprites (game characters, objects)
*   - Backgrounds
*   - UI elements (buttons, icons)
*   - Particle textures
*   - Tilesets (for tile-based maps)
*   - Font textures (for custom fonts)
*   
*   SPRITE SHEETS:
*   Large images containing many small sprites
*   Use source rectangle in DrawTexturePro() to extract individual sprites
*   Example:
*   
*   Rectangle source = { spriteX, spriteY, spriteWidth, spriteHeight };
*   Rectangle dest = { screenX, screenY, screenWidth, screenHeight };
*   DrawTexturePro(spriteSheet, source, dest, origin, 0, WHITE);
*   
*   TEXTURE FILTERING:
*   Controls how texture looks when scaled:
*   
*   SetTextureFilter(texture, TEXTURE_FILTER_POINT);      // Pixelated (retro)
*   SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);   // Smooth (default)
*   
*   BEST PRACTICES:
*   1. Load textures once (in initialization)
*   2. Draw many times per frame (in game loop)
*   3. Unload when done (in de-initialization)
*   4. Use power-of-2 sizes for best performance (64, 128, 256, 512, 1024)
*   5. Use PNG for images with transparency
*   6. Use JPG for photos/backgrounds (smaller file size)
*   7. Use sprite sheets instead of many small files
*   8. Consider texture atlases for optimization
*   
*   TIPS:
*   - Keep texture sizes reasonable (not too huge)
*   - Use DrawTextureEx() for most game sprites
*   - Use DrawTexturePro() for sprite sheets and advanced effects
*   - WHITE tint = original colors
*   - Origin at center makes rotation look better
*   - Test on different resolutions
*
*******************************************************************************************/

