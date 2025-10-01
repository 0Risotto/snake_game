#include "ai.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

SnakeAI::SnakeAI(double alpha, double gamma, double epsilon)
    : alpha(alpha), gamma(gamma), epsilon(epsilon) {
  srand(time(0));
}

State SnakeAI::getState(const Snake &snake, const Food &food) {
  auto head = snake.body.front();
  State s;
  s.dx = (food.x - head.first) / std::max(1, abs(food.x - head.first));
  s.dy = (food.y - head.second) / std::max(1, abs(food.y - head.second));
  s.dir = snake.dir;
  return s;
}

Direction SnakeAI::chooseAction(const Snake &snake, const Food &food, int width,
                                int height) {
  State s = getState(snake, food);

  // Initialize Q-values if state unseen
  if (Q.find(s) == Q.end()) {
    Q[s] = std::vector<double>(4, 0.0);
  }

  // Epsilon-greedy choice
  double r = ((double)rand() / RAND_MAX);
  Direction action;
  if (r < epsilon) {
    action = static_cast<Direction>(rand() % 4); // explore
  } else {
    auto &qvals = Q[s];
    int best = std::max_element(qvals.begin(), qvals.end()) - qvals.begin();
    action = static_cast<Direction>(best);
  }

  lastState = s;
  lastAction = action;
  return action;
}

void SnakeAI::update(const Snake &snake, const Food &food, Direction action,
                     int reward) {
  State s = getState(snake, food);

  // Initialize if unseen
  if (Q.find(s) == Q.end()) {
    Q[s] = std::vector<double>(4, 0.0);
  }
  if (Q.find(lastState) == Q.end()) {
    Q[lastState] = std::vector<double>(4, 0.0);
  }

  // Q-learning update
  double oldQ = Q[lastState][lastAction];
  double maxQ = *std::max_element(Q[s].begin(), Q[s].end());
  Q[lastState][lastAction] = oldQ + alpha * (reward + gamma * maxQ - oldQ);
}
