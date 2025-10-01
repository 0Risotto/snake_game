#include "ai.h"
#include "bot.h"
#include "food.h"
#include "map.h"
#include "score.h"
#include "snake.h"
#include <ncurses.h>
#include <unistd.h> // for usleep

int main() {
  // Init ncurses
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  int width = 40;
  int height = 20;

  // --- Menu ---
  int choice = 0;
  const char *options[3] = {"Human Player", "Greedy Bot", "AI Bot"};
  while (true) {
    clear();
    mvprintw(height / 2 - 2, (width / 2) - 5, "Select Mode:");
    for (int i = 0; i < 3; i++) {
      if (i == choice)
        attron(A_REVERSE);
      mvprintw(height / 2 + i, (width / 2) - 7, "%s", options[i]);
      if (i == choice)
        attroff(A_REVERSE);
    }
    refresh();

    int ch = getch();
    if (ch == KEY_UP && choice > 0) {
      choice--;
    } else if (ch == KEY_DOWN && choice < 2) {
      choice++;
    } else if (ch == '\n' || ch == KEY_ENTER) {
      break;
    }
  }

  nodelay(stdscr, TRUE); // back to async input

  // Snake
  Snake snake;
  initSnake(snake, width / 2, height / 2, 3);

  // Food
  Food food;
  spawnFood(food, width, height, snake);

  // Scoreboard
  ScoreBoard sb;
  initScore(sb);
  loadHighScore(sb, "highscore.txt");

  AI ai(0.5, 0.9, 0.2);

  bool gameOver = false;
  int episodes = 0; // for AI training cycles

  // --- Game loop ---
  while (!gameOver) {
    drawMap(width, height, snake, food, sb);

    // --- Input / Bot decision ---
    if (choice == 0) {
      // Human
      int ch = getch();
      switch (ch) {
      case KEY_UP:
        if (snake.dir != DOWN)
          snake.dir = UP;
        break;
      case KEY_DOWN:
        if (snake.dir != UP)
          snake.dir = DOWN;
        break;
      case KEY_LEFT:
        if (snake.dir != RIGHT)
          snake.dir = LEFT;
        break;
      case KEY_RIGHT:
        if (snake.dir != LEFT)
          snake.dir = RIGHT;
        break;
      case 'q':
        gameOver = true;
        break;
      }
    } else if (choice == 1) {
      // Greedy bot
      snake.dir = botNextMove(snake, food, width, height);
    } else {
      // AI bot
      Direction action = ai.chooseAction(snake, food, width, height);
      snake.dir = action;
    }

    // --- Snake movement / food eating ---
    if (isFoodEaten(snake, food)) {
      addScore(sb, 10);
      spawnFood(food, width, height, snake);
      moveSnake(snake, true); // grow

      if (choice == 2) {
        ai.update(snake, food, snake.dir, +10, width, height);
      }
    } else {
      moveSnake(snake, false);

      if (choice == 2) {
        ai.update(snake, food, snake.dir, -1, width, height);
      }
    }

    // --- Collision check ---
    if (checkCollision(snake, width, height)) {
      if (choice == 2) {
        ai.update(snake, food, snake.dir, -100, width, height);

        // Reset snake & food but keep AI running
        episodes++;
        initSnake(snake, width / 2, height / 2, 3);
        spawnFood(food, width, height, snake);
        initScore(sb);

        // Show training stats
        mvprintw(0, 0, "AI Training - Episodes: %d", episodes);
        refresh();

      } else {
        gameOver = true; // human & greedy bot stop
      }
    }

    // Control speed
    if (choice == 0) {
      usleep(120000);
    } else if (choice == 1) {
      usleep(4500);
    } else if (choice == 2) {
      usleep(1000);
    }
  }

  // Save high score
  saveHighScore(sb, "highscore.txt");

  // --- Game Over screen (only for human/greedy bot) ---
  if (choice != 2) {
    clear();
    mvprintw(height / 2, (width / 2) - 5, "GAME OVER!");
    mvprintw((height / 2) + 1, (width / 2) - 8, "Final Score: %d",
             sb.currentScore);
    mvprintw((height / 2) + 2, (width / 2) - 9, "High Score: %d", sb.highScore);
    mvprintw((height / 2) + 4, (width / 2) - 12, "Press any key to exit...");
    refresh();

    nodelay(stdscr, FALSE);
    getch();
  }

  endwin();
  return 0;
}
