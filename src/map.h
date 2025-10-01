#pragma once

#include "food.h"
#include "score.h"
#include "snake.h"
#include <ncurses.h>

void drawMap(int width, int height, const Snake &snake, const Food &food,
             const ScoreBoard &sb);
