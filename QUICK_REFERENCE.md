# Raylib Quick Reference Guide

## Essential Functions Cheat Sheet

### Window Management
```c
InitWindow(width, height, "title");  // Create window
CloseWindow();                        // Close window and cleanup
WindowShouldClose();                  // Check if ESC or X pressed
SetTargetFPS(60);                     // Set frame rate limit
GetFPS();                             // Get current FPS
```

### Drawing
```c
BeginDrawing();                       // Start drawing
EndDrawing();                         // Finish drawing
ClearBackground(color);               // Fill screen with color

// Shapes
DrawRectangle(x, y, width, height, color);
DrawCircle(x, y, radius, color);
DrawLine(x1, y1, x2, y2, color);
DrawText("text", x, y, fontSize, color);
```

### Input - Keyboard
```c
IsKeyDown(KEY_SPACE);                 // Held continuously
IsKeyPressed(KEY_SPACE);              // Pressed once
IsKeyReleased(KEY_SPACE);             // Released once
```

### Input - Mouse
```c
GetMouseX();                          // Mouse X position
GetMouseY();                          // Mouse Y position
GetMousePosition();                   // Vector2 position
IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
IsMouseButtonDown(MOUSE_BUTTON_LEFT);
```

### Textures
```c
Texture2D tex = LoadTexture("file.png");
DrawTexture(tex, x, y, WHITE);
DrawTextureEx(tex, pos, rotation, scale, tint);
UnloadTexture(tex);                   // Always unload!
```

### Audio
```c
InitAudioDevice();                    // MUST call first
Sound snd = LoadSound("file.wav");
PlaySound(snd);
Music mus = LoadMusicStream("file.mp3");
PlayMusicStream(mus);
UpdateMusicStream(mus);               // Call every frame!
CloseAudioDevice();                   // Call at end
```

### Collision
```c
CheckCollisionRecs(rect1, rect2);     // Rectangle vs Rectangle
CheckCollisionCircles(c1, r1, c2, r2); // Circle vs Circle
CheckCollisionPointRec(point, rect);  // Point vs Rectangle
```

### Colors
```c
// Predefined: RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, etc.
Color custom = { 255, 128, 0, 255 };  // R, G, B, A
Color faded = Fade(RED, 0.5f);        // 50% transparent
```

### Common Patterns

#### Game Loop
```c
while (!WindowShouldClose()) {
    // 1. Update game logic
    
    // 2. Draw
    BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw everything here
    EndDrawing();
}
```

#### Movement
```c
if (IsKeyDown(KEY_RIGHT)) x += speed;
if (IsKeyDown(KEY_LEFT))  x -= speed;
if (IsKeyDown(KEY_DOWN))  y += speed;
if (IsKeyDown(KEY_UP))    y -= speed;
```

#### Collision Response
```c
Rectangle prev = player;
player.x += velocityX;
if (CheckCollisionRecs(player, wall)) {
    player = prev;  // Block movement
}
```

#### Animation
```c
frameCounter++;
if (frameCounter >= framesSpeed) {
    frameCounter = 0;
    currentFrame++;
    if (currentFrame >= maxFrames) currentFrame = 0;
}
```

## File Organization

### Typical Project Structure
```
my_game/
├── main.c
├── game.h
├── assets/
│   ├── textures/
│   ├── sounds/
│   └── music/
└── Makefile
```

### Compilation
```bash
# Single file
gcc game.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# With warnings
gcc game.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra

# Debug mode
gcc game.c -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g
```

## Common Structures

### Vector2
```c
Vector2 pos = { 100.0f, 200.0f };
float x = pos.x;
float y = pos.y;
```

### Rectangle
```c
Rectangle rect = { x, y, width, height };
```

### Camera2D
```c
Camera2D camera = { 0 };
camera.offset = (Vector2){ screenWidth/2, screenHeight/2 };
camera.target = (Vector2){ playerX, playerY };
camera.rotation = 0.0f;
camera.zoom = 1.0f;

BeginMode2D(camera);
    // Draw world
EndMode2D();
```

## Tips & Tricks

1. **Always check return values**
   ```c
   Texture2D tex = LoadTexture("file.png");
   if (tex.id == 0) {
       // Loading failed!
   }
   ```

2. **Use const for constants**
   ```c
   const int SCREEN_WIDTH = 800;
   const float PLAYER_SPEED = 5.0f;
   ```

3. **Separate logic from drawing**
   ```c
   void UpdateGame() { /* logic */ }
   void DrawGame() { /* rendering */ }
   ```

4. **Use structs for game objects**
   ```c
   typedef struct {
       Vector2 position;
       Vector2 velocity;
       float radius;
       Color color;
   } Ball;
   ```

5. **Always unload resources**
   ```c
   UnloadTexture(texture);
   UnloadSound(sound);
   UnloadMusicStream(music);
   ```

## Key Constants

### Keys
- `KEY_SPACE`, `KEY_ENTER`, `KEY_ESCAPE`
- `KEY_A` through `KEY_Z`
- `KEY_UP`, `KEY_DOWN`, `KEY_LEFT`, `KEY_RIGHT`
- `KEY_LEFT_SHIFT`, `KEY_LEFT_CONTROL`

### Mouse Buttons
- `MOUSE_BUTTON_LEFT`
- `MOUSE_BUTTON_RIGHT`
- `MOUSE_BUTTON_MIDDLE`

### Colors (some examples)
- `WHITE`, `BLACK`, `GRAY`, `DARKGRAY`, `LIGHTGRAY`
- `RED`, `GREEN`, `BLUE`, `YELLOW`, `ORANGE`, `PURPLE`
- `RAYWHITE`, `SKYBLUE`, `LIME`, `GOLD`, `MAROON`

## Performance Tips

1. Load textures once (initialization)
2. Draw many times (game loop)
3. Unload once (cleanup)
4. Use DrawTexture for simple cases
5. Use DrawTexturePro for sprite sheets
6. Limit collision checks (spatial partitioning)
7. Use GetFrameTime() for time-based movement

## Learning Path

1. ✓ Window and basic shapes
2. ✓ Input handling
3. ✓ Movement and animation
4. ✓ Textures and sprites
5. ✓ Collision detection
6. ✓ Audio
7. ✓ Complete games
8. → Your own projects!

## Resources

- Official: https://www.raylib.com
- Cheatsheet: https://www.raylib.com/cheatsheet/cheatsheet.html
- Examples: https://www.raylib.com/examples.html
- Discord: https://discord.gg/raylib

## Common Errors & Solutions

**Error: "raylib.h: No such file or directory"**
- Solution: Install raylib library

**Error: "undefined reference to 'InitWindow'"**
- Solution: Add `-lraylib` to compilation command

**Black screen / Nothing drawing**
- Solution: Check BeginDrawing/EndDrawing are called
- Solution: Check SetTargetFPS is set

**Textures not loading**
- Solution: Check file path is correct
- Solution: Check file format is supported (PNG, JPG, etc.)

**Audio not playing**
- Solution: Call InitAudioDevice() first
- Solution: Call UpdateMusicStream() every frame for music

**Collision not working**
- Solution: Check hitbox positions match visuals
- Solution: Verify collision check is in update loop

**Memory leaks**
- Solution: Always Unload what you Load
- Solution: CloseWindow and CloseAudioDevice at end

---

**Remember:** Start simple, test often, and have fun!

