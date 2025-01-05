#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;


enum Suit {HEART, SPADE, CLUB, DIAMOND};

class Card{
	public:
		Suit suit;
		int rank;
		
		Card(Suit s, int r)
		{
			suit = s;
			rank = r;
		}
		
	bool isOppositeColor(Card* other)
	{
		bool red = (suit==HEART || suit==DIAMOND);
		bool otherRed = (other->suit==HEART || other->suit==DIAMOND);
		return red!=otherRed;
	}
	
	bool isOneLower(Card* other)
	{
		return rank==other->rank -1;
	}
	
	void Display()
	{
		string symbols[] = {"\u2665", "\u2660", "\u2663", "\u2666"};
		
		cout<<symbols[suit]<<rank<<" ";
	}
};




class List
{
	public:
	class Node
	{
		public:
			Card* card;
			Node* prev;
			Node* next;
			
			
			Node(Card* c)
			{
				card = c;
				prev = nullptr;
				next = nullptr;
			}
	};
	
	Node* head;
	Node* tail;
	
	List()
	{
		head = nullptr;
		tail = nullptr;
	}
	
	
	void append(Card* card)
	{
		Node* newNode = new Node(card);
		if (!head)
		{
			head = tail = newNode;
		} else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}
	
	Node* movesubList(Node* start, int n)
	{
		Node* current = start;
		for (int i=1;i<n && current;i++)
		{
			current = current->next;
		}
		
		if (current)
		{
			if (start->prev)
			{
				start->prev->next = nullptr;
			}
			
			if (current->next)
			{
				current->next->prev = nullptr;
			}
		}
		return current;
	}
	
	

	Card* getTopCard() {
    if (tail != nullptr) {
        return tail->card;  // Return the card at the tail (top card of the column)
    } else {
        throw runtime_error("Error: Tableau column is empty!");  // Throw an error if the list is empty

    }
    
    
}


	void removeTopCard() {
    if (tail != nullptr) {
        Node* toDelete = tail;
        if (tail->prev != nullptr) {
            tail = tail->prev;  // Move the tail back one node
            tail->next = nullptr;  // Disconnect the last node
        } else {
            // If this is the last node, set both head and tail to nullptr
            head = nullptr;
            tail = nullptr;
        }
        delete toDelete;  // Free the memory of the removed node
    } else {
        cout << "Error: Tableau column is already empty!" << endl;
    }
}

	bool isEmpty()
	{
		return head==nullptr;
	}
	
};



class Stack
{
	public:
		class Node
		{
			public:
				Card* card;
				Node* next;
				
				
				Node(Card* c)
				{
					card = c;
					next = nullptr;
				}		
		};
		
		Node* top;
		Stack()
		{
			top = nullptr;
		}
		
		void push(Card* card)
		{
			Node* newNode = new Node(card);
			newNode->next = top;
			top = newNode;
		}
		
		
		Card* pop()
		{
			if (!top)
			{
				return nullptr;
			}
			else
			{
				Node* temp = top;
				Card* card = top->card;
				top = top->next;
				delete temp;
				return card;
			}
		}
		
		Card* peek()
		{
			if (!top)
			{
				return nullptr;
			}
			else{
			
			return top->card;
		}
		}
		
		bool isEmpty()
		{
			return top==nullptr;
		}
};

class Command
{
	public:
		string type;
		string source;
		string destination;
		int numCards;
		
		
		
		Command(string t, string s, string d, int n)
		{
			type = t;
			source = s;
			destination = d;
			numCards = n;
		}
};


class Game
{
	public:
	List tableau[7];
	Stack foundations[4];
	Stack stockpile;
	Stack wastepile;
	Stack commandStack;
	
	std::vector<Card*> deck;
	public:
		Game()
		{
			setupNewGame();
		}
		
		void createDeck()
		{
			for (int suit=0; suit<4;suit++)
			{
				for (int rank=1; rank<=13;rank++)
				{
					deck.push_back(new Card(static_cast<Suit>(suit), rank));
				}
			}
			std::random_shuffle(deck.begin(), deck.end());
		}
		
		void setupNewGame()
		{
			createDeck();
			int cardIndex =0;
			for (int i=0; i<7;i++)
			{
				for (int j=0; j<=i;j++)
				{
					tableau[i].append(deck[cardIndex++]);
				}
			}
			
			for (int i = cardIndex;i<deck.size();i++)
			{
				stockpile.push(deck[i]);
			}
		}
		
		
		void drawCard()
		{
			if (!stockpile.isEmpty())
			{
				//if stockpile is not empty then card is popped from stock and pushed to waste
				Card* card = stockpile.pop();
				wastepile.push(card);
			}
			else
			{
				refillStockpile();
			}
			
		}
		
		void refillStockpile()
		{
			while (!wastepile.isEmpty())
			{
				//if the stock is empty then all cards from waste are pushed into stock
				stockpile.push(wastepile.pop());
			}
		}
		
		
		


	void moveCard(string source, string destination, int num) {
    // Case 1: Move from tableau to tableau
    if (source[0] == 'c' && destination[0] == 'c') {  //source = c1
        int srcIdx = source[1] - '1';  // Get tableau index (0 to 6)
        int destIdx = destination[1] - '1';  // Get destination tableau index

        if (srcIdx >= 0 && srcIdx < 7 && destIdx >= 0 && destIdx < 7) {
            Stack tempStack;
		
            // Move 'num' cards from source tableau to destination tableau
            
            //First card is removed from source and added to tempstack. Later it is removed from tempstack to be added to destination
            for (int i = 0; i < num; i++) {
                if (!tableau[srcIdx].isEmpty()) {
                    tempStack.push(tableau[srcIdx].getTopCard());  // Using the method for doubly linked list to get the top card
                    tableau[srcIdx].removeTopCard();  // Remove the top card from the linked list 
                }
            }

            // Add cards to destination tableau
            while (!tempStack.isEmpty()) {
                tableau[destIdx].append(tempStack.pop());  // Add card to tableau, pop from the stack
            }
        } else {
            cout << "Invalid tableau index!" << endl;
        }
    }
    // Case 2: Move from wastepile to tableau or foundation
    else if (source[0] == 'w') {
        // Wastepile to tableau
        // Checks if destination address includes and calculates the destination index
        if (destination[0] == 'c') {
            int destIdx = destination[1] - '1';
            if (destIdx >= 0 && destIdx < 7 && !wastepile.isEmpty()) {
                tableau[destIdx].append(wastepile.pop());  // Add card to tableau, pop from the wastepile (stack)
            } else {
                cout << "Invalid move to tableau!" << endl;
            }
        } 
        // Wastepile to foundation
        else if (destination[0] == 'f') {
            int destIdx = destination[1] - '1';
            if (destIdx >= 0 && destIdx < 4 && !wastepile.isEmpty()) {
            	//moving card from waste to foundation
                foundations[destIdx].push(wastepile.pop());  // wastepile is popped and pushed into foundations
            } else {
                cout << "Invalid move to foundation!" << endl;
            }
        }
    }
    // Case 3: Move from foundation to tableau
    else if (source[0] == 'f' && destination[0] == 'c') {
        int srcIdx = source[1] - '1';
        int destIdx = destination[1] - '1';
        if (srcIdx >= 0 && srcIdx < 4 && destIdx >= 0 && destIdx < 7) {
            if (!foundations[srcIdx].isEmpty()) {
                tableau[destIdx].append(foundations[srcIdx].pop());  // Move card from foundation (stack) to tableau (list)
            } else {
                cout << "Foundation is empty!" << endl;
            }
        } else {
            cout << "Invalid move from foundation to tableau!" << endl;
        }
    }
}


		
   void processCommand(Command command) {
        if (command.type == "s") {
            drawCard();  //from stock
        } else if (command.type == "m") {
            moveCard(command.source, command.destination, command.numCards);
        } else if (command.type == "z") {
            undoLastCommand();
        }
    }
    
        void displayGame() {
        // Display the game state: tableau, foundations, stockpile, wastepile
        cout << "Foundations: ";
        for (int i = 0; i < 4; i++) {
            if (foundations[i].peek()) foundations[i].peek()->Display();
            else cout << "Empty ";
        }
        cout << endl;

        cout << "Stockpile: ";
        if (!stockpile.isEmpty()) cout << "[Cards Available]";
        else cout << "[Empty]";
        cout << endl;

        cout << "Wastepile: ";
        if (wastepile.peek()) wastepile.peek()->Display();
        else cout << "[Empty]";
        cout << endl;

        cout << "Tableau:" << endl;
        for (int i = 0; i < 7; i++) {
            cout << "Column " << i + 1 << ": ";
            List::Node* current = tableau[i].head;
            while (current) {
                current->card->Display();
                current = current->next;
            }
            cout << endl;
        }
    }

    
    
    bool checkWin()
    {
    	for (int i=0;i<4;i++)
    	{
    		if (foundations[i].peek()==nullptr || foundations[i].peek()->rank!=13)
    		{
    			return false;
			}
			
		}
		return true;
	}
	
	
	Command parseInput(string input)
	{
		string type, source, destination;
		int num = 0;
		
		if (input[0] == 's')
		{
			return Command("s", "", "", 0);
		}
		else if(input[0] == 'm')
		{
			type = "m";
			source = input.substr(2,2);
			destination = input.substr(6,2);
			num = stoi(input.substr(9));      //num = input[9]- '0';
			return Command(type, source, destination, num);
		}
		else if(input[0] == 'z')
		{
			return Command("z", "", "", 0);
		}
		return Command("", "", "", 0);
	}
    
    void start()
    {
    	string input;
    	while (true)
    	{
    		displayGame();
    		cout<<"Enter Command: ";
    		std::getline(std::cin, input);
    		Command cmd = parseInput(input);
    		processCommand(cmd);
    		if (checkWin())
    		{
    			cout<<"You Win"<<endl;
    			break;
			}
		}
	}
    
    void undoLastCommand()
    {
	}
//    void undoLastCommand() {
//    if (commandStack.isEmpty()) {
//        cout << "No moves to undo!" << endl;
//        return;
//    }
//
//    // Pop the last command from the stack
//    Command lastCommand = commandStack.pop();
//
//    if (lastCommand.type == "m") {
//        string source = lastCommand.destination;  // Reverse the source and destination
//        string destination = lastCommand.source;
//        int numCards = lastCommand.numCards;
//
//        // Reverse the move by moving the cards back
//        moveCard(source, destination, numCards);
//
//        cout << "Undo successful: moved cards from " << lastCommand.destination << " back to " << lastCommand.source << endl;
//    }
//    else if (lastCommand.type == "s") {
//        // Reverse a stockpile draw (move from wastepile back to stockpile)
//        if (!wastepile.isEmpty()) {
//            stockpile.push(wastepile.pop());
//            cout << "Undo successful: card returned to stockpile from wastepile." << endl;
//        }
//    }
//    else {
//        cout << "Invalid command for undo!" << endl;
//    }
//}


};


int main()
{
	Game game;
	game.start();
}
