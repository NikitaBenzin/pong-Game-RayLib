#include "raylib.h"


// struct with BALL settings
struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw() {
		// draw the circle in the midle of window
		DrawCircle((int) x, (int) y, radius, WHITE);
	}
};

// struct with Paddle settings
struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect() 
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
	}

	void Draw() 
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};

// ------------------------------------- MAIN -------------------------------------- // 
int main()
{
	// init the window 
	InitWindow(800, 600, "Pong");
	// set window updating to the max of monitor
	SetWindowState(FLAG_VSYNC_HINT);

// ------------------------------------------------------------- //
	// creat a ball 
	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;

	// players (paddle) creation
	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;

	const char* winnerText = nullptr;
// ------------------------------------------------------------- //

	// main while loop. game loop
	while (!WindowShouldClose())
	{
		// move the ball  
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();
		// screen Y collider
		if (ball.y > GetScreenHeight()) { 
			ball.y = GetScreenHeight(); 
			ball.speedY *= -1; 
		} else if (ball.y < 0) { 
			ball.y = 0; 
			ball.speedY *= -1; 
		}
		
		// left player collision with screen
		if (IsKeyDown(KEY_W)) {
			if (!(leftPaddle.y < 0 + leftPaddle.height / 2)) {
				leftPaddle.y -= leftPaddle.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_S)) {
			if (!(leftPaddle.y > GetScreenHeight() - leftPaddle.height / 2)) {
				leftPaddle.y += leftPaddle.speed * GetFrameTime();
			}
		}

		// right player collision with screen
		if (IsKeyDown(KEY_UP)) {
			if (!(rightPaddle.y < 0 + rightPaddle.height / 2)) {
				rightPaddle.y -= rightPaddle.speed * GetFrameTime();
			}
		}
		if (IsKeyDown(KEY_DOWN)) {
			if (!(rightPaddle.y > GetScreenHeight() - rightPaddle.height / 2)) {
				rightPaddle.y += rightPaddle.speed * GetFrameTime();
			}
		}

		// collision of ball with paddles
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			if (ball.speedX < 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		};
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		};

		// ball position reset and counter set 
		if (ball.x > GetScreenWidth()) {
			winnerText = "Left Wins!";
		}
		else if (ball.x < 0) {
			winnerText = "Right Wins!";
		}

		// restart the game if space down
		if (IsKeyDown(KEY_SPACE)) {
			winnerText = nullptr;
			ball.x = GetScreenWidth() / 2.0f;
			ball.y = GetScreenHeight() / 2.0f;
			ball.speedX = 300;
			ball.speedY = 300;
		}

		// start the render of window
		BeginDrawing();
		// color the window 
		ClearBackground(BLACK);
		// draw the ball
		ball.Draw();

		// draw the players rectangle 
		leftPaddle.Draw();
		rightPaddle.Draw();

		// draw the text if someone scored 
		if (winnerText) {
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		// show the fps on the window
		DrawFPS(0, 0);

		// stop drawing proces
		EndDrawing();
	}

	// close the window. end the program 
	CloseWindow();
	return 0;
}
