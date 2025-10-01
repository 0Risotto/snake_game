#pragma once

#include "food.h"
#include "snake.h"

Direction botNextMove(const Snake &snake, const Food &food, int width,
                      int height);
