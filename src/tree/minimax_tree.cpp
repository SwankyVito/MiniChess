#include <iostream>
#include <sstream>
#include <cstdint>
#include <algorithm>

#include "./minimax_tree.hpp"
#include "../state/state.hpp"
#include "../config.hpp"

/*
void Tree::construct_tree(int depth){
    max_depth = depth;
    int d = 0;
    for(auto move: this->legal_actions){
          State *tmp = this->next_state(move);
          tmp->get_legal_actions();
          tmp->get_legal_State();
          std::pair<int,State> pairing;
          pairing.first = d; pairing.second = *tmp;
          tree[pairing] = tmp->legal_states;
    }
    //暫存減少下次搜尋數
    std::vector<State> prev=this->legal_states;
    std::vector<State> next;
    while(d <= depth){
      d++;
      for(auto node : prev){
        node.get_legal_actions();
        for(auto move : node.legal_actions){
          State *tmp = this->next_state(move);
          tmp->get_legal_actions();
          tmp->get_legal_State();
          std::pair<int,State> pairing;
          pairing.first = d; pairing.second = *tmp;
          tree[pairing] = tmp->legal_states;
          next.push_back(*tmp);
        }
      }
      prev = next;
      next.clear();
    }
}
*/
