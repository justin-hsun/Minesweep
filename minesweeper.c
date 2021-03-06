#include "minesweeper.h"
#include <assert.h>

const char UNREVEALED = ' ' ;
const char REVEALED[9] = "012345678";
const char FLAG = 'F';
const char MINE = '*';

bool flag(struct ms_board *b, int x, int y) {
  assert(b!=0);
  assert(1 <= x && x <= b->width);
  assert(1 <= y && y <= b->height);
  if(b->board[(y-1) * (b->width) + x - 1] ==' '){
    b->board[(y-1) * (b->width) + x - 1] = 'F';
    return true;
  } else if (b->board[(y-1) * (b->width) + x - 1] =='F'){
    b->board[(y-1) * (b->width) + x - 1] = ' ';
    return true;
  } else {
    return false;
  }
}
bool is_in_mine (struct posn *mines, int mine_len, int x, int y){
  for(int i=0;i<mine_len;i++){
    if(mines[i].x == x && mines[i].y == y)return true;
  }
  return false;
}

bool reveal(struct ms_board *b, int x, int y) {
  assert(b!=0);
  assert(1 <= x && x <= b->width);
  assert(1 <= y && y <= b->height);
  if(b->board[(y-1) * (b->width) + x - 1] ==' '){
    for(int i=0;i<b->num_mines;i++){
      if((b->mines[i].x == x) && (b->mines[i].y == y)){
        b->board[(y-1) * (b->width) + x - 1] = '*';
        return true;
      }
    }//check if it's a mine
    //if it's not a mine
    int mine_count=0;
    for(int y_off = -1; y_off<=1; y_off++){
      for(int x_off = -1; x_off<=1; x_off++){
        if(x+x_off<1||x+x_off>b->width||y+y_off<1||y+y_off>b->height){
          continue;
        }
        if(is_in_mine(b->mines,b->num_mines,x+x_off,y+y_off)){
          mine_count++;
          //          printf("x+x_off = %d\ny+y_off = %d\n",x+x_off,y+y_off);
        }
      }
    }//search for how many mine nearby
    if(mine_count==0){
      b->board[(y-1) * (b->width) + x - 1] = REVEALED[mine_count];
      for(int y_off = -1; y_off<=1; y_off++){
        for(int x_off = -1; x_off<=1; x_off++){
          if(x+x_off<1||x+x_off>b->width||y+y_off<1||y+y_off>b->height)continue;
          reveal(b,x+x_off,y+y_off);
        }
      } 
      return true;//if z is 0
    } else {
      b->board[(y-1) * (b->width) + x - 1] = REVEALED[mine_count];
      return true;
    }//if z is not 0
  } else {
    return false;
  }//if it's revealed
}

bool game_won(const struct ms_board *b) {
  assert(b!=0);
  int tagged_mine = 0;
  for(int y =1;y<=b->height;y++){
    for(int x =1;x<=b->width;x++){
      if(b->board[(y-1) * (b->width) + x - 1]=='*')return false;
      if(b->board[(y-1) * (b->width) + x - 1]=='F'
         ||b->board[(y-1) * (b->width) + x - 1]==' '){
        for(int i=0;i<b->num_mines;i++){
          if(x == b->mines[i].x&&y == b->mines[i].y){
            tagged_mine++;
            break;
          }
          if(i == b->num_mines-1)return false;
        }
      }    
    }
  }
  if(tagged_mine>b->num_mines)return false;
  return true;
}

bool game_lost(const struct ms_board *b) {
  for(int y =1;y<=b->height;y++){
    for(int x =1;x<=b->width;x++){
      if(b->board[(y-1) * (b->width) + x - 1]=='*'){
        return true;
      }
    }
  }
  return false;
}
