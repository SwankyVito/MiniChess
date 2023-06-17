#include <cstdlib>

#include "../state/state.hpp"
#include "./random2.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random2::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  State *select = nullptr;
  int target = 0;
  auto actions = state->legal_actions;
  for(int i=0;i<(int)actions.size();i++){
    State *tmp;
    tmp = state->next_state(actions[i%actions.size()]);
    if(tmp->minimax_tree(*tmp,0,true,-1028,1028) > select->minimax_tree(*tmp,0,true,-1028,1028) || !select){
      select = tmp;
      target = i;
      //get the target with largest point
    }
  }
  //temporary selections
  return actions[(target)%actions.size()];
}