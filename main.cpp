#include <ncurses.h>
#include <string>
#include <iostream>
using namespace std;

#define WHITE_ON_BLACK 1
#define WHITE_ON_WHITE 2
#define BLACK_ON_BLACK 3
#define BLACK_ON_WHITE 4

void labelBoardEdges() {
  for (int index = 1; index < 9; index++) {
    mvaddch(index, 0, index + 48);
    mvaddch(0, index, index + 96);
  }
}

void render(int board[64]) {
  char pieces[13];
  pieces[0] = ' ';
  pieces[1] = 'K';
  pieces[2] = 'Q';
  pieces[3] = 'R';
  pieces[4] = 'B';
  pieces[5] = 'N';
  pieces[6] = 'P';
  pieces[7] = 'K';
  pieces[8] = 'Q';
  pieces[9] = 'R';
  pieces[10] = 'B';
  pieces[11] = 'N';
  pieces[12] = 'P';

  labelBoardEdges();
  for (int index = 0; index < 64; index++) {
    int col = index % 8 + 1;
    int row = index / 8 + 1;
    int piece_index = board[index];
    char piece_icon = pieces[piece_index];

    int tile_color = (int)((index % 2) != (row % 2));
    int team_color = (int)(piece_index > 6);
    int color_scheme = 2 * team_color + 1 + tile_color;

    attron(COLOR_PAIR(color_scheme));
    mvaddch(row, col, piece_icon);
    attroff(COLOR_PAIR(color_scheme));
  }
}

int main(int argc, char ** argv)
{
    int board[64] = {
      3, 5, 4, 2, 1, 4, 5, 3,
      6, 6, 6, 6, 6, 6, 6, 6,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      12, 12, 12, 12, 12, 12, 12, 12,
      9, 11, 10, 7, 8, 10, 11, 9,
    };

    // init screen and sets up screen
    initscr();
    start_color();
    init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLUE);
    init_pair(WHITE_ON_WHITE, COLOR_WHITE, COLOR_RED);
    init_pair(BLACK_ON_BLACK, COLOR_BLACK, COLOR_BLUE);
    init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_RED);

    std::string input;
    while (true) {
      // print to screen
      char message[] = "Enter a move:";
      char input[10] = "";
      render(board);
      mvprintw(10, 0, message);
  
      // refreshes the screen
      refresh();
      getstr(input); 
      clear(); 
      // endwin();
    }
    return 0;
}

