#pragma once
#include "food.h"
#include "snake.h"
#include <unordered_map>
#include <vector>

// Richer state representation
struct State {
  bool dangerAhead;
  bool dangerLeft;
  bool dangerRight;

  bool foodLeft;
  bool foodRight;
  bool foodUp;
  bool foodDown;

  Direction dir;

  bool operator==(const State &other) const {
    return dangerAhead == other.dangerAhead && dangerLeft == other.dangerLeft &&
           dangerRight == other.dangerRight && foodLeft == other.foodLeft &&
           foodRight == other.foodRight && foodUp == other.foodUp &&
           foodDown == other.foodDown && dir == other.dir;
  }
};

// Hash so State can be used in unordered_map
namespace std {
template <> struct hash<State> {
  size_t operator()(const State &s) const {
    size_t h = 0;
    h |= s.dangerAhead << 0;
    h |= s.dangerLeft << 1;
    h |= s.dangerRight << 2;
    h |= s.foodLeft << 3;
    h |= s.foodRight << 4;
    h |= s.foodUp << 5;
    h |= s.foodDown << 6;
    h |= s.dir << 7;
    return h;
  }
};
} // namespace std

class AI {
  double alpha;   // learning rate
  double gamma;   // discount
  double epsilon; // exploration (will decay)

  State lastState;
  Direction lastAction;

  std::unordered_map<State, std::vector<double>> Q;

public:
  AI(double alpha, double gamma, double epsilon);

  State getState(const Snake &snake, const Food &food, int width, int height);

  Direction chooseAction(const Snake &snake, const Food &food, int width,
                         int height);

  void update(const Snake &snake, const Food &food, Direction action,
              int reward, int width, int height);

  void decayEpsilon();
};
