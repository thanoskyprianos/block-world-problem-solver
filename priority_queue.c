#include <limits.h> /* used in remove to avoid undefined behavior */

#include "priority_queue.h"

#ifndef BLOCKS_H
# define BLOCKS_H
# include "blocks.h"
#endif

#include <stdlib.h>

typedef struct node_tag {
  blocks data; /* made state as data */
  struct node_tag *next;
} node;

struct pq_tag { /* pq struct is now hidden */
  int count;
  node *items;
};

priority_queue new_pq(void) {
  priority_queue new = malloc(sizeof *new);
  new->count = 0;
  new->items = NULL;

  return new;
}

void free_pq(priority_queue pq){
  node *cur = pq->items;
  while(cur != NULL){
    node *temp = cur;
    cur = cur->next;
    free(temp);
  }
  free(pq);
}

int is_empty(priority_queue pq) {
  return pq->count == 0;
}

int count(priority_queue pq) { /* count is now hidden */
  return pq->count;
}

node *sorted_insert(blocks state, node *n) {
  node *new;
  if (n == NULL || heuristic(state) <= heuristic(n->data)) { /* inserting by smallest value */
    new = malloc(sizeof *new);
    new->data = state;
    new->next = n;
    return new;
  } 
  else {
    n->next = sorted_insert(state, n->next);
    return n;
  }
}

void insert_node(blocks state, priority_queue pq) {
  pq->count++;
  pq->items = sorted_insert(state, pq->items);
}

void print_pq(priority_queue pq){
  node *cur = pq->items;
  while(cur != NULL){
    print_blocks(cur->data);
    cur = cur->next;
  }
}

blocks remove_node(priority_queue pq){
  node *temp = NULL;
  blocks state = NULL;
  if(!is_empty(pq)){
    temp = pq->items;
    pq->items = pq->items->next;
    pq->count--;
    state = temp->data;
    free(temp);
  }

  return state;
}