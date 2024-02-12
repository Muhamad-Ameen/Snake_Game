#include <iostream>
#include <conio.h>
using namespace std;

bool gameover;
const int width = 30;
const int length = 30;
int x, y, pointX, pointY, score;
int tailX[100], tailY[100];
int Ntail;
enum direction { stop = 0, LEFT, RIGHT, up, down };
direction dir;


void setup()
{
	gameover = false;
	dir = stop;
	x = width / 2;
	y = length / 2;
	pointX = rand() % width;
	pointY = rand() % length;
	score = 0;
};


void draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x) // head
				cout << "O";
			else if (i == pointY && j == pointX) // points
				cout << "$";
			else
			{
				bool print = false;
				for (int k = 0;k < Ntail;k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}

				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:- " << score << endl;
};


void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = up;
			break;
		case 's':
			dir = down;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
};
void logic()
{
	int lastX = tailX[0];
	int lastY = tailY[0];
	int last2X, last2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1;i < Ntail;i++)
	{
		last2X = tailX[i];
		last2Y = tailY[i];
		tailX[i] = lastX;
		tailY[i] = lastY;
		lastX = last2X;
		lastY = last2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case up:
		y--;
		break;
	case down:
		y++;
		break;
	}
	if (x > width || x < 0 || y > length || y < 0)
		gameover = true;

	for (int i = 1;i < Ntail;i++)
		if (tailX[i] == x && tailY[i] == y)
			gameover = true;

	if (x == pointX && y == pointY)

	{
		score += 10;
		pointX = rand() % width;
		pointY = rand() % length;
		Ntail++;
	}
};

int main()
{
	while (!gameover)
	{
		draw();
		input();
		logic();
		//Sleep(10);
	};
}