// flip7-strategy-engine.cpp : Defines the entry point for the application.
//

#include "flip7-strategy-engine.h"
#include <random>

using namespace std;

int main()
{
	cout << "--- Flip7 Simulator Prototype ---" << endl;

	// Random engine
	random_device rd;
	mt19937 gen(rd());

	// Initial weights for each card type

	int newDeck[13] = { 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }; // Weights for cards 0-12
	
	// Initialize card weights from newDeck
	int cardWeights[13]; 
	for (int i = 0; i < 13; ++i) {
		cardWeights[i] = newDeck[i];
	}

	int points { 0 };
	int playerGoal { 15 };
	bool isTurnActive { true };
	bool possessesDuplicate { false };

	int playerCards[13] = { 0 }; // Initialize player card counts to 0

	cout << "--- Playing a round ---" << std::endl;
	while (isTurnActive) {
		// Create a discrete distribution based on the current weights
		discrete_distribution<int> cardDistribution(cardWeights, cardWeights + 13); // why is the same as vector begin and end?

		// Generate a card based on the distribution
		int card = cardDistribution(gen);
		cout << "Generated card: " << card << std::endl;

		// Update the distribution weights based on the generated card
		cardWeights[card]--; // Decrease the weight of the generated card

		if (playerCards[card] > 0) {
			possessesDuplicate = true;
			cout << "Bust! Drawn duplicate card " << card << ". Score reset to 0." << std::endl;
			points = 0;
			isTurnActive = false;
			possessesDuplicate = true;
		}
		else {
			playerCards[card]++;
			points += card; // Assuming the card value is equal to its index, change later
			if (points < playerGoal) {				
				cout << "Current points: " << points << std::endl;
			}
			else {
				cout << "Congratulations! You've reached the goal of " << playerGoal << " points!" << std::endl;
				isTurnActive = false;
			}
		}
	}



	return 0;
}
