/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all 
users interation. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSubmmary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// the entry point for the application
int main() 
{
	
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0; // exit the application
}



void PrintIntro() 
{ 
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of. \n";
	std::cout << std::endl;
	return;
}

// plays a single game to completion 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	int bcount = 0;
	while (!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
		bcount++;
	}
	PrintGameSubmmary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "TRY " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << " Enter your guess: ";
		std::getline(std::cin, Guess);

		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) 
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letter. \n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please Enter a lower case \n\n";
			break;

		case EGuessStatus::Wrong_Length:
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letters.\n\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get valid input 
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSubmmary()
{
	if (BCGame.isGameWon()) 
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else 
	{
		std::cout << "BETTER LUCK NEXT TIME!\n";
	}
	return;
}
