#ifndef TREE_H
#define TREE_H

#include <memory>
#include <string>
#include <iostream>

struct Node{
	std::shared_ptr<Node> yes;
	std::shared_ptr<Node> no;
	std::string input;
	Node(std::string i) : input(i), yes(nullptr), no(nullptr){}
	virtual std::string printInput() = 0;
};
struct Question : public Node{
	Question(std::string question) : Node(question){}
	std::string printInput(){
		return input;
	}
};

struct Answer : public Node{
	Answer(std::string answer) : Node(answer){}
	std::string printInput(){
		return "Are you thinking of a " + input + " (yes or no)? ";
	}
};

class Game{
public:
	void run(){
		std::string userInput;
		bool condition = false;
		bool parentYes = true;
		std::shared_ptr<Node> current;
		std::shared_ptr<Node> parent;
		current = root;

		std::cout << "Okay, I need you to think of something...\n\n";
		while (condition == false){
			std::cout << current->printInput() + " ";
			getline(std::cin, userInput);
			if (userInput == "yes"){
				if (current->yes == nullptr){
				std::cout << "\nI win! Pretty good huh?\n\n";
				condition = true;
				}
				else{
					parentYes = true;
					parent = current;
					current = current->yes;
				}
			}
			else if (userInput == "no"){
				if (current->no == nullptr){
					replace(current, parent, parentYes);
					condition = true;
				}
				else {
					parentYes = false;
					parent = current;
					current = current->no;
				}
			}
			else{
				std::cout << "\n\nInvalid input.\n\n";
			}
		}
	}
void replace(std::shared_ptr<Node> &current, std::shared_ptr<Node> & parent, bool parentYes){
	bool isRoot = false;
	if (current == root){
		isRoot = true;
	}
	std::string whatYouThinking, betterQuestion;
	std::cout << "\n\nYou got me. What were you thinking of? ";
	getline(std::cin, whatYouThinking);
	std::cout << "\n\nWhat question could I have asked to know that you \nwere thinking of "
		+ whatYouThinking + " and not a " + current->input+ "? ";
	getline(std::cin, betterQuestion);

	auto answer = std::make_shared<Answer>(whatYouThinking);
	auto question = std::make_shared<Question>(betterQuestion);
	question->yes = answer;
	question->no = current;
	current = question;

	if (isRoot){
		root = question;
	}
	else if (parentYes){
		parent->yes = question;
	}
	else if (!parentYes){
		parent->no = question;
	}
}
	Game() : root(std::make_shared<Answer>("sword")){}
private:
	std::shared_ptr<Node> root;
};
#endif