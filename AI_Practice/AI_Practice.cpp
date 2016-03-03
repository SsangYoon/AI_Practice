// AI_Practice.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#define MAX_STACK_SIZE		2048

// Maze Row, Column
#define MAZE_ROW		12
#define MAZE_COL		15

// Exit Point
#define EXIT_ROW		MAZE_ROW
#define EXIT_COL		MAZE_COL

// Offset struct
struct Offset
{
	int vertical;		// Vertical
	int horizontal;		// Horizontal
};

// Element struct
struct Element
{
	int row;		// Row
	int col;		// Column
	int dir;		// Direction
};

// Maze array
int maze[MAZE_ROW + 2][MAZE_COL + 2] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1,
	1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

// 8 Directions
Offset	Move[8];

int Mark[MAZE_ROW + 2][MAZE_COL + 2] = { 0, };

Element Stack[MAX_STACK_SIZE];
int StackTop;


// Stack Function
void AddElement(int* top, Element* element);
Element* DeleteElement(int* top);

// Direction
void Path();

// Draw Maze
void DrawMaze();

// Main
int _tmain(int argc, _TCHAR* argv[])
{
	// Direction Initialize
	Move[0].vertical = -1; Move[0].horizontal = 0;		// North
	Move[1].vertical = -1; Move[1].horizontal = 1;		// North
	Move[2].vertical = 0; Move[2].horizontal = 1;		// North
	Move[3].vertical = 1; Move[3].horizontal = 1;		// North
	Move[4].vertical = 1; Move[4].horizontal = 0;		// North
	Move[5].vertical = 1; Move[5].horizontal = -1;		// North
	Move[6].vertical = 0; Move[6].horizontal = -1;		// North
	Move[7].vertical = -1; Move[7].horizontal = -1;		// North

	StackTop = -1;

	Path();

	return 0;
}

void AddElement(int* top, Element* element)
{
	if (*top >= MAX_STACK_SIZE - 1)
	{
		printf("Stack is FULL\n");
		exit(1);
	}
	memcpy(&Stack[++*top], element, sizeof(Element));
}

Element* DeleteElement(int* top)
{
	if (*top == -1)
	{
		printf("Stack is Empty\n");
		exit(1);
	}
	return &Stack[(*top)--];
}

void Path()
{
	int row, col;				// row, col
	int next_row, next_col;		// Next row,col
	int dir;					// Direction
	bool isFound = false;		// is Found

	Element position;			// Position

	Mark[1][1] = 1;
	StackTop = 0;
	Stack[0].row = 1;
	Stack[0].col = 1;
	Stack[0].dir = 2;

	while (StackTop > -1 && !isFound)
	{
		memcpy(&position, DeleteElement(&StackTop), sizeof(Element));
		row = position.row;
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !isFound)
		{
			next_row = row + Move[dir].vertical;
			next_col = col + Move[dir].horizontal;

			if (next_row == EXIT_ROW && next_col == EXIT_COL)
			{
				position.row = row;
				position.col = col;
				position.dir = dir;

				AddElement(&StackTop, &position);

				isFound = true;
			}
			else if (!maze[next_row][next_col] && !Mark[next_row][next_col])
			{
				Mark[next_row][next_col] = 1;
				
				position.row = row;
				position.col = col;
				position.dir = dir;

				AddElement(&StackTop, &position);

				row = next_row;
				col = next_col;
				dir = 0;
			}
			else
				dir++;
		}
	}

	if (isFound)
	{
		DrawMaze();
		printf("The Path is : \n");

		for (int i = 0; i <= StackTop; i++)
		{
			printf("(%2d,%2d)->", Stack[i].row, Stack[i].col);
		}
		printf("(%2d,%2d)\n", EXIT_ROW, EXIT_COL);
	}
	else
	{
		printf("The Maze Does Not Have A Path");
	}

	return;
}

void DrawMaze()
{
	for (int i = 0; i <= StackTop; i++)
	{
		maze[Stack[i].row][Stack[i].col] = Stack[i].dir + 10;
	}
	
	maze[EXIT_ROW][EXIT_COL] = 99;

	for (int i = 0; i < MAZE_ROW + 2; i++)
	{
		for (int j = 0; j < MAZE_COL + 2; j++)
		{
			switch (maze[i][j])
			{
			case 0:
				printf("□");
				break;

			case 1:
				printf("■");
				break;

			case 10:
				printf("↑");    
				break;

			case 11:
				printf("↗");
				break;

			case 12:
				printf("→");
				break;

			case 13:
				printf("↘"); 
				break;

			case 14:
				printf("↓");
				break;

			case 15:
				printf("↙");		   
				break;

			case 16:
				printf("←");
				break;

			case 17:
				printf("↖");
				break;

			case 99:
				printf("♣");
				break;
			}
		}
		printf("\n");
	}
	getchar();
}