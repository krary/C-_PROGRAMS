#include<iostream>
#include<raylib.h>
int player_score = 0;
int cpu_score = 0;
class Ball {
public:
	float x, y;
	int speed_x, speed_y; // Changed to float for consistency
	int radius;
	void Draw() {
			



		DrawCircle(x, y, radius,RED);
	}
	void Update() {
		x += speed_x;
		y += speed_y;
		std::cout << "Player Score: " << player_score << " CPU Score: " << cpu_score << std::endl;
		if (y + radius > GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1;
		}
		if (x + radius >= GetScreenWidth() || x - radius <= 0) {
			speed_x *= -1;
			if(x + radius >= GetScreenWidth()) {
				player_score++;
			}
			if(x - radius <= 0) {
				cpu_score++;
			}
		}
	}
};
class Paddle {
protected:
	void LimiteMovement(){
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}
		if (y <= 0) {
			y = 0;
		}
	}
public:
	float x, y;
	int width, height;
	int speed;
	void Draw() {
		DrawRectangle(x, y, width, height, BLUE);
	}
	void Update() {
		if(IsKeyDown(KEY_UP)){
			y -= speed;}
		if (IsKeyDown(KEY_DOWN)) {
			y += speed;
		}
		LimiteMovement();
	}};
class CpuPaddle: public Paddle{
public:
	void Update(int ball_y) {
		if (y + height / 2 > ball_y) {
			y = y - speed;
		}
		if (y + height / 2 < ball_y) {
			y = y + speed;
		}
		LimiteMovement();
	}
};
Ball ball;
Paddle paddle_left;
CpuPaddle paddle_right;
int main(int arc, const char** argv) {

	const int screen_width = 1280;
	const int screen_height = 800;
	InitWindow(screen_width,screen_height,"Ping Pong");
	SetTargetFPS(60);
	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;
	paddle_left.x = 10;
	paddle_left.y = screen_height / 2 - 60;
	paddle_left.width = 25;
	paddle_left.height = 120;
	paddle_left.speed = 6;
	paddle_right.x = GetScreenWidth() - 35;
	paddle_right.y = screen_height / 2 - 60;
	paddle_right.width = 25;
	paddle_right.height = 120;
	paddle_right.speed = 6;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ball.Update();
		paddle_right.Update(ball.y);
		paddle_left.Update();//Let call the Update function for moving the ball
		
		if(CheckCollisionCircleRec(Vector2{ static_cast<float>(ball.x), static_cast<float>(ball.y)}, static_cast<float>(ball.radius), Rectangle{ static_cast<float>(paddle_left.x), static_cast<float>(paddle_left.y), static_cast<float>(paddle_left.width),static_cast<float>( paddle_left.height) })) {
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ static_cast<float>(ball.x), static_cast<float>(ball.y) }, static_cast<float>(ball.radius), Rectangle{ static_cast<float>(paddle_right.x), static_cast<float>(paddle_right.y), static_cast<float>(paddle_right.width),static_cast<float>(paddle_right.height) })) {
			ball.speed_x *= -1;
		}

		ClearBackground(BLACK);
		
		ball.Draw();      //Let call the Draw function for drawing the ball
		paddle_left.Draw();
		paddle_right.Draw();
		DrawText(TextFormat("%i",cpu_score), screen_width / 4 - 20, 20, 20, WHITE);
		DrawText(TextFormat("%i", player_score), screen_width - 320, 20, 20, WHITE);
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, BLUE);

		EndDrawing();
	}




	CloseWindow();
	return 0;
}