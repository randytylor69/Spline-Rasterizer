#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

/*    build command (yes i'm a lazy chud):
 *    clear && gcc -Wall -o spline main.c -lm -lraylib && ./spline   */

typedef struct{
    Vector2 *items; // array pointer
    size_t count;   // how many items
    size_t capacity; // total items 
} ControlPoints;

void da_append(ControlPoints *da, Vector2 item){
    if (da->count >= da->capacity){
	da->capacity = (da->capacity == 0) ? 256 : da->capacity * 2;
	da->items = realloc(da->items, da->capacity * sizeof(*da->items));
    } da->items[da->count++] = item;
}

Vector2 Lerp(Vector2 v1, Vector2 v2, float amount){
    return (Vector2) { v1.x + (v2.x - v1.x) * amount, v1.y + (v2.y - v1.y) * amount };
}

static ControlPoints points = {0};

int main(){
    InitWindow(900, 600, "Spline Rasterizer");
    while (!WindowShouldClose()){
	BeginDrawing();
	ClearBackground(DARKBROWN);
	
	/* detect mouse press */
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
	    Vector2 new_control_point = GetMousePosition();
	    da_append(&points, new_control_point);
	}

	/* draw all control points */
	for (size_t i=0; i<points.count; i++){
	    Vector2 size = {30, 30};
	    DrawRectangleV(points.items[i], size , WHITE);
	}
	
	/* draw quadratic Bezier Curve */
	for (size_t i=0; i+2<=points.count; i+=2){
	    Vector2 p1 = points.items[i];
	    Vector2 p2 = points.items[i+1];
	    Vector2 p3 = points.items[(i+2)%points.count];

	    for (float t = 0.0 ; t <= 1; t += 0.05){

		// below looks messy because I'm expanding the nested Lerp() functions
		// into one line, making it way faster to calculate the intersection point
		float B_x = (p3.x-2*p2.x+p1.x)*t*t + 2*t*(p2.x-p1.x)+p1.x;
		float B_y = (p3.y-2*p2.y+p1.y)*t*t + 2*t*(p2.y-p1.y)+p1.y;
		
		Vector2 bezier_point_position = {B_x, B_y};
		Vector2 size = {10,10};
		DrawRectangleV(bezier_point_position, size, YELLOW);
	    }
	}
	EndDrawing();
    }
    CloseWindow();
    return 0;
}
