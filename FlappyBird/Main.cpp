#include <iostream>
#include <raylib.h>
#include <vector>
#include <algorithm>
#include <filesystem>


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
const int PipeHeight = 1000;

float PipeSpeed = 100.f;




//Sprites
//Background
Texture2D Background;
float BackgroundOffset = 0.f;
const float BackgroundSpeed = 50.f;



Vector2 PipeStartPosition = Vector2(ScreenWidht - 100.f, ScreenHeight - 200);
Vector2 PipeStartPositionTop = Vector2(ScreenWidht - 100.f, ScreenHeight - 900);

const float FallingSpeed = 50.f;

Vector2 BirdStartPosition = Vector2(ScreenWidht / 2.f - 500.f, ScreenHeight / 2.f);


// bird class
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
// pipe class
class Pipe
{
private:
	Vector2 PipePositionTop;
	Vector2 PipePositionBottom;
	float RandomOfsetPipes;
	int margin = 80;
	
	
public:
	bool Collision = true;

	Rectangle Pipe1;
	Rectangle Pipe2;
	Rectangle PipesMiddle;

	Pipe(Vector2 PositionTop, Vector2 PositionBottom) :
		PipePositionTop(PositionTop),
		PipePositionBottom(PositionBottom)
	{
	
		int OfsetY = GetRandomValue(-450,180);
		
		RandomOfsetPipes = std::clamp(OfsetY,-450,180);
	}

	~Pipe()
	{
		
	}

	// Draws pipes
	void DrawPipe()
	{

		Pipe1 = { PipePositionTop.x, (PipePositionTop.y ) + RandomOfsetPipes,PipeWidth, PipeHeight };
		Pipe2 = { PipePositionBottom.x, (PipePositionBottom.y - 500) + RandomOfsetPipes, PipeWidth, PipeHeight };
		PipesMiddle = { PipePositionBottom.x , PipePositionTop.y  - 200.f + RandomOfsetPipes, PipeWidth, PipeHeight - 800.f };

		DrawRectangleRec(Pipe1, GREEN);
		DrawRectangleRec(Pipe2, GREEN);
		DrawRectangleRec(PipesMiddle, YELLOW);
		
	}

	void MovePipes(float PipeSpeed)
	{
		PipePositionTop.x -= PipeSpeed * GetFrameTime();
		PipePositionBottom.x -= PipeSpeed * GetFrameTime();

	}

	bool PipeOutOffScreen()
	{
		if (PipePositionTop.x < -100.f)
		{
			std::cout << "Del Pipe" << std::endl;

			return true;
		}
		else
		{
			return false;
		}
		
		
	}

	void CheckCollision()
	{
		if ((CheckCollisionRecs(Pipe1, PlayerBird.BirdRec) || CheckCollisionRecs(Pipe2, PlayerBird.BirdRec)) && (Collision) == true)
		{

			std::cout << "Close Window" << std::endl;

			Collision = false;

			
			UnloadTexture(Background);
			EndDrawing();
			CloseWindow();
			exit(0);

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

	


	if (SpawnTime <= timer)
	{
		timer = 0.f;
		


		PipeArray.push_back(Pipe(PipeStartPosition, PipeStartPositionTop));

	}


	for (int i = 0; i < PipeArray.size(); i++)
	{
		if (PipeArray[i].PipeOutOffScreen())
		{
			PipeArray.erase(PipeArray.begin() + i);
		}

		PipeArray[i].DrawPipe();
		PipeArray[i].MovePipes(PipeSpeed);
		PipeArray[i].CheckCollision();


	}

	


}

int main()
{

	

	

	InitWindow(ScreenWidht, ScreenHeight, "20 Games challenge Flappy Bird");
	SetTargetFPS(60);

	Background = LoadTexture("Sprites/Background/Background5.png");
	

	HightScorePoints = HighScore();


	while (!WindowShouldClose())
	{
		BeginDrawing();

		BackgroundOffset -= BackgroundSpeed * GetFrameTime();

		
		if (BackgroundOffset <= -ScreenWidht)
		{
			BackgroundOffset = 0.f;
		}

		
		DrawTexturePro(Background,
			{ 0, 0, (float)Background.width, (float)Background.height },
			{ BackgroundOffset, 0, (float)ScreenWidht, (float)ScreenHeight },
			{ 0, 0 }, 0, WHITE);

		DrawTexturePro(Background,
			{ 0, 0, (float)Background.width, (float)Background.height },
			{ BackgroundOffset + ScreenWidht, 0, (float)ScreenWidht, (float)ScreenHeight },
			{ 0, 0 }, 0, WHITE);

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

	UnloadTexture(Background);
	CloseWindow();

}