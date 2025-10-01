#include "food.h"
#include <cstdlib>
#include <ctime>

void spawnFood(Food &food, int width, int height, const Snake &snake) {
  srand(time(0));
  bool valid = false;
  while (!valid) {
    food.x = rand() % (width - 2) + 1;
    food.y = rand() % (height - 2) + 1;
    valid = true;
    for (auto &fs : snake.body) {
      if (fs.first == food.x && fs.second == food.y) {
        valid = false;
        break;
      }
    }
  }
}
bool isFoodEaten(const Snake &snake, const Food &food) {
  int a = snake.body.front().first;
  int b = snake.body.front().second;
  return (a == food.x && b == food.y);
}
