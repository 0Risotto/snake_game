#pragma once
#include <deque>
#include <utility>
enum Direction { UP, DOWN, LEFT, RIGHT };

struct Snake {
  std::deque<std::pair<int, int>> body;
  Direction dir;
};

void initSnake(Snake &snake, int startx, int startY, int length);
void moveSnake(Snake &snake, bool grow = false);
bool checkCollision(Snake &snake, int width, int height);
