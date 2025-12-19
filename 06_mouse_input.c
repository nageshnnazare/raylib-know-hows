/*******************************************************************************************
*
*   RAYLIB LESSON 06: Mouse Input
*   
*   Learn how to use the mouse! This covers mouse position, buttons, and the mouse wheel.
*   Essential for point-and-click games, drawing apps, and UI interaction.
*
*******************************************************************************************/

#include "raylib.h"
#include <math.h>  // For distance calculations

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - mouse input");
    
    SetTargetFPS(60);

    // ============================================================
    // VARIABLES
    // ============================================================
    
    // Box that follows the mouse
    Vector2 boxPosition = { 400, 225 };
    float boxSize = 30;
    
    // Click tracking
    Vector2 lastClickPosition = { 0, 0 };
    bool wasClicked = false;
    
    // Drawing system
    #define MAX_POINTS 1000
    Vector2 drawPoints[MAX_POINTS];
    int pointCount = 0;
    
    // Draggable rectangle
    Rectangle dragRect = { 100, 100, 80, 80 };
    bool isDragging = false;
    Vector2 dragOffset = { 0, 0 };
    
    // Circle that grows with mouse wheel
    float circleRadius = 30.0f;
    Vector2 circlePosition = { 650, 350 };

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // ============================================================
        // MOUSE POSITION
        // ============================================================
        
        // GetMousePosition() returns a Vector2 with X and Y coordinates
        // This tells you where the mouse cursor is on the screen
        // (0, 0) is top-left corner
        Vector2 mousePosition = GetMousePosition();
        
        // Alternative: Get X and Y separately
        int mouseX = GetMouseX();  // X coordinate only
        int mouseY = GetMouseY();  // Y coordinate only
        
        // Make the box follow the mouse
        boxPosition = mousePosition;
        
        // ============================================================
        // MOUSE BUTTONS - LEFT CLICK
        // ============================================================
        
        // IsMouseButtonPressed() - Triggers ONCE when button is clicked
        // Use for single-click actions
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Record where the click happened
            lastClickPosition = mousePosition;
            wasClicked = true;
        }
        
        // IsMouseButtonDown() - True WHILE button is held down
        // Use for continuous actions (like drawing)
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            // Add points while mouse is held (for drawing)
            if (pointCount < MAX_POINTS)
            {
                drawPoints[pointCount] = mousePosition;
                pointCount++;
            }
        }
        
        // IsMouseButtonReleased() - Triggers when button is let go
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            // Button was released
        }
        
        // IsMouseButtonUp() - True when button is NOT pressed
        // (opposite of IsMouseButtonDown)
        
        // ============================================================
        // MOUSE BUTTONS - RIGHT CLICK
        // ============================================================
        
        // Right click to clear drawing
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            pointCount = 0;  // Clear all drawn points
            wasClicked = false;
        }
        
        // ============================================================
        // DRAG AND DROP
        // ============================================================
        
        // Check if mouse is over the draggable rectangle
        // CheckCollisionPointRec() checks if a point is inside a rectangle
        bool mouseOverRect = CheckCollisionPointRec(mousePosition, dragRect);
        
        // Start dragging if we click on the rectangle
        if (mouseOverRect && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            isDragging = true;
            // Calculate offset from rectangle's top-left corner to mouse
            // This makes dragging feel natural (mouse stays where you grabbed)
            dragOffset.x = mousePosition.x - dragRect.x;
            dragOffset.y = mousePosition.y - dragRect.y;
        }
        
        // While dragging, move the rectangle with the mouse
        if (isDragging)
        {
            dragRect.x = mousePosition.x - dragOffset.x;
            dragRect.y = mousePosition.y - dragOffset.y;
            
            // Stop dragging when mouse button is released
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                isDragging = false;
            }
        }
        
        // ============================================================
        // MOUSE WHEEL
        // ============================================================
        
        // GetMouseWheelMove() returns wheel movement
        // Positive value = scroll up
        // Negative value = scroll down
        // Zero = no scroll
        float wheelMove = GetMouseWheelMove();
        
        if (wheelMove != 0)
        {
            // Change circle size with mouse wheel
            circleRadius += wheelMove * 5.0f;  // Multiply for faster change
            
            // Keep radius within reasonable bounds
            if (circleRadius < 10.0f) circleRadius = 10.0f;
            if (circleRadius > 100.0f) circleRadius = 100.0f;
        }
        
        // ============================================================
        // MOUSE DELTA (Movement)
        // ============================================================
        
        // GetMouseDelta() returns how much the mouse moved since last frame
        // Useful for camera controls, looking around in 3D, etc.
        Vector2 mouseDelta = GetMouseDelta();
        // mouseDelta.x = horizontal movement
        // mouseDelta.y = vertical movement
        
        // ============================================================
        // DISTANCE CALCULATION
        // ============================================================
        
        // Calculate distance from mouse to circle (just for demonstration)
        float dx = mousePosition.x - circlePosition.x;
        float dy = mousePosition.y - circlePosition.y;
        float distance = sqrtf(dx * dx + dy * dy);
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(DARKGRAY);
            
            // Title
            DrawText("MOUSE INPUT", 280, 10, 30, WHITE);
            
            // Instructions
            DrawText("Move mouse to move the blue box", 20, 50, 12, LIGHTGRAY);
            DrawText("LEFT CLICK & DRAG to draw", 20, 65, 12, LIGHTGRAY);
            DrawText("RIGHT CLICK to clear drawing", 20, 80, 12, LIGHTGRAY);
            DrawText("Drag the green square", 20, 95, 12, LIGHTGRAY);
            DrawText("SCROLL WHEEL to resize orange circle", 20, 110, 12, LIGHTGRAY);
            
            // ============================================================
            // DRAW MOUSE FOLLOWER BOX
            // ============================================================
            
            DrawRectangle((int)(boxPosition.x - boxSize/2), 
                         (int)(boxPosition.y - boxSize/2), 
                         (int)boxSize, (int)boxSize, BLUE);
            
            // ============================================================
            // DRAW LAST CLICK POSITION
            // ============================================================
            
            if (wasClicked)
            {
                // Draw an X where the user last clicked
                DrawLine((int)lastClickPosition.x - 10, (int)lastClickPosition.y - 10,
                        (int)lastClickPosition.x + 10, (int)lastClickPosition.y + 10, RED);
                DrawLine((int)lastClickPosition.x + 10, (int)lastClickPosition.y - 10,
                        (int)lastClickPosition.x - 10, (int)lastClickPosition.y + 10, RED);
            }
            
            // ============================================================
            // DRAW THE DRAWING (Paint-style)
            // ============================================================
            
            // Draw all the points the user has drawn
            for (int i = 0; i < pointCount - 1; i++)
            {
                // Connect consecutive points with lines to create a drawing
                DrawLineEx(drawPoints[i], drawPoints[i + 1], 3.0f, YELLOW);
            }
            
            // ============================================================
            // DRAW DRAGGABLE RECTANGLE
            // ============================================================
            
            // Change color if mouse is over it or if it's being dragged
            Color rectColor = GREEN;
            if (isDragging)
            {
                rectColor = LIME;  // Brighter green while dragging
            }
            else if (CheckCollisionPointRec(GetMousePosition(), dragRect))
            {
                rectColor = DARKGREEN;  // Darker green when hovering
            }
            
            DrawRectangleRec(dragRect, rectColor);
            DrawText("DRAG", (int)dragRect.x + 15, (int)dragRect.y + 30, 15, WHITE);
            
            // ============================================================
            // DRAW WHEEL-CONTROLLED CIRCLE
            // ============================================================
            
            DrawCircleV(circlePosition, circleRadius, ORANGE);
            DrawText("SCROLL", (int)circlePosition.x - 30, (int)circlePosition.y - 5, 12, WHITE);
            
            // ============================================================
            // DISPLAY INFORMATION
            // ============================================================
            
            // Show current mouse position
            DrawText(TextFormat("Mouse: (%d, %d)", mouseX, mouseY), 20, 410, 15, WHITE);
            
            // Show mouse button states
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                DrawText("LEFT DOWN", 200, 410, 15, RED);
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
                DrawText("RIGHT DOWN", 320, 410, 15, RED);
            if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
                DrawText("MIDDLE DOWN", 450, 410, 15, RED);
            
            // Show wheel movement
            if (wheelMove != 0)
            {
                DrawText(TextFormat("Wheel: %.1f", wheelMove), 600, 410, 15, YELLOW);
            }
            
            // Show circle size
            DrawText(TextFormat("Circle Radius: %.0f", circleRadius), 580, 390, 12, LIGHTGRAY);
            
            // Show distance to circle
            DrawText(TextFormat("Distance to circle: %.0f", distance), 580, 370, 12, LIGHTGRAY);

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
*   MOUSE POSITION:
*   - GetMousePosition() - Returns Vector2 with x and y
*   - GetMouseX() - Returns only X coordinate
*   - GetMouseY() - Returns only Y coordinate
*   - Position (0,0) is top-left corner of window
*   
*   MOUSE BUTTONS:
*   Three main mouse buttons:
*   - MOUSE_BUTTON_LEFT (left click)
*   - MOUSE_BUTTON_RIGHT (right click)
*   - MOUSE_BUTTON_MIDDLE (middle/wheel click)
*   
*   BUTTON STATE FUNCTIONS:
*   
*   1. IsMouseButtonPressed(button)
*      - Triggers ONCE on initial click
*      - Use for: single-click actions, UI buttons
*   
*   2. IsMouseButtonDown(button)
*      - True WHILE button is held
*      - Use for: continuous actions, drawing, dragging
*   
*   3. IsMouseButtonReleased(button)
*      - Triggers when button is let go
*      - Use for: drag-and-drop (detect drop)
*   
*   4. IsMouseButtonUp(button)
*      - True when button is NOT pressed
*      - Opposite of IsMouseButtonDown()
*   
*   MOUSE WHEEL:
*   - GetMouseWheelMove()
*   - Returns positive value for scroll up
*   - Returns negative value for scroll down
*   - Returns 0 if no scrolling
*   - Use for: zooming, changing values, scrolling lists
*   
*   MOUSE DELTA:
*   - GetMouseDelta()
*   - Returns Vector2 of mouse movement since last frame
*   - Use for: camera control, first-person looking
*   
*   COLLISION DETECTION WITH MOUSE:
*   - CheckCollisionPointRec(point, rectangle)
*   - Checks if mouse is over a rectangle
*   - Essential for UI buttons, clickable objects
*   
*   DRAG AND DROP PATTERN:
*   
*   1. Check if mouse is over object
*   2. If clicked, start dragging
*   3. Calculate offset (where on object you grabbed)
*   4. While dragging, move object with mouse
*   5. Stop dragging when button released
*   
*   Code pattern:
*   if (mouseOver && IsMouseButtonPressed(LEFT)) {
*       startDrag = true;
*       offset = mouse - objectPosition;
*   }
*   if (startDrag) {
*       objectPosition = mouse - offset;
*   }
*   if (IsMouseButtonReleased(LEFT)) {
*       startDrag = false;
*   }
*   
*   DRAWING APPLICATION PATTERN:
*   
*   1. Store array of points
*   2. While mouse button down, add current position to array
*   3. Draw lines between consecutive points
*   4. This creates a paint/drawing effect
*   
*   DISTANCE CALCULATION:
*   To find distance between two points:
*   
*   dx = x2 - x1
*   dy = y2 - y1
*   distance = sqrt(dx*dx + dy*dy)
*   
*   Useful for: detecting clicks on circles, proximity checks
*   
*   VECTOR2 STRUCTURE:
*   Vector2 is a structure with .x and .y fields:
*   
*   Vector2 pos = { 100, 200 };
*   float x = pos.x;  // 100
*   float y = pos.y;  // 200
*   
*   RECTANGLE STRUCTURE:
*   Rectangle has .x, .y, .width, .height:
*   
*   Rectangle rect = { 50, 50, 100, 80 };
*   float x = rect.x;      // 50 (left edge)
*   float y = rect.y;      // 50 (top edge)
*   float w = rect.width;  // 100
*   float h = rect.height; // 80
*   
*   TIPS:
*   - Use IsMouseButtonPressed() for UI clicks
*   - Use IsMouseButtonDown() for drawing/dragging
*   - Always check collision before acting on clicks
*   - Store offset when dragging for natural feel
*   - Mouse wheel is great for zooming and adjusting values
*   - Combine keyboard and mouse for better controls
*
*******************************************************************************************/

