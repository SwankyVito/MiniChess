#pragma once
#include "../state/state.hpp"
#include "./minimax_call.hpp"
/*
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Random3{
public:
  static Move get_move(State *state,int depth);
  int max_depth;
};