#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"
#include "./minimax_call.hpp"

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random3::get_move(State *state ,int depth){
  if(!state->legal_actions.size()){
    state->get_legal_actions();
    state->get_legal_State();
  }
  auto actions = state->legal_actions;
  Move select;
  int point = 0;
  int flag = 0;
  for(auto move : state->legal_actions){
    State *next = state->next_state(move);
    minimax *cal = new minimax();
    int tmp = cal->do_minimax(next,depth,true);
    if(!flag) { select = move; flag = 1;}
    if( tmp >= point){
      select = move;
      point = tmp;
    }
  }

  //temporary selections
  return select;
}
