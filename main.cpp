//
//  main.cpp
//  BullCowGame
//
//  Created by francisc munteanu on 28/08/16.
//  Copyright © 2016 francisc munteanu. All rights reserved.
//
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "FBullCowGame.hpp"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();
FText GetGuess();

FBullCowGame BCGame;

int main() {
    
    PrintIntro();
    
    do{
        PlayGame();
    }while(AskToPlayAgain());
    
    return 0;
}

// introduce the game
void PrintIntro(){
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n\n";
    
    std::ifstream t("/Users/francisc/projects/Unreal/Section_02/BullCowGame/BullCowGame/asciiart.in");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::cout << buffer.str() << std::endl;
    
    std::cout << "Can you guess the " << BCGame.GetHiddenWorldLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

void PrintGameSummary()
{
    std::cout << std::endl;
    if(BCGame.IsGameWon()) std::cout << " YOU WON!" << std::endl;
    else std::cout << "BAD LUCK!" << std::endl;
}

// get a guess from the player, loop till valid guess
FText GetValidGuess(){
    
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    
    do {
        
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << " . ";
        std::cout << "Enter your guess: ";
        getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWorldLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter lowercase word.\n\n";
                break;
                
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
                
            default:
                break;
        }
        
    } while(Status != EGuessStatus::OK);
    
    return Guess;
}

void PlayGame(){
    
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    // loop asking for guesses while the game
    // is NOT won and there are still tries remaining
    while( ! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        FText Guess = GetValidGuess(); // TODO make loop checking valid
        
        
        // submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        // print number of bulls and cows
        
        std::cout << " Bulls: " << BullCowCount.Bulls << std::endl;
        std::cout << " Cows: " << BullCowCount.Cows << std::endl;
    }
    
    // summarise game
    PrintGameSummary();
    return;
}

bool AskToPlayAgain(){
    std::cout << std::endl;
    std::cout << "Do you want to play again with the same hidden word (y/n)?\n";
    FText Response = "";
    getline(std::cin, Response);
    
    return (Response[0] == 'y') || (Response[0] == 'Y');
}