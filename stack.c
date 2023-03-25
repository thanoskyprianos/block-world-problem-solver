#include <stdlib.h>
#include "blocks.h"


struct ntag{
  blocks data;
  struct ntag* next;
};

struct stag{
  struct ntag* top;
};

typedef struct ntag *node;
typedef struct stag *stack;

stack s; /* used to free states */

void initialize_stack(void){
  s = malloc(sizeof *s);
  s->top = NULL;
}

void push(blocks data){
  node top = s->top;
  node new = malloc(sizeof *new);
  new->data = data;
  new->next = top;
  s->top = new;
}

void free_stack(void){
  node top = s->top;
  while(top != NULL){
    node temp = top;
    s->top = top->next;
    free_state(temp->data);
    free(temp);
    top = s->top;
  }
  free(s);
}