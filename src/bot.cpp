#include "bot.h"

static bool isSafe(const Snake &snake, int x, int y, int width, int height) {
  if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1)
    return false;
  for (auto &seg : snake.body) {
    if (seg.first == x && seg.second == y)
      return false;
  }
  return true;
}

Direction botNextMove(const Snake &snake, const Food &food, int width,
                      int height) {
  auto head = snake.body.front();
  int hx = head.first, hy = head.second;

  // Try to move closer to food
  if (food.x < hx && snake.dir != RIGHT) {
    if (isSafe(snake, hx - 1, hy, width, height))
      return LEFT;
  }
  if (food.x > hx && snake.dir != LEFT) {
    if (isSafe(snake, hx + 1, hy, width, height))
      return RIGHT;
  }
  if (food.y < hy && snake.dir != DOWN) {
    if (isSafe(snake, hx, hy - 1, width, height))
      return UP;
  }
  if (food.y > hy && snake.dir != UP) {
    if (isSafe(snake, hx, hy + 1, width, height))
      return DOWN;
  }

  // If greedy move not possible, pick a safe fallback
  if (isSafe(snake, hx, hy - 1, width, height) && snake.dir != DOWN)
    return UP;
  if (isSafe(snake, hx, hy + 1, width, height) && snake.dir != UP)
    return DOWN;
  if (isSafe(snake, hx - 1, hy, width, height) && snake.dir != RIGHT)
    return LEFT;
  if (isSafe(snake, hx + 1, hy, width, height) && snake.dir != LEFT)
    return RIGHT;

  // If nothing safe → keep direction (will likely crash)
  return snake.dir;
}
