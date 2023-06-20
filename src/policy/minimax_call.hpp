#ifndef __minimax_H__
#define __minimax_H__
#include "../state/state.hpp"

const int MAX = 1051;
const int MIN = -1051;
class minimax{
    public:
    minimax(){}
    int do_minimax(State *state, int depth, bool maxplayer){
        if(depth == 0 || state->game_state == WIN){
            return state->evaluate();
        }
        if(maxplayer){
            int val = MIN;
            for(auto move: state->legal_actions){
                State *next = state->next_state(move);
                val = std::max(val,do_minimax(next, depth-1, false));
            }
            return val;
        }
        else{
            int val = MAX;
            for(auto move: state->legal_actions){
                State *next = state->next_state(move);
                val = std::min(val,do_minimax(next, depth-1, true));
            }
            return val;
        }
    }

};
#endif