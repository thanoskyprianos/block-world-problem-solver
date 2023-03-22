#include <stdio.h>

typedef struct block_tag *blocks;

blocks initialize_state(int size);
void free_state(blocks state);
void add_block_state(char *name, char *on, blocks state);
int is_on(char *name, char *on, blocks state);
int holds(char *name, blocks state);
void print_blocks(blocks state);
int start_goal(FILE *fptr, int block_count, blocks state, blocks goal);