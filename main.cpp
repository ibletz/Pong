/*
	Pong with raylib
	2024.07.11
	tutorial URL: youtube.com/watch?v=VLJlTaFvHo4
*/
#include <iostream>
#include "raylib.h"


//global variables :<
int playerScore{};
int cpuScore{};
Color Green =		Color{ 38,185,154,255 };
Color Dark_Green =	Color{ 20,160,133,255 };
Color Light_Green = Color{ 129,204,184,255 };
Color Yellow =		Color{ 243,213,91,255 };

class Ball
{
public:

	float x{};
	float y{};
	int speed_x{};
	int speed_y{};
	int radius{};

	void draw()
	{
		// draw the ball
		DrawCircle(x, y, radius, Yellow);
	}

	void update()
	{
		x += speed_x;
		y += speed_y;

		// bounce the ball off of the screen edges and score points
		if (y + radius >= GetScreenHeight() || y - radius <= 0)
			speed_y *= -1;
		
		if (x + radius >= GetScreenWidth()) // player scores a point
		{
			playerScore++;
			resetBall();
		}
		if (x - radius <= 0) // cpu scores a point
		{
			cpuScore++;
			resetBall();
		}
			
	}

	// reset ball when someone scores
	void resetBall()
	{
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;

		int speed_choices[] = { -1,1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)];
		speed_y *= speed_choices[GetRandomValue(0, 1)];
	}
};

class Paddle
{
public:
	float x{};
	float y{};
	float width{};
	float height{};
	int speed{};

	void draw()
	{
	//	DrawRectangle(x, y, width, height, WHITE);
		DrawRectangleRounded(Rectangle{ x,y,width,height }, 0.8, 0, WHITE);
	}

	void update()
	{
		// move the paddle with key presses
		if (IsKeyDown(KEY_W))
				y = y - speed;
		if (IsKeyDown(KEY_S))
				y = y + speed;
		limitMovement();
	}

protected:
	// stop paddle from moving out of bounds
	void limitMovement()
	{
		if (y <= 0)
			y = 0;
		if (y + height >= GetScreenHeight())
			y = GetScreenHeight() - height;
	}
};

class CpuPaddle : public Paddle
{
public:
	void update(int ball_y) 
	{
		// move the paddle to follow the ball (Artifical Intelligence!)
		if (y + height / 2 > ball_y)
			y = y - speed;
		if (y + height / 2 <= ball_y)
			y = y + speed;
		limitMovement();
	}
};

int main()
{
	std::cout << "Starting the game..." << '\n';

	const int window_width{ 1280 };
	const int window_height{ 800 };
	InitWindow(window_width, window_height, "raylib Pong");

	const int padding{ 10 };

	Ball ball {};
	Paddle playerPaddle {};
	CpuPaddle cpuPaddle {};

	// set ball attributes
	ball.radius = 20;
	ball.x = window_width / 2;
	ball.y = window_height / 2;
	ball.speed_x = 8;
	ball.speed_y = 8;

	// set player paddle attributes
	playerPaddle.width = 25;
	playerPaddle.height = 120;
	playerPaddle.x = padding;
	playerPaddle.y = window_height / 2 - playerPaddle.height / 2;
	playerPaddle.speed = 6.f;
	
	// set cpu paddle attributes
	cpuPaddle.width = 25;
	cpuPaddle.height = 120;
	cpuPaddle.x = window_width - cpuPaddle.width - padding;
	cpuPaddle.y = window_height / 2 - cpuPaddle.height / 2;
	cpuPaddle.speed = 6.f;

	SetTargetFPS(60);
	/*----------------------------------------------------*/
	/* Game loop starts here							  */
	/*----------------------------------------------------*/
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		// background colors
		ClearBackground(Dark_Green);
		DrawRectangle(window_width / 2, 0, window_width / 2, window_height, Green);
		DrawCircle(window_width / 2, window_height / 2, 150, Light_Green);

		// draw center line
		DrawLine(window_width / 2, 0, window_width / 2, window_height, WHITE);

		// Updating
		ball.update();
		playerPaddle.update();
		cpuPaddle.update(ball.y);

		// collision checks
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ playerPaddle.x,playerPaddle.y,playerPaddle.width,playerPaddle.height }))
		{
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ cpuPaddle.x,cpuPaddle.y,cpuPaddle.width,cpuPaddle.height }))
		{
			ball.speed_x *= -1;
		}

		// drawing
		ball.draw();
		playerPaddle.draw();
		cpuPaddle.draw();
		DrawText(TextFormat("%i", playerScore), window_width / 4, 20, 80, WHITE); // display player score
		DrawText(TextFormat("%i", cpuScore), 3*window_width / 4, 20, 80, WHITE); // display CPU score


		EndDrawing();
	}

	CloseWindow();
	return 0;
}