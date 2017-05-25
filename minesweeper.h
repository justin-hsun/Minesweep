#include <stdbool.h>

struct posn {
  int x;
  int y;
};

extern const char UNREVEALED;
extern const char REVEALED[];
extern const char FLAG;
extern const char MINE;

struct ms_board {
  int width;
  int height;
  char *board;
  int num_mines;
  struct posn *mines;
};

bool flag(struct ms_board *b, int x, int y);

bool reveal(struct ms_board *b, int x, int y);

bool game_won(const struct ms_board *b);

bool game_lost(const struct ms_board *b);
