#ifndef __alphabeta_H__
#define __alphabeta_H__
#include "../state/state.hpp"

const int MAX = 1051;
const int MIN = -1051;
class alphabeta{
    public:
    alphabeta(){}
    int do_alphabeta(State *state, int depth, bool maxplayer, int alpha, int beta){
        if(depth == 0 || state->game_state == WIN){
            return state->evaluate();
        }
        if(maxplayer){
            int best = MIN;
            for(auto move: state->legal_actions){
                State *next = state->next_state(move);
                //int val = 0;
                int val = do_alphabeta(next, depth-1, false, alpha, beta);
                best = std::max(best ,val);
                alpha = std::max(alpha ,best);
                if(beta<=alpha)
                    break;
            }
            return best;
        }
        else{
            int best = MAX;
            for(auto move: state->legal_actions){
                State *next = state->next_state(move);
                int val = do_alphabeta(next, depth-1, true, alpha, beta);
                //int val = 0;
                best = std::min(best ,val);
                beta = std::min(beta ,best);
                if(beta<=alpha)
                break;
            }
            return best;
        }
    }

};
#endif