#include "snake.h"

void initSnake(Snake &snake, int startX, int startY, int length) {
  snake.body.clear();
  for (int i = 0; i < length; i++)
    snake.body.push_back({startX - i, startY});

  snake.dir = RIGHT;
}

void moveSnake(Snake &snake, bool grow) {
  int headX = snake.body.front().first;
  int headY = snake.body.front().second;

  switch (snake.dir) {
  case UP:
    headY--;
    break;

  case DOWN:
    headY++;
    break;

  case RIGHT:
    headX++;
    break;

  case LEFT:
    headX--;
    break;
  }

  snake.body.push_front({headX, headY});

  if (!grow) {
    snake.body.pop_back();
  }
}

bool checkCollision(Snake &snake, int width, int height) {
  int headX = snake.body.front().first;
  int headY = snake.body.front().second;
  if (headX <= 0 || headY <= 0 || headY >= height - 1 || headX >= width - 1) {
    return true;
  }
  for (size_t i = 1; i < snake.body.size(); i++) {
    if (snake.body[i].first == headX && snake.body[i].second == headY)
      return true;
  }
  return false;
}
