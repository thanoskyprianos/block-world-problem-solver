
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "priority_queue.h"

#include "blocks.h"

typedef struct  data_tag block;
struct data_tag{
  char *name; /* strings are used to handle big N */
  char *on;
};

struct block_tag{
  block *data;
  int index; /* used when adding blocks */
};

blocks initialize_state(int size){
  blocks state = malloc(sizeof(struct block_tag));
  state->data = malloc(size * sizeof(block));
  state->index = 0;

  return state;
}

void free_state(blocks state){
  block *arr = state->data;
  for(int i = 0; i < 5; i++){
    free(arr[i].name);
    free(arr[i].on);
  }
  free(arr);
  free(state);
}

void add_block_state(char *name, char *on, blocks state){
  block *arr = state->data;
  
  arr[state->index].name = malloc(strlen(name) + 1);
  arr[state->index].on = malloc(strlen(on) + 1);

  strcpy(arr[state->index].name, name);
  strcpy(arr[state->index].on, on);

  state->index++;
}

int is_on(char *name, char *on, blocks state){
  block *arr = state->data;
  for(int i = 0; i < 5; i++)
    if(strcmp(arr[i].name, name) == 0 && strcmp(arr[i].on, on) == 0)
      return 1;
  return 0;
}

int holds(char *name, blocks state){
  block *arr = state->data;
  for(int i = 0; i < 5; i++)
    if(strcmp(arr[i].on, name) == 0) /* if block is on 'on' field then it always holds */
      return 1;
  return 0;
}

void preety_print(blocks state, char *table){
  block *arr = state->data;
  for(int i = 0; i < state->index; i++){
    if(strcmp(arr[i].on, table) == 0){
      if(strcmp(table, "#") == 0)
        printf("|");
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
}

int start_goal(FILE *fptr, int block_count, blocks start, blocks goal){
  if(!read_state(fptr, block_count, start)) return 0;
  fscanf(fptr, "\n");
  if(!read_state(fptr, block_count, goal)) return 0;
}

int main(){

  FILE *fptr = fopen("input.txt", "r");
  if(fptr == NULL){
    fprintf(stderr, "Input error\n");
    return 1;
  }

  int block_count;
  if(fscanf(fptr, "%d", &block_count) != 1){
    fprintf(stderr, "Formating error. Can't read block count.\n");
    return 1;
  }

  blocks start = initialize_state(block_count);
  blocks goal = initialize_state(block_count);
  if(!start_goal(fptr, block_count, start, goal)){
    fprintf(stderr, "Formating error. Can't read start or goal state.\n");
    free_state(start); free_state(goal);
    return 1;
  }


  printf("Start:\n");
  print_blocks(start);
  printf("Goal:\n");
  print_blocks(goal);

  free_state(start); free_state(goal);

  fclose(fptr);
  return 0;
}