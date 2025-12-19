/*******************************************************************************************
*
*   RAYLIB COMPLETE GAME: SNAKE
*   
*   This is a complete implementation of the classic Snake game.
*   Every line is explained to help you understand how all the concepts come together!
*
*   GAME RULES:
*   - Control the snake with arrow keys
*   - Eat food to grow longer and gain points
*   - Don't hit walls or your own body
*   - Game gets faster as you score more
*
*******************************************************************************************/

#include "raylib.h"
#include <stdlib.h>  // For rand()
#include <time.h>    // For time() to seed random

// ============================================================
// CONSTANTS AND CONFIGURATION
// ============================================================

// Screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Grid configuration
// The game world is divided into a grid
#define GRID_SIZE 20              // Size of each grid cell in pixels
#define GRID_WIDTH (SCREEN_WIDTH / GRID_SIZE)   // 40 cells wide
#define GRID_HEIGHT (SCREEN_HEIGHT / GRID_SIZE) // 30 cells tall

// Snake configuration
#define MAX_SNAKE_LENGTH 300      // Maximum snake length
#define INITIAL_SNAKE_LENGTH 3    // Starting length

// Game speed (frames between moves)
#define INITIAL_SPEED 15          // Lower = faster
#define MIN_SPEED 5               // Fastest possible speed

// ============================================================
// DATA STRUCTURES
// ============================================================

// Direction enum - represents which way the snake is moving
typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

// Game state enum - tracks what screen/state we're in
typedef enum {
    SCREEN_TITLE,    // Title/start screen
    SCREEN_PLAYING,  // Actively playing
    SCREEN_GAMEOVER  // Game over screen
} GameScreen;

// Position structure - represents a grid position
typedef struct {
    int x;  // Grid X coordinate (0 to GRID_WIDTH-1)
    int y;  // Grid Y coordinate (0 to GRID_HEIGHT-1)
} GridPosition;

// Snake structure - contains all snake data
typedef struct {
    GridPosition body[MAX_SNAKE_LENGTH];  // Array of body segment positions
    int length;                            // Current snake length
    Direction direction;                   // Current movement direction
    Direction nextDirection;               // Next direction (for input buffering)
} Snake;

// ============================================================
// GLOBAL VARIABLES
// ============================================================

Snake snake;                    // The player's snake
GridPosition food;              // Food position
int score = 0;                  // Player's score
int frameCounter = 0;           // Counts frames for movement timing
int moveSpeed = INITIAL_SPEED; // Current movement speed
GameScreen currentScreen = SCREEN_TITLE;  // Current game screen
bool gameOver = false;          // Game over flag

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

void InitGame(void);            // Initialize/reset the game
void UpdateGame(void);          // Update game logic
void DrawGame(void);            // Draw everything
void MoveSnake(void);           // Move the snake
void GrowSnake(void);           // Add a segment to the snake
void SpawnFood(void);           // Place food at random position
bool CheckSelfCollision(void);  // Check if snake hit itself
bool CheckWallCollision(void);  // Check if snake hit wall
bool CheckFoodCollision(void);  // Check if snake ate food

// ============================================================
// MAIN FUNCTION
// ============================================================

int main(void)
{
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game - Complete Raylib Example");
    
    // Seed random number generator
    // This ensures we get different random food positions each run
    srand(time(NULL));
    
    // Set target FPS
    SetTargetFPS(60);
    
    // Initialize the game
    InitGame();

    // ============================================================
    // MAIN GAME LOOP
    // ============================================================
    while (!WindowShouldClose())
    {
        // Update game logic
        UpdateGame();
        
        // Draw everything
        DrawGame();
    }

    // Cleanup and close
    CloseWindow();
    
    return 0;
}

// ============================================================
// FUNCTION IMPLEMENTATIONS
// ============================================================

//----------------------------------------------------------------------------------
// InitGame() - Initialize or reset the game state
//----------------------------------------------------------------------------------
void InitGame(void)
{
    // Reset score and speed
    score = 0;
    moveSpeed = INITIAL_SPEED;
    gameOver = false;
    
    // Initialize snake in the center of the screen
    snake.length = INITIAL_SNAKE_LENGTH;
    snake.direction = DIR_RIGHT;
    snake.nextDirection = DIR_RIGHT;
    
    // Place snake segments in a horizontal line
    // Start position is roughly center of grid
    int startX = GRID_WIDTH / 2;
    int startY = GRID_HEIGHT / 2;
    
    for (int i = 0; i < snake.length; i++)
    {
        // Each segment is placed to the left of the previous one
        // This creates a snake moving right
        snake.body[i].x = startX - i;
        snake.body[i].y = startY;
    }
    
    // Spawn initial food
    SpawnFood();
}

//----------------------------------------------------------------------------------
// UpdateGame() - Main game update logic
//----------------------------------------------------------------------------------
void UpdateGame(void)
{
    // ============================================================
    // UPDATE BASED ON CURRENT SCREEN
    // ============================================================
    
    if (currentScreen == SCREEN_TITLE)
    {
        // On title screen, wait for ENTER to start
        if (IsKeyPressed(KEY_ENTER))
        {
            currentScreen = SCREEN_PLAYING;
            InitGame();  // Reset game
        }
    }
    else if (currentScreen == SCREEN_PLAYING)
    {
        // ============================================================
        // INPUT HANDLING
        // ============================================================
        
        // Read arrow key input to change direction
        // We use nextDirection to buffer the input
        // This prevents the player from reversing into themselves
        
        if (IsKeyPressed(KEY_UP) && snake.direction != DIR_DOWN)
        {
            snake.nextDirection = DIR_UP;
        }
        if (IsKeyPressed(KEY_DOWN) && snake.direction != DIR_UP)
        {
            snake.nextDirection = DIR_DOWN;
        }
        if (IsKeyPressed(KEY_LEFT) && snake.direction != DIR_RIGHT)
        {
            snake.nextDirection = DIR_LEFT;
        }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction != DIR_LEFT)
        {
            snake.nextDirection = DIR_RIGHT;
        }
        
        // ============================================================
        // MOVEMENT TIMING
        // ============================================================
        
        // Increment frame counter
        frameCounter++;
        
        // Only move snake every 'moveSpeed' frames
        // This controls game speed
        if (frameCounter >= moveSpeed)
        {
            frameCounter = 0;  // Reset counter
            
            // Update direction from buffered input
            snake.direction = snake.nextDirection;
            
            // Move the snake
            MoveSnake();
            
            // ============================================================
            // COLLISION DETECTION
            // ============================================================
            
            // Check if snake ate food
            if (CheckFoodCollision())
            {
                // Grow snake
                GrowSnake();
                
                // Increase score
                score += 10;
                
                // Spawn new food
                SpawnFood();
                
                // Increase speed slightly (make game harder)
                if (moveSpeed > MIN_SPEED)
                {
                    moveSpeed--;  // Lower number = faster
                }
            }
            
            // Check if snake hit wall or itself
            if (CheckWallCollision() || CheckSelfCollision())
            {
                currentScreen = SCREEN_GAMEOVER;
                gameOver = true;
            }
        }
    }
    else if (currentScreen == SCREEN_GAMEOVER)
    {
        // On game over screen, wait for ENTER to restart
        if (IsKeyPressed(KEY_ENTER))
        {
            currentScreen = SCREEN_PLAYING;
            InitGame();  // Reset game
        }
    }
}

//----------------------------------------------------------------------------------
// DrawGame() - Render everything
//----------------------------------------------------------------------------------
void DrawGame(void)
{
    BeginDrawing();
    
        ClearBackground(DARKGREEN);
        
        // ============================================================
        // DRAW BASED ON CURRENT SCREEN
        // ============================================================
        
        if (currentScreen == SCREEN_TITLE)
        {
            // ============================================================
            // TITLE SCREEN
            // ============================================================
            
            DrawText("SNAKE GAME", 250, 150, 60, LIME);
            DrawText("Classic Snake implemented in Raylib", 220, 230, 20, LIGHTGRAY);
            
            DrawText("HOW TO PLAY:", 300, 300, 20, YELLOW);
            DrawText("- Use arrow keys to move", 250, 330, 18, WHITE);
            DrawText("- Eat food to grow and gain points", 250, 355, 18, WHITE);
            DrawText("- Don't hit walls or yourself!", 250, 380, 18, WHITE);
            
            DrawText("Press ENTER to start", 270, 450, 22, LIME);
            
            // Draw a small snake example
            DrawRectangle(100, 500, GRID_SIZE, GRID_SIZE, LIME);
            DrawRectangle(120, 500, GRID_SIZE, GRID_SIZE, LIME);
            DrawRectangle(140, 500, GRID_SIZE, GRID_SIZE, LIME);
        }
        else if (currentScreen == SCREEN_PLAYING)
        {
            // ============================================================
            // GAME SCREEN
            // ============================================================
            
            // Draw grid (optional, helps visualize the game space)
            for (int x = 0; x < GRID_WIDTH; x++)
            {
                for (int y = 0; y < GRID_HEIGHT; y++)
                {
                    // Checkerboard pattern for better visibility
                    Color gridColor = ((x + y) % 2 == 0) ? DARKGREEN : Fade(DARKGREEN, 0.9f);
                    DrawRectangle(x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE, gridColor);
                }
            }
            
            // Draw snake
            for (int i = 0; i < snake.length; i++)
            {
                // Head is brighter than body
                Color segmentColor = (i == 0) ? LIME : GREEN;
                
                // Calculate screen position from grid position
                int screenX = snake.body[i].x * GRID_SIZE;
                int screenY = snake.body[i].y * GRID_SIZE;
                
                // Draw segment with a small gap for better appearance
                DrawRectangle(screenX + 1, screenY + 1, GRID_SIZE - 2, GRID_SIZE - 2, segmentColor);
            }
            
            // Draw eyes on snake head for fun!
            int headX = snake.body[0].x * GRID_SIZE;
            int headY = snake.body[0].y * GRID_SIZE;
            DrawCircle(headX + 6, headY + 6, 2, BLACK);
            DrawCircle(headX + 14, headY + 6, 2, BLACK);
            
            // Draw food
            int foodX = food.x * GRID_SIZE;
            int foodY = food.y * GRID_SIZE;
            DrawCircle(foodX + GRID_SIZE/2, foodY + GRID_SIZE/2, GRID_SIZE/2 - 2, RED);
            
            // Draw HUD (Heads-Up Display)
            DrawRectangle(0, 0, SCREEN_WIDTH, 30, Fade(BLACK, 0.7f));
            DrawText(TextFormat("Score: %d", score), 10, 5, 20, WHITE);
            DrawText(TextFormat("Length: %d", snake.length), 200, 5, 20, WHITE);
            DrawText(TextFormat("Speed: %d", INITIAL_SPEED - moveSpeed + 1), 400, 5, 20, WHITE);
        }
        else if (currentScreen == SCREEN_GAMEOVER)
        {
            // ============================================================
            // GAME OVER SCREEN
            // ============================================================
            
            DrawText("GAME OVER", 280, 200, 50, RED);
            DrawText(TextFormat("Final Score: %d", score), 300, 270, 30, WHITE);
            DrawText(TextFormat("Snake Length: %d", snake.length), 280, 310, 25, WHITE);
            
            DrawText("Press ENTER to play again", 250, 400, 22, LIGHTGRAY);
        }
    
    EndDrawing();
}

//----------------------------------------------------------------------------------
// MoveSnake() - Move the snake in current direction
//----------------------------------------------------------------------------------
void MoveSnake(void)
{
    // Move all body segments forward
    // Start from the tail and copy each segment to the next position
    // This is like a chain - each link follows the one in front
    for (int i = snake.length - 1; i > 0; i--)
    {
        snake.body[i] = snake.body[i - 1];  // Copy previous segment position
    }
    
    // Move the head based on current direction
    switch (snake.direction)
    {
        case DIR_UP:
            snake.body[0].y--;  // Move up (decrease Y)
            break;
        case DIR_DOWN:
            snake.body[0].y++;  // Move down (increase Y)
            break;
        case DIR_LEFT:
            snake.body[0].x--;  // Move left (decrease X)
            break;
        case DIR_RIGHT:
            snake.body[0].x++;  // Move right (increase X)
            break;
    }
}

//----------------------------------------------------------------------------------
// GrowSnake() - Add a segment to the snake
//----------------------------------------------------------------------------------
void GrowSnake(void)
{
    // Only grow if we haven't reached max length
    if (snake.length < MAX_SNAKE_LENGTH)
    {
        // The new segment will be placed at the tail position
        // It will automatically be in the right place after the next move
        snake.body[snake.length] = snake.body[snake.length - 1];
        snake.length++;
    }
}

//----------------------------------------------------------------------------------
// SpawnFood() - Place food at a random empty position
//----------------------------------------------------------------------------------
void SpawnFood(void)
{
    // Keep trying random positions until we find one that's not on the snake
    bool validPosition = false;
    
    while (!validPosition)
    {
        // Generate random grid position
        food.x = rand() % GRID_WIDTH;
        food.y = rand() % GRID_HEIGHT;
        
        // Check if this position overlaps with any snake segment
        validPosition = true;
        for (int i = 0; i < snake.length; i++)
        {
            if (food.x == snake.body[i].x && food.y == snake.body[i].y)
            {
                validPosition = false;  // Food is on snake, try again
                break;
            }
        }
    }
}

//----------------------------------------------------------------------------------
// CheckFoodCollision() - Check if snake head is on food
//----------------------------------------------------------------------------------
bool CheckFoodCollision(void)
{
    // Compare snake head position with food position
    return (snake.body[0].x == food.x && snake.body[0].y == food.y);
}

//----------------------------------------------------------------------------------
// CheckWallCollision() - Check if snake hit the walls
//----------------------------------------------------------------------------------
bool CheckWallCollision(void)
{
    // Check if head is outside the grid boundaries
    GridPosition head = snake.body[0];
    
    return (head.x < 0 ||                   // Left wall
            head.x >= GRID_WIDTH ||         // Right wall
            head.y < 0 ||                   // Top wall
            head.y >= GRID_HEIGHT);         // Bottom wall
}

//----------------------------------------------------------------------------------
// CheckSelfCollision() - Check if snake hit its own body
//----------------------------------------------------------------------------------
bool CheckSelfCollision(void)
{
    GridPosition head = snake.body[0];
    
    // Check if head position matches any body segment (skip head itself at index 0)
    for (int i = 1; i < snake.length; i++)
    {
        if (head.x == snake.body[i].x && head.y == snake.body[i].y)
        {
            return true;  // Snake hit itself!
        }
    }
    
    return false;  // No self-collision
}

/*******************************************************************************************
*
*   WHAT YOU LEARNED IN THIS COMPLETE GAME:
*   
*   GAME STRUCTURE:
*   1. Data structures (Snake, Position, Enums)
*   2. Game states (Title, Playing, GameOver)
*   3. Separation of logic: Init, Update, Draw
*   4. Frame-based timing for game speed
*   
*   CORE CONCEPTS APPLIED:
*   1. Grid-based movement
*   2. Input buffering (nextDirection prevents reverse)
*   3. Snake movement (chain of body segments)
*   4. Collision detection (food, walls, self)
*   5. Score tracking and increasing difficulty
*   6. Random positioning (food spawning)
*   
*   RAYLIB FEATURES USED:
*   - Window management
*   - Drawing shapes (rectangles, circles)
*   - Text rendering
*   - Input handling (keyboard)
*   - Frame timing
*   - Colors and transparency
*   
*   CODE ORGANIZATION:
*   - Functions for specific tasks
*   - Clear variable names
*   - Comments explaining logic
*   - Constant defines for easy tweaking
*   
*   GAME DESIGN PATTERNS:
*   1. State machine (different screens)
*   2. Game loop (Update -> Draw)
*   3. Entity management (snake as structure)
*   4. Difficulty progression (speed increase)
*   
*   POSSIBLE ENHANCEMENTS:
*   - Add sound effects (eating, game over)
*   - Add power-ups (speed boost, slow time)
*   - Add obstacles in the playing field
*   - Add high score saving
*   - Add different game modes
*   - Add walls/mazes
*   - Add multiplayer (two snakes)
*   - Add particle effects
*   - Add animations (smooth movement)
*   - Add pause functionality
*   
*   Try modifying this game to make it your own!
*
*******************************************************************************************/

