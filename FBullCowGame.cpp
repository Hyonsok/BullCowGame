#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

int32 FBullCowGame::GetMaxTries() const
{
	// {Word length, Max Tries}
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10},{6,16},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];

}


void FBullCowGame::Reset()
{

	const FString HIDDEN_WORD = "plane"; // this MUST be the isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// receives a VALID guess, increments turn, and return counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar) // if they are in the same place
				{  
					BullCowCount.Bulls++; // increment bulls
				}
				else // if they are not
				{ 
					BullCowCount.Cows++; //  increment cows
				}       
			}
				
		}
	}
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::isIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)	  // for all letters of tthe word
	{	
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false;	// we do NOT have an isogram 
		}
		else 
		{
			// add the letter to the map as seen
			LetterSeen[Letter] = true;
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::isLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter))  // if not a lowercase letter
		{
			return false;
		}
		return true;

	}
}


// default constructor
FBullCowGame::FBullCowGame()
{
	Reset();
}


int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
	return bGameIsWon;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!isIsogram(Guess)) //	if the guess is not an isogram
	{  
		return EGuessStatus::Not_Isogram;
	}
	else if (!isLowercase(Guess)) //  if the guess is not all lowercase 
	{ 
		return EGuessStatus::Not_Lowercase;  
	}
	else if (Guess.length() != GetHiddenWordLength())  //	if the guess length is wrong,
	{ 
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
}
