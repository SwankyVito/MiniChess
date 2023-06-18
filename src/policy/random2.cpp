#include <cstdlib>

#include "../state/state.hpp"
#include "./random2.hpp"
#include "../minimax/minimax.hpp"

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random2::get_move(State *state, int depth){
  if(!state->legal_actions.size()){
    state->get_legal_actions();
    state->get_legal_State();
  }
  auto actions = state->legal_actions;
  Move select = state->legal_actions[1];
  int point = MIN;
  
  for(auto move : state->legal_actions){
    State *next = state->next_state(move);
    minimax *cal = new minimax();
    int tmp = cal->do_minimax(next,1,true,MIN,MAX);
    if( tmp >= point){
      select = move;
      point = tmp;
    }
    
  }
  
  //temporary selections
  return select;
}
