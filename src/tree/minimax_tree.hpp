#ifndef __TREE_H__
#define __TREE_H__
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include <map>
#include "../config.hpp"
#include "../state/state.hpp"

class Tree{
    public:
        Tree(State init,int depth): init(init), maxd(depth){}
        int minimax();
        State init;
        int maxd;
        std::map<std::pair<int,State>,std::vector<State>> tree;
};

#endif