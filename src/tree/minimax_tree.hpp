#ifndef __TREE_H__
#define __TREE_H__
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include <map>
#include "../config.hpp"
#include "../state/state.hpp"

typedef std::pair<int,State> node; 
const int MAX = 1028;
const int MIN = -1028;

class Tree{
    public:
        State init;
        int maxd;
        std::map<node,std::vector<State>> tree;

        Tree(State init,int depth): init(init), maxd(depth){}
        
        int minimax(State s,int depth,bool maximizingPlayer,int alpha,int beta){
            if((s.game_state == WIN) || depth == maxd)
                return s.evaluate();
            node key;
            key.first = depth; key.second = s;
            if(maximizingPlayer){
                int best = MIN;
                for(auto it : tree[key]){
                int val = minimax(it,depth+1,false,alpha,beta);
                best = std::max(best,val);
                alpha= std::max(alpha,best);
                if(beta<=alpha)
                    break;
                }
                return best;
            }
            else{
                int best = MAX;
                for(auto it : tree[key]){
                int val = minimax(it,depth+1,false,alpha,beta);
                best = std::max(best,val);
                beta= std::max(beta,best);
                if(beta<=alpha)
                    break;
                }
                return best;
            }
        }

        int next_id();
        void construct_tree();
};

#endif