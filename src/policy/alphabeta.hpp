#pragma once
#include "../state/state.hpp"
#include "./alphabeta_call.hpp"
/*
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Random2{
public:
  static Move get_move(State *state,int depth);
  int max_depth;
  
};