#include <iostream>
#include <raylib.h>

const int ScreenWidth = 1600;
const int ScreenHeigth = 900;




int main()
{
	InitWindow(ScreenWidth, ScreenHeigth, "20 Games Chalenge Flappy Bird");
	SetTargetFPS(60);


	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		EndDrawing();
	}

	CloseWindow();

}