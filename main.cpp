#include <raylib.h>

// Window Configuration
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE "Pong Bong"

// Box/Court Configuration
#define BOX_WIDTH 900
#define BOX_HEIGHT 500

// Calculated Box Position (centered)
const int BOX_X = (WINDOW_WIDTH - BOX_WIDTH) / 2;
const int BOX_Y = (WINDOW_HEIGHT - BOX_HEIGHT) / 2;

// Paddle Configuration
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 80
#define PADDLE_SPEED 7
#define PADDLE_MARGIN 10 // Distance from box edge

// Ball Configuration
#define BALL_RADIUS 8
#define BALL_SPEED_X 5
#define BALL_SPEED_Y 5

// Score Display Configuration
#define SCORE_FONT_SIZE 20
#define SCORE_Y_POSITION 10
#define SCORE_SPACING 150

void draw(int paddleX, int paddleY, int paddle2X, int paddle2Y, float ballX,
          float ballY, int score1, int score2) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  // Draw court
  DrawRectangle(BOX_X, BOX_Y, BOX_WIDTH, BOX_HEIGHT, BLACK);

  // Draw center line
  DrawLine(BOX_X + BOX_WIDTH / 2, BOX_Y, BOX_X + BOX_WIDTH / 2,
           BOX_Y + BOX_HEIGHT, GRAY);

  // Draw paddles
  DrawRectangle(paddleX, paddleY, PADDLE_WIDTH, PADDLE_HEIGHT, BLUE);
  DrawRectangle(paddle2X, paddle2Y, PADDLE_WIDTH, PADDLE_HEIGHT, RED);

  // Draw ball
  DrawCircle(ballX, ballY, BALL_RADIUS, WHITE);

  // Draw scores (centered above court)
  DrawText(TextFormat("Player 1: %d", score1), WINDOW_WIDTH / 2 - SCORE_SPACING,
           SCORE_Y_POSITION, SCORE_FONT_SIZE, BLACK);
  DrawText(TextFormat("Player 2: %d", score2),
           WINDOW_WIDTH / 2 + SCORE_SPACING / 2, SCORE_Y_POSITION,
           SCORE_FONT_SIZE, BLACK);

  EndDrawing();
}

int main() {
  // Paddle starting positions
  int paddleX = BOX_X + PADDLE_MARGIN;
  int paddleY = BOX_Y + (BOX_HEIGHT - PADDLE_HEIGHT) / 2;

  int paddle2X = BOX_X + BOX_WIDTH - PADDLE_WIDTH - PADDLE_MARGIN;
  int paddle2Y = BOX_Y + (BOX_HEIGHT - PADDLE_HEIGHT) / 2;

  // Ball starting position (center of court)
  float ballX = BOX_X + static_cast<float>(BOX_WIDTH) / 2;
  float ballY = BOX_Y + static_cast<float>(BOX_HEIGHT) / 2;
  float ballSpeedX = BALL_SPEED_X;
  float ballSpeedY = BALL_SPEED_Y;

  // Scores
  int score1 = 0;
  int score2 = 0;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    // Paddle movement - Player 1 (W/S)
    if (IsKeyDown('S')) {
      if (paddleY + PADDLE_HEIGHT < BOX_Y + BOX_HEIGHT)
        paddleY += PADDLE_SPEED;
    }
    if (IsKeyDown('W')) {
      if (paddleY > BOX_Y)
        paddleY -= PADDLE_SPEED;
    }

    // Paddle movement - Player 2 (Arrow Keys)
    if (IsKeyDown(KEY_DOWN)) {
      if (paddle2Y + PADDLE_HEIGHT < BOX_Y + BOX_HEIGHT)
        paddle2Y += PADDLE_SPEED;
    }
    if (IsKeyDown(KEY_UP)) {
      if (paddle2Y > BOX_Y)
        paddle2Y -= PADDLE_SPEED;
    }

    // Ball movement
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Top wall collision
    if (ballY - BALL_RADIUS <= BOX_Y) {
      ballSpeedY = -ballSpeedY;
      ballY = BOX_Y + BALL_RADIUS;
    }

    // Bottom wall collision
    if (ballY + BALL_RADIUS >= BOX_Y + BOX_HEIGHT) {
      ballSpeedY = -ballSpeedY;
      ballY = BOX_Y + BOX_HEIGHT - BALL_RADIUS;
    }

    // Paddle 1 collision detection
    bool ballIsInPaddleX = false;
    bool ballIsInPaddleY = false;

    if (ballY + BALL_RADIUS >= paddleY &&
        ballY - BALL_RADIUS <= paddleY + PADDLE_HEIGHT) {
      ballIsInPaddleY = true;
    }
    if (ballX + BALL_RADIUS >= paddleX &&
        ballX - BALL_RADIUS <= paddleX + PADDLE_WIDTH) {
      ballIsInPaddleX = true;
    }

    // Paddle 2 collision detection
    bool ballIsInPaddle2X = false;
    bool ballIsInPaddle2Y = false;

    if (ballY + BALL_RADIUS >= paddle2Y &&
        ballY - BALL_RADIUS <= paddle2Y + PADDLE_HEIGHT) {
      ballIsInPaddle2Y = true;
    }
    if (ballX + BALL_RADIUS >= paddle2X &&
        ballX - BALL_RADIUS <= paddle2X + PADDLE_WIDTH) {
      ballIsInPaddle2X = true;
    }

    // Paddle bounces
    if (ballIsInPaddleX && ballIsInPaddleY) {
      ballSpeedX = -ballSpeedX;
      ballX = paddleX + PADDLE_WIDTH + BALL_RADIUS;
    }
    if (ballIsInPaddle2X && ballIsInPaddle2Y) {
      ballSpeedX = -ballSpeedX;
      ballX = paddle2X - BALL_RADIUS;
    }

    // Scoring - Left wall (Player 2 scores)
    if (ballX - BALL_RADIUS <= BOX_X) {
      score2++;
      ballX = BOX_X + static_cast<float>(BOX_WIDTH) / 2;
      ballY = BOX_Y + static_cast<float>(BOX_HEIGHT) / 2;
    }

    // Scoring - Right wall (Player 1 scores)
    if (ballX + BALL_RADIUS >= BOX_X + BOX_WIDTH) {
      score1++;
      ballX = BOX_X + static_cast<float>(BOX_WIDTH) / 2;
      ballY = BOX_Y + static_cast<float>(BOX_HEIGHT) / 2;
    }

    draw(paddleX, paddleY, paddle2X, paddle2Y, ballX, ballY, score1, score2);
  }

  CloseWindow();
  return 0;
}
