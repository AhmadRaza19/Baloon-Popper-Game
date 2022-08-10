//Author: Ahmad Raza

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "simpleio.h"
#include "bpgame.h"

#define MY_NONE '.'
static char Balloons[] = {MY_NONE, Red, Blue, Green, Yellow};



typedef struct bpgame
{
    char** array;
    char** lastMove;
    int row;
    int col;
    int score;
    int prev;
}BPgame;


BPGame * bp_create(int nrows , int ncols){
    BPGame *b = malloc(sizeof(b));

    b->row = nrows;
    b->col = ncols;

    if (nrows < MAX_ROWS && ncols < MAX_COLS && nrows > 0 && ncols > 0)
    {
        b->array = (char**)malloc(nrows * sizeof(char*));
        b->lastMove =(char**)malloc(nrows * sizeof(char*));
        for (int i = 0; i < nrows; i++){
            b->array[i] = (char*)malloc(ncols * (sizeof(char)));
            b->lastMove[i] = (char*)malloc(ncols * (sizeof(char)));
        }
    }else{
        printf("The numbers of rows/columns entered are outside of range\n");
        return NULL;
    }
    srand (time(NULL));
    int temp; 
    for (int i=0; i < nrows; i++){
        for (int j=0; j < ncols; j++) {
            temp = rand() % 5;
            b->array[i][j] = Balloons[temp];
        }
    }
    return b;

}

extern BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols) {

    if (nrows > MAX_ROWS || ncols > MAX_COLS || nrows < 0 || ncols < 0){
        return NULL;
    }
    BPGame *b = malloc(sizeof(BPGame));
    b->row = nrows;
    b->col = ncols;

    b->array = (char**)malloc(nrows * sizeof(char*));
    b->lastMove =(char**)malloc(nrows * sizeof(char*));
    for (int i = 0; i < nrows; i++) {
        b->array[i] = (char*)malloc(ncols * sizeof(char));
        b->lastMove[i] = (char*)malloc(ncols * (sizeof(char)));
    }
    for (int k = 0; k < nrows; k++){
    for (int j = 0; j < ncols; j++) {
        b->array[k][j] = mtx[k][j];
        }
    }
    return b;
}

void bp_destroy(BPGame * b)
{
    for (int i = 0; i < b->row; i++)
    {
        free(b->array[i]);
    }
    free(b->array);
 }


void bp_display(BPGame * b){
    //Prints Front Border
    printf("  +");
    for (int x=0; x < (b->col * 2)+1; x++) {
        printf("-");
    }
    printf("+\n");

    //Prints Array Contents and Row Index
    for (int i=0; i < b->row; i++) {
        if (b->row <10){
         printf("%d | ", i);
        }else{
            if (i < 10){
                printf("%d | ", i);
            }else{
                printf("%d| ", i);
            }
        }
        for (int j=0; j< b->col; j++) {
            printf("%c " , b->array[i][j]);
        }
        printf("|\n");
    }

    //Prints End Border
    printf("  +");
    for (int x=0; x < (b->col * 2)+1; x++) {
        printf("-");
    }

    //Prints Column Index
    printf("+\n");
    printf("    ");
    for (int j=0; j< b->col; j++) {
        printf("%d ", j);
    }
    printf("\n");
}



int pop(BPGame * b, int r, int c, char temp)
{
int size = 0;
if (temp != '.'){
  if (r-1 >= 0){
    if (b->array[r-1][c] == temp){
        size++;
        b->array[r][c] = '.';
        b->array[r-1][c] = '.';
        size+= pop(b, r-1, c, temp);
   } 
  }
  if (r+1 < b->row){
      if (b->array[r+1][c] == temp){
        size++;
        b->array[r][c] = '.';
        b->array[r+1][c] = '.';   
        size+= pop(b, r+1, c, temp);
   }
  }  
  if (c-1 >= 0){
      if (b->array[r][c-1] == temp){
        size++;
        b->array[r][c] = '.';
        b->array[r][c-1] = '.';   
        size+= pop(b, r, c-1, temp);
   }
  } 
  if (c+1 < b->col){
      if (b->array[r][c+1] == temp){
        size++;
        b->array[r][c] = '.';
        b->array[r][c+1] = '.';   
        size+= pop(b, r, c+1, temp);
   }
  }
}

return size;
}


extern int bp_pop(BPGame * b, int r, int c){
  b->prev = b->score;
  for (int i=0; i < b->row; i++){
      for (int j=0; j < b->col; j++){
        b->lastMove[i][j] = b->array[i][j];
      }
   }
  char temp = b->array[r][c];
  int size = pop(b, r, c, temp) + 1;

  if (size == 1){
      size = 0;
  }

  b->score += size * (size - 1);
  return size;
}



extern int bp_is_compact(BPGame* b)
{
    int temp = 0;
    for (int j = 0; j < b->col; j++)
    {
        for (int i = b->row-1; i > 0; i--)
        {
            if (b->array[i][j] != '.'){
                if (b->array[i-1][j] == '.')
                {
                    temp = 1;
                }
            }
        }
    }

if (temp == 1){
    return 0;
}
return 1;
}


void bp_float_one_step(BPGame * b){
    char temp;
    for (int j=0; j < b->col; j++){
        for (int i = 0; i < b->row; i++){
            if (b->array[i][j] != '.'){
                if (i-1 >= 0)
                 {
                    if (b->array[i-1][j] == '.')
                    {
                        b->array[i-1][j] = b->array[i][j];
                        b->array[i][j] = '.';
                    }
                }
            }
        }
    }
}


 int bp_get_balloon(BPGame * b, int r, int c){
    if ((r <= b->row && r >= 0) && (c <= b->col && c >= 0)){
        return b->array[r][c];
    }
      return -1;
}


 extern int bp_can_pop(BPGame * b){ 
      for(int i = 0;i < b->row; i++){ 
        for(int j = 0; j <b->col; j++){
          if (b->array[i][j] != '.'){
            if (i-1 >= 0){
                if (b->array[i][j] == b->array[i-1][j]){
                return 1;
                }
          }
            if (i+1 < b->row){
                if (b->array[i][j] == b->array[i+1][j]){
                return 1;
                }
          }
            if (j-1 >= 0){
                if (b->array[i][j] == b->array[i][j-1]){
                return 1;
                }
          }
            if (j+1 < b->col){
                if (b->array[i][j] == b->array[i][j+1]){
                return 1;
                }

          }
         
        }
    }
  }
    return 0;
 }

 extern int bp_score(BPGame * b)
{
    return b->score;
 }

void bp_display_STD(BPGame *b) {
    for(int i = 0; i < b->row; i++){    
        for (int j = 0; j < b->col; j++){
            printf("%c", b->array[i][j]);
        }
        printf("\n");
    }
}

 extern int bp_undo(BPGame * b){
    b->score = b->prev;
    for (int i=0; i < b->row; i++) {
        for (int j=0; j < b->col; j++) {
            b->array[i][j] = b->lastMove[i][j];
        }
    } 
   return 1;
 }


#define MAIN 1
#if MAIN

#endif


