#include <iostream>
#include <raylib.h>

const int ScreenWidht = 1600;
const int ScreenHeight = 900;

const int BirdHight = 70;
const int BrdWidth = 70;



int main()
{
	InitWindow(ScreenWidht, ScreenHeight, "20 Games Chalenge Flappy Bird");
	SetTargetFPS(60);


	while (!WindowShouldClose())
	{
		BeginDrawing();

		DrawRectangle(ScreenWidht / 2.f - 500, ScreenHeight / 2.f, BrdWidth, BirdHight, RED);

		ClearBackground(RAYWHITE);

		EndDrawing();
	}

	CloseWindow();

}