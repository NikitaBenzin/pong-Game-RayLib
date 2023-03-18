#include "raylib.h"

int main() 
{
	// init the window 
	InitWindow(800, 600, "Pong");
	// set window updating to the max of monitor
	SetWindowState(FLAG_VSYNC_HINT);

	// main while loop. game loop
	while (!WindowShouldClose()) 
	{
		// start the render of window
		BeginDrawing();
		// color the window 
		ClearBackground(BLACK);



		// show the fps on the window
		DrawFPS(0, 0);

		// stop drawing proces
		EndDrawing();
	}



	// close the window. end the program 
	CloseWindow();
	return 0;
}