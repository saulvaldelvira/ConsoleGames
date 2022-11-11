#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <string>
#include <algorithm>
using std::cout;
using std::endl;
using std::cin;
using std::string;
enum DIFFICULTY {EASY = 25, MEDIUM = 50, HARD = 150, IMPOSIBLE = 99999} difficulty;
const int INVALID_DIFFICULTY = -1;
static int CHANCES;

int wins, losses;

//Clears the cin buffer and ignores everything left
void clearCin(){
    cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//returns true if the given int has only numeric characters
bool isInteger(const std::string &s) {
    if(!s.empty() && std::all_of(s.begin(), s.end(), ::isdigit)){
        try{
            std::stoi(s);
        }catch(std::out_of_range){
            return false;
        }
        return true;
    }
    return false;
}

//reads and integer 
int readInteger(){
    string n;
    bool valid_input = false;

	do {
		cout<<"Choose a number between [0 - " << difficulty << "]: ";
		cin>>n;
        valid_input = cin.good() && isInteger(n);
		if (!(valid_input)) {
			cout << "That input is invalid!\n";
			clearCin();
		}

	} while (!valid_input);
    return std::stoi(n);
}

void setDifficulty(){
    cout<<"First, choose a difficulty\n1)Easy 2)Medium 3)Hard 4)Imposible: ";
    bool flag;
    do{
        char choice;
        flag = false;
        cin >> choice;
        switch (choice)
        {
        case '1':
            difficulty = EASY;
            CHANCES = 3;
            break;
        case '2':
            difficulty = MEDIUM;
            CHANCES = 6;
            break;
        case '3':
            difficulty = HARD;
            CHANCES = 8;
            break;
        case '4':
            difficulty = IMPOSIBLE;
            CHANCES = 20;
            break;
        default:
            cout<<"Invalid choice\nChoose a difficulty\n1)Easy 2)Medium 3)Hard 4)Imposible: ";
            flag=true;
            clearCin();
            break;
        }
    }while(flag);
}

void setup(){
    srand(time(NULL));
    wins = 0;
    losses = 0;
    cout<<"**********************************************************************************" <<endl<<
          "* Welcome, this is a simple guessing game.                                       * " <<endl<<
          "* You have to input a number through the console, and if you miss, the game will *" <<endl<<
          "* give you a hint (higher or lower)                                              *" <<endl<<
          "* That way, your objetive is to guess the number before you run out of chances.  *" <<endl<<
          "**********************************************************************************" <<endl;
    setDifficulty();

    cout<<"\nGood luck!"<<endl<<endl;;
}

bool guess(){
    int number, guess, chances = CHANCES;
    number = rand() % difficulty + 1;
    cout<<"You have " << chances << " chances"<<endl;
    while(chances > 0){
        guess = readInteger();
        chances--;
        cout<< endl;
        if(guess>number)
            cout<<"Lower"<<endl;
        else if(guess<number)
            cout<<"Higher"<<endl;
        else
            return true;
        cout<<chances<<" chances left"<<endl<<endl;;
    }
    return false;
}

void loop(){
    while(1){
        if(guess()){
            cout<<"\nGood job!\n";
            wins++;
        }else{
            cout<<"\nSorry, you ran out of chances\n";
            losses++;
        }
        cout<<"Wanna play again?\n(Y)es (N)o: ";
        char choice;
        cin >> choice;
        cout<<endl;
        if(choice!='Y' && choice != 'y')
            break;
    }
}

void goodbye(){
    cout<<"\n***Final stats***\nWins:   "<<wins<<endl<<"Losses: "<<losses<<endl<<"\nGoodbye!";
}

int main(){
    setup();
    loop();
    goodbye();
}