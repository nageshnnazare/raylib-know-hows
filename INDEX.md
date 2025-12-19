# Complete Raylib Tutorial Index

## 📚 Guide Contents

This comprehensive guide contains **15 fully-explained examples** progressing from basics to complete games. Every line of code is documented to help you understand not just *how* but *why*.

---

## 🎯 Getting Started

**Before you begin:**
1. Read: `INSTALLATION.md` - Set up raylib on your system
2. Review: `QUICK_REFERENCE.md` - Handy cheat sheet
3. Use: `compile.sh` - Compile individual examples
4. Test: `compile_all.sh` - Verify all examples

---

## 📖 Tutorial Lessons (In Order)

### Part 1: Fundamentals (Start Here!)

#### **01_hello_window.c** - Your First Raylib Program
- Creating a window
- The game loop concept
- Drawing text
- Frame rate control
- **Concepts:** InitWindow, BeginDrawing/EndDrawing, CloseWindow

#### **02_basic_shapes.c** - Drawing Shapes
- Rectangles, circles, lines, triangles
- Filled vs outlined shapes
- Coordinate system explained
- Using Vector2 and Rectangle structures
- **Concepts:** DrawRectangle, DrawCircle, DrawLine, DrawPoly

#### **03_colors.c** - Working with Colors
- Predefined colors
- Custom RGBA colors
- Color mixing (RGB theory)
- Transparency/alpha channel
- Color functions (Fade, ColorAlpha, ColorTint)
- **Concepts:** Color structure, RGBA values, transparency

#### **04_movement.c** - Animation and Movement
- Creating motion
- Bouncing ball physics
- Back-and-forth movement
- Pulsing animations
- Rotation
- **Concepts:** Position += velocity, collision with boundaries, trigonometry basics

---

### Part 2: User Input

#### **05_keyboard_input.c** - Keyboard Controls
- IsKeyDown vs IsKeyPressed
- Continuous vs single-press actions
- Player movement with WASD/arrows
- Key release detection
- **Concepts:** Input handling, movement patterns, boundary checking

#### **06_mouse_input.c** - Mouse Interaction
- Mouse position tracking
- Click detection
- Drag and drop
- Mouse wheel input
- Drawing with mouse
- **Concepts:** GetMousePosition, collision with cursor, drag offset

#### **07_gamepad_input.c** - Game Controller Support
- Gamepad availability checking
- Button input
- Analog sticks
- Triggers
- Deadzone handling
- **Concepts:** Two-player local multiplayer, analog vs digital input

---

### Part 3: Graphics

#### **08_textures.c** - Images and Textures
- Loading and drawing images
- Image vs Texture (RAM vs GPU)
- Different drawing methods
- Texture properties (tint, rotation, scale)
- **Concepts:** LoadTexture, DrawTextureEx, DrawTexturePro, UnloadTexture

#### **09_sprites.c** - Sprite Animation
- Frame-based animation
- Sprite sheets
- Animation timing and speed
- Extracting frames
- **Concepts:** Animation loops, frame counters, sprite sheet layout

#### **10_text_fonts.c** - Text Rendering
- Drawing text
- Font sizes and colors
- Formatted text (TextFormat)
- Text measurement and centering
- Text effects (shadows, backgrounds)
- **Concepts:** DrawText, MeasureText, text alignment

#### **11_camera_2d.c** - 2D Camera System
- Camera basics
- Following the player
- Zoom and rotation
- World space vs screen space
- **Concepts:** Camera2D, BeginMode2D/EndMode2D, coordinate conversion

---

### Part 4: Audio

#### **12_audio_basic.c** - Sound and Music
- Audio system initialization
- Sound vs Music (short vs long audio)
- Playing sounds
- Music streaming
- Volume and pitch control
- **Concepts:** InitAudioDevice, PlaySound, PlayMusicStream, UpdateMusicStream

---

### Part 5: Advanced Topics

#### **13_collision.c** - Collision Detection
- Rectangle vs rectangle
- Circle vs circle
- Circle vs rectangle
- Point vs rectangle
- Collision response (blocking, triggers, collectibles)
- **Concepts:** CheckCollisionRecs, collision resolution, trigger zones

---

### Part 6: Complete Games

#### **14_snake_game.c** - Classic Snake
**A complete game demonstrating:**
- Grid-based movement
- Growing snake mechanic
- Self-collision detection
- Score system
- Game states (title, playing, game over)
- Difficulty progression
- **Lines of Code:** ~380 (heavily documented)

#### **15_pong_game.c** - Two-Player Pong
**A complete game demonstrating:**
- Physics-based ball movement
- Paddle controls (2 players)
- Collision angles
- Score tracking
- Win condition
- Game flow and screens
- **Lines of Code:** ~340 (heavily documented)

---

## 🎓 Learning Path Recommendations

### Absolute Beginner Path
```
01 → 02 → 03 → 04 → 05 → 10 → 14 (Snake)
```
Focus on fundamentals, then build Snake as your first complete game.

### Game Developer Path
```
All lessons in order (01-15)
```
Complete understanding of all raylib features.

### Quick Start Path
```
01 → 05 → 13 → 14 (Snake) or 15 (Pong)
```
Basics → Input → Collision → Complete game

### Graphics Focused Path
```
01 → 02 → 03 → 08 → 09 → 10 → 11
```
Master rendering and animation.

---

## 📊 Difficulty Levels

- **Beginner** ⭐: 01, 02, 03, 05, 10
- **Intermediate** ⭐⭐: 04, 06, 08, 09, 12
- **Advanced** ⭐⭐⭐: 07, 11, 13
- **Complete Games** 🎮: 14, 15

---

## 🛠️ Tools and Scripts

### compile.sh
Compile a single example:
```bash
./compile.sh 01_hello_window.c
./01_hello_window
```

### compile_all.sh
Test compilation of all examples:
```bash
./compile_all.sh
```

### README.md
Main guide overview and installation instructions.

### INSTALLATION.md
Detailed raylib installation for all platforms:
- Linux (Ubuntu/Debian/Fedora/Arch)
- macOS (Homebrew/manual)
- Windows (MinGW/vcpkg)
- Troubleshooting

### QUICK_REFERENCE.md
Cheat sheet with:
- Essential functions
- Common patterns
- Quick lookup
- Tips and tricks

---

## 📝 Code Style and Documentation

Each example includes:
- ✅ **Header comments** explaining the lesson
- ✅ **Line-by-line explanations** of all code
- ✅ **Concept summaries** at the end
- ✅ **Tips and best practices**
- ✅ **Common mistakes to avoid**
- ✅ **Extension ideas**

### Comment Types Used

```c
// Single-line explanation of next line

/* Multi-line explanation
   of complex concepts */

//============================================================
// Section divider for organization
//============================================================

//----------------------------------------------------------------------------------
// Function separator
//----------------------------------------------------------------------------------

/*******************************************************************************************
*   Large documentation block at end of file
*******************************************************************************************/
```

---

## 🎯 What You'll Learn

### Programming Concepts
- Game loop architecture
- Frame-based timing
- State machines
- Data structures (structs, enums)
- Memory management
- Function organization

### Game Development
- Player controls
- Physics simulation
- Collision detection and response
- Animation systems
- Audio integration
- Camera systems
- UI/HUD design
- Game states and flow

### Raylib Specifics
- Window management
- Drawing primitives
- Texture handling
- Input systems (keyboard, mouse, gamepad)
- Audio system
- 2D camera
- Collision functions
- Color system

---

## 🚀 Next Steps After Completing

1. **Modify the examples**
   - Change colors, speeds, sizes
   - Add new features
   - Combine multiple examples

2. **Build your own games**
   - Asteroids
   - Platformer
   - Space shooter
   - Puzzle game
   - Racing game

3. **Explore advanced topics**
   - 3D graphics (raylib supports this!)
   - Shaders
   - Particle systems
   - Networking
   - Save/load systems

4. **Join the community**
   - Share your projects
   - Get feedback
   - Learn from others
   - Contribute back

---

## 📚 Additional Resources

### Official Raylib
- **Website:** https://www.raylib.com/
- **Documentation:** https://www.raylib.com/cheatsheet/cheatsheet.html
- **Examples:** https://www.raylib.com/examples.html (100+ examples!)
- **GitHub:** https://github.com/raysan5/raylib

### Community
- **Discord:** https://discord.gg/raylib (Very active!)
- **Reddit:** r/raylib
- **Twitter:** @raysan5

### Learning
- **raylib wiki:** https://github.com/raysan5/raylib/wiki
- **Raylib 4.0 features:** Check GitHub releases
- **YouTube tutorials:** Search "raylib tutorial"

---

## 🎮 Example Games Made with Raylib

Want inspiration? Check out:
- Games in raylib's examples folder
- Raylib game jam entries
- Showcase on raylib website
- GitHub topic: "raylib-game"

---

## 💡 Tips for Success

1. **Type, don't copy-paste** - You learn better by typing
2. **Read all comments** - They explain why, not just what
3. **Experiment** - Change values, break things, fix them
4. **Start small** - Master basics before complex projects
5. **Ask questions** - Community is helpful!
6. **Build projects** - Apply what you learn
7. **Have fun!** - Game development should be enjoyable

---

## 🏆 Challenge Yourself

After completing the tutorial:

### Easy Challenges
- [ ] Make Snake wrap around screen edges
- [ ] Add pause to Pong
- [ ] Create a 3-ball Pong variant
- [ ] Add power-ups to Snake

### Medium Challenges
- [ ] Build Breakout/Arkanoid
- [ ] Create Flappy Bird
- [ ] Make Space Invaders
- [ ] Build a simple platformer

### Hard Challenges
- [ ] Create a particle system
- [ ] Build a level editor
- [ ] Implement A* pathfinding
- [ ] Make a physics engine

---

## 📞 Getting Help

If you get stuck:

1. **Read the error message carefully**
2. **Check INSTALLATION.md troubleshooting**
3. **Review the comments in the example**
4. **Search raylib GitHub issues**
5. **Ask on Discord** (fastest response)
6. **Post on forums with code samples**

When asking for help, include:
- What you're trying to do
- What's happening instead
- Error messages (full text)
- Your code (relevant parts)
- Your system (OS, compiler)

---

## 🌟 Credits

This tutorial was created to provide:
- **Complete explanations** of every line
- **Progressive learning** from simple to complex
- **Real-world examples** you can actually use
- **Best practices** from the start

Raylib is created and maintained by **Ramon Santamaria (@raysan5)**

---

## 📄 License

These tutorial examples are provided as educational material.
Raylib itself is licensed under zlib/libpng license.

Feel free to:
- ✅ Use these examples to learn
- ✅ Modify them for your projects
- ✅ Share them with others
- ✅ Build upon them

---

## 🎓 Final Words

Game development is a journey. Don't rush! Each example builds on previous ones. Take your time, experiment, and most importantly - have fun!

**Remember:**
> "The best way to learn programming is by writing programs."
> 
> Start with lesson 01, and before you know it, you'll be creating your own games!

Good luck, and happy coding! 🚀

---

**Ready to begin?** Start with `01_hello_window.c` after installing raylib!

