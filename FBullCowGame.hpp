//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by francisc munteanu on 28/08/16.
//  Copyright © 2016 francisc munteanu. All rights reserved.
//
#pragma once
#include <string>
#include <set>
#include <map>
#include <algorithm>
#define TSet std::set
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EWordStatus
{
    OK,
    No_Hidden_Word
};

enum class EGuessStatus
{
    Invalid_Status,
    Not_Isogram,
    OK,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); // constructor
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWorldLength() const;
    
    EGuessStatus CheckGuessValidity(FString) const;
    
    bool IsGameWon() const;
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;

    void Reset();
    
    FBullCowCount SubmitValidGuess(FString);
    
private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameWon;
};