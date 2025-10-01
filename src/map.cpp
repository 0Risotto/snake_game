#include "map.h"
#include "score.h"

void drawMap(int width, int height, const Snake &snake, const Food &food,
             const ScoreBoard &sb) {
  clear();

  for (int x = 0; x < width; x++) {
    mvprintw(0, x, "#");
    mvprintw(height - 1, x, "#");
  }
  for (int y = 0; y < height; y++) {
    mvprintw(y, 0, "#");
    mvprintw(y, width - 1, "#");
  }

  bool headDrawn = false;
  for (auto &seg : snake.body) {
    if (!headDrawn) {
      mvprintw(seg.second, seg.first, "O");
      headDrawn = true;
    } else {
      mvprintw(seg.second, seg.first, "o");
    }
  }

  mvprintw(food.y, food.x, "*");

  mvprintw(height, 0, "Score: %d  |  High Score: %d", sb.currentScore,
           sb.highScore);

  refresh();
}
