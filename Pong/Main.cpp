#include "raylib.h"

struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int) x, (int) y, radius, GOLD);
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GegRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 20, 200 };
	}

	void Draw()
	{
		DrawRectangle(x - width/2, y - height/2, 20, 200, LIME);
	}
};

int main()
{
	InitWindow(2000, 1500, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 15;
	ball.speedX = 400;
	ball.speedY = 400;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 20;
	leftPaddle.height = 200;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 20;
	rightPaddle.height = 200;
	rightPaddle.speed = 500;

	const char* winnerText = nullptr;


	while (!WindowShouldClose())
	{

		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}


		if (leftPaddle.y < 0 && KEY_S)
		{
			leftPaddle.y = 0;
		}


		if (leftPaddle.y > GetScreenHeight() && KEY_W)
		{
			leftPaddle.y = GetScreenHeight();
		}

		if (rightPaddle.y < 0 && KEY_S)
		{
			rightPaddle.y = 0;
		}


		if (rightPaddle.y > GetScreenHeight() && KEY_W)
		{
			rightPaddle.y = GetScreenHeight();
		}

		if (IsKeyDown(KEY_W))
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP))
		{
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GegRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GegRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}

		}


		if (ball.x < 0)
		{
			winnerText = "Congrats! Right Player Wins!! Press space to restart.";
		}

		if (ball.x > GetScreenWidth())
		{
			winnerText = "Congrats! Left player Wins!! Press space to restart.";
		}

		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 400;
			ball.speedY = 400;
			winnerText = nullptr;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();

		if (winnerText)
		{
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		DrawFPS(10, 10);
		EndDrawing();

	}

	return 0;
}