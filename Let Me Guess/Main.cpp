#include "tree.h"

int main(){
	bool playGame = true;
	bool condition = true;
	std::string playAgain;
	Game game;
	std::cout << "Let's play 20 questions!\n\n";
	while (playGame){
		game.run();
		std::cout << "\nWould you like to play again? (yes or no) ";
		getline(std::cin, playAgain);
		condition = true;
		while (condition){
			if (playAgain == "no"){
				playGame = false;
				condition = false;
			}
			else if (playAgain == "yes"){
				condition = false;
			}
			else {
				std::cout << "\nWould you like to play again? (yes or no) ";
				getline(std::cin, playAgain);
			}
		}
		std::cout << std::endl;
	}
	std::cout << "\nThanks for playing!!\n";
}