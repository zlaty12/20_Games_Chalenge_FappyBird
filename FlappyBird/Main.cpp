#include <iostream>
#include <raylib.h>

const int ScreenWidht = 1600;
const int ScreenHeight = 900;

const int BirdHight = 70;
const int BrdWidth = 70;
bool collision = false;

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
	
	Rectangle Pipe1;
	Rectangle Pipe2;

	Pipe(Vector2 PositionTop, Vector2 PositionBottom) :
		PiplePositionTop(PositionTop),
		PipePositionBottom(PositionBottom)
	{
		
	}

	void DrawPipe()
	{

		Pipe1 = { PiplePositionTop.x, PiplePositionTop.y,PipeWidth, PipeHeight };
		Pipe2 = { PipePositionBottom.x, PipePositionBottom.y, PipeWidth, PipeHeight };

		DrawRectangleRec(Pipe1, GREEN);
		DrawRectangleRec(Pipe2, GREEN);
		
	}

	void MovePipes(float PipeSpeed)
	{
		PiplePositionTop.x -= PipeSpeed * GetFrameTime();
		PipePositionBottom.x -= PipeSpeed * GetFrameTime();

	}

	void GameOver()
	{

		//CheckCollisionRecs()
		//if(false)
		//SetTargetFPS(0);
	}
};


class Bird
{
	
public:

	Rectangle BirdRec;
	

public:
	bool bCanJump;
	Vector2 Position;

	Bird(Vector2 Position)
		: Position(Position)
	{
		
	}


	void DrawBird()
	{
		BirdRec = { Position.x, Position.y, BrdWidth, BirdHight };

		DrawRectangleRec(BirdRec, RED);
	}


	
};


int main()
{
	InitWindow(ScreenWidht, ScreenHeight, "20 Games Chalenge Flappy Bird");
	SetTargetFPS(60);

	Bird PlayerBird = Bird(BirdStartPosition);

	Pipe Pipes = Pipe(PipeStartPosition,PipeStartPositionTop);

	
	while (!WindowShouldClose())
	{

		

		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		PlayerBird.DrawBird();

		Pipes.DrawPipe();

		Pipes.MovePipes(PipeSpeed);

		if (CheckCollisionRecs(Pipes.Pipe1, PlayerBird.BirdRec) || CheckCollisionRecs(Pipes.Pipe2, PlayerBird.BirdRec))
		{

			std::cout << "Close Window" << std::endl;

			CloseWindow();
			

			
		}

		if (IsKeyPressed(KEY_SPACE)) PlayerBird.Position.y += -50.f;

		PlayerBird.Position.y += FallingSpeed * GetFrameTime();

		

		EndDrawing();
	}

	CloseWindow();

}