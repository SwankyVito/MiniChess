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

class Tree{
    public:
        State init;
        int maxd;
        std::map<node,std::vector<node>> tree;

        Tree(State init,int depth): init(init), maxd(depth){}
        
        int minimax();
        void construct_tree();
};

#endif