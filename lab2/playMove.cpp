//
//  playMove.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"
#include <iostream>

int winCodeCheck(GameState& game_state);

void playMove(GameState& game_state) {
    bool isBoardFull = true;
    int occupied = 0;
    game_state.set_moveValid(true);
    if(game_state.get_gameBoard(game_state.get_selectedRow(),(game_state.get_selectedColumn())) == O || game_state.get_gameBoard(game_state.get_selectedRow(),(game_state.get_selectedColumn())) == X)
    {
        game_state.set_moveValid(false);
        return;
    }
    else{
        if(game_state.get_turn()){
            game_state.set_gameBoard(game_state.get_selectedRow(),game_state.get_selectedColumn(),X);
            game_state.set_turn(false);
        }
        else{
            game_state.set_gameBoard(game_state.get_selectedRow(),game_state.get_selectedColumn(),O);
            game_state.set_turn(true);
        }
    }
    winCodeCheck(game_state);
    if(winCodeCheck(game_state)!= 0){
        game_state.set_gameOver(true);
        return;
    }
    
    for (int i = 0; i < boardSize; i++)
    {
       for (int j = 0; j < boardSize; j++)
       {
           if(game_state.get_gameBoard(game_state.get_selectedRow(),game_state.get_selectedColumn()) == Empty){
               isBoardFull = false;
           }
       }
    }
    
    if(isBoardFull == false){
        game_state.set_gameOver(true);
        return;
    }
    // for (int i = 0; i < boardSize; i++)
    // {
    //    for (int j = 0; j < boardSize; j++)
    //    {
    //        if(game_state.get_gameBoard(i,j) == X || game_state.get_gameBoard(i,j) == O){
    //            occupied++;
    //        }
    //    }
    // }
    // if(occupied ==9){
    //     game_state.set_gameOver(true);
    //     return;
    // }

}




int winCodeCheck(GameState& game_state){
    int row1=0,col1=0,row2=0,col2=0,row3=0,col3=0,row4=0,col4=0,row5=0,col5=0,row6=0,col6=0,row7=0,col7=0,row8=0,col8=0;
    for(int i=0;i<boardSize;i++){
        if(game_state.get_gameBoard(0,i) == X){
            row1++;
        }
        if(game_state.get_gameBoard(0,i) == O){
            col1++;
        }
        if(row1==3 || col1==3){
                game_state.set_winCode(1);
        }
    }

    for(int i=0;i<boardSize;i++){
        if(game_state.get_gameBoard(1,i) == X){
            row2++;
        }
        if(game_state.get_gameBoard(1,i) == O){
            col2++;
        }
        if(row2==3 || col2==3 ){
            game_state.set_winCode(2);   
        }
    }

    for(int i=0;i<boardSize;i++){
        if(game_state.get_gameBoard(2,i) == X){
            row3++;
        }
        if(game_state.get_gameBoard(2,i) == O){
            col3++;
        }
        if(row3==3 || col3==3){
            game_state.set_winCode(3);
        }
    }

    for(int i=0;i<boardSize;i++){
        if(game_state.get_gameBoard(i,0) == X){
            row4++;
        }
        if(game_state.get_gameBoard(i,0) == O){
            col4++;
        }
        if(row4==3 || col4==3 ){
            game_state.set_winCode(4);
        }
    }

    for(int i=0;i<boardSize;i++){
        if(game_state.get_gameBoard(i,1) == X){
            row5++;
        }
        if(game_state.get_gameBoard(i,1) == O){
            col5++;
        }
        if(row5==3 || col5==3 ){
            game_state.set_winCode(5);
        }
    }

    for(int i=0;i<boardSize;i++){
        
        if(game_state.get_gameBoard(i,2) == X){
            row6++;
        }
        if(game_state.get_gameBoard(i,2) == O){
            col6++;
        }
        if(row6==3 || col6==3 ){
            game_state.set_winCode(6);
        }
    }

    for(int i=0;i<boardSize;i++){
        if(game_state.get_gameBoard(i,i) == X){
            row7++;
        }
        if(game_state.get_gameBoard(i,i) == O){
            col7++;
        }
        if(row7==3 || col7==3 ){
                game_state.set_winCode(7);
            
        }
    }

    for(int i=0;i<boardSize;i++){
        if(game_state.get_gameBoard(2-i,i) == X){
            row8++;
        }
        if(game_state.get_gameBoard(2-i,i) == O){
            col8++;
        }
        if(row8==3 || col8==3){
            game_state.set_winCode(8);
        }
    }

    
    return game_state.get_winCode();
}