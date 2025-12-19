/*******************************************************************************************
*
*   RAYLIB COMPLETE GAME: PONG
*   
*   A complete implementation of the classic Pong game.
*   This is simpler than Snake and great for understanding game physics!
*
*   GAME RULES:
*   - Player 1 (left paddle): W/S keys
*   - Player 2 (right paddle): UP/DOWN arrows
*   - First to 5 points wins
*   - Ball bounces off paddles and top/bottom walls
*
*******************************************************************************************/

#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

// ============================================================
// CONSTANTS
// ============================================================

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Paddle settings
#define PADDLE_WIDTH 15
#define PADDLE_HEIGHT 80
#define PADDLE_SPEED 6.0f

// Ball settings
#define BALL_RADIUS 8.0f
#define BALL_SPEED_START 5.0f
#define BALL_SPEED_MAX 12.0f
#define BALL_SPEED_INCREASE 0.5f

// Game settings
#define WINNING_SCORE 5

// ============================================================
// STRUCTURES
// ============================================================

typedef struct {
    Vector2 position;
    float speed;
} Paddle;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float radius;
} Ball;

typedef enum {
    SCREEN_MENU,
    SCREEN_GAME,
    SCREEN_WINNER
} GameScreen;

// ============================================================
// GLOBAL VARIABLES
// ============================================================

Paddle leftPaddle;
Paddle rightPaddle;
Ball ball;
int player1Score = 0;
int player2Score = 0;
int winner = 0;  // 1 or 2
GameScreen currentScreen = SCREEN_MENU;

// ============================================================
// FUNCTION DECLARATIONS
// ============================================================

void InitGame(void);
void ResetBall(int direction);  // direction: -1 for left, 1 for right
void UpdateGame(void);
void DrawGame(void);

// ============================================================
// MAIN FUNCTION
// ============================================================

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong - Complete Raylib Example");
    
    srand(time(NULL));
    SetTargetFPS(60);
    
    InitGame();
    
    while (!WindowShouldClose())
    {
        UpdateGame();
        DrawGame();
    }
    
    CloseWindow();
    return 0;
}

// ============================================================
// FUNCTION IMPLEMENTATIONS
// ============================================================

//----------------------------------------------------------------------------------
// InitGame() - Initialize game state
//----------------------------------------------------------------------------------
void InitGame(void)
{
    // Initialize left paddle (Player 1)
    leftPaddle.position = (Vector2){ 30, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
    leftPaddle.speed = PADDLE_SPEED;
    
    // Initialize right paddle (Player 2)
    rightPaddle.position = (Vector2){ SCREEN_WIDTH - 30 - PADDLE_WIDTH, 
                                      SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
    rightPaddle.speed = PADDLE_SPEED;
    
    // Reset scores
    player1Score = 0;
    player2Score = 0;
    
    // Reset ball (send it to the right initially)
    ResetBall(1);
}

//----------------------------------------------------------------------------------
// ResetBall() - Reset ball to center with velocity in given direction
//----------------------------------------------------------------------------------
void ResetBall(int direction)
{
    // Place ball in center
    ball.position = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    ball.radius = BALL_RADIUS;
    
    // Set velocity
    // direction: -1 = left, 1 = right
    float angle = ((rand() % 60) - 30) * DEG2RAD;  // Random angle between -30 and +30 degrees
    
    ball.velocity.x = cosf(angle) * BALL_SPEED_START * direction;
    ball.velocity.y = sinf(angle) * BALL_SPEED_START;
}

//----------------------------------------------------------------------------------
// UpdateGame() - Game logic
//----------------------------------------------------------------------------------
void UpdateGame(void)
{
    if (currentScreen == SCREEN_MENU)
    {
        // Wait for SPACE to start
        if (IsKeyPressed(KEY_SPACE))
        {
            currentScreen = SCREEN_GAME;
            InitGame();
        }
    }
    else if (currentScreen == SCREEN_GAME)
    {
        // ============================================================
        // PADDLE CONTROLS
        // ============================================================
        
        // Player 1 (left paddle) - W and S keys
        if (IsKeyDown(KEY_W))
        {
            leftPaddle.position.y -= leftPaddle.speed;
        }
        if (IsKeyDown(KEY_S))
        {
            leftPaddle.position.y += leftPaddle.speed;
        }
        
        // Player 2 (right paddle) - Arrow keys
        if (IsKeyDown(KEY_UP))
        {
            rightPaddle.position.y -= rightPaddle.speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            rightPaddle.position.y += rightPaddle.speed;
        }
        
        // ============================================================
        // PADDLE BOUNDARY CHECKING
        // ============================================================
        
        // Keep paddles on screen
        if (leftPaddle.position.y < 0)
            leftPaddle.position.y = 0;
        if (leftPaddle.position.y + PADDLE_HEIGHT > SCREEN_HEIGHT)
            leftPaddle.position.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
            
        if (rightPaddle.position.y < 0)
            rightPaddle.position.y = 0;
        if (rightPaddle.position.y + PADDLE_HEIGHT > SCREEN_HEIGHT)
            rightPaddle.position.y = SCREEN_HEIGHT - PADDLE_HEIGHT;
        
        // ============================================================
        // BALL MOVEMENT
        // ============================================================
        
        ball.position.x += ball.velocity.x;
        ball.position.y += ball.velocity.y;
        
        // ============================================================
        // BALL COLLISION WITH TOP/BOTTOM WALLS
        // ============================================================
        
        if (ball.position.y - ball.radius <= 0 || 
            ball.position.y + ball.radius >= SCREEN_HEIGHT)
        {
            // Bounce off top or bottom wall
            ball.velocity.y = -ball.velocity.y;
            
            // Keep ball inside screen to prevent sticking
            if (ball.position.y - ball.radius < 0)
                ball.position.y = ball.radius;
            if (ball.position.y + ball.radius > SCREEN_HEIGHT)
                ball.position.y = SCREEN_HEIGHT - ball.radius;
        }
        
        // ============================================================
        // BALL COLLISION WITH PADDLES
        // ============================================================
        
        // Left paddle collision
        Rectangle leftPaddleRect = { leftPaddle.position.x, leftPaddle.position.y, 
                                     PADDLE_WIDTH, PADDLE_HEIGHT };
        
        if (CheckCollisionCircleRec(ball.position, ball.radius, leftPaddleRect))
        {
            // Ball hit left paddle
            if (ball.velocity.x < 0)  // Only bounce if ball is moving toward paddle
            {
                ball.velocity.x = -ball.velocity.x;  // Reverse horizontal direction
                
                // Add some angle based on where ball hits paddle
                // Hit near top = angle up, hit near bottom = angle down
                float hitPos = (ball.position.y - leftPaddle.position.y) / PADDLE_HEIGHT;
                float angle = (hitPos - 0.5f) * 60.0f * DEG2RAD;  // -30 to +30 degrees
                
                // Increase speed slightly
                float speed = sqrtf(ball.velocity.x * ball.velocity.x + 
                                   ball.velocity.y * ball.velocity.y);
                speed += BALL_SPEED_INCREASE;
                if (speed > BALL_SPEED_MAX) speed = BALL_SPEED_MAX;
                
                // Apply new angle and speed
                ball.velocity.x = cosf(angle) * speed;
                ball.velocity.y = sinf(angle) * speed;
                
                // Move ball out of paddle to prevent sticking
                ball.position.x = leftPaddle.position.x + PADDLE_WIDTH + ball.radius;
            }
        }
        
        // Right paddle collision
        Rectangle rightPaddleRect = { rightPaddle.position.x, rightPaddle.position.y, 
                                      PADDLE_WIDTH, PADDLE_HEIGHT };
        
        if (CheckCollisionCircleRec(ball.position, ball.radius, rightPaddleRect))
        {
            // Ball hit right paddle
            if (ball.velocity.x > 0)  // Only bounce if ball is moving toward paddle
            {
                ball.velocity.x = -ball.velocity.x;
                
                // Add angle based on hit position
                float hitPos = (ball.position.y - rightPaddle.position.y) / PADDLE_HEIGHT;
                float angle = (hitPos - 0.5f) * 60.0f * DEG2RAD;
                
                // Increase speed
                float speed = sqrtf(ball.velocity.x * ball.velocity.x + 
                                   ball.velocity.y * ball.velocity.y);
                speed += BALL_SPEED_INCREASE;
                if (speed > BALL_SPEED_MAX) speed = BALL_SPEED_MAX;
                
                // Apply new angle and speed
                ball.velocity.x = -cosf(angle) * speed;  // Negative for left direction
                ball.velocity.y = sinf(angle) * speed;
                
                // Move ball out of paddle
                ball.position.x = rightPaddle.position.x - ball.radius;
            }
        }
        
        // ============================================================
        // SCORING (Ball goes off screen)
        // ============================================================
        
        // Ball went off left side - Player 2 scores
        if (ball.position.x < 0)
        {
            player2Score++;
            
            // Check for winner
            if (player2Score >= WINNING_SCORE)
            {
                winner = 2;
                currentScreen = SCREEN_WINNER;
            }
            else
            {
                ResetBall(1);  // Send ball to the right
            }
        }
        
        // Ball went off right side - Player 1 scores
        if (ball.position.x > SCREEN_WIDTH)
        {
            player1Score++;
            
            // Check for winner
            if (player1Score >= WINNING_SCORE)
            {
                winner = 1;
                currentScreen = SCREEN_WINNER;
            }
            else
            {
                ResetBall(-1);  // Send ball to the left
            }
        }
    }
    else if (currentScreen == SCREEN_WINNER)
    {
        // Wait for SPACE to restart
        if (IsKeyPressed(KEY_SPACE))
        {
            currentScreen = SCREEN_GAME;
            InitGame();
        }
    }
}

//----------------------------------------------------------------------------------
// DrawGame() - Render everything
//----------------------------------------------------------------------------------
void DrawGame(void)
{
    BeginDrawing();
    
        ClearBackground(BLACK);
        
        if (currentScreen == SCREEN_MENU)
        {
            // ============================================================
            // MENU SCREEN
            // ============================================================
            
            DrawText("PONG", 320, 150, 80, WHITE);
            
            DrawText("CONTROLS:", 330, 280, 20, LIGHTGRAY);
            DrawText("Player 1 (Left): W / S", 260, 320, 18, WHITE);
            DrawText("Player 2 (Right): UP / DOWN", 240, 345, 18, WHITE);
            
            DrawText("First to 5 points wins!", 270, 400, 20, YELLOW);
            
            DrawText("Press SPACE to start", 270, 480, 22, GREEN);
        }
        else if (currentScreen == SCREEN_GAME)
        {
            // ============================================================
            // GAME SCREEN
            // ============================================================
            
            // Draw center line
            for (int i = 0; i < SCREEN_HEIGHT; i += 20)
            {
                DrawRectangle(SCREEN_WIDTH / 2 - 2, i, 4, 10, GRAY);
            }
            
            // Draw paddles
            DrawRectangleV(leftPaddle.position, (Vector2){ PADDLE_WIDTH, PADDLE_HEIGHT }, WHITE);
            DrawRectangleV(rightPaddle.position, (Vector2){ PADDLE_WIDTH, PADDLE_HEIGHT }, WHITE);
            
            // Draw ball
            DrawCircleV(ball.position, ball.radius, WHITE);
            
            // Draw ball trail (for effect)
            DrawCircle((int)(ball.position.x - ball.velocity.x * 0.5f), 
                      (int)(ball.position.y - ball.velocity.y * 0.5f), 
                      ball.radius * 0.7f, Fade(WHITE, 0.3f));
            
            // Draw scores
            DrawText(TextFormat("%d", player1Score), SCREEN_WIDTH / 4, 30, 60, GRAY);
            DrawText(TextFormat("%d", player2Score), SCREEN_WIDTH * 3 / 4, 30, 60, GRAY);
            
            // Draw player labels
            DrawText("PLAYER 1", 60, SCREEN_HEIGHT - 30, 12, DARKGRAY);
            DrawText("PLAYER 2", SCREEN_WIDTH - 140, SCREEN_HEIGHT - 30, 12, DARKGRAY);
        }
        else if (currentScreen == SCREEN_WINNER)
        {
            // ============================================================
            // WINNER SCREEN
            // ============================================================
            
            DrawText(TextFormat("PLAYER %d WINS!", winner), 220, 200, 50, GREEN);
            
            DrawText(TextFormat("Final Score: %d - %d", player1Score, player2Score), 
                    280, 280, 30, WHITE);
            
            DrawText("Press SPACE to play again", 240, 400, 22, LIGHTGRAY);
        }
    
    EndDrawing();
}

/*******************************************************************************************
*
*   WHAT YOU LEARNED IN THIS GAME:
*   
*   GAME PHYSICS:
*   1. Velocity-based movement (ball.position += ball.velocity)
*   2. Collision response (reversing velocity)
*   3. Angle-based deflection (hit position affects bounce angle)
*   4. Speed increase over time (difficulty progression)
*   5. Boundary constraints (keeping paddles on screen)
*   
*   COLLISION DETECTION:
*   1. Circle vs Rectangle (CheckCollisionCircleRec)
*   2. Point vs boundary (simple number comparison)
*   3. Preventing tunneling (moving object out of collision)
*   
*   GAME FLOW:
*   1. State machine (Menu -> Game -> Winner)
*   2. Score tracking
*   3. Win condition checking
*   4. Game reset between rounds
*   
*   PLAYER CONTROLS:
*   1. Two-player local multiplayer
*   2. Different key bindings for each player
*   3. Continuous input (IsKeyDown for movement)
*   
*   VISUAL EFFECTS:
*   1. Motion blur (ball trail)
*   2. Dashed center line
*   3. Color feedback
*   
*   RAYLIB FEATURES:
*   - Vector2 math
*   - Rectangle structures
*   - Collision functions
*   - Text formatting
*   - Transparency (Fade)
*   
*   IMPROVEMENTS YOU COULD ADD:
*   - Sound effects (ball hit, score)
*   - Particle effects on hit
*   - Power-ups (bigger paddle, faster ball)
*   - AI opponent for single-player
*   - Ball trails with multiple fading circles
*   - Screen shake on collisions
*   - Combo system (consecutive hits)
*   - Different difficulty levels
*   - Paddle acceleration
*   - Special moves (curve ball)
*   
*   PHYSICS CONCEPTS:
*   - Velocity = change in position per frame
*   - Collision = objects overlapping
*   - Reflection = velocity reversal
*   - Angle of incidence = angle of reflection (modified by hit position)
*   - Speed accumulation = getting faster over time
*   
*   Try modifying values like BALL_SPEED_START, PADDLE_SPEED, and WINNING_SCORE
*   to change how the game feels!
*
*******************************************************************************************/

