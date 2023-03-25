#include <stdio.h>

#include "blocks.h"

int main(int argc, char **argv){

  if(argc != 2){
    fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
    return 1;
  }

  if(!blocks_world(argv[1]))
    return 1;

  return 0;
}