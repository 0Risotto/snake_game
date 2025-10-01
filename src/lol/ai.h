#pragma once
#include "food.h"
#include "snake.h"
#include <unordered_map>
#include <vector>

struct State {
  int dx;
  int dy;
  Direction dir;
};

// Hashing for state (so we can use it as map key)
struct StateHash {
  size_t operator()(const State &s) const {
    return std::hash<int>()(s.dx) ^ std::hash<int>()(s.dy) ^
           std::hash<int>()(s.dir);
  }
};

struct StateEqual {
  bool operator()(const State &a, const State &b) const {
    return a.dx == b.dx && a.dy == b.dy && a.dir == b.dir;
  }
};

// Q-Learning Agent
class SnakeAI {
public:
  SnakeAI(double alpha = 0.1, double gamma = 0.9, double epsilon = 0.2);

  Direction chooseAction(const Snake &snake, const Food &food, int width,
                         int height);
  void update(const Snake &snake, const Food &food, Direction action,
              int reward);

private:
  std::unordered_map<State, std::vector<double>, StateHash, StateEqual> Q;
  double alpha;   // learning rate
  double gamma;   // discount
  double epsilon; // exploration
  State lastState;
  Direction lastAction;

  State getState(const Snake &snake, const Food &food);
};
