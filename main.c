#include <stdio.h>
#include "raylib.h"

/* build command (yes i'm a lazy chud):
 * clear && gcc -Wall -o spline main.c -lm -lraylib && ./spline
 */

#define WIN_WIDTH 900
#define WIN_HEIGHT 600

int main(){
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Spline Rasterizer");
    while (!WindowShouldClose()){
	BeginDrawing();
	ClearBackground(RED);
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
