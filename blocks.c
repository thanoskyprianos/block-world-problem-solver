#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "priority_queue.h"

#ifndef BLOCKS_H
# define BLOCKS_H
# include "blocks.h"
#endif

#include "stack.h"

typedef struct  data_tag block;
struct data_tag{ /* strings are used to handle big N */
  char *name; /* name of block */
  char *on; /* block it is on */
};

struct block_tag{
  block *data;
  int index; /* used when adding blocks and then to show block count */
  struct block_tag *prev; /* state originated from */
  int cost; /* cost g(x) to get to state */
  int heuristic; /* h(x) heuristic value */
};

blocks initialize_state(int size, const blocks prev){
  blocks state = malloc(sizeof(struct block_tag));
  state->data = malloc(size * sizeof(block));
  state->index = 0;
  state->prev = prev;
  state->cost = prev != NULL ? prev->cost + 1 : 0;
  state->heuristic = INT_MAX; /* INT_MAX represents infinity */

  return state;
}

void free_state(blocks state){
  block *arr = state->data;
  for(int i = 0; i < state->index; i++){
    free(arr[i].name);
    free(arr[i].on);
  }
  free(arr);
  free(state);
}

void copy_state(blocks *dest, const blocks src){
  *dest = initialize_state(src->index, src);

  block *arr = src->data;
  for(int i = 0; i < src->index; i++){
    add_block_state(arr[i].name, arr[i].on, *dest);
  }
}

int get_heuristic(const blocks state){
  return state->heuristic;
}

char *holds_what(char *name, const blocks state){
  block *arr = state->data;
  for(int i = 0; i < state->index; i++)
    if(strcmp(arr[i].on, name) == 0)
      return arr[i].name;
  return NULL;
}

int h(const blocks state1, const blocks state2){
  block *arr1 = state1->data;
  block *arr2 = state2->data;

  int cost = 0;
  for(int i = 0; i < state1->index; i++){
    if(strcmp(arr1[i].on, arr2[i].on) != 0) /* not on same block */
      cost++;

    char *hold1 = holds_what(arr1[i].name, state1);
    char *hold2 = holds_what(arr1[i].name, state2);

    if(hold1 != NULL && hold2 != NULL && strcmp(hold1, hold2) != 0) /* not holding same block */
      cost++;
  }

  return cost;
}

void add_block_state(char *name, char *on, blocks state){
  block *arr = state->data;
  
  int len1 = strlen(name);
  int len2 = strlen(on);

  arr[state->index].name = malloc(len1 + 1);
  arr[state->index].on = malloc(len2 + 1);

  memcpy(arr[state->index].name, name, len1 + 1);
  memcpy(arr[state->index].on, on, len2 + 1);

  state->index++;
}

int is_on(char *name, char *on, const blocks state){
  block *arr = state->data;
  for(int i = 0; i < state->index; i++)
    if(strcmp(arr[i].name, name) == 0 && strcmp(arr[i].on, on) == 0)
      return 1;
  return 0;
}

int holds(char *name, const blocks state){
  block *arr = state->data;
  for(int i = 0; i < state->index; i++)
    if(strcmp(arr[i].on, name) == 0) /* if block is on 'on' field then it always holds */
      return 1;
  return 0;
}

void set_on_at(char *on, int pos, const blocks state){
  block *arr = state->data;
  free(arr[pos].on);
  int len = strlen(on);
  arr[pos].on = malloc((len + 1) * sizeof(char));
  memcpy(arr[pos].on, on, len + 1);
}

/* recursive function that prints states as mentioned in README file */
void preety_print(blocks state, char *table){
  block *arr = state->data;
  for(int i = 0; i < state->index; i++){
    if(strcmp(arr[i].on, table) == 0){
      if(strcmp(table, "#") == 0)
        printf("|"); /* table */
      printf("%s ", arr[i].name);
      preety_print(state, arr[i].name);
      if(strcmp(table, "#") == 0)
        printf("\n");
    }
  }
}

void print_blocks(blocks state){
  preety_print(state, "#");
}

/* called by start_goal */
int read_state(FILE *fptr, int block_count, blocks state){
  for(int i = 0; i < block_count; i++){
    char name[64];
    char on[64];
    fscanf(fptr, "%63s %63s\n", name, on);

    if(strcmp(name, "#") == 0){
      fprintf(stderr, "Formating error. Table can't be block.\n");
      return 0;
    }

    add_block_state(name, on, state);
  }
  return 1;
}

/* read start and goal states from input file*/
int start_goal(blocks *start, blocks *goal, char *file_name){
  FILE *fptr = fopen(file_name, "r");
  if(fptr == NULL){
    fprintf(stderr, "Input error\n");
    return 0;
  }

  int block_count;
  if(fscanf(fptr, "%d", &block_count) != 1 || block_count <= 0){
    fprintf(stderr, "Formating error. Can't read block count.\n");
    return 0;
  }

  *start = initialize_state(block_count, NULL);
  *goal = initialize_state(block_count, NULL);

  if(!read_state(fptr, block_count, *start))
    return 0;

  fscanf(fptr, "\n");

  if(!read_state(fptr, block_count, *goal))
    return 0;

  fclose(fptr);
  return 1;
}

/* recursively print previous states of resulting state */
void print_result(blocks state){
  if(state != NULL){
    print_result(state->prev);
    print_blocks(state);
    printf("\n");
  }
}

void generate_next_states(blocks state, priority_queue pq, const blocks start, const blocks goal, int (*heuristic)(const blocks, const blocks)){
  block *arr = state->data;

  int len = state->index;
  blocks new_state;

  for(int i = 0; i < len; i++){
    if(!holds(arr[i].name, state)){ /* only top blocks can move */

      for(int j = 0; j < len; j++){
        copy_state(&new_state, state);
        
        if(j != i && !holds(arr[j].name, state))
          set_on_at(arr[j].name, i, new_state);
        else if(!is_on(arr[i].name, "#", state)) /* if it's not on table, move it there */
          set_on_at("#", i, new_state);

        if(state->prev != NULL){
          if(heuristic(new_state, state->prev) == 0){ /* if new_state results in previously generated state */
            free_state(new_state);
            continue;
          }
        }
        
        int temp_heuristic = new_state->cost + heuristic(new_state, goal);
        if(temp_heuristic < new_state->heuristic)
          new_state->heuristic = temp_heuristic;

        new_state->cost = state->cost + 1;

        insert_node(new_state, pq);
      }
    }
  }
}

void solve(const blocks start, const blocks goal){
  priority_queue pq = new_pq();
  initialize_stack(); /* stack used to save values removed from priority queue */
  
  insert_node(start, pq);
  while(!is_empty(pq)){
    blocks cur_state = remove_node(pq);
    if(h(cur_state, goal) == 0){
      printf("Solution steps:\n");
      print_result(cur_state);
      free_state(cur_state);
      break;
    }
    generate_next_states(cur_state, pq, start, goal, h);
    push(cur_state);
  }

  free_pq(pq);
  free_stack();
  free_state(goal);
}

int blocks_world(char *file_name){
  blocks start, goal;
  start = goal = NULL;
  if(!start_goal(&start, &goal, file_name)){
    fprintf(stderr, "Formating error. Can't read start or goal state.\n");
    if(start != NULL) free_state(start);
    if(goal != NULL) free_state(goal);
    return 0;
  }

  printf("Start state:\n");
  print_blocks(start);
  printf("Goal state:\n");
  print_blocks(goal);

  solve(start, goal);

  return 1;
}