#include <iostream>
#include <raylib.h>
#include <vector>

const int ScreenWidht = 1600;
const int ScreenHeight = 900;

const int BirdHight = 70;
const int BrdWidth = 70;
bool Loaded = false;


float timer;
const float SpawnTime = 5.f;
int HightScorePoints = 0;
int Points = 0;
const int PipeWidth = 100;
const int PipeHeight = 500;

float PipeSpeed = 100.f;

Vector2 PipeStartPosition = Vector2(ScreenWidht - 100.f, ScreenHeight - 200.f);
Vector2 PipeStartPositionTop = Vector2(ScreenWidht - 100.f, 0.f);

const float FallingSpeed = 50.f;

Vector2 BirdStartPosition = Vector2(ScreenWidht / 2.f - 500.f, ScreenHeight / 2.f);



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




void SaveHighScore(int score)
{
	SaveFileText("highscore.txt", TextFormat("%d", score));
}

int HighScore()
{
	if (FileExists("highscore.txt") && Loaded == false)
	{
		Loaded = true;
		int Score;

		sscanf_s(LoadFileText("highscore.txt"), "%d", &Score);
		return Score;
	}
	return 0;
}





Bird PlayerBird = Bird(BirdStartPosition);

class Pipe
{
private:
	Vector2 PipePositionTop;
	Vector2 PipePositionBottom;
	
	
	
public:
	bool Collision = true;

	Rectangle Pipe1;
	Rectangle Pipe2;
	Rectangle PipesMiddle;

	Pipe(Vector2 PositionTop, Vector2 PositionBottom) :
		PipePositionTop(PositionTop),
		PipePositionBottom(PositionBottom)
	{
		
	}

	~Pipe()
	{
		std::cout << "Pipe Deleted" << std::endl;
	}

	void DrawPipe()
	{

		Pipe1 = { PipePositionTop.x, PipePositionTop.y,PipeWidth, PipeHeight };
		Pipe2 = { PipePositionBottom.x, PipePositionBottom.y, PipeWidth, PipeHeight };
		PipesMiddle = { PipePositionBottom.x , PipePositionTop.y - 200.f, PipeWidth, PipeHeight - 300.f };

		DrawRectangleRec(Pipe1, GREEN);
		DrawRectangleRec(Pipe2, GREEN);
		DrawRectangleRec(PipesMiddle, YELLOW);
		
	}

	void MovePipes(float PipeSpeed)
	{
		PipePositionTop.x -= PipeSpeed * GetFrameTime();
		PipePositionBottom.x -= PipeSpeed * GetFrameTime();

	}



	void CheckCollision()
	{
		if ((CheckCollisionRecs(Pipe1, PlayerBird.BirdRec) || CheckCollisionRecs(Pipe2, PlayerBird.BirdRec)) && (Collision) == true)
		{

			std::cout << "Close Window" << std::endl;

			Collision = false;
			EndDrawing();
			CloseWindow();

		}

		if (CheckCollisionRecs(PipesMiddle, PlayerBird.BirdRec) && (Collision) == true)
		{
			Points += 1;
			Collision = false;


			if (Points > HightScorePoints)
			{
				HightScorePoints = Points;
				SaveHighScore(HightScorePoints);
			}


		}
		else if (!CheckCollisionRecs(PipesMiddle, PlayerBird.BirdRec) && (Collision) == false)
		{
			Collision = true;
		}
	}

};

std::vector<Pipe> PipeArray;

void SpawnPipes()
{
	timer += GetFrameTime();

	std::cout << timer << std::endl;


	if (SpawnTime <= timer)
	{
		timer = 0.f;
		std::cout << "Spawning" << std::endl;

		PipeArray.push_back(Pipe(PipeStartPosition, PipeStartPositionTop));

	}


	for (int i = 0; i < PipeArray.size(); i++)
	{
		PipeArray[i].DrawPipe();
		PipeArray[i].MovePipes(PipeSpeed);




	}


}

int main()
{
	InitWindow(ScreenWidht, ScreenHeight, "20 Games Chalenge Flappy Bird");
	SetTargetFPS(60);


	HightScorePoints = HighScore();


	while (!WindowShouldClose())
	{
		BeginDrawing();

		SpawnPipes();

		ClearBackground(RAYWHITE);

		PlayerBird.DrawBird();

		
		if (IsKeyPressed(KEY_SPACE)) 
			PlayerBird.Position.y += -50.f;

		PlayerBird.Position.y += FallingSpeed * GetFrameTime();


		if (IsKeyPressed(KEY_P))
		{
			HightScorePoints = 0;
			SaveHighScore(HightScorePoints);
		}


		DrawText(TextFormat("High Score: %d", HightScorePoints), 500, 20, 40, RED);
		DrawText(TextFormat("Score: %d", Points), 500, 100, 40, BLUE);
		DrawText(TextFormat("Press P to reset high score"), 800, 20, 40, BLACK);

		EndDrawing();
	}

	CloseWindow();

}