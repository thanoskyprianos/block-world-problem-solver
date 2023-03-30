typedef struct block_tag *blocks;

/* initializes a new empty state of size size and sets its previous state as prev */
blocks initialize_state(int size, const blocks prev);

/* frees a state */
void free_state(blocks state);

/* copies src state to dest */
void copy_state(blocks *dest, const blocks src);

/* returns heuristic value of state */
int get_heuristic(const blocks state);

/* heuristic function for blocks out of place */
int h(const blocks state1, const blocks state2);

/* adds a block on state on the state */
void add_block_state(char *name, char *on, blocks state);

/* checks if name is on on */
int is_on(char *name, char *on, const blocks state);

/* returns 1 if name holds block on top of it */
int holds(char *name, const blocks state);

/* set block under name in position pos */
void set_on_at(char *on, int pos, blocks state);

/* print block state */
void print_blocks(const blocks state);

/* solves the problem in file_name */
int blocks_world(char *file_name);