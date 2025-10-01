#include "score.h"
#include <fstream>

void initScore(ScoreBoard &sb) {
  sb.currentScore = 0;
  sb.highScore = 0;
}

void addScore(ScoreBoard &sb, int points) {
  sb.currentScore += points;
  if (sb.currentScore > sb.highScore) {
    sb.highScore = sb.currentScore;
  }
}

void saveHighScore(const ScoreBoard &sb, const std::string &filename) {
  std::ofstream out(filename);
  if (out.is_open()) {
    out << sb.highScore;
    out.close();
  }
}

void loadHighScore(ScoreBoard &sb, const std::string &filename) {
  std::ifstream in(filename);
  if (in.is_open()) {
    in >> sb.highScore;
    in.close();
  } else {
    sb.highScore = 0;
  }
}
