#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup () {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = width / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("clear");
	for (int i = 0; i < width + 2; ++i) 
		std::cout << "#";
	std::cout << std::endl; 
	

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (j == 0) {
				std::cout << "#";
			}
			if (i == y && j == x) 
				std::cout << "O";
			else if (i == fruitY && j == fruitX) 
				std::cout << "F";
			else {
				bool print = false;
				for (int k =0; k < nTail ; ++k) {
					if (tailX[k] == j && tailY[k] == i) {
						std::cout << "o";
						print = true;
					}
				}
				if (!print) {
					std::cout << " ";
				}
			}
			if (j == width -1) {
				std::cout << "#";
			} 	
		}
		std::cout << std::endl;
	}
	
	for (int i = 0; i < width + 2; ++i) {
		std::cout << "#";
	}
	std::cout << std::endl;
	std::cout << "Score: " << score << std::endl;

}

void Input () {
    struct termios oldt, newt;
    char ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch == 'a')
        dir = LEFT;
    else if (ch == 'd')
        dir = RIGHT;
    else if (ch == 'w')
        dir = UP;
    else if (ch == 's')
        dir = DOWN;
    else if (ch == 'q')
        gameOver = true;
	  else if (ch == 'p')
			  dir = STOP;
}

void Logic() {
	int prevY = tailY[0];
	int prevX = tailX[0];
	int prevX2, prevY2;
	tailX[0] = x;
	tailY[0] = y;
	
	for (int i = 1; i < nTail; ++i) {
		prevX2 = tailX[i];
		prevY2 = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prevX2;
		prevY = prevY2;
	}

	switch (dir) {
	case LEFT:
		--x;
		break;
	case RIGHT:
		++x;
		break;
	case UP:
		--y;
		break;
	case DOWN:
		++y;
		break;
	default:
		break;
	}
	
	if (x >= width) x = 0; else if (x < 0) x = width - 1; 
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	
	for (int i = 0; i < nTail ; ++i) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width; 
		fruitY = rand() % height; 
		nTail++;
	}
}

int main (void) {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		usleep(100000);
	}
	return 0;
}

