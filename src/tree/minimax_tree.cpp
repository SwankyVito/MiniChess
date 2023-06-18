#include <iostream>
#include <sstream>
#include <cstdint>
#include <algorithm>

#include "./minimax_tree.hpp"
#include "../state/state.hpp"
#include "../config.hpp"

void Tree::construct_tree(){
    int d = 0;
    init.get_legal_actions();
    init.get_legal_State();
    node init_;
    init_.first = 0; init_.second = init;
    tree[init_] = init.legal_states;
    //暫存減少下次搜尋數
    while(d <= maxd){
      for(const auto&[key , val] : tree){
          if(key.first == d){
            for(auto state: val){
              state.get_legal_actions();
              state.get_legal_State();
              node pairing;
              pairing.first = d+1; pairing.second = state;
              tree[pairing] = state.legal_states;
            }
          }
        }
        d++;
    }
}



int Tree::next_id(){
  
}

