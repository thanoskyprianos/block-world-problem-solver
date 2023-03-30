#ifndef BLOCKS_H
# define BLOCKS_H
# include "blocks.h"
#endif

typedef struct pq_tag *priority_queue;

priority_queue new_pq(void);
void free_pq(priority_queue pq);
int count(priority_queue pq);
int is_empty(priority_queue pq);
void insert_node(blocks state, priority_queue pq);
blocks remove_node(priority_queue pq);