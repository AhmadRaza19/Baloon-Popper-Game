//Author: Ahmad Raza

#define MAX_ROWS 40
#define MAX_COLS 40

/********
* Description:  This file specifies the interface/ADT for 
*	managing the "balloon-pop" game.

*	 A client/app to actually play the game must
*	 manage the user interface itself, but would
*	 use the ADT/interface here to perform the
*	 interface independent operations on the state
* 	 of the game.
*/



typedef struct bpgame BPGame;


#define None '.'
#define Red  '^'
#define Blue '='
#define Green 'o'
#define Yellow '+'


extern BPGame * bp_create(int nrows, int ncols);

extern BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols);

extern void bp_destroy(BPGame * b);

extern void bp_display(BPGame * b);

extern int bp_pop(BPGame * b, int r, int c);

extern int bp_is_compact(BPGame * b);

extern void bp_float_one_step(BPGame * b);

extern int bp_score(BPGame * b);

extern int bp_get_balloon(BPGame * b, int r, int c);

extern int bp_can_pop(BPGame * b);

extern int bp_undo(BPGame * b);

