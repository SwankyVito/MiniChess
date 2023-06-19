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
const int MAX = 40;
const int MIN = -40;



int State::evaluate2(){
  
  int score = 0;

  if(this->game_state == WIN)
    return MAX;
  if(this->game_state == DRAW)
    return 0;

  int point_table[7] = { 0, 1, 5, 3, 3, 9, 0};
  
  //kinght move table
  int move_x[8] = {1,1,-1,-1,2,2,-2,-2};
  int move_y[8] = {2,-2,2,-2,1,-1,1,-1};

  int atk_play[BOARD_H][BOARD_W],atk_opt[BOARD_H][BOARD_W];
  int gp[BOARD_H][BOARD_W],go[BOARD_H][BOARD_W];

  for(int i=0; i<BOARD_H; i++){
    for(int j=0; j<BOARD_W; j++){
      if(board.board[this->player][i][j]){
        
        //white
        if(!this->player){
          int wp = board.board[this->player][i][j];
          score += point_table[wp];
          switch (wp)
          {
            case 1:
              // move_table_rook_bishop[6][0][1&2] move_table_rook_bishop[7][0][1&2]
              //check where is it
              if(j == 0) { 
                if(point_table[atk_opt[i-1][j+1]] > point_table[wp])
                  atk_play[i-1][j+1] = wp; 
                gp[i-1][j+1]++; 
              }
              else if(j == 4) { 
                if(point_table[atk_play[i-1][j-1]] > point_table[wp])
                  atk_play[i-1][j-1] = wp; 
                gp[i-1][j-1]++; 
              }
              else { 
                atk_play[i-1][j+1] = wp; gp[i-1][j+1]++; 
                atk_play[i-1][j-1] = wp; gp[i-1][j-1]++;
              }
              break;
            case 4:
              //move_table_rook_bishop[4,5,6,7][all][1&2]
              //i 0~6 j 0~4 
              for(int k=-4;k<=4;k++){
                  int i_ = i+k;
                  int j_ = j+k;
                  if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_play[i_][j_]] > point_table[wp])
                      atk_play[i_][j_] = wp;
                    gp[i_][j_]++; 
                  }
              }
              break;
            case 2:
              //move_table_rook_bishop[0,1,2,3][all][1&2]
              for(int k=1;k<=5;k++){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_play[i_][j]] > point_table[wp])
                      atk_play[i_][j] = wp;
                    gp[i_][j]++;
                    int next= board.board[this->player][i_][j];
                    if(next) break; 
                }
                
              }
              for(int k=-1;k>=-5;k--){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_play[i_][j]] > point_table[wp])
                      atk_play[i_][j] = wp;
                    gp[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }    
              }
              for(int k=1;k<=4;k++){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_play[i][j_]] > point_table[wp])
                      atk_play[i][j_] = wp;
                    gp[i][j_]++; 
                  int next= board.board[this->player][i][j_];
                  if(next) break;
                }
              }
              for(int k=-1;k>=-4;k--){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_play[i][j_]] > point_table[wp])
                      atk_play[i][j_] = wp;
                    gp[i][j_]++; 
                  int next= board.board[this->player][i][j_];
                  if(next) break;
                }
                
              }
              break;
            case 5:
              //move_table_rook_bishop all
              //bishop part
              for(int k=-4;k<=4;k++){
                  int i_ = i+k;
                  int j_ = j+k;
                  if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_play[i_][j_]] > point_table[wp])
                      atk_play[i_][j_] = wp;
                    gp[i_][j_]++; 
                  }
              }
              //rook part
              
              for(int k=1;k<=5;k++){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_play[i_][j]] > point_table[wp])
                      atk_play[i_][j] = wp;
                    gp[i_][j]++;
                    int next= board.board[this->player][i_][j];
                    if(next) break; 
                }
                
              }
              for(int k=-1;k>=-5;k--){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_play[i_][j]] > point_table[wp])
                      atk_play[i_][j] = wp;
                    gp[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }    
              }
              for(int k=1;k<=4;k++){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_play[i][j_]] > point_table[wp])
                      atk_play[i][j_] = wp;
                    gp[i][j_]++; 
                  int next= board.board[this->player][i][j_];
                  if(next) break;
                }
              }
              for(int k=-1;k>=-4;k--){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_play[i][j_]] > point_table[wp])
                      atk_play[i][j_] = wp;
                    gp[i][j_]++; 
                  int next= board.board[this->player][i][j_];
                  if(next) break;
                }
                
              }
              break;
            case 3:
              //move_table_knight
              
              for(int k=0;k<8;k++){
                int i_ = i + move_y[k];
                int j_ = j + move_x[k];
                if(i_>=0 && i_<=5 && j_ >=0 && j_<=4){
                  if(point_table[atk_play[i_][j_]] > point_table[wp])
                    atk_play[i_][j_] = wp;
                  gp[i_][j_]++;
                }
              }
              break;
            case 6:
              //move_table_king
              
              break;
            default:
              break;
          }
        }
        
        //black
        else {
          int bp = board.board[this->player][i][j];
          score += point_table[bp];
          switch (bp)
          {
            case 1:
              // move_table_rook_bishop[6][0][1&2] move_table_rook_bishop[7][0][1&2]
              if(j == 0) { 
                if(point_table[atk_play[i+1][j+1]] > point_table[bp])
                  atk_play[i+1][j+1] = bp; 
                gp[i+1][j+1]++; 
              }
              else if(j == 4) { 
                if(point_table[atk_play[i+1][j-1]] > point_table[bp])
                  atk_play[i+1][j-1] = bp; 
                gp[i+1][j-1]++; 
              }
              else { 
                atk_play[i+1][j+1] = bp; gp[i+1][j+1]++; 
                atk_play[i+1][j-1] = bp; gp[i+1][j-1]++;
              }
              break;
            case 4:
              //move_table_rook_bishop[4,5,6,7][all][1&2]
              for(int k=-4;k<=4;k++){
                  int i_ = i+k;
                  int j_ = j+k;
                  if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_play[i_][j_]] > point_table[bp])
                      atk_play[i_][j_] = bp;
                    gp[i_][j_]++; 
                  }
              }
              break;
            case 2:
              for(int k=1;k<=5;k++){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_play[i_][j]] > point_table[bp])
                      atk_play[i_][j] = bp;
                    gp[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }
              }
              for(int k=-1;k>=-5;k--){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_play[i_][j]] > point_table[bp])
                      atk_play[i_][j] = bp;
                    gp[i_][j]++;
                    int next= board.board[this->player][i_][j];
                    if(next) break; 
                }
                
              }
              for(int k=1;k<=4;k++){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_play[i][j_]] > point_table[bp])
                      atk_play[i][j_] = bp;
                    gp[i][j_]++;
                    int next= board.board[this->player][i][j_];
                    if(next) break; 
                }
              }
              for(int k=-1;k>=-4;k--){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_play[i][j_]] > point_table[bp])
                      atk_play[i][j_] = bp;
                    gp[i][j_]++; 
                    int next= board.board[this->player][i][j_];
                    if(next) break;
                }
              }
              //move_table_rook_bishop[0,1,2,3][all][1&2]
              break;
            case 5:
              //move_table_rook_bishop all
              //bishop part
              for(int k=-4;k<=4;k++){
                  int i_ = i+k;
                  int j_ = j+k;
                  if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_play[i_][j_]] > point_table[bp])
                      atk_play[i_][j_] = bp;
                    gp[i_][j_]++; 
                  }
              }

              //rook part
              for(int k=1;k<=5;k++){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_play[i_][j]] > point_table[bp])
                      atk_play[i_][j] = bp;
                    gp[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }
              }
              for(int k=-1;k>=-5;k--){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_play[i_][j]] > point_table[bp])
                      atk_play[i_][j] = bp;
                    gp[i_][j]++;
                    int next= board.board[this->player][i_][j];
                    if(next) break; 
                }
                
              }
              for(int k=1;k<=4;k++){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_play[i][j_]] > point_table[bp])
                      atk_play[i][j_] = bp;
                    gp[i][j_]++;
                    int next= board.board[this->player][i][j_];
                    if(next) break; 
                }
              }
              for(int k=-1;k>=-4;k--){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_play[i][j_]] > point_table[bp])
                      atk_play[i][j_] = bp;
                    gp[i][j_]++; 
                    int next= board.board[this->player][i][j_];
                    if(next) break;
                }
              }
              
              break;
            case 3:
              //move_table_knight
              
              for(int k=0;k<8;k++){
                int i_ = i + move_y[k];
                int j_ = j + move_x[k];
                if(i_>=0 && i_<=5 && j_ >=0 && j_<=4){
                  if(point_table[atk_play[i_][j_]] > point_table[bp])
                    atk_play[i_][j_]  = bp;
                  gp[i_][j_]++;
                }
              }
              break;
            case 6:
              //move_table_king
              break;
            default:
              break;
          }
        }
      }
      if(board.board[1-this->player][i][j]){
        //white
        if(!(1-this->player)){
          int wp = board.board[1-this->player][i][j];
          score -= point_table[wp];
          switch (wp)
          {
            case 1:
              // move_table_rook_bishop[6][0][1&2] move_table_rook_bishop[7][0][1&2]
              if(j == 0) { 
                if(point_table[atk_opt[i-1][j+1]] > point_table[wp])
                  atk_opt[i-1][j+1] = wp; 
                go[i-1][j+1]++; 
              }
              else if(j == 4) { 
                if(point_table[atk_opt[i-1][j-1]] > point_table[wp])
                  atk_opt[i-1][j-1] = wp; 
                go[i-1][j-1]++; 
              }
              else { 
                atk_opt[i-1][j+1] = wp; go[i-1][j+1]++; 
                atk_opt[i-1][j-1] = wp; go[i-1][j-1]++;
              }
              break;
            case 4:
              //move_table_rook_bishop[4,5,6,7][all][1&2]
              for(int k=-4;k<=4;k++){
                  int i_ = i+k;
                  int j_ = j+k;
                  if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_opt[i_][j_]] > point_table[wp])
                      atk_opt[i_][j_] = wp;
                    go[i_][j_]++; 
                  }
              }
              break;
            case 2:
              //move_table_rook_bishop[0,1,2,3][all][1&2]
              for(int k=1;k<=5;k++){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_opt[i_][j]] > point_table[wp])
                      atk_opt[i_][j] = wp;
                    go[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }
              }
              for(int k=-1;k>=-5;k--){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_opt[i_][j]] > point_table[wp])
                      atk_opt[i_][j] = wp;
                    go[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }
              }
              for(int k=1;k<=4;k++){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_opt[i][j_]] > point_table[wp])
                      atk_opt[i][j_] = wp;
                    go[i][j_]++;
                    int next= board.board[this->player][i][j_];
                    if(next) break; 
                }
              }
              for(int k=-1;k>=-4;k--){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_opt[i][j_]] > point_table[wp])
                      atk_opt[i][j_] = wp;
                    go[i][j_]++; 
                    int next= board.board[this->player][i][j_];
                    if(next) break;
                }
              }
              
              break;
            case 5:
              //move_table_rook_bishop all

              //bishop part
              for(int k=-4;k<=4;k++){
                  int i_ = i+k;
                  int j_ = j+k;
                  if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_opt[i_][j_]] > point_table[wp])
                      atk_opt[i_][j_] = wp;
                    go[i_][j_]++; 
                  }
              }

              //rook part
              for(int k=1;k<=5;k++){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_opt[i_][j]] > point_table[wp])
                      atk_opt[i_][j] = wp;
                    go[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }
              }
              for(int k=-1;k>=-5;k--){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_opt[i_][j]] > point_table[wp])
                      atk_opt[i_][j] = wp;
                    go[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }
              }
              for(int k=1;k<=4;k++){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_opt[i][j_]] > point_table[wp])
                      atk_opt[i][j_] = wp;
                    go[i][j_]++;
                    int next= board.board[this->player][i][j_];
                    if(next) break; 
                }
              }
              for(int k=-1;k>=-4;k--){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_opt[i][j_]] > point_table[wp])
                      atk_opt[i][j_] = wp;
                    go[i][j_]++; 
                    int next= board.board[this->player][i][j_];
                    if(next) break;
                }
              }

              break;
            case 3:
              //move_table_knight
              
              for(int k=0;k<8;k++){
                int i_ = i + move_y[k];
                int j_ = j + move_x[k];
                if(i_>=0 && i_<=5 && j_ >=0 && j_<=4){
                  if(point_table[atk_opt[i_][j_]] > point_table[wp])
                      atk_opt[i_][j_] = wp;
                  go[i_][j_]++;
                }
              }
              break;
            case 6:
              //move_table_king
              break;
            default:
              break;
          }
        }

        //black
        else {
          int bp = board.board[1-this->player][i][j];
          score -= point_table[bp];
          switch (bp)
          {
            case 1:
              // move_table_rook_bishop[6][0][1&2] move_table_rook_bishop[7][0][1&2]
              if(j == 0) { 
                if(point_table[atk_opt[i+1][j+1]] > point_table[bp])
                  atk_opt[i+1][j+1] = bp; 
                go[i+1][j+1]++; 
              }
              else if(j == 4) { 
                if(point_table[atk_opt[i+1][j-1]] > point_table[bp])
                  atk_opt[i+1][j-1] = bp; 
                go[i+1][j-1]++; 
              }
              else { 
                atk_opt[i+1][j+1] = bp; go[i+1][j+1]++; 
                atk_opt[i+1][j-1] = bp; go[i+1][j-1]++;
              }
              break;
            case 4:
              //move_table_rook_bishop[4,5,6,7][all][1&2]
              for(int k=-4;k<=4;k++){
                  int i_ = i+k;
                  int j_ = j+k;
                  if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_opt[i_][j_]] > point_table[bp])
                      atk_opt[i_][j_] = bp;
                    go[i_][j_]++; 
                  }
              }
              break;
            case 2:
              //move_table_rook_bishop[0,1,2,3][all][1&2]
              for(int k=1;k<=5;k++){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_opt[i_][j]] > point_table[bp])
                      atk_opt[i_][j] = bp;
                    go[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }
              }
              for(int k=-1;k>=-5;k--){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_opt[i_][j]] > point_table[bp])
                      atk_opt[i_][j] = bp;
                    go[i_][j]++;
                    int next= board.board[this->player][i_][j];
                    if(next) break; 
                }
              }
              for(int k=1;k<=4;k++){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_opt[i][j_]] > point_table[bp])
                      atk_opt[i][j_] = bp;
                    go[i][j_]++; 
                    int next= board.board[this->player][i][j_];
                    if(next) break;
                }
              }
              for(int k=-1;k>=-4;k--){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_opt[i][j_]] > point_table[bp])
                      atk_opt[i][j_] = bp;
                    go[i][j_]++; 
                    int next= board.board[this->player][i][j_];
                    if(next) break;
                }
              }
              
              break;
            case 5:
              //move_table_rook_bishop all
              //bishop part
              for(int k=-4;k<=4;k++){
                  int i_ = i+k;
                  int j_ = j+k;
                  if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_opt[i_][j_]] > point_table[bp])
                      atk_opt[i_][j_] = bp;
                    go[i_][j_]++; 
                  }
              }
              //rook part
              
              for(int k=1;k<=5;k++){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_opt[i_][j]] > point_table[bp])
                      atk_opt[i_][j] = bp;
                    go[i_][j]++; 
                    int next= board.board[this->player][i_][j];
                    if(next) break;
                }
              }
              for(int k=-1;k>=-5;k--){
                int i_ = i+k;
                if(i_>=0 && i_<=5){
                  if(point_table[atk_opt[i_][j]] > point_table[bp])
                      atk_opt[i_][j] = bp;
                    go[i_][j]++;
                    int next= board.board[this->player][i_][j];
                    if(next) break; 
                }
              }
              for(int k=1;k<=4;k++){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_opt[i][j_]] > point_table[bp])
                      atk_opt[i][j_] = bp;
                    go[i][j_]++; 
                    int next= board.board[this->player][i][j_];
                    if(next) break;
                }
              }
              for(int k=-1;k>=-4;k--){
                int j_ = j+k;
                if(j_>=0 && j_<=4){
                  if(point_table[atk_opt[i][j_]] > point_table[bp])
                      atk_opt[i][j_] = bp;
                    go[i][j_]++; 
                    int next= board.board[this->player][i][j_];
                    if(next) break;
                }
              }
              
              break;
            case 3:
              //move_table_knight
              for(int k=0;k<8;k++){
                int i_ = i + move_y[k];
                int j_ = j + move_x[k];
                if(i_>=0 && i_<=5 && j_>=0 && j_<=4){
                    if(point_table[atk_opt[i_][j_]] > point_table[bp])
                      atk_opt[i_][j_] = bp;
                    go[i_][j_]++; 
                }    
              }
              break;
            case 6:
              //move_table_king
              break;
            default:
              break;
          }
        }
      }
    }
  }

  //compare atk_play atk_opt gp go
  int get = 0;
  int lose = 0;
  
  for(int i=0; i<BOARD_H; i++){
    for(int j=0; j<BOARD_W; j++){
      int gain = board.board[1-this->player][i][j];
      int got = board.board[this->player][i][j];
      if(atk_play[i][j] && gain){
        if(atk_opt[i][j]){
          int cal = point_table[gain] - point_table[atk_play[i][j]];
          if(cal<0) continue;
          get = std::max(cal,get);
        }
        else{
          get = std::max(point_table[gain],get);
        }
      }
      if(atk_opt[i][j] && got){
        if(atk_play[i][j]){
          int cal = point_table[got] - point_table[atk_opt[i][j]];
          if(cal<0) continue;
          lose = std::max(cal,lose);
        }
        else{
          lose = std::max(lose,point_table[got]);
        }
      }
    }
  }
  
  //king safty
  /*
  for(int i=0; i<BOARD_H; i++){
    for(int j=0; j<BOARD_W; j++){
      if(board.board[this->player][i][j] == 6 && atk_opt[i][j] == 0){
        score += 20;
      }
      else if(board.board[this->player][i][j] == 6 && atk_opt[i][j] != 0){
        score -= 20;
      }
      else if(board.board[this->player][i][j] == 6){
        if(i == 5 && this->player == 0) score+=10;
        else if(this->player == 0) score -=10;
        if(i == 0 && this->player == 1) score+=10;
        else if(this->player == 1) score -=10;
      }
    }
  }
  */
  score += (get - lose);
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