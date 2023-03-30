#ifndef BLOCKS_H
# define BLOCKS_H
# include "blocks.h"
#endif

#include "blocks.h"

/* initializes the freeing stack */
void initialize_stack(void);

/* pushes state on stack */
void push(blocks data);

/* frees states on stack */
void free_stack(void);