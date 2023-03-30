#ifndef BLOCKS_H
# define BLOCKS_H
# include "blocks.h"
#endif

typedef struct pq_tag *priority_queue;

/* creates new empty priority queue */
priority_queue new_pq(void);

/* frees pq */
void free_pq(priority_queue pq);

/* returns count of pq */
int count(priority_queue pq);

/* returns if pq is empty */
int is_empty(priority_queue pq);

/* inserts new node according to priority */
void insert_node(blocks state, priority_queue pq);

/* removes node with biggest priority*/
blocks remove_node(priority_queue pq);