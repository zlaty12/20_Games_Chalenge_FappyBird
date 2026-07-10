#include <iostream>
#include <raylib.h>

const int ScreenWidht = 1600;
const int ScreenHeight = 900;

const int BirdHight = 70;
const int BrdWidth = 70;


const int PipeWidth = 100;
const int PipeHeight = 500;

float PipeSpeed = 100.f;

Vector2 PipeStartPosition = Vector2(ScreenWidht - 100.f, ScreenHeight - 200.f);
Vector2 PipeStartPositionTop = Vector2(ScreenWidht - 100.f, 0.f);

const float FallingSpeed = 50.f;

Vector2 BirdStartPosition = Vector2(ScreenWidht / 2.f - 500.f, ScreenHeight / 2.f);

class Pipe
{
private:
	Vector2 PiplePositionTop;
	Vector2 PipePositionBottom;

	
public:
	

	Pipe(Vector2 PositionTop, Vector2 PositionBottom) :
		PiplePositionTop(PositionTop),
		PipePositionBottom(PositionBottom)
	{

	}

	void DrawPipe()
	{
		DrawRectangle(PiplePositionTop.x, PiplePositionTop.y, PipeWidth, PipeHeight, GREEN);
		DrawRectangle(PipePositionBottom.x, PipePositionBottom.y, PipeWidth, PipeHeight, GREEN);
	}

	void MovePipes(float PipeSpeed)
	{
		PiplePositionTop.x -= PipeSpeed * GetFrameTime();
		PipePositionBottom.x -= PipeSpeed * GetFrameTime();

	}
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

	Pipe FirstPipe = Pipe(PipeStartPosition,PipeStartPositionTop);

	
	while (!WindowShouldClose())
	{

		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		PlayerBird.DrawBird();

		FirstPipe.DrawPipe();

		FirstPipe.MovePipes(PipeSpeed);

		if (IsKeyPressed(KEY_SPACE)) PlayerBird.Position.y += -50.f;

		PlayerBird.Position.y += FallingSpeed * GetFrameTime();

		

		EndDrawing();
	}

	CloseWindow();

}