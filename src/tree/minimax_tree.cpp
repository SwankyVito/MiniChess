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


int Tree::minimax(State s,int depth,bool maximizingPlayer,int alpha,int beta){
  if(depth = maxd)
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

int Tree::next_id(){
  
}

