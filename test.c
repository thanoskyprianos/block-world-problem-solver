#include "../../acutest/acutest.h"
#include "blocks.h"
#include "stack.h"

void test_copy_state(void){
  blocks dest = initialize_state(3, NULL);
  blocks src = initialize_state(3, NULL);
  add_block_state("a", "#", src);
  add_block_state("b", "a", src);
  add_block_state("c", "b", src);

  copy_state(&dest, src);

  TEST_CHECK(is_on("a", "#", dest) && is_on("b", "a", dest) && is_on("c", "b", dest));

  free_state(dest); free_state(src);
}

void test_is_on(void){
  blocks state = initialize_state(3, NULL);
  add_block_state("a", "#", state);
  add_block_state("b", "a", state);
  add_block_state("c", "b", state);

  TEST_CHECK(is_on("b", "a", state) && is_on("c", "b", state) && is_on("a", "#", state));

  free_state(state);
}

void test_holds(void){
  blocks state = initialize_state(3, NULL);
  add_block_state("a", "#", state);
  add_block_state("b", "a", state);
  add_block_state("c", "b", state);

  TEST_CHECK(holds("a", state) && holds("b", state) && !holds("c", state));

  free_state(state);
}

void test_set_on_at(void){
  blocks state = initialize_state(3, NULL);
  add_block_state("a", "#", state);
  add_block_state("b", "a", state);
  add_block_state("c", "b", state);

  set_on_at("#", 2, state);

  TEST_CHECK(is_on("b", "a", state) && is_on("c", "#", state) && is_on("a", "#", state));

  free_state(state);
}

TEST_LIST = {
  {"copy_state", test_copy_state},
  {"is_on", test_is_on},
  {"holds", test_holds},
  {"set_on_at", test_set_on_at},
  {NULL, NULL}
};