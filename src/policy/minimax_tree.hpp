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
        Tree(){}
        int minimax();
        std::map<std::pair<int,State>,std::vector<State>> tree;
};

#endif