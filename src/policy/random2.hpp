#pragma once
#include "../state/state.hpp"

const int MAX = 1028;
const int MIN = -1028;
/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Random2{
public:
  static Move get_move(State *state, int depth);
  int max_depth;
  int minimax(State state, int depth, bool maxplayer, int alpha, int beta){
    if(depth == max_depth || state.game_state == WIN){
      return state.evaluate();
    }
    if(maxplayer){
      int best = MIN;
      for(auto move: state.legal_actions){
        State next = *(state.next_state(move));
        int val = minimax(next, depth+1, false, alpha, beta);
        best = std::max(best ,val);
        alpha = std::max(alpha ,best);
        if(beta<=alpha)
          break;
      }

      return best;
    }
    else{
      int best = MAX;
      for(auto move: state.legal_actions){
        State next = *(state.next_state(move));
        int val = minimax(next, depth+1, true, alpha, beta);
        best = std::min(best ,val);
        beta = std::min(beta ,best);
        if(beta<=alpha)
          break;
      }
      return best;
    }
  }
};