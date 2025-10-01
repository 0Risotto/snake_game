#pragma once

#include "snake.h"
#include <deque>
#include <utility>

struct Food {
  int x, y;
};

void spawnFood(Food &food, int width, int height, const Snake &snake);
bool isFoodEaten(const Snake &snake, const Food &food);
