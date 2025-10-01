#include "ai.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

AI::AI(double alpha, double gamma, double epsilon)
    : alpha(alpha), gamma(gamma), epsilon(epsilon) {
  srand(time(nullptr));
}

// Helper: check if position collides with wall or snake body
static bool willCollide(int x, int y, int width, int height,
                        const Snake &snake) {
  if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1)
    return true; // wall
  for (auto &seg : snake.body) {
    if (seg.first == x && seg.second == y)
      return true;
  }
  return false;
}

State AI::getState(const Snake &snake, const Food &food, int width,
                   int height) {
  State s;

  int headX = snake.body.front().first;
  int headY = snake.body.front().second;

  // Food relative position
  s.foodLeft = (food.x < headX);
  s.foodRight = (food.x > headX);
  s.foodUp = (food.y < headY);
  s.foodDown = (food.y > headY);

  s.dir = snake.dir;

  // Dangers relative to direction
  s.dangerAhead = false;
  s.dangerLeft = false;
  s.dangerRight = false;

  if (snake.dir == UP) {
    s.dangerAhead = willCollide(headX, headY - 1, width, height, snake);
    s.dangerLeft = willCollide(headX - 1, headY, width, height, snake);
    s.dangerRight = willCollide(headX + 1, headY, width, height, snake);
  } else if (snake.dir == DOWN) {
    s.dangerAhead = willCollide(headX, headY + 1, width, height, snake);
    s.dangerLeft = willCollide(headX + 1, headY, width, height, snake);
    s.dangerRight = willCollide(headX - 1, headY, width, height, snake);
  } else if (snake.dir == LEFT) {
    s.dangerAhead = willCollide(headX - 1, headY, width, height, snake);
    s.dangerLeft = willCollide(headX, headY + 1, width, height, snake);
    s.dangerRight = willCollide(headX, headY - 1, width, height, snake);
  } else if (snake.dir == RIGHT) {
    s.dangerAhead = willCollide(headX + 1, headY, width, height, snake);
    s.dangerLeft = willCollide(headX, headY - 1, width, height, snake);
    s.dangerRight = willCollide(headX, headY + 1, width, height, snake);
  }

  return s;
}

int actionToIndex(Direction d) {
  switch (d) {
  case UP:
    return 0;
  case DOWN:
    return 1;
  case LEFT:
    return 2;
  case RIGHT:
    return 3;
  }
  return 0;
}

Direction indexToAction(int idx) {
  switch (idx) {
  case 0:
    return UP;
  case 1:
    return DOWN;
  case 2:
    return LEFT;
  case 3:
    return RIGHT;
  }
  return UP;
}

Direction AI::chooseAction(const Snake &snake, const Food &food, int width,
                           int height) {
  State state = getState(snake, food, width, height);

  // Initialize if unseen
  if (Q.find(state) == Q.end()) {
    Q[state] = std::vector<double>(4, 0.0);
  }

  // Exploration
  if ((double)rand() / RAND_MAX < epsilon) {
    int r = rand() % 4;
    lastState = state;
    lastAction = indexToAction(r);
    return lastAction;
  }

  // Exploitation
  auto &values = Q[state];
  int best = std::max_element(values.begin(), values.end()) - values.begin();
  lastState = state;
  lastAction = indexToAction(best);
  return lastAction;
}

void AI::update(const Snake &snake, const Food &food, Direction action,
                int reward, int width, int height) {
  State state = getState(snake, food, width, height);

  if (Q.find(state) == Q.end()) {
    Q[state] = std::vector<double>(4, 0.0);
  }

  int aIdx = actionToIndex(action);

  // Max Q for next state
  double maxQ = *std::max_element(Q[state].begin(), Q[state].end());

  // Q-learning update
  Q[lastState][actionToIndex(lastAction)] +=
      alpha * (reward + gamma * maxQ - Q[lastState][actionToIndex(lastAction)]);
}

void AI::decayEpsilon() {
  epsilon *= 0.999; // slowly reduce randomness
  if (epsilon < 0.01)
    epsilon = 0.01;
}
