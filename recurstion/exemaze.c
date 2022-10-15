#include <stdio.h>
#include <stdbool.h>

#define LINE 10

bool mazeescape(int y, int x, char maze[][LINE+1]);

int main(void){
   char maze[LINE][LINE+1];
   char str[] = "##########..#......##.#.#.##.##.#.####.##.#....#.##.#.####.##.#....#.##.####.#.##......#..##########";
   char* p = str;
   for (int j = 0; j < LINE; j++){
      for (int i = 0; i < LINE; i++){
           maze[j][i] = *(p++); 
      }
      maze[j][LINE] = '\0';
   }

   for (int j = 0; j < LINE; j++){
      puts(maze[j]);
   }
   int x = mazeescape(1, 0, maze);
   printf("%d", x);
}

bool mazeescape(int y, int x, char maze[][LINE+1]){
   if (x < 0 || y < 0 || x >= LINE || y >= LINE){
      return false;
   }
   
   if (x == LINE - 1) {
      return true;
   }
   
   if (y + 1 < LINE && maze[y+1][x] == '.'){
      maze[y][x] = '#';
      if (mazeescape(y+1, x, maze)){
         return true;
      }else{
         maze[y][x] = '.';
         maze[y+1][x] = '#';
      }
   }
   
   if (x + 1 < LINE && maze[y][x+1] == '.'){
      maze[y][x] = '#';
      if (mazeescape(y, x+1, maze)){
         return true;
      }else{
         maze[y][x] = '.';
         maze[y][x+1] = '#';
      }
   }
   
   
   if (x - 1 > 0 && maze[y][x-1] == '.'){
      maze[y][x] = '#';
      if (mazeescape(y, x-1, maze)){
         return true;
      }else{
         maze[y][x] = '.';
         maze[y][x-1] = '#';
      }
   }
   
   if (y - 1 > 0 && maze[y-1][x] == '.'){
      maze[y][x] = '#';
      if (mazeescape(y-1, x, maze)){
         return true;
      }else{
         maze[y][x] = '.';
         maze[y-1][x] = '#';
      }
   }
   
   return false;
}
