/*
	Pong with raylib
	2024.07.11
	tutorial URL: youtube.com/watch?v=VLJlTaFvHo4
*/
#include <iostream>
#include "raylib.h"

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
		DrawCircle(x, y, radius, WHITE);
	}

	void update()
	{
		x += speed_x;
		y += speed_y;

		// bounce the ball off of the screen edges
		if (y + radius >= GetScreenHeight() || y - radius <= 0)
			speed_y *= -1;
		if (x + radius >= GetScreenWidth() || x - radius <= 0)
			speed_x *= -1;
	}
};

Ball ball{};

int main()
{
	std::cout << "Starting the game..." << '\n';

	const int window_width{ 1280 };
	const int window_height{ 800 };
	InitWindow(window_width, window_height, "raylib Pong");

	const int paddleWidth{ 25 };
	const int paddleHeight{ 120 };
	const int paddlePadding{ 20 };

	ball.radius = 20;
	ball.x = window_width / 2;
	ball.y = window_height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	SetTargetFPS(60);
	/*----------------------------------------------------*/
	/* Game loop starts here							  */
	/*----------------------------------------------------*/
	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(BLACK);

		// draw center line
		DrawLine(window_width / 2, 0, window_width / 2, window_height, WHITE);

		// Updating
		ball.update();

		// drawing
		ball.draw();
		DrawRectangle(paddlePadding, window_height / 2 - paddleHeight / 2, paddleWidth, paddleHeight, WHITE);
		DrawRectangle(window_width - paddleWidth - paddlePadding, window_height / 2 - paddleHeight / 2, paddleWidth, paddleHeight, WHITE);



		EndDrawing();
	}

	CloseWindow();
	return 0;
}