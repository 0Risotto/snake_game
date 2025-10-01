#pragma once

#include <string>

struct ScoreBoard {
  int currentScore;
  int highScore;
};

void initScore(ScoreBoard &sb);
void addScore(ScoreBoard &sb, int points);
void saveHighScore(const ScoreBoard &sb, const std::string &filename);
void loadHighScore(ScoreBoard &sb, const std::string &filename);
