#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>

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
	clear();
	for (int i = 0; i < width + 2 ; ++i)
		mvprintw(0, i , "#");
	for (int i = 0; i < height + 2 ; ++i)
		mvprintw(0, i , "#");
	for (int i = 0; i < width + 2 ; ++i)
		mvprintw(height + 1, i , "#");
	for (int i = 0; i < height + 2 ; ++i)
		mvprintw(i , width + 1 ,"#");

	// drawing the snake :)) 
	mvprintw(y, x, "O");
	for (int i = 0; i < nTail ; i++) {
		mvprintw(tailY[i], tailX[i], "o");
	}

	mvprintw(fruitY, fruitX, "F");
	mvprintw(height + 3, 0, "score: %d", score);
	refresh();
}

void Input() {
	keypad(stdscr, TRUE);
	halfdelay(1);
	int c = getch();
	switch (c) {
		case KEY_LEFT:
		  dir = LEFT;
		  break;
		case KEY_RIGHT:
		  dir = RIGHT;
		  break;
		case KEY_UP:
		  dir = UP;
		  break;
		case KEY_DOWN:
		  dir = DOWN;
		  break;
		case 'q':
		  gameOver = true;
		  break;
	}

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
	
		if (x == fruitX && y == fruitY) {
			std::cout << "clicked" << std::endl;
			score += 10;
			fruitX = rand() % width; 
			fruitY = rand() % height; 
			nTail++;
		}
	}
}

int main () {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		usleep(100000);
	}
	endwin();
	return 0;
}

