#include <raylib.h>
#include <stdio.h>
// window variables
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define WINDOW_TITILE "Pong Bong"
#define BOX_TOP 50
#define BOX_BOTTOM 550

// box variables
#define BOX_WIDTH 900
#define BOX_HEIGHT 500

// game objects
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 80
#define CHANGE_RATE 7
#define BALL_RADIUS 8

void draw(int paddleX, int paddleY, int paddle2X, int paddle2Y, float ballX,
          float ballY, int score1, int score2) {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  DrawRectangle(BOX_TOP, BOX_TOP, BOX_WIDTH, BOX_HEIGHT, BLACK);

  DrawRectangle(paddleX, paddleY, PADDLE_WIDTH, PADDLE_HEIGHT, BLUE);
  DrawRectangle(paddle2X, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, RED);

  DrawCircle(ballX, ballY, BALL_RADIUS, WHITE);
  DrawText(TextFormat("player 1: %d ", score1), WINDOW_WIDTH / 2 - 50, 10, 20,
           BLACK);
  DrawText(TextFormat("player 2: %d", score2), WINDOW_WIDTH / 2 - 50, 30, 20,
           BLACK);
  EndDrawing();
}

int main() {
  int paddleX = BOX_TOP + 10;
  int paddleY = BOX_TOP + ((BOX_HEIGHT - PADDLE_HEIGHT) / 2);
  int paddle2X = BOX_TOP + BOX_WIDTH - PADDLE_WIDTH - 10;
  int paddle2Y = BOX_TOP + ((BOX_HEIGHT - PADDLE_HEIGHT) / 2);
  float ballX = BOX_TOP + static_cast<float>(BOX_WIDTH / 2);
  float ballY = BOX_TOP + static_cast<float>(BOX_HEIGHT / 2);
  float ballSpeedX = 5;
  float ballSpeedY = 5;
  int score1 = 0;
  int score2 = 0;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITILE);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    // paddle movement player 1
    if (IsKeyDown('S')) {
      if (paddleY + PADDLE_HEIGHT < BOX_TOP + BOX_HEIGHT)
        paddleY += CHANGE_RATE; // prevent paddle from moving out of bounds
    }
    if (IsKeyDown('W')) {
      if (paddleY > BOX_TOP)
        paddleY -= CHANGE_RATE;
    };

    // movement player 2
    if (IsKeyDown(KEY_DOWN)) {
      if (paddle2Y + PADDLE_HEIGHT < BOX_TOP + BOX_HEIGHT)
        paddle2Y += CHANGE_RATE; // prevent paddle from moving out of bounds
    }
    if (IsKeyDown(KEY_UP)) {
      if (paddle2Y > BOX_TOP)
        paddle2Y -= CHANGE_RATE;
    };

    // ball movement
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // coords calculated from the start of the ball
    // top wall
    if (ballY - BALL_RADIUS <= BOX_TOP) {
      ballSpeedY = -ballSpeedY;
      ballY = BOX_TOP + BALL_RADIUS;
    }

    // bottom wall
    if (ballY + BALL_RADIUS >= BOX_TOP + BOX_HEIGHT) {
      ballSpeedY = -ballSpeedY;
      ballY = BOX_TOP + BOX_HEIGHT - BALL_RADIUS;
    }

    // // left wall
    // if (ballX - BALL_RADIUS <= BOX_TOP) {
    //   ballSpeedX = -ballSpeedX;
    //   ballX = BOX_TOP + BALL_RADIUS;
    // }

    // right wall
    // if (ballX + BALL_RADIUS >= BOX_TOP + BOX_WIDTH) {
    //   ballSpeedX = -ballSpeedX;
    //   ballX = BOX_TOP + BOX_WIDTH - BALL_RADIUS;
    // }

    // paddle bounce
    bool ballIsInPaddleX = false;
    bool ballIsInPaddleY = false;
    bool ballIsInPaddle2X = false;
    bool ballIsInPaddle2Y = false;

    if (ballY + BALL_RADIUS >= paddleY &&
        ballY - BALL_RADIUS <= paddleY + PADDLE_HEIGHT) {
      ballIsInPaddleY = true;
    }
    printf("Ball: left=%f, right=%f | Paddle: left=%d, right=%d\n",
           ballX - BALL_RADIUS, ballX + BALL_RADIUS, paddleX,
           paddleX + PADDLE_WIDTH);
    if (ballX + BALL_RADIUS >= paddleX &&
        ballX - BALL_RADIUS <= paddleX + PADDLE_WIDTH) {
      ballIsInPaddleX = true;
    }

    if (ballY + BALL_RADIUS >= paddle2Y &&
        ballY - BALL_RADIUS <= paddle2Y + PADDLE_HEIGHT) {
      ballIsInPaddle2Y = true;
    }
    if (ballX + BALL_RADIUS >= paddle2X &&
        ballX - BALL_RADIUS <= paddle2X + PADDLE_WIDTH) {
      ballIsInPaddle2X = true;
    }

    if (ballIsInPaddleX && ballIsInPaddleY) {
      ballSpeedX = -ballSpeedX;
      ballX = paddleX + PADDLE_WIDTH + BALL_RADIUS;
    }
    if (ballIsInPaddle2X && ballIsInPaddle2Y) {
      ballSpeedX = -ballSpeedX;
      ballX = paddle2X - BALL_RADIUS;
    }

    // scoring
    // left wall
    if (ballX - BALL_RADIUS <= BOX_TOP) {
      score2++;
      ballX = BOX_TOP + static_cast<float>(BOX_WIDTH / 2);
      ballY = BOX_TOP + static_cast<float>(BOX_HEIGHT / 2);
    }
    if (ballX + BALL_RADIUS >= BOX_TOP + BOX_WIDTH) {
      score1++;
      ballX = BOX_TOP + static_cast<float>(BOX_WIDTH / 2);
      ballY = BOX_TOP + static_cast<float>(BOX_HEIGHT / 2);
    }
    draw(paddleX, paddleY, paddle2X, paddle2Y, ballX, ballY, score1, score2);
  }
  CloseWindow();

  return 0;
}
