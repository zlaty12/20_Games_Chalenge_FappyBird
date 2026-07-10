#include <iostream>
#include <raylib.h>

const int ScreenWidht = 1600;
const int ScreenHeight = 900;

const int BirdHight = 70;
const int BrdWidth = 70;

const float FallingSpeed = 50.f;

Vector2 BirdStartPosition = Vector2(ScreenWidht / 2.f - 500.f, ScreenHeight / 2.f);

class Pipe
{

public:
	Vector2 PiplePositionTop;
	Vector2 PipePositionBottom;

	// add two pipe draws
	//DrawRectangle(Position.x, Position.y, BrdWidth, BirdHight, RED);
	//DrawRectangle(Position.x, Position.y, BrdWidth, BirdHight, RED);
};


class Bird
{
	
	
	

public:
	bool bCanJump;
	Vector2 Position;

	Bird(Vector2 Position)
		: Position(Position)
	{
		
	}


	void DrawBird()
	{
		DrawRectangle(Position.x, Position.y, BrdWidth, BirdHight, RED);
	}
};


int main()
{
	InitWindow(ScreenWidht, ScreenHeight, "20 Games Chalenge Flappy Bird");
	SetTargetFPS(60);

	Bird PlayerBird = Bird(BirdStartPosition);


	
	while (!WindowShouldClose())
	{

		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		PlayerBird.DrawBird();

		if (IsKeyPressed(KEY_SPACE)) PlayerBird.Position.y += -50.f;

		PlayerBird.Position.y += FallingSpeed * GetFrameTime();

		

		EndDrawing();
	}

	CloseWindow();

}