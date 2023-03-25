typedef struct block_tag *blocks;

blocks initialize_state(int size, const blocks prev);
void free_state(blocks state);
void copy_state(blocks *dest, const blocks src);
int get_heuristic(const blocks state);
int h(const blocks state1, const blocks state2);
void add_block_state(char *name, char *on, blocks state);
int is_on(char *name, char *on, const blocks state);
int holds(char *name, const blocks state);
void set_on_at(char *on, int pos, blocks state);
void print_blocks(const blocks state);
int blocks_world(char *file_name);