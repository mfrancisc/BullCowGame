//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by francisc munteanu on 28/08/16.
//  Copyright © 2016 francisc munteanu. All rights reserved.
//

#include "FBullCowGame.hpp"

FBullCowGame::FBullCowGame() {
    Reset();
}

void FBullCowGame::Reset(){
    
    const FString HIDDEN_WORD = "donk";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    
    bGameWon = false;
    return;
}



int32 FBullCowGame::GetMaxTries() const
{
    TMap <int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20} };
    
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWorldLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameWon; }
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    // if the guess isn't a isogram return error
    if(!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    
    // if the gues isn't all lowercase return error
    if(!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    
    // if the gess length is worng return error
    if(Guess.length() != GetHiddenWorldLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    
    // otherwise return 0k
    return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    
    MyCurrentTry++;
    
    // setup a return variable
    FBullCowCount BullCowGame;
    
    int32 WordLength = MyHiddenWord.length(); // assume words are same length
    
    // loop through all letters int he guess
    for(int32 i = 0; i < WordLength; i++)
    {
        // compare letters against the gived word
        for(int32 j = 0; j <WordLength; j++)
        {
            if(MyHiddenWord[i] == Guess[j])
            {
                if(j == i) BullCowGame.Bulls++;
                else BullCowGame.Cows++;
            }
        }
    }
    
    // set game won if word is correct
    bGameWon = (Guess == MyHiddenWord);
    
    return BullCowGame;
}

bool FBullCowGame::IsIsogram(FString Guess) const {
    
    TSet <char> DistinctLetters;
    for(int32 i = 0; i < Guess.length(); i++)
    {
        DistinctLetters.insert(Guess[i]);
    }
    
    return DistinctLetters.size() == Guess.length();
}

bool FBullCowGame::IsLowercase(FString Guess) const {
    
    for(auto Letter : Guess)
    {
        if(!std::islower(Letter)) return false;
    }
    
    return true;
}