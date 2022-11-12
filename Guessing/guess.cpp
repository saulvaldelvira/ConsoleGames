//I/O
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <stdlib.h> //rand function
#include <time.h> //time function (used to set the rand seed)
#include <limits> //used to clear the cin

//string
#include <string>
using std::string;

#include <algorithm> //used in isInteger to check if all of the string are numeric values

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

//returns wheter the int is in the range
bool isInRange(int n){
    return n>=0 && n<=difficulty;
}

//reads an integer from console. And checks if it is valid (it's an int, and it's in the rang of the game)
int readInteger(int min, int max){
    string n;
    bool valid_input = false;

	do {
		cout<<"Choose a number between [" << min <<" - " <<max << "]: ";
		cin>>n;
        valid_input = cin.good() && isInteger(n) && isInRange(std::stoi(n));
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
            CHANCES = 4;
            break;
        case '2':
            difficulty = MEDIUM;
            CHANCES = 5;
            break;
        case '3':
            difficulty = HARD;
            CHANCES = 5;
            break;
        case '4':
            difficulty = IMPOSIBLE;
            CHANCES = 1;
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
          "* Welcome, this is a simple game in which you'll have to try to guess a number.  *" <<endl<<
          "* To play, you enter a number through the console, and if you miss, you will be  *" <<endl<<
          "* given a hint (higher or lower)                                                 *" <<endl<<
          "* That way, your objective is to guess the number before you run out of chances. *" <<endl<<
          "**********************************************************************************" <<endl;
    setDifficulty();

    cout<<"\nGood luck!"<<endl<<endl;;
}

bool guess(){
    int number, guess, chances = CHANCES, minInter = 0, maxInter = difficulty;
    number = rand() % difficulty + 1;
    cout<<"You have " << chances;
    if(chances==1)
        cout<<" chance "<<endl;
    else
        cout<<" chances "<<endl;
    while(chances > 0){
        guess = readInteger(minInter, maxInter);
        chances--;
        cout<< endl;
        if(guess>number){
            cout<<"Lower"<<endl;
            maxInter = guess;
        }else if(guess<number){
            cout<<"Higher"<<endl;
            minInter = guess;
        }else return true;
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
    cout<<"\n***Final stats***\nWins:   "<<wins<<endl<<"Losses: "<<losses<<endl<<"\nGoodbye!"<<endl;
#ifdef _WIN32
    system("pause");
#elif __linux__
    system("read");
#endif
}

int main(){
    setup();
    loop();
    goodbye();
    return 0;
}