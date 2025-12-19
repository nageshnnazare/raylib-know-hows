/*******************************************************************************************
*
*   RAYLIB LESSON 02: Basic Shapes
*   
*   Learn to draw basic geometric shapes: rectangles, circles, lines, and more.
*   Shapes are the building blocks of 2D games!
*
*******************************************************************************************/

#include "raylib.h"

int main(void)
{
    // Screen dimensions
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes");
    
    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------
    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Clear with a dark blue background for contrast
            ClearBackground(DARKBLUE);

            // ============================================================
            // DRAWING TEXT
            // ============================================================
            
            // Let's label what we're drawing
            DrawText("Basic Shape Drawing", 250, 20, 20, WHITE);
            
            // ============================================================
            // DRAWING LINES
            // ============================================================
            
            // DrawLine() draws a straight line between two points
            // Parameters: startX, startY, endX, endY, color
            // Starting point: (50, 70), Ending point: (200, 70)
            DrawLine(50, 70, 200, 70, RED);
            
            // Let's draw a few more lines to make a simple pattern
            DrawLine(50, 80, 200, 80, ORANGE);
            DrawLine(50, 90, 200, 90, YELLOW);
            
            // Label it
            DrawText("Lines", 110, 95, 10, WHITE);
            
            // ============================================================
            // DRAWING RECTANGLES
            // ============================================================
            
            // DrawRectangle() draws a filled rectangle
            // Parameters: x, y, width, height, color
            // x, y is the TOP-LEFT corner of the rectangle
            DrawRectangle(50, 130, 100, 60, GREEN);
            
            // DrawRectangleLines() draws just the outline (not filled)
            // Same parameters as DrawRectangle()
            DrawRectangleLines(170, 130, 100, 60, LIME);
            
            // Labels
            DrawText("Filled", 70, 200, 10, WHITE);
            DrawText("Outline", 185, 200, 10, WHITE);
            
            // ============================================================
            // DRAWING CIRCLES
            // ============================================================
            
            // DrawCircle() draws a filled circle
            // Parameters: centerX, centerY, radius, color
            // Center at (350, 160), radius of 40 pixels
            DrawCircle(350, 160, 40, BLUE);
            
            // DrawCircleLines() draws just the outline of a circle
            DrawCircleLines(450, 160, 40, SKYBLUE);
            
            // Labels
            DrawText("Filled", 325, 210, 10, WHITE);
            DrawText("Outline", 425, 210, 10, WHITE);
            
            // ============================================================
            // DRAWING TRIANGLES
            // ============================================================
            
            // DrawTriangle() draws a filled triangle
            // Parameters: point1, point2, point3, color
            // Each point is defined by its x and y coordinates
            // Vector2 is a raylib type that holds an x and y value
            
            // Define the three corners of our triangle
            Vector2 point1 = { 550, 130 };  // Top point
            Vector2 point2 = { 520, 190 };  // Bottom-left point
            Vector2 point3 = { 580, 190 };  // Bottom-right point
            
            DrawTriangle(point1, point2, point3, PURPLE);
            
            // Draw an outlined triangle next to it
            Vector2 point4 = { 650, 130 };
            Vector2 point5 = { 620, 190 };
            Vector2 point6 = { 680, 190 };
            
            DrawTriangleLines(point4, point5, point6, VIOLET);
            
            // Labels
            DrawText("Filled", 525, 200, 10, WHITE);
            DrawText("Outline", 625, 200, 10, WHITE);
            
            // ============================================================
            // DRAWING POLYGONS
            // ============================================================
            
            // DrawPoly() draws a regular polygon (all sides equal)
            // Parameters: center, sides, radius, rotation, color
            
            // Draw a hexagon (6 sides)
            Vector2 hexCenter = { 100, 320 };
            DrawPoly(hexCenter, 6, 40, 0, MAROON);
            DrawText("Hexagon (6 sides)", 50, 370, 10, WHITE);
            
            // Draw a pentagon (5 sides), rotated 30 degrees
            Vector2 pentCenter = { 250, 320 };
            DrawPoly(pentCenter, 5, 40, 30, GOLD);
            DrawText("Pentagon (5 sides)", 195, 370, 10, WHITE);
            
            // ============================================================
            // DRAWING ELLIPSES
            // ============================================================
            
            // DrawEllipse() draws a filled ellipse (stretched circle)
            // Parameters: centerX, centerY, radiusH, radiusV, color
            // radiusH = horizontal radius, radiusV = vertical radius
            DrawEllipse(420, 320, 50, 30, PINK);
            DrawText("Ellipse", 395, 360, 10, WHITE);
            
            // ============================================================
            // DRAWING RINGS (Partial circles/arcs)
            // ============================================================
            
            // DrawRing() draws a ring (donut shape) or arc
            // Parameters: center, innerRadius, outerRadius, startAngle, endAngle, segments, color
            Vector2 ringCenter = { 600, 320 };
            
            // Full ring (0 to 360 degrees)
            DrawRing(ringCenter, 25, 40, 0, 360, 36, ORANGE);
            DrawText("Ring", 580, 370, 10, WHITE);
            
            // Partial ring (arc) - only 0 to 180 degrees
            Vector2 arcCenter = { 700, 320 };
            DrawRing(arcCenter, 25, 40, 0, 180, 36, SKYBLUE);
            DrawText("Arc", 685, 370, 10, WHITE);
            
            // ============================================================
            // DRAWING ROUNDED RECTANGLES
            // ============================================================
            
            // DrawRectangleRounded() draws a rectangle with rounded corners
            // First parameter is a Rectangle structure: {x, y, width, height}
            // Second parameter is roundness: 0.0 (sharp) to 1.0 (fully rounded)
            // Third parameter is segments (more = smoother curves)
            // Fourth parameter is color
            Rectangle roundedRect = { 50, 400, 120, 40 };
            DrawRectangleRounded(roundedRect, 0.5, 16, DARKGREEN);
            DrawText("Rounded Rectangle", 200, 410, 10, WHITE);

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
*   SHAPES YOU CAN DRAW:
*   1. Lines - DrawLine()
*   2. Rectangles - DrawRectangle(), DrawRectangleLines()
*   3. Circles - DrawCircle(), DrawCircleLines()
*   4. Triangles - DrawTriangle(), DrawTriangleLines()
*   5. Polygons - DrawPoly() (any regular polygon)
*   6. Ellipses - DrawEllipse()
*   7. Rings/Arcs - DrawRing()
*   8. Rounded Rectangles - DrawRectangleRounded()
*   
*   FILLED vs OUTLINED:
*   - Regular functions (DrawCircle) draw filled shapes
*   - Functions ending in "Lines" (DrawCircleLines) draw outlines only
*   
*   COORDINATE SYSTEM:
*   - (0, 0) is the TOP-LEFT corner of the screen
*   - X increases as you go RIGHT
*   - Y increases as you go DOWN
*   - This is different from math class where Y goes up!
*   
*   VECTOR2:
*   - A structure that holds x and y coordinates
*   - Used for points, positions, and directions
*   - Example: Vector2 pos = { 100, 200 };
*   
*   RECTANGLE:
*   - A structure that holds x, y, width, height
*   - Example: Rectangle rect = { 50, 50, 100, 100 };
*
*******************************************************************************************/

