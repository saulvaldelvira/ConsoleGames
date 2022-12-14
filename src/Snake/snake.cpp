#include <iostream>
#include <Windows.h>
#include <list>
#include <thread>
using std::list;
using std::chrono::system_clock;
using namespace std::chrono_literals;
int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 30;	        // Console Screen Size Y (rows)

const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

struct sSnakeSegment{
    int x, y;
};

int main(){
    // Create Screen Buffer
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

    while(1){
    list<sSnakeSegment> snake = {{60, 15}, {61, 15}, {62, 15}, {63, 15}, {64, 15}, {65, 15}, {66, 15}, {67, 15}, {68, 15}, {69, 15}};
    int nFoodX = 30,
        nFoodY = 15,
        nScore = 0,
        nSnakeDirection = 3;
    bool bDead = false;

    bool bKeyLeft = false,
         bKeyRight = false,
         bKeyUp = false, 
         bKeyDown = false,
         bKeyLeftOld = false,
         bKeyRightOld = false,
         bKeyUpOld = false,
         bKeyDownOld = false;

    srand(time(NULL));

    while(!bDead){

        // Timing & input
            //Get Input
        auto t1 = system_clock::now();
        while((system_clock::now() - t1) < (nSnakeDirection % 2 == 1 ? 120ms : 200ms)){
            bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)(VK_RIGHT))) != 0;
            bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)(VK_LEFT))) != 0;
            bKeyUp = (0x8000 & GetAsyncKeyState((unsigned char)(VK_UP))) != 0;
            bKeyDown = (0x8000 & GetAsyncKeyState((unsigned char)(VK_DOWN))) != 0;

            //optimizar quitar if
            if(bKeyRight && !bKeyRightOld){
                if(nSnakeDirection!=LEFT)
                    nSnakeDirection = RIGHT;
            }

            if(bKeyLeft && !bKeyLeftOld){
                if(nSnakeDirection!=RIGHT)
                    nSnakeDirection = LEFT;
            }

            if(bKeyUp && !bKeyUpOld){
                if(nSnakeDirection != DOWN)
                    nSnakeDirection = UP;
            }

            if(bKeyDown && !bKeyDownOld){
                if(nSnakeDirection != UP)
                    nSnakeDirection = DOWN;
            }

            bKeyLeftOld = bKeyLeft;
            bKeyRightOld = bKeyRight;
            bKeyUpOld = bKeyUp;
            bKeyDownOld = bKeyDown;
        }
        
    // Game Logic

        //Update Snake Position
        switch(nSnakeDirection){
        case UP:
            snake.push_front({snake.front().x, snake.front().y - 1});
            break;
        case RIGHT:
            snake.push_front({snake.front().x + 1, snake.front().y});
            break;
        case DOWN:
            snake.push_front({snake.front().x, snake.front().y + 1});
            break;
        case LEFT:
            snake.push_front({snake.front().x - 1, snake.front().y});
            break;
        }

    //Collision Detection
        
        //Snake - Food
        if(snake.front().x == nFoodX && snake.front().y == nFoodY){
            nScore += 30;
            while(screen[nFoodY * nScreenWidth + nFoodX] != L' '){
                nFoodX = rand() % nScreenWidth;
                nFoodY = (rand() % (nScreenHeight - 3)) + 3;
            }

            for(int i=0; i<5; i++)
                snake.push_back({snake.back().x, snake.back().y});
        }

        //Snake - World
        if(snake.front().x < 0 || snake.front().x >= nScreenWidth ||
           snake.front().y < 3 || snake.front().y >= nScreenHeight )
                bDead = true;

        //Snake - Snake
        /*for(list<sSnakeSegment>::iterator i = snake.begin(); i!=snake.end(); i++)
            bDead = i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y;*/

        for (list<sSnakeSegment>::iterator i = snake.begin(); i != snake.end(); i++)
				if (i != snake.begin() && i->x == snake.front().x && i->y == snake.front().y)
					bDead = true;

        //Chop off snakes tail
        snake.pop_back();

    // Display to Player

        //Clear Screen
        for(int i=0; i< nScreenHeight*nScreenWidth; i++)
            screen[i] = L' ';

        //Draw stats and border
        for(int i=0; i<nScreenWidth; i++){
            screen[i] = L'=';
            screen[2 * nScreenWidth + i] = L'=';
        }
        wsprintf(&screen[nScreenWidth + 46], L" S N A K E - SCORE: %d", nScore);

        //Draw Snake
        for(auto s : snake)
            screen[s.y * nScreenWidth + s.x] = bDead ? L'+' : L'O';

        //Draw Snake head
        screen[snake.front().y * nScreenWidth + snake.front().x] = bDead ? L'X' : L'@';

        //Draw Food
        screen[nFoodY * nScreenWidth + nFoodX] = L'%';

        if(bDead)
            wsprintf(&screen[15 * nScreenWidth + 40], L"    PRESS 'SPACE' TO PLAY AGAIN");

            //Display Frame
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }
        while((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
    }	
}