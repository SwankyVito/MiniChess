#ifndef __MINIMAX_H__
#define __MINIMAX_H__
#include "../state/state.hpp"

const int MAX = 1028;
const int MIN = -1028;
class minimax{
    public:
    minimax(){}
    int do_minimax(State *state, int depth, bool maxplayer, int alpha, int beta){
        
        if(depth == 3 || state->game_state == WIN){
            return state->evaluate();
        }
        if(maxplayer){
            int best = MIN;
            for(auto move: state->legal_actions){
                State *next = state->next_state(move);
                //int val = 0;
                int val = do_minimax(next, depth+1, false, alpha, beta);
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
                int val = do_minimax(next, depth+1, true, alpha, beta);
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