#include <iostream>
#include <sstream>
#include <cstdint>
#include <algorithm>

#include "./state.hpp"
#include "../config.hpp"

/**
 * @brief evaluate the state
 * 
 * @return int 
 */
const int MAX = 1051;
const int MIN = -1051;
static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};

int State::evaluate() {
    if(this->game_state == WIN) return MIN;
    if(this->game_state == DRAW) return 0;
    //if king being attacked -1000
    int point_table[7] = { 0, 2, 6, 7, 8, 20, 1000 };
    int score = 0;
    for (int i = 0; i < BOARD_H; i ++) {
        for (int j = 0; j < BOARD_W; j ++) {
            int  now = this->board.board[this->player][i][j];
            bool under_attack = false; 
            if (now) score -= point_table[now];
            
            //自己被攻擊 -1000 且對手未被攻擊
            if(now == 6){
              for(int mode = 1;mode<=6;mode++){
                switch (mode){
                    case 1: //pawn
                      //white
                      if(this->player){
                        int i_ = i-1; int j_ =j-1;
                        if(i_<=BOARD_H && i_>=0 && j_<=BOARD_W && j_>=0)
                          if(this->board.board[1-this->player][i_][j_]){
                            score -= point_table[6];
                            under_attack = !under_attack; 
                          }
                        i_ = i-1; j_=j+1;
                        if(i_<=BOARD_H && i_>=0 && j_<=BOARD_W && j_>=0)
                          if(this->board.board[1-this->player][i_][j_]){
                            score += point_table[6];
                            under_attack = !under_attack; 
                          }
                      }
                      //black
                      else{
                        int i_ = i+1; int j_ =j+1;
                        if(i_<=BOARD_H && i_>=0 && j_<=BOARD_W && j_>=0)
                          if(this->board.board[1-this->player][i_][j_] == 1){
                            score -= point_table[6];
                            under_attack = !under_attack; 
                          }
                        i_ = i+1; j_=j-1;
                        if(i_<=BOARD_H && i_>=0 && j_<=BOARD_W && j_>=0)
                          if(this->board.board[1-this->player][i_][j_] == 1){
                            score -= point_table[6];
                            under_attack = !under_attack; 
                          }
                      }
                      break;                    
                    case 2: //rook
                    case 4: //bishop
                    case 5: //queen
                      int st, end;
                      switch (mode){
                        case 2: st=0; end=4; break; //rook
                        case 4: st=4; end=8; break; //bishop
                        case 5: st=0; end=8; break; //queen
                        default: st=0; end=-1;
                      }
                      for(int part=st; part<end; part+=1){
                        auto move_list = move_table_rook_bishop[part];
                        for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                          int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                          if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                          if(this->board.board[1-this->player][p[0]][p[1]] == 2){
                            score -= point_table[6];                        
                            under_attack = !under_attack; 
                          }
                        }
                      }
                      break;
                    
                    case 3: //knight
                      for(auto move: move_table_knight){
                        int x = move[0] + i;
                        int y = move[1] + j;
                        if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
                        if(this->board.board[1-this->player][x][y] == 3){
                          score -= point_table[6]; 
                          under_attack = !under_attack; 
                        }
                      }
                      break;
                }
              }
            }
            

            now = this->board.board[1-this->player][i][j]; 
            if (now)  score += point_table[now];
            if(!under_attack){
              if(now == 6){
              for(int mode = 1;mode<=6;mode++){
                switch (mode){
                    case 1: //pawn
                      //white
                      if(1-this->player){
                        int i_ = i-1; int j_ =j-1;
                        if(i_<=BOARD_H && i_>=0 && j_<=BOARD_W && j_>=0)
                          if(this->board.board[this->player][i_][j_])
                            score += point_table[6];
                        i_ = i-1; j_=j+1;
                        if(i_<=BOARD_H && i_>=0 && j_<=BOARD_W && j_>=0)
                          if(this->board.board[this->player][i_][j_])
                            score += point_table[6];
                      }
                      //black
                      else{
                        int i_ = i+1; int j_ =j+1;
                        if(i_<=BOARD_H && i_>=0 && j_<=BOARD_W && j_>=0)
                          if(this->board.board[this->player][i_][j_] == 1)
                            score += point_table[6];
                        i_ = i+1; j_=j-1;
                        if(i_<=BOARD_H && i_>=0 && j_<=BOARD_W && j_>=0)
                          if(this->board.board[this->player][i_][j_] == 1)
                            score += point_table[6];
                      }
                      break;                    
                    case 2: //rook
                    case 4: //bishop
                    case 5: //queen
                      int st, end;
                      switch (mode){
                        case 2: st=0; end=4; break; //rook
                        case 4: st=4; end=8; break; //bishop
                        case 5: st=0; end=8; break; //queen
                        default: st=0; end=-1;
                      }
                      for(int part=st; part<end; part+=1){
                        auto move_list = move_table_rook_bishop[part];
                        for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                          int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                          if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                          if(this->board.board[this->player][p[0]][p[1]] == 2)
                            score += point_table[6];                        
                        }
                      }
                      break;
                    
                    case 3: //knight
                      for(auto move: move_table_knight){
                        int x = move[0] + i;
                        int y = move[1] + j;
                        if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
                        if(this->board.board[this->player][x][y] == 3)
                            score += point_table[6]; 
                      }
                      break;
                  }
                }
              }
            }
            //對手被攻擊 +1000
        }
    }
    return score;
}

/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;

  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}





/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  this->legal_actions = all_actions;
}

void State::get_legal_State(){
    std::vector<State> all_states;
    for(auto move : legal_actions){
        State *tmp = this->next_state(move);
        all_states.push_back(*tmp);
    }
    legal_states = all_states;
}


const char piece_table[2][7][5] = {
  {" ", "♙ ", "♖ ", "♘ ", "♗ ", "♕ ", "♔ "},
  {" ", "♟ ", "♜ ", "♞ ", "♝ ", "♛ ", "♚ "}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}