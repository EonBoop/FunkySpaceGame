#include <raylib.h>
#include "spacestuff.h"

int main(){

InitWindow(0, 0, "Rotating Image around Center");
    SetTargetFPS(60);  

  Vector2 polyPoints[] = {
        {200, 100},
        {400, 100},
        {3000, 3000}
    };

   while (!WindowShouldClose()) {

    BeginDrawing();
   ClearBackground(RAYWHITE);

        // Draw the polygon
        DrawTriangle(polyPoints[0],polyPoints[1],polyPoints[2],RED);
        // Check if the mouse pointer is inside the polygon
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointPoly(mousePoint, polyPoints, 3)) {
            DrawText("Mouse inside the polygon!", 100, 100, 200, GREEN);
        } else {
            DrawText("Mouse outside the polygon.", 100, 100, 200, BLUE);
        }
    EndDrawing();

  }

}
