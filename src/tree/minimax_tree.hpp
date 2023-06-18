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
        
        int minimax(State s, int depth,bool maximizingPlayer,int alpha,int beta);
        int next_id();
        void construct_tree();
};

#endif