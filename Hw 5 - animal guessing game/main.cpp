//  Hw 5 - animal guessing game
//  Safa Mohammed
//  4/9/22.
//  Purpose: This program creates a 20 questions style animal guessing game from the ground up. It learns which questions to ask based on user input and which animals to guess.
//  Special features: Uses pointers, binary trees, and structures
//  Change log: 4/9/2022 - added ability to create the first 2 branches from the root ie the yes or no nodes for each previous node
//              4/10/2022 - added ability to create multiple branches using a while loop, created a new function for asking questions


#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

struct AnimalNode{
    string question;
    string guess;
    AnimalNode *yesAnswer;
    AnimalNode *noAnswer;
};

void createTree (AnimalNode *curNode) {
    string rightAnimal;
    string questionToUse;
    string answerToQuestion;
    
    getline(cin, rightAnimal);
    cout << "Bummer! What animal were you thinking of?" << endl;
    getline(cin, rightAnimal);
    
    // create two new nodes, one for the yes node and one for the no node
    AnimalNode *noNode = new AnimalNode();
    AnimalNode *yesNode = new AnimalNode();
    
    curNode->noAnswer = noNode;
    curNode->yesAnswer = yesNode;
    
    cout << "What is a yes/no question that I can use to tell a " << curNode->guess << " from a " << rightAnimal << "?" << endl;
    //int t = 0;
    getline(cin, questionToUse);
    
    curNode->question = questionToUse;
    
    
    cout << "For a " << rightAnimal << ", is the answer yes or no?" << endl;
    cin >> answerToQuestion;
    
    // based on user's response, decide which side the actual guess will go and which side the previous guess will go
    if (answerToQuestion == "y" || answerToQuestion == "yes") {
        yesNode->guess = rightAnimal;
        noNode->guess = curNode->guess;
        curNode->guess = "";
        
    }
    else if (answerToQuestion == "n" || answerToQuestion == "no") {
        noNode->guess = rightAnimal;
        yesNode->guess = curNode->guess;
        curNode->guess = "";
    }
    
}

AnimalNode *askQuestion (AnimalNode *ptr) {
    string userAnswer;
    // ask the question inside the node
    cout << ptr->question << endl;
    cin >> userAnswer;
    
    if (userAnswer == "y" || userAnswer == "yes") {
        ptr = ptr->yesAnswer;
        
    }
    else if (userAnswer == "n" || userAnswer == "no") {
        ptr = ptr->noAnswer;
    }
    // return address of the next node based on the user's response
    return ptr;
}


int main() {
    
    AnimalNode *root;
    root = nullptr;
    
    // create the first node which will be the root
    AnimalNode *rootNode = new AnimalNode();
    
    //initialize the first node with a guess
    rootNode->question = "";
    rootNode->guess = "lizard";
    rootNode->yesAnswer = nullptr;
    rootNode->noAnswer = nullptr;
    
    // store the address of the first node
    root = rootNode;
    
    cout << "Let's play the Guess the Animal game." << endl;
    cout << "Think of an animal and hit return when you’re ready." << endl;
    cin.get();
    
    string correct;
    
    cout << "Is it a(an) " << rootNode->guess << " ?" << endl;
    cin >> correct;
    
    string rightAnimal;
    string questionToUse;
    string answerToQuestion;
    
    string playAgain = "y";
    
    // check if the initial guess was correct
    if (correct == "n" || correct == "no") {
        // create the new branches
        createTree(rootNode);
        
        cout << "Try again?" << endl;
        cin >> playAgain;
    }
    else if (correct == "y" || correct == "yes") {
        cout << "you won!" << endl;
        cout << "Try again?" << endl;
        cin >> playAgain;
    }
        
    // create a new placeholder and initialize to null
    AnimalNode *ptr = nullptr;
    
    // continue playing the game as long as the user wants to
    while (playAgain != "n") {
        ptr = root; // start from the first node
        
        while (ptr != nullptr) {
            //check if the current node is a guess nide or question node
            if (ptr->guess == "") {
               ptr = askQuestion(ptr);
            }
            else if (ptr->question == "") {
                // make a guess
                cout << "Is your animal " << ptr->guess << endl;
                cin >> correct;
                // if guess is incorrect, create new branches
                if (correct == "n" || correct == "no") {
                    createTree(ptr);
                    
                    cout << "Try again?" << endl;
                    cin >> playAgain;
                    
                    ptr = nullptr;
                }
                
                else if (correct == "y" || correct == "yes") {
                    cout << "you won!" << endl;
                    cout << "Try again?" << endl;
                    cin >> playAgain;
                    ptr = ptr->yesAnswer; // should be null because it is a guess node
                }
            }
        }
    }
    
    return 0;
}
